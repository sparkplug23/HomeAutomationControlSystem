#include "2_CoreSystem/Telemetry/mTelemetry.h"

const char* mTelemetry::PM_MODULE_CORE_TELEMETRY_CTR = D_MODULE_CORE_TELEMETRY_CTR;
const char* mTelemetry::PM_MODULE_CORE_TELEMETRY_FRIENDLY_CTR = D_MODULE_CORE_TELEMETRY_FRIENDLY_CTR;

int8_t mTelemetry::Tasker(uint8_t function, JsonParserObject obj){

  // DEBUG_PRINT_FUNCTION_NAME_TEST;
  switch(function){
    case FUNC_INIT:
      Init();
    break;
    
    #ifdef USE_MODULE_NETWORK_WEBSERVER
    case FUNC_WEB_ADD_HANDLER:
      WebPage_Root_AddHandlers();
    break;
    #endif //  #ifdef USE_MODULE_NETWORK_WEBSERVER
    /************
     * MQTT SECTION * 
    *******************/
    #ifdef USE_MODULE_NETWORK_MQTT
    case FUNC_MQTT_HANDLERS_INIT:
    case FUNC_MQTT_HANDLERS_RESET:
      MQTTHandler_Init();
      break;
    case FUNC_MQTT_HANDLERS_REFRESH_TELEPERIOD:
      MQTTHandler_Set_TelePeriod();
      break;
    case FUNC_MQTT_SENDER:
      MQTTHandler_Sender();
      break;
    #endif //USE_MODULE_NETWORK_MQTT
  }

}


void mTelemetry::parse_JSONCommand(JsonParserObject obj){}

#ifdef USE_MODULE_NETWORK_WEBSERVER
void mTelemetry::WebPage_Root_AddHandlers(){

  /**
   *Add telemetry calls-- retrieve tele by http request and return as text 
   **/ 
  /* 
  pCONT_web->pWebServer->on("/status/telemetry/health.json", HTTP_GET, [this](AsyncWebServerRequest *request){  
    ConstructJSON_Health(JSON_LEVEL_ALL);
    pCONT_web->WebSend_Response(request,200,CONTENT_TYPE_APPLICATION_JSON_ID,data_buffer.payload.ctr); 
  });
  pCONT_web->pWebServer->on("/status/telemetry/settings.json", HTTP_GET, [this](AsyncWebServerRequest *request){ 
    ConstructJSON_Settings(JSON_LEVEL_ALL);
    pCONT_web->WebSend_Response(request,200,CONTENT_TYPE_APPLICATION_JSON_ID,data_buffer.payload.ctr); 
  });
  pCONT_web->pWebServer->on("/status/telemetry/firmware.json", HTTP_GET, [this](AsyncWebServerRequest *request){    
    ConstructJSON_Firmware(JSON_LEVEL_ALL);
    pCONT_web->WebSend_Response(request,200,CONTENT_TYPE_APPLICATION_JSON_ID,data_buffer.payload.ctr); 
  });
  pCONT_web->pWebServer->on("/status/telemetry/log.json", HTTP_GET, [this](AsyncWebServerRequest *request){  
    ConstructJSON_Log(JSON_LEVEL_ALL);
    pCONT_web->WebSend_Response(request,200,CONTENT_TYPE_APPLICATION_JSON_ID,data_buffer.payload.ctr); 
  });
  pCONT_web->pWebServer->on("/status/telemetry/memory.json", HTTP_GET, [this](AsyncWebServerRequest *request){  
    ConstructJSON_Memory(JSON_LEVEL_ALL);
    pCONT_web->WebSend_Response(request,200,CONTENT_TYPE_APPLICATION_JSON_ID,data_buffer.payload.ctr); 
  });
  pCONT_web->pWebServer->on("/status/telemetry/network.json", HTTP_GET, [this](AsyncWebServerRequest *request){  
    ConstructJSON_Network(JSON_LEVEL_ALL);
    pCONT_web->WebSend_Response(request,200,CONTENT_TYPE_APPLICATION_JSON_ID,data_buffer.payload.ctr); 
  });
  pCONT_web->pWebServer->on("/status/telemetry/mqtt.json", HTTP_GET, [this](AsyncWebServerRequest *request){  
    ConstructJSON_MQTT(JSON_LEVEL_ALL);
    pCONT_web->WebSend_Response(request,200,CONTENT_TYPE_APPLICATION_JSON_ID,data_buffer.payload.ctr); 
  });
  pCONT_web->pWebServer->on("/status/telemetry/time.json", HTTP_GET, [this](AsyncWebServerRequest *request){  
    ConstructJSON_Time(JSON_LEVEL_ALL);
    pCONT_web->WebSend_Response(request,200,CONTENT_TYPE_APPLICATION_JSON_ID,data_buffer.payload.ctr);
  });
  pCONT_web->pWebServer->on("/status/telemetry/devices.json", HTTP_GET, [this](AsyncWebServerRequest *request){  
    ConstructJSON_Devices(JSON_LEVEL_ALL);
    pCONT_web->WebSend_Response(request,200,CONTENT_TYPE_APPLICATION_JSON_ID,data_buffer.payload.ctr); 
  });
  pCONT_web->pWebServer->on("/status/telemetry/reboot.json", HTTP_GET, [this](AsyncWebServerRequest *request){  
    ConstructJSON_Reboot(JSON_LEVEL_ALL);
    pCONT_web->WebSend_Response(request,200,CONTENT_TYPE_APPLICATION_JSON_ID,data_buffer.payload.ctr); 
  });
  pCONT_web->pWebServer->on("/status/telemetry/debug/minimal.json", HTTP_GET, [this](AsyncWebServerRequest *request){  
    ConstructJSON_Debug_Minimal(JSON_LEVEL_ALL);
    pCONT_web->WebSend_Response(request,200,CONTENT_TYPE_APPLICATION_JSON_ID,data_buffer.payload.ctr); 
  });
  pCONT_web->pWebServer->on("/status/telemetry/debug/pins.json", HTTP_GET, [this](AsyncWebServerRequest *request){  
    ConstructJSON_Debug_Pins(JSON_LEVEL_ALL);
    pCONT_web->WebSend_Response(request,200,CONTENT_TYPE_APPLICATION_JSON_ID,data_buffer.payload.ctr); 
  });
  pCONT_web->pWebServer->on("/status/telemetry/debug/template.json", HTTP_GET, [this](AsyncWebServerRequest *request){  
    ConstructJSON_Debug_Template(JSON_LEVEL_ALL);
    pCONT_web->WebSend_Response(request,200,CONTENT_TYPE_APPLICATION_JSON_ID,data_buffer.payload.ctr); 
  });
  pCONT_web->pWebServer->on("/status/telemetry/debug/moduleinterface.json", HTTP_GET, [this](AsyncWebServerRequest *request){  
    ConstructJSON_Debug_ModuleInterface(JSON_LEVEL_ALL);
    pCONT_web->WebSend_Response(request,200,CONTENT_TYPE_APPLICATION_JSON_ID,data_buffer.payload.ctr); 
  });*/

}
#endif //  #ifdef USE_MODULE_NETWORK_WEBSERVER




#ifdef USE_MODULE_NETWORK_MQTT



void mTelemetry::MQTTHandler_Init(){

  handler<mTelemetry>* p;

  p = &mqtthandler_health;
  p->handler_id = MQTT_HANDLER_SYSTEM_HEALTH_ID;
  p->tSavedLastSent = millis();
  p->flags.PeriodicEnabled = true;
  p->flags.SendNow = true;
  p->tRateSecs = DEFAULT_MQTT_SYSTEM_MINIMAL_RATE_SECS; 
  p->flags.FrequencyRedunctionLevel = MQTT_FREQUENCY_REDUCTION_LEVEL_REDUCE_AFTER_10_MINUTES_ID;
  p->topic_type = MQTT_TOPIC_TYPE_SYSTEM_ID;
  p->json_level = JSON_LEVEL_DETAILED;
  p->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_HEALTH_CTR;
  p->ConstructJSON_function = &mTelemetry::ConstructJSON_Health;
  
  p = &mqtthandler_settings;
  p->handler_id = MQTT_HANDLER_SYSTEM_SETTINGS_ID;
  p->tSavedLastSent = millis();
  p->flags.PeriodicEnabled = true;
  p->flags.SendNow = true;
  p->tRateSecs = SEC_IN_HOUR; 
  p->flags.FrequencyRedunctionLevel = MQTT_FREQUENCY_REDUCTION_LEVEL_UNCHANGED_ID;
  p->topic_type = MQTT_TOPIC_TYPE_SYSTEM_ID;
  p->json_level = JSON_LEVEL_DETAILED;
  p->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_SETTINGS_CTR;
  p->ConstructJSON_function = &mTelemetry::ConstructJSON_Settings;
  
  p = &mqtthandler_log;
  p->handler_id = MQTT_HANDLER_SYSTEM_LOG_ID;
  p->tSavedLastSent = millis();
  p->flags.PeriodicEnabled = true;
  p->flags.SendNow = true;
  p->tRateSecs = SEC_IN_HOUR; 
  p->flags.FrequencyRedunctionLevel = MQTT_FREQUENCY_REDUCTION_LEVEL_UNCHANGED_ID;
  p->topic_type = MQTT_TOPIC_TYPE_SYSTEM_ID;
  p->json_level = JSON_LEVEL_DETAILED;
  p->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_LOG_CTR;
  p->ConstructJSON_function = &mTelemetry::ConstructJSON_Log;
  
  p = &mqtthandler_firmware;
  p->handler_id = MQTT_HANDLER_SYSTEM_FIRMWARE_ID;
  p->tSavedLastSent = millis();
  p->flags.PeriodicEnabled = true;
  p->flags.SendNow = true;
  p->tRateSecs = SEC_IN_HOUR; 
  p->flags.FrequencyRedunctionLevel = MQTT_FREQUENCY_REDUCTION_LEVEL_UNCHANGED_ID;
  p->topic_type = MQTT_TOPIC_TYPE_SYSTEM_ID;
  p->json_level = JSON_LEVEL_DETAILED;
  p->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_FIRMWARE_CTR;
  p->ConstructJSON_function = &mTelemetry::ConstructJSON_Firmware;
  
  p = &mqtthandler_memory;
  p->handler_id = MQTT_HANDLER_SYSTEM_MEMORY_ID;
  p->tSavedLastSent = millis();
  p->flags.PeriodicEnabled = true;
  p->flags.SendNow = true;
  p->tRateSecs = SEC_IN_HOUR; 
  p->flags.FrequencyRedunctionLevel = MQTT_FREQUENCY_REDUCTION_LEVEL_UNCHANGED_ID;
  p->topic_type = MQTT_TOPIC_TYPE_SYSTEM_ID;
  p->json_level = JSON_LEVEL_DETAILED;
  p->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_MEMORY_CTR;
  p->ConstructJSON_function = &mTelemetry::ConstructJSON_Memory;
  
  p = &mqtthandler_network;
  p->handler_id = MQTT_HANDLER_SYSTEM_NETWORK_ID;
  p->tSavedLastSent = millis();
  p->flags.PeriodicEnabled = true;
  p->flags.SendNow = true;
  p->tRateSecs = SEC_IN_HOUR; 
  p->flags.FrequencyRedunctionLevel = MQTT_FREQUENCY_REDUCTION_LEVEL_UNCHANGED_ID;
  p->topic_type = MQTT_TOPIC_TYPE_SYSTEM_ID;
  p->json_level = JSON_LEVEL_DETAILED;
  p->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_NETWORK_CTR;
  p->ConstructJSON_function = &mTelemetry::ConstructJSON_Network;
  
  p = &mqtthandler_mqtt;
  p->handler_id = MQTT_HANDLER_SYSTEM_MQTT_ID;
  p->tSavedLastSent = millis();
  p->flags.PeriodicEnabled = true;
  p->flags.SendNow = true;
  p->tRateSecs = SEC_IN_HOUR; 
  p->flags.FrequencyRedunctionLevel = MQTT_FREQUENCY_REDUCTION_LEVEL_UNCHANGED_ID;
  p->topic_type = MQTT_TOPIC_TYPE_SYSTEM_ID;
  p->json_level = JSON_LEVEL_DETAILED;
  p->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_MQTT_CTR;
  p->ConstructJSON_function = &mTelemetry::ConstructJSON_MQTT;
  
  p = &mqtthandler_time;
  p->handler_id = MQTT_HANDLER_SYSTEM_TIME_ID;
  p->tSavedLastSent = millis();
  p->flags.PeriodicEnabled = true;
  p->flags.SendNow = true;
  p->tRateSecs = SEC_IN_HOUR; 
  p->flags.FrequencyRedunctionLevel = MQTT_FREQUENCY_REDUCTION_LEVEL_UNCHANGED_ID;
  p->topic_type = MQTT_TOPIC_TYPE_SYSTEM_ID;
  p->json_level = JSON_LEVEL_DETAILED;
  p->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_TIME_CTR;
  p->ConstructJSON_function = &mTelemetry::ConstructJSON_Time;
  
  p = &mqtthandler_devices;
  p->handler_id = MQTT_HANDLER_SYSTEM_DEVICES_ID;
  p->tSavedLastSent = millis();
  p->flags.PeriodicEnabled = true;
  p->flags.SendNow = true;
  p->tRateSecs = SEC_IN_HOUR; 
  p->flags.FrequencyRedunctionLevel = MQTT_FREQUENCY_REDUCTION_LEVEL_UNCHANGED_ID;
  p->topic_type = MQTT_TOPIC_TYPE_SYSTEM_ID;
  p->json_level = JSON_LEVEL_DETAILED;
  p->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_DEVICES_CTR;
  p->ConstructJSON_function = &mTelemetry::ConstructJSON_Devices;
  
  p = &mqtthandler_reboot;
  p->handler_id = MQTT_HANDLER_SYSTEM_REBOOT_ID;
  p->tSavedLastSent = millis();
  p->flags.PeriodicEnabled = true;
  p->flags.SendNow = true;
  p->tRateSecs = SEC_IN_HOUR; 
  p->flags.FrequencyRedunctionLevel = MQTT_FREQUENCY_REDUCTION_LEVEL_UNCHANGED_ID;
  p->topic_type = MQTT_TOPIC_TYPE_SYSTEM_ID;
  p->json_level = JSON_LEVEL_DETAILED;
  p->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_REBOOT_CTR;
  p->ConstructJSON_function = &mTelemetry::ConstructJSON_Reboot;
  
  p = &mqtthandler_reboot_event;
  p->handler_id = MQTT_HANDLER_SYSTEM_REBOOT_EVENT_ID;
  p->tSavedLastSent = millis();
  p->flags.PeriodicEnabled = false;
  p->flags.SendNow = true;
  p->tRateSecs = SEC_IN_HOUR;  
  p->flags.FrequencyRedunctionLevel = MQTT_FREQUENCY_REDUCTION_LEVEL_UNCHANGED_ID;
  p->topic_type = MQTT_TOPIC_TYPE_SYSTEM_ID;
  p->json_level = JSON_LEVEL_ALL;
  p->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_REBOOT_EVENT_CTR;
  p->ConstructJSON_function = &mTelemetry::ConstructJSON_Reboot;

  #ifdef ENABLE_MQTT_DEBUG_TELEMETRY
  p = &mqtthandler_debug_pins;
  p->handler_id = MQTT_HANDLER_SYSTEM_DEBUG_PINS_ID;
  p->tSavedLastSent = millis();
  p->flags.PeriodicEnabled = true;
  p->flags.SendNow = true;
  p->tRateSecs = SEC_IN_HOUR; 
  p->flags.FrequencyRedunctionLevel = MQTT_FREQUENCY_REDUCTION_LEVEL_UNCHANGED_ID;
  p->topic_type = MQTT_TOPIC_TYPE_SYSTEM_ID;
  p->json_level = JSON_LEVEL_DETAILED;
  p->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_DEBUG_PINS_CTR;
  p->ConstructJSON_function = &mTelemetry::ConstructJSON_Debug_Pins;

  p = &mqtthandler_debug_template;
  p->handler_id = MQTT_HANDLER_SYSTEM_DEBUG_TEMPLATE_ID;
  p->tSavedLastSent = millis();
  p->flags.PeriodicEnabled = true;
  p->flags.SendNow = true;
  p->tRateSecs = SEC_IN_HOUR; 
  p->flags.FrequencyRedunctionLevel = MQTT_FREQUENCY_REDUCTION_LEVEL_UNCHANGED_ID;
  p->topic_type = MQTT_TOPIC_TYPE_SYSTEM_ID;
  p->json_level = JSON_LEVEL_DETAILED;
  p->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_DEBUG_TEMPLATE_CTR;
  p->ConstructJSON_function = &mTelemetry::ConstructJSON_Debug_Template;

  p = &mqtthandler_debug_moduleinterface;
  p->handler_id = MQTT_HANDLER_SYSTEM_DEBUG_MODULEINTERFACE_ID;
  p->tSavedLastSent = millis();
  p->flags.PeriodicEnabled = true;
  p->flags.SendNow = true;
  p->tRateSecs = SEC_IN_HOUR; 
  p->flags.FrequencyRedunctionLevel = MQTT_FREQUENCY_REDUCTION_LEVEL_UNCHANGED_ID;
  p->topic_type = MQTT_TOPIC_TYPE_SYSTEM_ID;
  p->json_level = JSON_LEVEL_DETAILED;
  p->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_DEBUG_MODULETEMPLATE_CTR;
  p->ConstructJSON_function = &mTelemetry::ConstructJSON_Debug_ModuleInterface;
  #endif
  
  p = &mqtthandler_debug_minimal;
  p->handler_id = MQTT_HANDLER_SYSTEM_DEBUG_MINIMAL_ID;
  p->tSavedLastSent = millis();
  p->flags.PeriodicEnabled = true;
  p->flags.SendNow = true;
  p->tRateSecs = DEFAULT_MQTT_SYSTEM_MINIMAL_RATE_SECS;
  p->flags.FrequencyRedunctionLevel = MQTT_FREQUENCY_REDUCTION_LEVEL_UNCHANGED_ID;// MQTT_FREQUENCY_REDUCTION_LEVEL_REDUCE_AFTER_10_MINUTES_ID;
  p->topic_type = MQTT_TOPIC_TYPE_SYSTEM_ID;
  p->json_level = JSON_LEVEL_DETAILED;
  p->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_DEBUG_MODULEMINIMAL_CTR;
  p->ConstructJSON_function = &mTelemetry::ConstructJSON_Debug_Minimal;

} //end "MQTTHandler_Init"


/**
 * @brief Set flag for all mqtthandlers to send
 * */
void mTelemetry::MQTTHandler_Set_fSendNow()
{
  for(auto& handle:mqtthandler_list){
    handle->flags.SendNow = true;
  }
}

/**
 * @brief Update 'tRateSecs' with shared teleperiod
 * */
void mTelemetry::MQTTHandler_Set_TelePeriod()
{
  for(auto& handle:mqtthandler_list){
    if(handle->topic_type == MQTT_TOPIC_TYPE_TELEPERIOD_ID)
      handle->tRateSecs = pCONT_set->Settings.sensors.teleperiod_secs;
  }
}

/**
 * @brief Check all handlers if they require action
 * */
void mTelemetry::MQTTHandler_Sender(uint8_t id)
{
  for(auto& handle:mqtthandler_list){
    pCONT_mqtt->MQTTHandler_Command(*this, EM_MODULE_CORE_TELEMETRY_ID, handle, id);
  }
}

#endif // USE_MODULE_NETWORK_MQTT



void mTelemetry::Init(){
    #ifdef ENABLE_DEVFEATURE_HARDWARE_STATUS
  memset(&hardwarestatus,0,sizeof(hardwarestatus));
  hardwarestatus.len += 0;//sprintf(hardwarestatus.ctr,"Restarted");
    #endif// ENABLE_DEVFEATURE_HARDWARE_STATUS
}


uint8_t mTelemetry::ConstructJSON_Health(uint8_t json_level){ //BuildHealth

  IPAddress localip = WiFi.localIP();

    #ifdef ENABLE_DEVFEATURE_HARDWARE_STATUS
  // Generate status message from all modules for human readable message
  memset(&hardwarestatus,0,sizeof(hardwarestatus));
  pCONT->Tasker_Interface(FUNC_STATUS_MESSAGE_APPEND);

    #endif// ENABLE_DEVFEATURE_HARDWARE_STATUS

  JsonBuilderI->Start();
  
    // //test devices
    // JsonBuilderI->Level_Start("Test");
    //   JsonBuilderI->Add("activity.loop_counter", pCONT_sup->activity.loop_counter);
    // //   JsonBuilderI->Add("sleep", pCONT_set->sleep);
    // //   JsonBuilderI->Add("loop_runtime_millis", pCONT_sup->loop_runtime_millis);
    // //   JsonBuilderI->Add("loops_per_second", pCONT_sup->loops_per_second);
    // //   JsonBuilderI->Add("this_cycle_ratio", pCONT_sup->this_cycle_ratio);
    // //   JsonBuilderI->Add("loop_load_avg", pCONT_set->loop_load_avg);
    // //   JsonBuilderI->Add("enable_sleep", pCONT_set->Settings.enable_sleep);
    // JsonBuilderI->Level_End();
    // // test end

    JsonBuilderI->Add(PM_JSON_TIME,           pCONT_time->RtcTime.hhmmss_ctr);
    JsonBuilderI->Add_FV(PM_JSON_UPTIME,      PSTR("\"%02dT%02d:%02d:%02d\""), pCONT_time->uptime.Yday,pCONT_time->uptime.hour,pCONT_time->uptime.minute,pCONT_time->uptime.second);
    JsonBuilderI->Add(PM_JSON_UPSECONDS,      pCONT_time->uptime.seconds_nonreset);
    JsonBuilderI->Add(PM_JSON_SLEEPMODE,      pCONT_set->runtime_var.sleep ? "Dynamic" : "Unknown");
    JsonBuilderI->Add(PM_JSON_SLEEP,          pCONT_set->runtime_var.sleep); // typ. 20
    JsonBuilderI->Add(PM_JSON_LOOPSSEC,       pCONT_sup->activity.cycles_per_sec); // typ. 50hz
    // JsonBuilderI->Add(PM_JSON_LOOPDELAY,      pCONT_sup->loop_delay_temp);
    JsonBuilderI->Add(PM_JSON_LOADAVERAGE,    pCONT_set->loop_load_avg); // average loops_per_second
    JsonBuilderI->Add(PM_JSON_FREEHEAP,       ESP.getFreeHeap());
    JsonBuilderI->Add(PM_JSON_DEVICEFRIENDLYNAME, pCONT_set->Settings.system_name.friendly);
    JsonBuilderI->Level_Start(PM_JSON_NETWORK);
      JsonBuilderI->Add_FV(PM_JSON_IPADDRESS, PSTR("\"%d.%d.%d.%d\""), localip[0],localip[1],localip[2],localip[3]);
      JsonBuilderI->Add(PM_JSON_SSID,         WiFi.SSID().c_str());
      JsonBuilderI->Add(PM_JSON_RSSI,         WiFi.RSSI());
      // JsonBuilderI->Add(PM_JSON_CONNECTCOUNT, wifi_reconnects_counter);
      JsonBuilderI->Add(PM_JSON_DOWNTIME,     "00T00:00:00");
      JsonBuilderI->Add(PM_JSON_DOWNSECS,     (uint8_t)0);
    JsonBuilderI->Level_End();
    // JsonBuilderI->Level_Start(PM_JSON_MQTT);
    //   JsonBuilderI->Add(PM_JSON_SENTCOUNT,       pCONT_mqtt->pubsub->stats.packets_sent_counter);
    //   JsonBuilderI->Add(PM_JSON_RECEIVEDCOUNT,   pCONT_mqtt->pubsub->stats.packets_sent_counter);
    //   JsonBuilderI->Add(PM_JSON_SENTPERMINUTE,   pCONT_mqtt->pubsub->stats.packets_sent_per_minute);
    // JsonBuilderI->Level_End();
    #ifdef ENABLE_DEVFEATURE_HARDWARE_STATUS
    JsonBuilderI->Level_Start(PM_JSON_STATUS);
      JsonBuilderI->Add(PM_JSON_MESSAGE,         hardwarestatus.ctr); //this can be turned into a subadd method
      JsonBuilderI->Add(PM_JSON_LEVEL,           hardwarestatus.importance);
    JsonBuilderI->Level_End();
    #endif// ENABLE_DEVFEATURE_HARDWARE_STATUS
    // JsonBuilderI->Add(PM_JSON_PAYLOAD_RATE,      pCONT_time->RtcTime.hhmmss_ctr);
  return JsonBuilderI->End();
    
}


uint8_t mTelemetry::ConstructJSON_Settings(uint8_t json_level){ 
  char buffer[50];
  JsonBuilderI->Start();
    JsonBuilderI->Add(PM_JSON_MODULENAME,     pCONT_set->Settings.system_name.friendly);
    JsonBuilderI->Add(PM_JSON_FRIENDLYNAME,   pCONT_pins->ModuleName(buffer, sizeof(buffer))); 
    JsonBuilderI->Add(PM_JSON_POWER,          pCONT_set->power); 
    JsonBuilderI->Add(PM_JSON_POWERONSTATE,   pCONT_set->Settings.poweronstate); 
    JsonBuilderI->Add(PM_JSON_LEDSTATE,       pCONT_set->Settings.ledstate);
    JsonBuilderI->Add_FV(PM_JSON_LEDMASK,     PSTR("\"%04X\""), 0); 
    JsonBuilderI->Add(PM_JSON_SAVEDATA,       0); 
    JsonBuilderI->Add(PM_JSON_SAVESTATE,      0); 
    JsonBuilderI->Add(PM_JSON_SWITCHMODE,     0); 
    JsonBuilderI->Add(PM_JSON_BUTTONRETAIN,   pCONT_set->Settings.flag_system.mqtt_button_retain); 
    JsonBuilderI->Add(PM_JSON_SWITCHRETAIN,   pCONT_set->Settings.flag_system.mqtt_switch_retain); 
    JsonBuilderI->Add(PM_JSON_SENSORRETAIN,   pCONT_set->Settings.flag_system.mqtt_sensor_retain); 
    JsonBuilderI->Add(PM_JSON_POWERRETAIN,    pCONT_set->Settings.flag_system.mqtt_power_retain);
    JsonBuilderI->Add(PM_JSON_BAUDRATE,       (uint16_t)115200);
    JsonBuilderI->Add(PM_JSON_SETTINGS_HOLDER,pCONT_set->Settings.cfg_holder);
    JsonBuilderI->Add(PM_JSON_OTAURL,         "http://something.org/TBD/release/minimal.bin");
    JsonBuilderI->Add_FV(PM_JSON_SAVEADDRESS, PSTR("\"%X\""), pCONT_set->GetSettingsAddress());
    JsonBuilderI->Add(PM_JSON_SAVECOUNT,      pCONT_set->Settings.save_flag);
    JsonBuilderI->Add(PM_JSON_STARTUPUTC,     "2019-12-10T21:35:44");
  return JsonBuilderI->End();
}


uint8_t mTelemetry::ConstructJSON_Firmware(uint8_t json_level){ //BuildHealth
  char buffer[30];
  JsonBuilderI->Start();
    JsonBuilderI->Add(PM_JSON_BUILDDATE,       __DATE__);
    JsonBuilderI->Add(PM_JSON_VERSIONNAME,     pCONT_set->firmware_version.current.name_ctr);


    JsonBuilderI->Add(PM_JSON_SERIAL,          pCONT_sto->GetLogLevelNamebyID(pCONT_set->Settings.seriallog_level, buffer));
    JsonBuilderI->Add(PM_JSON_BOOTCOUNT,       pCONT_set->Settings.bootcount);
    JsonBuilderI->Add(PM_JSON_BOOTCOUNTERRORS, pCONT_set->Settings.bootcount_errors_only);
    JsonBuilderI->Add(PM_JSON_BUILDDATETIME,   pCONT_time->GetBuildDateAndTime(buffer, sizeof(buffer)));
    JsonBuilderI->Add(PM_JSON_BUILDTIME,       __TIME__);
    // JsonBuilderI->Add(PM_JSON_VERSION,         pCONT_set->my_version);
    JsonBuilderI->Add(PM_JSON_VERSIONNUMBER,   PROJECT_VERSION);
    JsonBuilderI->Add(PM_JSON_COREVERSION,     ARDUINO_ESP8266_RELEASE); 
    
#ifdef ESP8266
    JsonBuilderI->Add(PM_JSON_BOOTVERSION,     ESP.getBootVersion());
  #endif // ESP8266
    JsonBuilderI->Add(PM_JSON_SDKVERSION,      ESP.getSdkVersion());    
    // JsonBuilderI->Add(PM_JSON_DRIVERS,         "1,2,3,4,5,6,7,8,9,10,12,14,16,17,18,19,20,21,22,24,26,30");
    // JsonBuilderI->Add(PM_JSON_SENSORS,         "1,2,3,4,5,6,7,8,9,10,12,14,16,17,18,19,20,21,22,24,26,30");
    JsonBuilderI->Add_FV(PM_JSON_FEATURES,     PSTR("[\"%08X\",\"%08X\",\"%08X\",\"%08X\"]"), 0,0,0,0);
    JsonBuilderI->Add(PM_JSON_SDKVERSION,      ESP.getSdkVersion());    
    JsonBuilderI->Add(PM_JSON_FREESKETCHSPACE,      ESP.getFreeSketchSpace());
    JsonBuilderI->Add(PM_JSON_TEMPLATE_USED,   pCONT_set->boot_status.module_template_used);  
    JsonBuilderI->Add(PM_JSON_TEMPLATE_PARSE_SUCCESS, pCONT_set->boot_status.module_template_parse_success); 
  return JsonBuilderI->End();
}


uint8_t mTelemetry::ConstructJSON_Log(uint8_t json_level){ 
  char buffer[30];
  JsonBuilderI->Start();
    JsonBuilderI->Level_Start(PM_JSON_LOGLEVELS);
      JsonBuilderI->Add(PM_JSON_SERIAL, pCONT_sto->GetLogLevelNamebyID(pCONT_set->Settings.seriallog_level, buffer));
      JsonBuilderI->Add(PM_JSON_SYSTEM, pCONT_sto->GetLogLevelNamebyID(pCONT_set->Settings.syslog_level, buffer));
      JsonBuilderI->Add(PM_JSON_WEB,    pCONT_sto->GetLogLevelNamebyID(pCONT_set->Settings.weblog_level, buffer));
      JsonBuilderI->Add(PM_JSON_TELNET, pCONT_sto->GetLogLevelNamebyID(pCONT_set->Settings.telnetlog_level, buffer));
    JsonBuilderI->Level_End();
  return JsonBuilderI->End();
}


uint8_t mTelemetry::ConstructJSON_Memory(uint8_t json_level){ // Debug info
  JsonBuilderI->Start();
    JsonBuilderI->Add(PM_JSON_PROGRAMSIZE,      ESP.getSketchSize()/1024);
    #ifdef ESP8266
    JsonBuilderI->Add(PM_JSON_FREEMEMORY,       ESP.getFreeSketchSpace()/1024); // this takes seconds on esp32, what about here?... should I get and store on boot
    JsonBuilderI->Add(PM_JSON_HEAPSIZE,         ESP.getFreeHeap()/1024);
    JsonBuilderI->Add(PM_JSON_PROGRAMFLASHSIZE, ESP.getFlashChipSize()/1024);
    JsonBuilderI->Add(PM_JSON_FLASHSIZE,        ESP.getFlashChipRealSize()/1024);
    JsonBuilderI->Add(PM_JSON_FLASHCHIPID,      ESP.getFlashChipId());
    #endif // ESP8266
    JsonBuilderI->Add(PM_JSON_FLASHMODE,        (uint8_t)ESP.getFlashChipMode()); //FlashMode_t
  return JsonBuilderI->End();
}


uint8_t mTelemetry::ConstructJSON_Network(uint8_t json_level){ // Debug info not just wifi, might be ethernet later
  
  IPAddress localip   = WiFi.localIP();
  IPAddress staticip  = IPAddress(pCONT_set->Settings.ip_address[0]);
  IPAddress gatewayip = IPAddress(pCONT_set->Settings.ip_address[1]);
  IPAddress subnetip  = IPAddress(pCONT_set->Settings.ip_address[2]);
  IPAddress dnsip     = IPAddress(pCONT_set->Settings.ip_address[3]);

  JsonBuilderI->Start();
    JsonBuilderI->Add_FV(PM_JSON_IPADDRESS,PSTR("\"%d.%d.%d.%d\""),localip[0],localip[1],localip[2],localip[3]);
    JsonBuilderI->Add(PM_JSON_SSID, WiFi.SSID().c_str());
    JsonBuilderI->Add(PM_JSON_SSID_NUMBERED, pCONT_set->Settings.sta_active); // Used to debug switching in grafana
    JsonBuilderI->Add(PM_JSON_RSSI, WiFi.RSSI());
    // JsonBuilderI->Add(PM_JSON_CONNECTCOUNT, wifi_reconnects_counter);
    JsonBuilderI->Add(PM_JSON_HOSTNAME, pCONT_set->my_hostname);
    JBI->Add_P(PM_JSON_TELNET_PORT, TELNET_PORT);
    JsonBuilderI->Add_FV(PM_JSON_STATIC_IPADDRESS,PSTR("\"%d.%d.%d.%d\""),staticip[0],staticip[1],staticip[2],staticip[3]);
    JsonBuilderI->Add_FV(PM_JSON_GATEWAY,PSTR("\"%d.%d.%d.%d\""),gatewayip[0],gatewayip[1],gatewayip[2],gatewayip[3]);
    JsonBuilderI->Add_FV(PM_JSON_SUBNETMASK,PSTR("\"%d.%d.%d.%d\""),subnetip[0],subnetip[1],subnetip[2],subnetip[3]);
    JsonBuilderI->Add_FV(PM_JSON_DNSSERVER,PSTR("\"%d.%d.%d.%d\""),dnsip[0],dnsip[1],dnsip[2],dnsip[3]);
    JsonBuilderI->Add(PM_JSON_BSSID, WiFi.BSSIDstr().c_str());
    JsonBuilderI->Add(PM_JSON_MAC, WiFi.macAddress().c_str());
    JsonBuilderI->Add(PM_JSON_WEBSERVER_ENABLED, pCONT_set->Settings.webserver);
    JsonBuilderI->Add(PM_JSON_WIFICONFIG_STATE, pCONT_set->Settings.sta_config);
  return JsonBuilderI->End();

}


uint8_t mTelemetry::ConstructJSON_MQTT(uint8_t json_level){

  JsonBuilderI->Start();

    JBI->Add("ClientName", pCONT_set->Settings.mqtt.client_name);
    // JsonBuilderI->Level_Start(PM_JSON_PACKETS);
    //   JsonBuilderI->Add(PM_JSON_SENTCOUNT,      pCONT_mqtt->pubsub->stats.packets_sent_counter);
    //   JsonBuilderI->Add(PM_JSON_SENTPERMINUTE,  pCONT_mqtt->pubsub->stats.packets_sent_per_minute);
    // JsonBuilderI->Level_End();
    // JsonBuilderI->Level_Start(PM_JSON_CONNECTS);
    //   JsonBuilderI->Add(PM_JSON_COUNT,          pCONT_mqtt->pubsub->stats.reconnects_counter);
    //   JsonBuilderI->Add(PM_JSON_DOWNSECS,       pCONT_mqtt->pubsub->stats.connection_downtime);
    //   JsonBuilderI->Add(PM_JSON_UPSECONDS,      pCONT_mqtt->pubsub->stats.connection_uptime);
    //   JsonBuilderI->Add(PM_JSON_BROKERHOSTNAME, pCONT_set->Settings.mqtt.hostname_ctr);
    // JsonBuilderI->Level_End();
    JsonBuilderI->Add(PM_JSON_MQTT_ENABLE_RESTART,   (uint8_t)0);
  return JsonBuilderI->End();

}


uint8_t mTelemetry::ConstructJSON_Time(uint8_t json_level){ 

  char buffer[80];
       
  JsonBuilderI->Start();
    JsonBuilderI->Add(PM_JSON_UTC_TIME,   pCONT_time->GetDateAndTimeCtr(DT_UTC, buffer, sizeof(buffer)));
    JsonBuilderI->Add(PM_JSON_LOCAL_TIME, pCONT_time->GetDateAndTimeCtr(DT_LOCALNOTZ, buffer, sizeof(buffer)));
    JsonBuilderI->Add(PM_JSON_STARTDST,   pCONT_time->GetDateAndTimeCtr(DT_DST, buffer, sizeof(buffer)));
    JsonBuilderI->Add(PM_JSON_ENDDST,     pCONT_time->GetDateAndTimeCtr(DT_STD, buffer, sizeof(buffer)));
    JsonBuilderI->Add(PM_JSON_TIMEZONE,   pCONT_time->GetDateAndTimeCtr(DT_TIMEZONE, buffer, sizeof(buffer)));
    JsonBuilderI->Add(PM_JSON_SUNRISE,    pCONT_time->GetDateAndTimeCtr(DT_SUNRISE, buffer, sizeof(buffer)));
    JsonBuilderI->Add(PM_JSON_SUNSET,     pCONT_time->GetDateAndTimeCtr(DT_SUNSET, buffer, sizeof(buffer)));
#ifdef ENABLE_DEVFEATURE_RTC_TIME_V2_MQTT_DEBUG
    JsonBuilderI->Level_Start("debug_v2");
      JsonBuilderI->Add("utc_time",pCONT_time->Rtc.utc_time);
      JsonBuilderI->Add("local_time",pCONT_time->Rtc.local_time);
      JsonBuilderI->Add("daylight_saving_time",pCONT_time->Rtc.daylight_saving_time);
      JsonBuilderI->Add("standard_time",pCONT_time->Rtc.standard_time);
      JsonBuilderI->Add("ntp_time",pCONT_time->Rtc.ntp_time);
      JsonBuilderI->Add("midnight",pCONT_time->Rtc.midnight);
      JsonBuilderI->Add("restart_time",pCONT_time->Rtc.restart_time);
      JsonBuilderI->Add("millis",pCONT_time->Rtc.millis);
      JsonBuilderI->Add("last_sync",pCONT_time->Rtc.last_sync);
      JsonBuilderI->Add("time_timezone",pCONT_time->Rtc.time_timezone);
      JsonBuilderI->Add("ntp_sync_minute",pCONT_time->Rtc.ntp_sync_minute);
      JsonBuilderI->Add("midnight_now",pCONT_time->Rtc.midnight_now);
      JsonBuilderI->Add("user_time_entry",pCONT_time->Rtc.user_time_entry);
      JsonBuilderI->Add("ntp_last_active_secs", (millis()-pCONT_time->Rtc.ntp_last_active)/1000);
      JsonBuilderI->Add("last_sync_secs", (pCONT_time->Rtc.utc_time-pCONT_time->Rtc.last_sync)/1000);
      JsonBuilderI->Add("GetUptime",pCONT_time->GetUptime().c_str());
    JsonBuilderI->Level_End();
    JsonBuilderI->Level_Start("RtcTime");
      JsonBuilderI->Add("valid",pCONT_time->RtcTime.valid);
      JsonBuilderI->Add_FV("time","\"%02d:%02d:%02d\"",pCONT_time->RtcTime.hour,pCONT_time->RtcTime.minute,pCONT_time->RtcTime.second);
    JsonBuilderI->End();
#endif // ENABLE_DEVFEATURE_RTC_TIME_V2_MQTT_DEBUG
  return JsonBuilderI->End();

}


uint8_t mTelemetry::ConstructJSON_Devices(uint8_t json_level){ 

  JsonBuilderI->Start();
    JsonBuilderI->Add(PM_JSON_MODULENAME,          pCONT_set->Settings.module);
    JsonBuilderI->Array_AddArray(PM_JSON_DEVICEID, pCONT_set->Settings.device_name_buffer.device_id, sizeof(pCONT_set->Settings.device_name_buffer.device_id)/2);
    JsonBuilderI->Array_AddArray(PM_JSON_CLASSID,  pCONT_set->Settings.device_name_buffer.class_id,  sizeof(pCONT_set->Settings.device_name_buffer.class_id)/2);
    JsonBuilderI->Add("Buffer",        pCONT_set->Settings.device_name_buffer.name_buffer);

    #ifdef USE_FUNCTION_TEMPLATE
    //JsonBuilderI->Add("Function Template",   FUNCTION_TEMPLATE);
    #endif

  return JsonBuilderI->End();

}


uint8_t mTelemetry::ConstructJSON_Reboot(uint8_t json_level){ // 

  JsonBuilderI->Start();
  
  JsonBuilderI->Add(PM_JSON_DEVICE, pCONT_set->Settings.system_name.device);
  JsonBuilderI->Add(D_JSON_DEVICEFRIENDLYNAME, pCONT_set->Settings.system_name.friendly);
  JsonBuilderI->Add_FV(D_JSON_DATETIME, PSTR("\"%02d-%02d-%02d %02d:%02d:%02d\""),
                      pCONT_time->RtcTime.Mday, pCONT_time->RtcTime.month, pCONT_time->RtcTime.year,
                      pCONT_time->RtcTime.hour, pCONT_time->RtcTime.minute, pCONT_time->RtcTime.second
                    );
  JsonBuilderI->Level_Start(D_JSON_COUNTER);
    JsonBuilderI->Add("All", (uint8_t)0);
    // JsonBuilderI->Add("WDT", (uint8_t)0);
  JsonBuilderI->Level_End();

  // if (pCONT_sup->CrashFlag()) {
    
  JsonBuilderI->Level_Start(D_JSON_CRASHDUMP);
    pCONT_sup->WriteBuffer_P(PSTR(","));
    pCONT_sup->CrashDump_AddJson();
  JsonBuilderI->Level_End();

  // } else {
  //   char buffer[30];
  //   JsonBuilderI->Add("Reason", pCONT_sup->GetResetReason(buffer, sizeof(buffer)));
  // }

  return JsonBuilderI->End();

}




/****
 * 
 * 
 * 
 * Debug packets that are not part of the main telemetry and only used for debugging/developing the device
 * 
 * 
 * 
 * ****/

uint8_t mTelemetry::ConstructJSON_Debug_Minimal(uint8_t json_level){ //BuildHealth

  IPAddress localip = WiFi.localIP();
  
  JsonBuilderI->Start();
    JsonBuilderI->Add_FV(PM_JSON_UPTIME,      PSTR("\"%02dT%02d:%02d:%02d\""), pCONT_time->uptime.Yday,pCONT_time->uptime.hour,pCONT_time->uptime.minute,pCONT_time->uptime.second);
    JsonBuilderI->Add(PM_JSON_UPSECONDS,      pCONT_time->uptime.seconds_nonreset);
    JsonBuilderI->Add(PM_JSON_SLEEP,          pCONT_sup->loop_delay_temp);
    JsonBuilderI->Add(PM_JSON_LOOPSSEC,       pCONT_sup->activity.cycles_per_sec);
    JsonBuilderI->Add(PM_JSON_LOOPRATIO,      pCONT_sup->this_cycle_ratio);
    #ifdef USE_NETWORK_MDNS
    JsonBuilderI->Add(PM_JSON_MDNS,           pCONT_set->boot_status.mdns_started_succesfully);
    #endif // #ifdef USE_NETWORK_MDNS
    JsonBuilderI->Add(PM_JSON_FREEHEAP,       ESP.getFreeHeap());
    JsonBuilderI->Add(PM_JSON_VERSIONNAME,    pCONT_set->firmware_version.current.name_ctr);
    JsonBuilderI->Add_FV(PM_JSON_IPADDRESS,   PSTR("\"%d.%d.%d.%d\""), localip[0],localip[1],localip[2],localip[3]);
    JsonBuilderI->Add(PM_JSON_BOOTCOUNT,      pCONT_set->Settings.bootcount);
  return JsonBuilderI->End();

}


uint8_t mTelemetry::ConstructJSON_Debug_Pins(uint8_t json_level){ //BuildHealth

  char buffer[30];
  JsonBuilderI->Start();
  JBI->Add("flag_serial_set_tx_set",pCONT_pins-> flag_serial_set_tx_set);
    // JsonBuilderI->Level_Start(PM_JSON_GPIO);
    // for(uint16_t i=0;i<sizeof(pCONT_set->pin);i++){ 
    //   if(pCONT_pins->PinUsed(i)){ // skip pins not configured
    //     sprintf_P(buffer, PSTR("FUNC_%d"), i);
    //     JsonBuilderI->Add(buffer, pCONT_pins->GetPin(i));
    //   }
    // }
    // JsonBuilderI->Level_End();
    JsonBuilderI->Level_Start(PM_JSON_GPIO);
    for(uint16_t i=0;i<ARRAY_SIZE(pCONT_pins->pin_attached_gpio_functions);i++){ 
      if(pCONT_pins->PinUsed(pCONT_pins->pin_attached_gpio_functions[i])){ // skip pins not configured

      // AddLog(LOG_LEVEL_TEST, PSTR("buffer=%s %d %d %d"),
      // pCONT_pins->GetGPIOFunctionNamebyID_P(pCONT_pins->pin_attached_gpio_functions[i]),
      // pCONT_pins->pin_attached_gpio_functions[i],
      // pCONT_pins->GetPin(i),
      // i 
      // );


        sprintf_P(buffer, PSTR("%s"), pCONT_pins->GetGPIOFunctionNamebyID_P(pCONT_pins->pin_attached_gpio_functions[i]));
        JsonBuilderI->Add(buffer, pCONT_pins->GetPin(pCONT_pins->pin_attached_gpio_functions[i]));
      }
    }
    
    JsonBuilderI->Level_End();
    // JsonBuilderI->Level_Start(D_JSON_GPIO "_map");
    // for(uint16_t i=0;i<MAX_USER_PINS;i++){ 
    //   sprintf_P(buffer, PSTR("%d"),
      
    //   gpio_pin_by_index[i]
    //   //  i
    //    );
    //   JsonBuilderI->Add(buffer, pCONT_pins->GetPin(i));
    // }
    // JsonBuilderI->Level_End();

    // Debug by printing all arrays out
    JBI->Array_Start("pin_attached_gpio_functions");
    for(int i=0; i<ARRAY_SIZE(pCONT_pins->pin_attached_gpio_functions);i++)
      JBI->Add(pCONT_pins->pin_attached_gpio_functions[i]);
    JBI->Array_End();

    JBI->Array_Start("user_template_io");
    for(int i=0; i<ARRAY_SIZE(pCONT_set->Settings.user_template2.hardware.gp.io);i++)
      JBI->Add(pCONT_set->Settings.user_template2.hardware.gp.io[i]);
    JBI->Array_End();

    JBI->Array_Start("getpin");
    for(int i=0; i<ARRAY_SIZE(pCONT_pins->pin_attached_gpio_functions);i++)
      JBI->Add(pCONT_pins->GetPinWithGPIO(pCONT_pins->pin_attached_gpio_functions[i]));
    JBI->Array_End();





  return JsonBuilderI->End();

}


uint8_t mTelemetry::ConstructJSON_Debug_Template(uint8_t json_level){ //BuildHealth
  char buffer[50];
  JsonBuilderI->Start();
    JsonBuilderI->Add("Module" D_JSON_TEMPLATE,       pCONT_set->boot_status.module_template_parse_success?"Default":"Saved");
    JsonBuilderI->Add("Function" D_JSON_TEMPLATE,       pCONT_set->boot_status.function_template_parse_success);//?"Default":"Saved");

    JsonBuilderI->Add(PM_JSON_MODULENAME, pCONT_pins->AnyModuleName(pCONT_set->Settings.module, buffer, sizeof(buffer)));
    JsonBuilderI->Add(PM_JSON_MODULEID,   pCONT_set->Settings.module);
    JBI->Add("MyModuleType",pCONT_set->my_module_type);
    myio cmodule;
    pCONT_pins->TemplateGPIOs(&cmodule);
    // JsonBuilderI->Array_AddArray(PM_JSON_GPIO, cmodule.io, (uint8_t)sizeof(cmodule.io));
    JBI->Array_Start_P(PM_JSON_GPIO);
    for(int i=0;i<ARRAY_SIZE(cmodule.io);i++)
      JBI->Add(cmodule.io[i]);
    JBI->Array_End();
  return JsonBuilderI->End();
}


uint8_t mTelemetry::ConstructJSON_Debug_ModuleInterface(uint8_t json_level){ //BuildHealth

  JsonBuilderI->Start();
  
  #ifdef DEBUG_EXECUTION_TIME
    char buffer[50];
    JsonBuilderI->Level_Start(pCONT->GetModuleFriendlyName(pCONT->module_settings.list[ii], buffer));
      JsonBuilderI->Array_AddArray("average", pCONT->module_settings.execution_time_average_ms, sizeof(pCONT->module_settings.execution_time_average_ms));
      JsonBuilderI->Array_AddArray("max",     pCONT->module_settings.execution_time_max_ms,     sizeof(pCONT->module_settings.execution_time_max_ms));
    JsonBuilderI->Level_End();
  #endif

  JBI->Level_Start("ModuleSize");

  
  // for(uint8_t i=0;i<pCONT->module_settings.count;i++){
  //   JBI->Add_P(pCONT->GetModuleFriendlyName(pCONT->module_settings.list[i]),pCONT->GetClassSizeByID(pCONT->module_settings.list[i]));
  //   // if(pCONT->GetClassSizeByID(i)>10000){
  //   //   JBI->Add("bad",i);
  //   // }
  // }


  JBI->Level_End();


  return JsonBuilderI->End();
}











