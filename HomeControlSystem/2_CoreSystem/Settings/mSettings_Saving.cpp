
#include "2_CoreSystem/Settings/mSettings.h"



void mSettings::SettingsSaveAll(void)
{
  Serial.println("SettingsSaveAll");
  // if (Settings.flag_system.save_state) {
  //   Settings.power = power;
  // } else {
  //   Settings.power = 0;
  // }
  pCONT->Tasker_Interface(FUNC_SETTINGS_SAVE_VALUES_FROM_MODULE);
#ifdef USE_EEPROM
  EepromCommit();
#endif
  SettingsSave(0);
}

// /*********************************************************************************************\
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
//  * Config Save - Save parameters to Flash ONLY if any parameter has changed
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/
// \*********************************************************************************************/

// #ifdef ENABLE_DEVFEATURE_SETTINGS_V2

void mSettings::SettingsLoad(void) {
  
  #ifdef ENABLE_LOG_LEVEL_INFO
  AddLog(LOG_LEVEL_DEBUG_MORE,PSTR(D_LOG_MEMORY D_LOAD));
  #endif// ENABLE_LOG_LEVEL_INFO

#ifdef ESP8266
  // Load configuration from eeprom or one of 7 slots below if first valid load does not stop_flash_rotate
  // Activated with version 8.4.0.2 - Fails to read any config before version 6.6.0.11
  settings_location = 0;
  uint32_t save_flag = 0;
  uint32_t flash_location = SETTINGS_LOCATION;
  for (uint32_t i = 0; i < CFG_ROTATES; i++) {              // Read all config pages in search of valid and latest
    ESP.flashRead(flash_location * SPI_FLASH_SEC_SIZE, (uint32*)&Settings, sizeof(Settings));
    
    #ifdef ENABLE_LOG_LEVEL_INFO
    AddLog(LOG_LEVEL_DEBUG,PSTR(D_LOG_MEMORY D_LOAD " i=%d bootcount=%d version=%X"),i,Settings.bootcount,Settings.version);
    #endif // ENABLE_LOG_LEVEL_INFO

    if ((Settings.cfg_crc32 != 0xFFFFFFFF) && (Settings.cfg_crc32 != 0x00000000) && (Settings.cfg_crc32 == GetSettingsCrc32())) {
      
    #ifdef ENABLE_LOG_LEVEL_INFO
    AddLog(LOG_LEVEL_DEBUG,PSTR(D_LOG_MEMORY D_LOAD " cfg_crc==GetSettingsCrc32()| %d==%d"),Settings.cfg_crc32,GetSettingsCrc32());
    #endif // ENABLE_LOG_LEVEL_INFO
      
      if (Settings.save_flag > save_flag) {                 // Find latest page based on incrementing save_flag
    #ifdef ENABLE_LOG_LEVEL_INFO
      AddLog(LOG_LEVEL_DEBUG,PSTR(D_LOG_MEMORY D_LOAD " Settings.save_flag > save_flag %d>%d"),Settings.save_flag,save_flag);
    #endif // ENABLE_LOG_LEVEL_INFO
     
        save_flag = Settings.save_flag;
        settings_location = flash_location;
        if (Settings.flag_system.stop_flash_rotate && (0 == i)) {  // Stop if only eeprom area should be used and it is valid
    #ifdef ENABLE_LOG_LEVEL_INFO
      AddLog(LOG_LEVEL_DEBUG,PSTR(D_LOG_MEMORY D_LOAD " Settings.flag_system.stop_flash_rotate && (0 == i)"));
    #endif // ENABLE_LOG_LEVEL_INFO
          break;
        }
      }
    }
    flash_location--;
    delay(1);
  }
  if (settings_location > 0) {
    ESP.flashRead(settings_location * SPI_FLASH_SEC_SIZE, (uint32*)&Settings, sizeof(Settings));
    #ifdef ENABLE_LOG_LEVEL_INFO
    AddLog(LOG_LEVEL_TEST, PSTR(D_LOG_CONFIG D_LOADED_FROM_FLASH_AT " %X, " D_COUNT " %lu " D_JSON_BOOTCOUNT " %d"), settings_location, Settings.save_flag, Settings.bootcount);
    #endif // ENABLE_LOG_LEVEL_INFO
  }
// #else  // ESP32
//   SettingsRead(&Settings, sizeof(Settings));
//   AddLog_P2(LOG_LEVEL_NONE, PSTR(D_LOG_CONFIG "Loaded, " D_COUNT " %lu"), Settings.save_flag);
// #endif  // ESP8266 - ESP32

#ifndef FIRMWARE_MINIMAL
  if ((0 == settings_location) || (Settings.cfg_holder != (uint16_t)SETTINGS_HOLDER)) {  // Init defaults if cfg_holder differs from user settings in my_user_config.h
    //Settings.seriallog_level = LOG_LEVEL_ALL;
    pCONT_set->Settings.seriallog_level = pCONT_set->seriallog_level_during_boot;
    
    #ifdef ENABLE_LOG_LEVEL_INFO
    AddLog(LOG_LEVEL_TEST,PSTR(D_LOG_MEMORY "cfg_holder(%d) != SETTINGS_HOLDER(%d), Erasing"),Settings.cfg_holder,SETTINGS_HOLDER);
    #endif // ENABLE_LOG_LEVEL_INFO

    SettingsDefault();
  }else{
    #ifdef ENABLE_LOG_LEVEL_INFO
    AddLog(LOG_LEVEL_TEST,PSTR(D_LOG_MEMORY D_LOAD " " D_JSON_SUCCESSFUL ));
    #endif // ENABLE_LOG_LEVEL_INFO
  }
  settings_crc32 = GetSettingsCrc32();
#endif  // FIRMWARE_MINIMAL

  RtcSettingsLoad();

  #endif //  ESP8266
}


uint16_t mSettings::GetCfgCrc16(uint8_t *bytes, uint32_t size)
{
  uint16_t crc = 0;

  for (uint32_t i = 0; i < size; i++) {
    if ((i < 14) || (i > 15)) { crc += bytes[i]*(i+1); }  // Skip crc
  }
  return crc;
}

uint16_t mSettings::GetSettingsCrc(void)
{
  // Fix miscalculation if previous Settings was 3584 and current Settings is 4096 between 0x06060007 and 0x0606000A
  uint32_t size = /*((Settings.version < 0x06060007) || (Settings.version > 0x0606000A)) ? 3584 :*/ sizeof(Settings);
  return GetCfgCrc16((uint8_t*)&Settings, size);
}

uint32_t mSettings::GetCfgCrc32(uint8_t *bytes, uint32_t size)
{
  // https://create.stephan-brumme.com/crc32/#bitwise
  uint32_t crc = 0;

  while (size--) {
    crc ^= *bytes++;
    for (uint32_t j = 0; j < 8; j++) {
      crc = (crc >> 1) ^ (-int(crc & 1) & 0xEDB88320);
    }
  }
  return ~crc;
}

uint32_t mSettings::GetSettingsCrc32(void)
{
  return GetCfgCrc32((uint8_t*)&Settings, sizeof(Settings) -4);  // Skip crc32
}



void mSettings::SettingsSave(uint8_t rotate)
{

Serial.println("SettingsSave NOT return");
//   return;
  
    #ifdef ESP8266
/* Save configuration in eeprom or one of 7 slots below
 *
 * rotate 0 = Save in next flash slot
 * rotate 1 = Save only in eeprom flash slot until SetOption12 0 or restart
 * rotate 2 = Save in eeprom flash slot, erase next flash slots and continue depending on stop_flash_rotate
 * stop_flash_rotate 0 = Allow flash slot rotation (SetOption12 0)
 * stop_flash_rotate 1 = Allow only eeprom flash slot use (SetOption12 1)
 */
// #ifndef FIRMWARE_MINIMAL
  // UpdateBackwardCompatibility();
  if ((GetSettingsCrc32() != settings_crc32) || rotate) {
     if (1 == rotate) {   // Use eeprom flash slot only and disable flash rotate from now on (upgrade)
      stop_flash_rotate = 1;
    #ifdef ENABLE_LOG_LEVEL_INFO
      AddLog(LOG_LEVEL_DEBUG_MORE,PSTR(D_LOG_MEMORY D_SAVE " stop_flash_rotate"));//(upgrade) Use eeprom flash slot only and disable flash rotate from now on"));
    #endif// ENABLE_LOG_LEVEL_INFO
    }
    if (2 == rotate) {   // Use eeprom flash slot and erase next flash slots if stop_flash_rotate is off (default)
      settings_location = SETTINGS_LOCATION +1;
    // #ifdef ENABLE_LOG_LEVEL_INFO
    //   AddLog(LOG_LEVEL_DEBUG_MORE,PSTR(D_LOG_MEMORY D_SAVE " (default) Use eeprom flash slot and erase next flash slots if stop_flash_rotate is off(%d) (default)"),stop_flash_rotate);
    // #endif// ENABLE_LOG_LEVEL_INFO
    }
    if (stop_flash_rotate) {
      settings_location = SETTINGS_LOCATION;
    } else {
      settings_location--;
    #ifdef ENABLE_LOG_LEVEL_INFO
      AddLog(LOG_LEVEL_DEBUG_MORE,PSTR(D_LOG_MEMORY D_SAVE " settings_location=%d"),settings_location);
    #endif// ENABLE_LOG_LEVEL_INFO
      if (settings_location <= (SETTINGS_LOCATION - CFG_ROTATES)) {
        settings_location = SETTINGS_LOCATION;
    #ifdef ENABLE_LOG_LEVEL_INFO
      AddLog(LOG_LEVEL_TEST,PSTR("settings_location <= (SETTINGS_LOCATION - CFG_ROTATES)"));
    #endif // ENABLE_LOG_LEVEL_INFO
      }
    }

    Settings.save_flag++;
    // if (UtcTime() > START_VALID_TIME) {
    //   Settings.cfg_timestamp = UtcTime();
    // } else {
    //   Settings.cfg_timestamp++;
    // }
    Settings.cfg_size = sizeof(Settings);
    Settings.cfg_crc = GetSettingsCrc();  // Keep for backward compatibility in case of fall-back just after upgrade
    Settings.cfg_crc32 = GetSettingsCrc32();

// #ifdef ESP8266
    if (ESP.flashEraseSector(settings_location)) {
      ESP.flashWrite(settings_location * SPI_FLASH_SEC_SIZE, (uint32*)&Settings, sizeof(Settings));
    }

    if (!stop_flash_rotate && rotate) {
      for (uint32_t i = 1; i < CFG_ROTATES; i++) {
        ESP.flashEraseSector(settings_location -i);  // Delete previous configurations by resetting to 0xFF
        delay(1);
      }
    }
    #ifdef ENABLE_LOG_LEVEL_INFO
    AddLog(LOG_LEVEL_DEBUG, PSTR(D_LOG_CONFIG D_SAVED_TO_FLASH_AT " %X, " D_COUNT " %d, " D_BYTES " %d"), settings_location, Settings.save_flag, sizeof(Settings));
    #endif// ENABLE_LOG_LEVEL_INFO
// #else  // ESP32
//     SettingsWrite(&Settings, sizeof(Settings));
//     AddLog_P2(LOG_LEVEL_DEBUG, PSTR(D_LOG_CONFIG "Saved, " D_COUNT " %d, " D_BYTES " %d"), Settings.save_flag, sizeof(Settings));
// #endif  // ESP8266

    settings_crc32 = Settings.cfg_crc32;
  }
// #endif  // FIRMWARE_MINIMAL
  RtcSettingsSave();
  #endif //  ESP8266
}



// #else // ENABLE_DEVFEATURE_SETTINGS_V2


// void mSettings::SettingsLoad(void)
// {
//   AddLog(LOG_LEVEL_TEST,PSTR(D_LOG_MEMORY D_LOAD));

//   // Load configuration from eeprom or one of 7 slots below if first valid load does not stop_flash_rotate
//   struct SYSCFGH {
//     uint16_t cfg_holder;                     // 000
//     uint16_t cfg_size;                       // 002
//     unsigned long save_flag;                 // 004
//   } _SettingsH;
//   unsigned long save_flag = 0;

//   Settings.flag_system.stop_flash_rotate = 1;// temp measure

//   settings_location = 0;
//   uint32_t flash_location = SETTINGS_LOCATION +1; //next memory location

//   uint16_t cfg_holder = 0;

  
//   for (uint8_t i = 0; i < CFG_ROTATES; i++) {
//     flash_location--;
//     ESP.flashRead(flash_location * SPI_FLASH_SEC_SIZE, (uint32*)&Settings, sizeof(SYSCFG));

//     AddLog(LOG_LEVEL_TEST,PSTR(D_LOG_MEMORY D_LOAD " i=%d bootcount=%d version=%X"),i,Settings.bootcount,Settings.version);

//     // if(Settings.version != 0xFFFFFFFF){
//     //   AddLog(LOG_LEVEL_TEST,PSTR("i=%d version=%X DOES NOT EQUAL tversion=%X"),i,Settings.version,0xFFFFFFFF);
//     // }else{
//     //   AddLog(LOG_LEVEL_TEST,PSTR("ELSE ELSE i=%d version=%X tversion=%X"),i,Settings.version,0xFFFFFFFF);
//     //   //break;// test
//     // }

//     bool valid = false;
//     if((Settings.version > 0x06000000)&&(Settings.version != 0xFFFFFFFF)) {
//       //AddLog(LOG_LEVEL_TEST,PSTR("ESP.flashRead %i IF"),i);
//       bool almost_valid = (Settings.cfg_crc == GetSettingsCrc());
//       AddLog(LOG_LEVEL_TEST,PSTR(D_LOG_MEMORY D_LOAD " cfg_crc==GetSettingsCrc()| %d==%d"),Settings.cfg_crc,GetSettingsCrc());
//       // Sometimes CRC on pages below FB, overwritten by OTA, is fine but Settings are still invalid. So check cfg_holder too
//       if (almost_valid && (0 == cfg_holder)) { cfg_holder = Settings.cfg_holder; }  // At FB always active cfg_holder
//       valid = (cfg_holder == Settings.cfg_holder);
//     } else {


//       ESP.flashRead((flash_location -1) * SPI_FLASH_SEC_SIZE, (uint32*)&_SettingsH, sizeof(SYSCFGH));
//       valid = (Settings.cfg_holder == _SettingsH.cfg_holder);
//       if(Settings.cfg_holder == 65535){
//         // catch when memory is all 1's and not 0
//         valid = false;
//       }
//       AddLog(LOG_LEVEL_TEST,PSTR("flashRead ELSE %d %d %d"),valid,Settings.cfg_holder,_SettingsH.cfg_holder);
//     }
//     AddLog(LOG_LEVEL_TEST,PSTR(D_LOG_MEMORY D_LOAD " ESP.flashRead valid=%d"),valid);
//     if (valid) {
//       AddLog(LOG_LEVEL_TEST,PSTR(D_LOG_MEMORY D_LOAD " Settings.save_flag > save_flag %d>%d"),Settings.save_flag,save_flag);
//       if (Settings.save_flag > save_flag) {
//         save_flag = Settings.save_flag;
//         settings_location = flash_location;
//         if (Settings.flag_system.stop_flash_rotate && (0 == i)) {  // Stop only if eeprom area should be used and it is valid
//           break;
//         }
//       }
//     }

//     delay(1);
//   }

// /*
// #else  // CFG_RESILIENT
//   // Activated with version 8.4.0.2 - Fails to read any config before version 6.6.0.11
//   settings_location = 0;
//   uint32_t save_flag = 0;
//   uint32_t flash_location = SETTINGS_LOCATION;
//   for (uint32_t i = 0; i < CFG_ROTATES; i++) {              // Read all config pages in search of valid and latest
//     ESP.flashRead(flash_location * SPI_FLASH_SEC_SIZE, (uint32*)&Settings, sizeof(Settings));
//     if ((Settings.cfg_crc32 != 0xFFFFFFFF) && (Settings.cfg_crc32 != 0x00000000) && (Settings.cfg_crc32 == GetSettingsCrc32())) {
//       if (Settings.save_flag > save_flag) {                 // Find latest page based on incrementing save_flag
//         save_flag = Settings.save_flag;
//         settings_location = flash_location;
//         if (Settings.flag.stop_flash_rotate && (0 == i)) {  // Stop if only eeprom area should be used and it is valid
//           break;
//         }
//       }
//     }
//     flash_location--;
//     delay(1);
//   }
//   */
  
//   if (settings_location > 0) {
//     ESP.flashRead(settings_location * SPI_FLASH_SEC_SIZE, (uint32*)&Settings, sizeof(SYSCFG));
//     AddLog(LOG_LEVEL_TEST,PSTR(D_LOG_MEMORY D_LOAD D_LOADED_FROM_FLASH_AT " %X, " D_COUNT " %lu" D_BOOT_COUNT " %d"), settings_location, Settings.save_flag, Settings.bootcount);
//   }
//   // else{    
//   //   AddLog(LOG_LEVEL_TEST,PSTR(D_LOG_MEMORY D_LOAD " %s>%d"), "settings_location",settings_location);
//   // }

//   #ifndef FIRMWARE_MINIMAL
//   if (!settings_location || (Settings.cfg_holder != (uint16_t)SETTINGS_HOLDER)) {  // Init defaults if cfg_holder differs from user settings in .h
//     //Settings.seriallog_level = LOG_LEVEL_ALL;
//     pCONT_set->Settings.seriallog_level = pCONT_set->seriallog_level_during_boot;
    
//     AddLog(LOG_LEVEL_TEST,PSTR(D_LOG_MEMORY D_LOAD "cfg_holder(%d) != SETTINGS_HOLDER(%d), Erasing settings"),Settings.cfg_holder,SETTINGS_HOLDER);

//     // Clear system defaults
//     SettingsDefault();

//   }
//   settings_crc = GetSettingsCrc();
//   #endif  // FIRMWARE_MINIMAL

//   RtcSettingsLoad();
  
// }


// // uint16_t mSettings::GetSettingsCrc(void)
// // {
// //   uint16_t crc = 0;
// //   uint8_t *bytes = (uint8_t*)&Settings;

// //   for (uint16_t i = 0; i < sizeof(SYSCFG); i++) {
// //     if ((i < 14) || (i > 15)) { crc += bytes[i]*(i+1); }  // Skip crc
// //   }
// //   return crc;
// // }


// void mSettings::SettingsSave(uint8_t rotate)
// { 

  

// // return ;
// // #endif

//   // Serial.print("SettingsSave> ");Serial.println(rotate);
//   /* Save configuration in eeprom or one of 7 slots below
//  *
//  * rotate 0 = Save in next flash slot
//  * rotate 1 = Save only in eeprom flash slot until SetOption12 0 or restart
//  * rotate 2 = Save in eeprom flash slot, erase next flash slots and continue depending on stop_flash_rotate
//  * stop_flash_rotate 0 = Allow flash slot rotation (SetOption12 0)
//  * stop_flash_rotate 1 = Allow only eeprom flash slot use (SetOption12 1)
//  */
// //DEBUG_LINE_HERE;
// // #ifndef FIRMWARE_MINIMAL
//   if ((GetSettingsCrc() != settings_crc) || rotate) {
// //DEBUG_LINE_HERE;
//     if (1 == rotate) {   // Use eeprom flash slot only and disable flash rotate from now on (upgrade)
//       stop_flash_rotate = 1;
//       //AddLog(LOG_LEVEL_DEBUG_MORE,PSTR(D_LOG_MEMORY D_SAVE " stop_flash_rotate"));//(upgrade) Use eeprom flash slot only and disable flash rotate from now on"));
//     }
//     if (2 == rotate) {   // Use eeprom flash slot and erase next flash slots if stop_flash_rotate is off (default)
//       settings_location = SETTINGS_LOCATION +1;
//       //AddLog(LOG_LEVEL_DEBUG_MORE,PSTR(D_LOG_MEMORY D_SAVE " (default) Use eeprom flash slot and erase next flash slots if stop_flash_rotate is off(%d) (default)"),stop_flash_rotate);
//     }
//     if (stop_flash_rotate) {
//       settings_location = SETTINGS_LOCATION;
//     } else {
//       settings_location--;
//       //AddLog(LOG_LEVEL_DEBUG_MORE,PSTR(D_LOG_MEMORY D_SAVE " settings_location=%d"),settings_location);
//       if (settings_location <= (SETTINGS_LOCATION - CFG_ROTATES)) {
//         settings_location = SETTINGS_LOCATION;
//       //AddLog(LOG_LEVEL_TEST,PSTR("settings_location <= (SETTINGS_LOCATION - CFG_ROTATES)"));
//       }
//     }
//     Settings.save_flag++;
//     Settings.cfg_size = sizeof(SYSCFG);
//     Settings.cfg_crc = GetSettingsCrc();

// //DEBUG_LINE_HERE;
// // #ifdef USE_EEPROM
// //     if (SPIFFS_END == settings_location) {
// //       uint8_t* flash_buffer;
// //       flash_buffer = new uint8_t[SPI_FLASH_SEC_SIZE];
// //       if (eeprom_data && eeprom_size) {
// //         size_t flash_offset = SPI_FLASH_SEC_SIZE - eeprom_size;
// //         memcpy(flash_buffer + flash_offset, eeprom_data, eeprom_size);  // Write dirty EEPROM data
// //       } else {
// //         ESP.flashRead(settings_location * SPI_FLASH_SEC_SIZE, (uint32*)flash_buffer, SPI_FLASH_SEC_SIZE);   // Read EEPROM area
// //       }
// //       memcpy(flash_buffer, &Settings, sizeof(Settings));
// //       ESP.flashEraseSector(settings_location);
// //       ESP.flashWrite(settings_location * SPI_FLASH_SEC_SIZE, (uint32*)flash_buffer, SPI_FLASH_SEC_SIZE);
// //       delete[] flash_buffer;
// //     } else {
// //       ESP.flashEraseSector(settings_location);
// //       ESP.flashWrite(settings_location * SPI_FLASH_SEC_SIZE, (uint32*)&Settings, sizeof(SYSCFG));
// //     }
// // #else

// // ESP.wdtFeed();
// // ESP.wdtDisable();
// //DEBUG_LINE_HERE;
//     // settings_location = SETTINGS_LOCATION;
// //     AddLog(LOG_LEVEL_DEBUG_MORE,PSTR(D_LOG_MEMORY D_SAVE " settings_location <= (SETTINGS_LOCATION - CFG_ROTATES) %lu"),settings_location);

// // AddLog(LOG_LEVEL_DEBUG,PSTR(D_LOG_MEMORY D_SAVE " ENTERING UNSAFE AREA %d"),settings_location);

// // Serial.flush();
// // delay(1000);

// //DEBUG_LINE_HERE;

// #ifdef ENABLE_FLASH_ERASE_SECTOR_CURRENTLY_BUG
//   if (ESP.flashEraseSector(settings_location)) {
//     ESP.flashWrite(settings_location * SPI_FLASH_SEC_SIZE, (uint32*)&Settings, sizeof(Settings));
//   }
// #endif

// // AddLog(LOG_LEVEL_DEBUG,PSTR(D_LOG_MEMORY D_SAVE " LEAVING UNSAFE AREA %d"),settings_location);
// // ESP.wdtFeed();
// // delay(1000);

//     // ESP.flashEraseSector(settings_location);
// // //DEBUG_LINE_HERE;
// //     ESP.flashWrite(settings_location * SPI_FLASH_SEC_SIZE, (uint32*)&Settings, sizeof(SYSCFG));
// //DEBUG_LINE_HERE;
// // #endif  // USE_EEPROM

//     if (!stop_flash_rotate && rotate) {
//       for (uint8_t i = 1; i < CFG_ROTATES; i++) {
// //DEBUG_LINE_HERE;
//         ESP.flashEraseSector(settings_location -i);  // Delete previous configurations by resetting to 0xFF
//         delay(1);
//       }
//     }

//     AddLog(LOG_LEVEL_DEBUG_MORE,PSTR(D_LOG_MEMORY D_SAVE D_LOG_CONFIG D_SAVED_TO_FLASH_AT " %X, " D_COUNT " %d, " D_BYTES " %d"), settings_location, Settings.save_flag, sizeof(SYSCFG));

//     settings_crc = Settings.cfg_crc;
//   }
// // #endif  // FIRMWARE_MINIMAL
// //DEBUG_LINE_HERE;
//   RtcSettingsSave();

// }



// #endif // ENABLE_DEVFEATURE_SETTINGS_V2



uint32_t mSettings::GetSettingsAddress(void)
{
  #ifdef ESP8266
  return settings_location * SPI_FLASH_SEC_SIZE;
  #else
  return 0;
  #endif
}

void mSettings::SettingsErase(uint8_t type)
{
  /*
    0 = Erase from program end until end of physical flash
    1 = Erase SDK parameter area at end of linker memory model (0x0FDxxx - 0x0FFFFF) solving possible wifi errors
  */

#ifndef FIRMWARE_MINIMAL
  bool result;

  uint32_t _sectorStart = (ESP.getSketchSize() / SPI_FLASH_SEC_SIZE) + 1;
  uint32_t _sectorEnd = ESP.getFlashChipRealSize() / SPI_FLASH_SEC_SIZE;
  if (1 == type) {
    _sectorStart = SETTINGS_LOCATION +2;  // SDK parameter area above EEPROM area (0x0FDxxx - 0x0FFFFF)
    _sectorEnd = SETTINGS_LOCATION +5;
  }

  bool _serialoutput = (LOG_LEVEL_DEBUG_MORE <= seriallog_level);

    #ifdef ENABLE_LOG_LEVEL_INFO
  AddLog(LOG_LEVEL_DEBUG, PSTR(D_LOG_APPLICATION D_ERASE " %d " D_UNIT_SECTORS), _sectorEnd - _sectorStart);
    #endif// ENABLE_LOG_LEVEL_INFO

  for (uint32_t _sector = _sectorStart; _sector < _sectorEnd; _sector++) {
    result = ESP.flashEraseSector(_sector);
    if (_serialoutput) {
      Serial.print(F(D_LOG_APPLICATION D_ERASED_SECTOR " "));
      Serial.print(_sector);
      if (result) {
        Serial.println(F(" " D_OK));
      } else {
        Serial.println(F(" " D_ERROR));
      }
      delay(10);
    }
    //OsWatchLoop();
  }
#endif  // FIRMWARE_MINIMAL
}

// Copied from 2.4.0 as 2.3.0 is incomplete
bool mSettings::SettingsEraseConfig(void) 
{
  const size_t cfgSize = 0x4000;
  size_t cfgAddr = ESP.getFlashChipSize() - cfgSize;

  for (size_t offset = 0; offset < cfgSize; offset += SPI_FLASH_SEC_SIZE) {
    if (!ESP.flashEraseSector((cfgAddr + offset) / SPI_FLASH_SEC_SIZE)) {
      return false;
    }
  }
  return true;
}

void mSettings::SettingsSdkErase(void)
{
//   WiFi.disconnect(true);    // Delete SDK wifi config
//   SettingsErase(1);
//   SettingsEraseConfig();
//   delay(1000);
}

