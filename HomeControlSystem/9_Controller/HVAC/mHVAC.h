/*
  mHeating_Commands.cpp - Home Heating Controller

  Copyright (C) 2021  Michael

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MHEATING2_H
#define MHEATING2_H 0.4

#define D_UNIQUE_MODULE_CONTROLLER_HVAC_ID   131  // Unique value across all classes from all groups (e.g. sensor, light, driver, energy)
#define D_GROUP_MODULE_CONTROLLER_HVAC_ID    1    // Numerical accesending order of module within a group

/**
 * Moving forward, try making this heating work for all systems. "Heating" as a controller should accept any sensor, with any relays out
 * I will use this with one sensor and one relay to controller a room electric heater, this will be my development testbed
 * 
 * Create "Zones". Each will have its own temp, timers etc attached to it
 * Create heating methods as its own class
 * 
 * 
 * */

#include "1_TaskerManager/mTaskerManager.h"

#ifdef USE_MODULE_CONTROLLER_HVAC

#include "9_Controller/HVAC/mProgramTimer.h"
class ProgramTimer; //tmp fix
#include "9_Controller/HVAC/mProgramTemperatue.h"
class ProgramTemperature; //tmp fix


#include <NeoPixelBus.h>



   #define HEATING_DEVICE_MAX 4

#include <stdio.h>
#include <stdlib.h>

#include "2_CoreSystem/Time/mTime.h"

#include "2_CoreSystem/Logging/mLogging.h"





#define USE_FAILSAFES
#define USE_HVAC_TIMERS
#define USE_HVAC_TEMPS

// #define D_TASKNAME_HEATING "heating"

// #define WEB_HANDLE_HVAC_TIMER "heat_timer"

//disable  for debugging
#define ENABLE_RELAY_CONTROLS

// #define WEB_HANDLE_BUTTON_NAME_TEMP_SET "btte"
// #define WEB_HANDLE_BUTTON_NAME_TIMER_SET "btti"




#define D_HVAC_PROGRAM_TEMP "Program Temp > "
// #define D_HVAC_PROFILES "Profiles > "



//phase outstrcmp without case
#define D_HVAC_SENSOR_NAME_SHORT_DS_LOWERCASE "ds"
#define D_HVAC_SENSOR_NAME_SHORT_US_LOWERCASE "us"
#define D_HVAC_SENSOR_NAME_SHORT_WB_LOWERCASE "wb"
#define D_HVAC_SENSOR_NAME_SHORT_IH_LOWERCASE "ih"
#define D_HVAC_SENSOR_NAME_SHORT_TT_LOWERCASE "tt"
#define D_HVAC_SENSOR_NAME_SHORT_TM_LOWERCASE "tm"
#define D_HVAC_SENSOR_NAME_SHORT_TB_LOWERCASE "tb"
#define D_HVAC_SENSOR_NAME_SHORT_TO_LOWERCASE "to"



DEFINE_PGM_CTR(PM_MQTT_HANDLER_POSTFIX_TOPIC_PROGRAM_TIMERS_CTR) "program/timers";
DEFINE_PGM_CTR(PM_MQTT_HANDLER_POSTFIX_TOPIC_PROGRAM_TEMPS_CTR) "program/temps";
DEFINE_PGM_CTR(PM_MQTT_HANDLER_POSTFIX_TOPIC_PROGRAM_OVERVIEW_CTR) "program/overview";
DEFINE_PGM_CTR(PM_MQTT_HANDLER_POSTFIX_TOPIC_SENSOR_ZONE_CTR) "sensors/zone";
DEFINE_PGM_CTR(PM_MQTT_HANDLER_POSTFIX_TOPIC_ZONE_COLOUR_CTR) "sensors/zone/colours";
DEFINE_PGM_CTR(PM_MQTT_HANDLER_POSTFIX_TOPIC_RELAYS_CTR) "relays";


#define D_HVAC_SENSOR_NAME_SHORT_DS "DS"
#define D_HVAC_SENSOR_NAME_SHORT_US "US"
#define D_HVAC_SENSOR_NAME_SHORT_WB "WB"
#define D_HVAC_SENSOR_NAME_SHORT_IH "IH"
#define D_HVAC_SENSOR_NAME_SHORT_TT "TT"
#define D_HVAC_SENSOR_NAME_SHORT_TM "TM"
#define D_HVAC_SENSOR_NAME_SHORT_TB "TB"
#define D_HVAC_SENSOR_NAME_SHORT_TO "TO"


DEFINE_PGM_CTR(PM_HVAC_SENSOR_NAME_SHORT_DS_CTR)           D_HVAC_SENSOR_NAME_SHORT_DS;
DEFINE_PGM_CTR(PM_HVAC_SENSOR_NAME_SHORT_US_CTR)           D_HVAC_SENSOR_NAME_SHORT_US;
DEFINE_PGM_CTR(PM_HVAC_SENSOR_NAME_SHORT_WB_CTR)           D_HVAC_SENSOR_NAME_SHORT_WB;
DEFINE_PGM_CTR(PM_HVAC_SENSOR_NAME_SHORT_IH_CTR)           D_HVAC_SENSOR_NAME_SHORT_IH;
DEFINE_PGM_CTR(PM_HVAC_SENSOR_NAME_SHORT_TT_CTR)           D_HVAC_SENSOR_NAME_SHORT_TT;
DEFINE_PGM_CTR(PM_HVAC_SENSOR_NAME_SHORT_TM_CTR)           D_HVAC_SENSOR_NAME_SHORT_TM;
DEFINE_PGM_CTR(PM_HVAC_SENSOR_NAME_SHORT_TB_CTR)           D_HVAC_SENSOR_NAME_SHORT_TB;
DEFINE_PGM_CTR(PM_HVAC_SENSOR_NAME_SHORT_TO_CTR)           D_HVAC_SENSOR_NAME_SHORT_TO;

#define D_TEMP_MODE_OFF_CTR "Mode Off"

DEFINE_PGM_CTR(PM_TEMP_MODE_OFF_CTR)  D_TEMP_MODE_OFF_CTR;

#define D_HVAC_SENSOR_NAME_LONG_DS "Downstairs"
#define D_HVAC_SENSOR_NAME_LONG_US "Upstairs"
#define D_HVAC_SENSOR_NAME_LONG_WB "Boiler"
#define D_HVAC_SENSOR_NAME_LONG_IH "Immersion"
#define D_HVAC_SENSOR_NAME_LONG_TT "Tank Top"
#define D_HVAC_SENSOR_NAME_LONG_TM "Tank Middle"
#define D_HVAC_SENSOR_NAME_LONG_TB "Tank Bottom"
#define D_HVAC_SENSOR_NAME_LONG_TO "Tank Out"

// #define TEST_DEVICE_NAME


DEFINE_PGM_CTR(PM_HVAC_SENSOR_NAME_LONG_DS_CTR)           D_HVAC_SENSOR_NAME_LONG_DS;
DEFINE_PGM_CTR(PM_HVAC_SENSOR_NAME_LONG_US_CTR)           D_HVAC_SENSOR_NAME_LONG_US;
DEFINE_PGM_CTR(PM_HVAC_SENSOR_NAME_LONG_WB_CTR)           D_HVAC_SENSOR_NAME_LONG_WB;
DEFINE_PGM_CTR(PM_HVAC_SENSOR_NAME_LONG_IH_CTR)           D_HVAC_SENSOR_NAME_LONG_IH;
DEFINE_PGM_CTR(PM_HVAC_SENSOR_NAME_LONG_TT_CTR)           D_HVAC_SENSOR_NAME_LONG_TT;
DEFINE_PGM_CTR(PM_HVAC_SENSOR_NAME_LONG_TM_CTR)           D_HVAC_SENSOR_NAME_LONG_TM;
DEFINE_PGM_CTR(PM_HVAC_SENSOR_NAME_LONG_TB_CTR)           D_HVAC_SENSOR_NAME_LONG_TB;
DEFINE_PGM_CTR(PM_HVAC_SENSOR_NAME_LONG_TO_CTR)           D_HVAC_SENSOR_NAME_LONG_TO;

DEFINE_PGM_CTR(PM_HVAC_SCHEDULED_NAME_OFF_CTR)            D_JSON_OFF;
DEFINE_PGM_CTR(PM_HVAC_SCHEDULED_NAME_SET_CTR)            D_JSON_SCHEDULED_SET;
DEFINE_PGM_CTR(PM_HVAC_SCHEDULED_NAME_ON_CTR)             D_JSON_SCHEDULED_ON;
DEFINE_PGM_CTR(PM_HVAC_SCHEDULED_NAME_MANUAL_ON_CTR)      D_JSON_MANUAL_ON;


enum TEMP_MODE_IDS{
  TEMP_MODE_OFF_ID=0,
  TEMP_MODE_HVAC_ID,
  TEMP_MODE_MAINTAINING_ID,
  TEMP_MODE_SCHEDULED_ID,
  TEMP_MODE_SPLASH_RUN_TIME_ID,
  TEMP_MODE_LENGTH
};


enum SCH_MODE_IDS{
  SCHEDULED_OFF_ID=1,
  SCHEDULED_SET_ID,
  SCHEDULED_ON_ID,
  SCHEDULED_MANUAL_ON_ID
};
// Temp lookup table
// [15,16,17]
// if(15,16)
//   seconds = 120
// if(16,17)
//   seconds = 120

#define DEVICE_ID_TOTAL 4
enum DEVICE_HVAC_ID{
    DEVICE_US_ID=0,
    DEVICE_DS_ID=1,
    DEVICE_IH_ID=2,
    DEVICE_WB_ID=3
};

/**
 * Instead of numerical IDs, BITS_PACKED allows exclusive bit OR
 * */
enum ZONE_MODES_8BITS_PACKED{
  ZONE_MODE_DISABLED_8BITS=0, // no outputs set
  ZONE_MODE_HEAT_8BITS=1,
  ZONE_MODE_COOL_8BITS=2,
  ZONE_MODE_LENGTH_8BITS=128
};

//later another "sensor type" could be MQTT topic, ie if I have remote sensors, also http

#define MAX_ZONES 4

class mHVAC :
  public mTaskerInterface
{

  private:
  public:
    mHVAC(){};
    
    static const char* PM_MODULE_CONTROLLER_HVAC_CTR;
    static const char* PM_MODULE_CONTROLLER_HVAC_FRIENDLY_CTR;
    PGM_P GetModuleName(){          return PM_MODULE_CONTROLLER_HVAC_CTR; }
    PGM_P GetModuleFriendlyName(){  return PM_MODULE_CONTROLLER_HVAC_FRIENDLY_CTR; }
    uint8_t GetModuleUniqueID(){ return D_UNIQUE_MODULE_CONTROLLER_HVAC_ID; }

    #ifdef USE_DEBUG_CLASS_SIZE
    uint16_t GetClassSize(){
      return sizeof(mHVAC);
    };
    #endif

    // Leave as single zone for now, scale to array

    struct Zone{
      ProgramTemperature* program_temp_method = nullptr;
      ProgramTimer*       program_timer_method = nullptr;
      /**
       * @brief active mode set, heating, cool, off
       * */
      uint8_t active_mode = 0;
      /**
       * @brief modes that are allowed.. maybe contain by driver type?
       * bit0 - heating
       * bit1 - cool
       * bit2 - ?
       * */
      uint8_t bitpacked_modes_enabled = 0x00;

      struct SENSOR_STATE
      {
        //Add ROC here?
        float temperature;
        float humidity;
        /**
         * @brief This is the sensor module id (ie dht, db18s20, bme) so it knows which class to ask for temp readings 
         * */
        uint16_t module_id = 0;
        /**
         * @brief The index within the module I am using. This will need to be found using the unique name
         * */
        uint8_t index = 0;
      }sensor;
      struct DRIVER_STATE
      {
        /**
         * @brief Store multiple modules (Drivers) incase the devices are not the same type (eg, Relays, PWM, iFans03)
         * */
        std::vector<uint16_t> module_ids;
        /**
         * @brief Store multiple indexes if more than one driver is needed per zone (ie, relay for heating and another for cooling)
         * */
        std::vector<uint8_t> index;
        /**
         * @brief Driver type, what the thing attempts to control not what it is (ie, Relay can control lights, heaters, coolers etc, so I want to know what the purpose of the relay is)
         * */
        std::vector<uint8_t> driver_type;
      }output;
    }zone[MAX_ZONES];


    void Pre_Init(void);
    void init(void);    
    
    struct SETTINGS{
      uint8_t  fEnableModule = true;
      uint8_t active_zones = 0;
    }settings;

    // #include "9_Controller/Heating/mHeating_Web.h"

    void init_program_timers();
    void init_program_temps();
    void init_program_scheduling(void);

    // enum SENSORDB18_IDS{
    //   ID_DB18_DS=0,
    //   ID_DB18_US,
    //   ID_DB18_WB,
    //   ID_DB18_IH,
    //   ID_DB18_TT,
    //   ID_DB18_TM,
    //   ID_DB18_TB,
    //   ID_DB18_TO
    // };
        
    // enum SENSORDHT_IDS{
    //   ID_DHT_DS=0,
    //   ID_DHT_US,
    // };

    // enum DEVICELIST_ALL_IDS{
    //   DEVICELIST_RELAY_US=0,
    //   DEVICELIST_RELAY_DS,
    //   DEVICELIST_RELAY_IH,
    //   DEVICELIST_RELAY_WB,
    //   DEVICELIST_CLIMATE_US,
    //   DEVICELIST_CLIMATE_DS,
    //   DEVICELIST_WATER_US,
    //   DEVICELIST_WATER_DS,
    //   DEVICELIST_WATER_IH,
    //   DEVICELIST_WATER_WB,
    //   DEVICELIST_WATER_TT,
    //   DEVICELIST_WATER_TM,
    //   DEVICELIST_WATER_TB,
    //   DEVICELIST_WATER_TO,
    //   DEVICELIST_LENGTH
    // };

    // enum CLIMATESENSOR_DHT_IDS{
    //   DHT_DOWNSTAIRS_ID=0,
    //   DHT_UPSTAIRS_ID,
    //   DHT_COUNT_ID
    // };

    void Web_Append_Program_Timers_Buttons();
    void Web_Append_Program_Temps_Buttons();

    void WebPage_Root_SendBody();
    void WebSendBody_Liveview();

    void WebAppend_Root_Draw_Program_Buttons();
    void WebAppend_Root_Draw_PageTable();


    struct HEATING_STATUS{
      char message_ctr[100];
      char message_len = 0;
    }heating_status[HEATING_DEVICE_MAX];


    #ifdef USE_MODULE_NETWORK_WEBSERVER
    void WebPage_Root_AddHandlers();
    void WebAppend_Root_Status_Table();
    void Web_Root_Draw(AsyncWebServerRequest *request);
    #endif // USE_MODULE_NETWORK_WEBSERVER


    // uint8_t time_map_timers_upstairs[HEATING_DEVICE_MAX];// = {0, 60, 90, 120};
    // uint8_t time_map_timers_downstairs[HEATING_DEVICE_MAX];// = {0, 60, 90, 120};
    // uint8_t time_map_timers_immersion[HEATING_DEVICE_MAX];// = {0, 60, 90, 120};
    // uint8_t time_map_timers_boiler[HEATING_DEVICE_MAX];// = {0, 60, 90, 120};
    // uint8_t    time_map_temps_upstairs[HEATING_DEVICE_MAX];//                  = {0, 20, 23, 25};
    // uint8_t    time_map_temps_downstairs[HEATING_DEVICE_MAX];//                = {0, 20, 23, 25};
    // uint8_t    time_map_temps_immersion[HEATING_DEVICE_MAX];//                 = {0, 30, 40, 50};
    // uint8_t    time_map_temps_boiler[HEATING_DEVICE_MAX];//                    = {0, 30, 40, 50};

    void HandleTimerConfiguration(void);
    void HandleProgramTimerConfiguration();

    // *************** TIMERS ****************************************************************************************************
 
    // struct HEATING_DEVICE_TIMERS{
    //   uint8_t device_name;
    //   int16_t time_minutes_on;      
    //   int16_t time_minutes_on_start;
    //   int16_t ischanged;
    //   int8_t user_id = -1; // who asked, -1 if not known
    //   uint8_t mapped_defaults[HEATING_DEVICE_MAX];
    // }program_timers[HEATING_DEVICE_MAX];

    // uint8_t isanychanged_timers=0;
    // void HeatingTimers(void);
    // uint8_t fForceHeatingTimerUpdate = false;

    // void AddToHardwareMessage();

    // *************** TEMPS/SCHEDULES ****************************************************************************************************

    // struct HEATING_DEVICE_TEMPS{
    //   uint8_t device_name; //phase out
    //   struct TIMERRUNNING{
    //     int16_t on=-1;
    //     int16_t limit=60;
    //   }time_running;
    //   struct TIMEMAINTAINING{ // all in minutes
    //     int16_t on=-1;
    //     int16_t limit=60;
    //   }time_maintaining;
    //   struct TIMETOHEAT{
    //     int16_t minutes=-1;
    //   }time_to_heat;
    //   struct SCHEDULE{ //change schedule to be MODE/Prorgame type
    //     struct datetime ontime;
    //     struct datetime untilontime;
    //     struct datetime offtime;
    //     uint8_t fHasRun = false;
    //     uint8_t mode_sch = SCHEDULED_OFF_ID;
    //     uint8_t mode_sch_aftersplash = SCHEDULED_OFF_ID;
    //     uint8_t fRunning = false;
    //   }schedule;
    //   struct TEMP{
    //     float current=0;
    //     float error=0;
    //     float desired=0;
    //     uint8_t mapped_defaults[4];
    //   }temp;
    //   struct STATUS{
    //   //   struct DATA{
    //   //     uint8_t ctr[80];
    //   //     uint8_t len = 0;
    //   //   }data;
    //     uint8_t mode = 0;
    //   //   uint8_t mode_next = 0; //stored for after splash
    //   //   uint32_t tSplashTime = millis();
    //   //   uint8_t msSplashtime = 2000; //seconds
    //   }status;
    //   // struct MQTT{
    //   //   uint8_t fForceUpdate = false;
    //   //   uint32_t tSavedUpdate = millis();
    //   //   uint8_t rate = 5;
    //   // }mqtt;
    //   // int8_t user_id = -1; // who asked, -1 if not known
    // }program_temps[HEATING_DEVICE_MAX];

    // void SubTask_HeatingTemps_StatusMessage();
    // // void SubTask_HeatingTemps(void);
    // // void SubTask_HeatingTemps_Ticker();
    // void HeatingTemps(void);
    // // uint8_t fForceHeatingTempsUpdate = false;
    // uint8_t fForceHeatingTempsUpdate = false;
    // uint8_t fRunTemp = false;
    // uint8_t fHeatingTempsChanged = false;
    // // uint8_t fForceHeatingTempsUpdateMQTT = true;
    // uint8_t CheckIfROCExceedsNegativeLimit(uint8_t id);

    //   *******************************STATUS************************************************************

//"ConstructPretty_StatusMessage" and use the normal buffer (though this wont work unless its made inline for sending too)
    // #define STATUS_MESSAGE_MAX_LENGTH 200
    // struct STATUS_MESSAGE_S{
    //   //make function that appends pretty simple message
    //   char ctr[STATUS_MESSAGE_MAX_LENGTH];
    //   uint8_t len = 0;
    //   uint8_t importance = 0; //0 low, 1 med, 2 high
    // }status_message;


void Every_Second();

// ***************************************** RGB COLOURS ***********************************************/

    // #define LED_SIDE_VALUE 10 //brightness
    // #define LED_PANEL_PIXELS 9
    // uint8_t brightnessbycolour[12];
    // uint32_t tLED;
    // enum LED_NAME{LED_NAME_DOWN_LEFT=0,LED_NAME_DOWN_RIGHT=1,LED_NAME_UP_RIGHT=2,LED_NAME_UP_LEFT=3,LED_NAME_WB=4,LED_NAME_IH=5,LED_NAME_DS=6,LED_NAME_US=7};

    // uint8_t GetPixelNumByName(const char* in);
    // uint8_t fUpDownMode = SHOW_TANK;
    // enum PANELMODEL{SHOW_TANK=1,SHOW_STORED_COLOURS,SHOW_OFF=3};
    // void ConstructJSON_RGBPanelSettings();

    // uint8_t GetRGBUpDownModeIDByName(const char* in);

    int mapHeatingTempToHueColour(int val);
    int mapHeatingTempToBrightness(int val);
    // uint8_t ConstructSON_PipeTempsByColours(uint8_t json_level);
    // void SubTasker_UnderStairsPixels();
    // uint32_t tLED2;
    // void SubTasker_TopDownPixels();
    // uint8_t toggle_sender = false;
    

    // uint8_t fForceUpdatePanel= true;
    // uint32_t tSaved,tSaved2;

    // struct colour{
    //   uint16_t h;
    //   uint8_t s,v;
    // };

    // struct STOREDINFO{
    //   float temp[12];
    //   uint8_t state[12];
    // }stored_side;
    // struct STOREDINFO stored_all;
    // struct STOREDINFO stored_new;

    // struct PIXEL{
    //   colour c;
    // }pixel[LED_PANEL_PIXELS];

    // *************** RELAYS ****************************************************************************************************

    enum RELAY_STATES_ON{RELAY_STATE_OFF=0,RELAY_STATE_ON};
    void SetHeatingRelay(uint8_t device_id, uint8_t state);
    uint8_t GetHeatingRelay(uint8_t device_id);
    uint8_t GetAnyHeatingRelay();

    //PHASE OUT INTO RELAY DRIVERS (needs to be working first)
    // #ifndef ENABLE_DEVFEATURE_MIGRATE_RELAY_CONTROLS
    // struct HEATING_DEVICE_RELAYS{
    //   // struct datetime ontime;
    //   // struct datetime offtime; // can be used to find out how long its been off and "cold" for
    //   int16_t time_minutes_on;
    //   int16_t ischanged;
    // }heating_device_relays[4];
    // #endif // ENABLE_DEVFEATURE_MIGRATE_RELAY_CONTROLS

    // void MQQTSendHeatingRelaysIfChanged(void);
    uint8_t ConstructJSON_HeatingRelays(uint8_t json_level = 0);
    // uint32_t tSavedHeatingRelays;

    // *************** PROGRAMS/GENERAL ****************************************************************************************************

    // enum ACTICEPROGRAMMODE{ACTIVEP_OFF=0,ACTIVEP_ON=1,ACTIVEP_SCHEDULED=2};
    // struct ACTIVEPRORGAMS2{
    //   struct PROGRAM{
    //     uint8_t state = 0;
    //   };
    //   PROGRAM relays;
    //   PROGRAM timers;
    //   PROGRAM temps;
    // }activeprograms[HEATING_DEVICE_MAX];
    const char* GetActiveProgramNameCtrbyID(uint8_t activeprogram_id, char* buffer, uint8_t buflen);

    // void SubTasker_MQTTSender(void);

    // void SendVoiceSettings(void);

    int8_t Tasker(uint8_t function, JsonParserObject obj = 0);
    
    // int8_t CheckAndExecute_JSONCommands();
    void parse_JSONCommand(JsonParserObject obj);
    
    void CommandSet_ProgramTimer_TimeOn(uint8_t zone_id, uint8_t value);
    void CommandSet_ProgramTemperature_Desired_Temperature(uint8_t zone_id, float value);
    void CommandSet_ProgramTemperature_Schedule_Mode(uint8_t zone_id, int8_t value);
    void CommandSet_ProgramTemperature_TimeRunning_Limit(uint8_t zone_id, uint8_t value); 
    void CommandSet_ProgramTemperature_Mode(uint8_t zone_id, uint8_t mode);


    void SubTasker_HeatingTimers(void);
    void SubTasker_HeatingTemps(void);
    void SubTasker_ScheduledEvents(void);

    const char* GetScheduleNameCtrbyID(uint8_t mode, char* buffer, uint8_t buflen);
    const char* GetDeviceNameLongbyIDCtr(uint8_t device_id, char* buffer, uint8_t buflen);
    const char* GetDeviceNameUpperCaseCtrbyID(uint8_t device_id, char* buffer, uint8_t buflen);

    void SetHighestImportance(uint8_t* importanceset, int8_t thisvalue);

    void SetHeater(uint8_t device_name, uint8_t state);




    /**
     * This will trigger a zone to be set as active, and internally will decide if that should heat or cool depending on zone mode
     * */
    void SetZoneActive(uint8_t zone_id, uint8_t state = 0);
















    // int8_t GetHeater(uint8_t device);
    int8_t Tasker_PredictManualHeating();
    // void SendVoiceMessage(unsigned char device_name, unsigned char state);
    // void SendFormattedVoiceMessage(unsigned char device_name, unsigned char state);
    // void SendMQTTAlertOnChangeofState(uint8_t device, uint8_t state);

    #define FAILSAFE_MINUTES_WARNING 60*5
    #define FAILSAFE_MINUTES_ERROR 60*10

    // void MQQTSendPipesTempsByColoursIfChanged(void);

    uint8_t rateSavedSendActive = 1;

    const char* GetTempActiveProgramByDeviceIDCtr(uint8_t device, char* buffer, uint8_t buflen);
    
    // uint32_t tSavedHeatingTemps,tSavedHeatingTemps2,tSavedHeatingTemps3;

    // const char* GetDeviceNamebyIDCtr(uint8_t name, char* buffer, uint8_t buflen);
    int8_t GetScheduleModeIDByCtr(const char* c);
    // int8_t GetDeviceIDbyName(const char* c);
    // int8_t GetUserIDbyName(const char* c);

    // const char* GetUserNameByID(int8_t id, char* buffer);// = nullptr);

    struct FAILSAFES{
      // uint32_t tSaved;
      int tSavedMinuteFailSafe;
    }failsafes;

    // int8_t SubContructCtr_HardwareStatus();
    // int8_t SubContructCtr_HardwareStatus_Long();

    // uint32_t tSavedSendActive;
    // unsigned long tSavedSendClimate;
    // unsigned long tSavedSlow;
    // uint32_t tSavedSendRateOfChange=millis();
    // uint8_t mSavedROC10m=0;
    // uint32_t tSavedForceUpdate = millis();
    // int cTicker;
    // uint8_t fSendSingleFunctionData = false;
    // const char* GetTempModeByDeviceIDCtr(uint8_t device, char* buffer, uint8_t buflen);

    // int8_t GetWaterSensorIDbyShortName(const char* c);
    // float GetWaterTempsRawByID(uint8_t device_id);

    const char* GetSensorNameByID(uint8_t sensor_id, char* buffer, uint8_t buflen);
    const char* GetSensorNameLongbyID(uint8_t sensor_id, char* buffer, uint8_t buflen);

    uint8_t ConstructJSON_ProgramTimers(uint8_t json_level = 0);
    uint8_t ConstructJSON_ProgramTemps(uint8_t json_level = 0);

    uint8_t ConstructJSON_ZoneSensors(uint8_t json_level = 0);
    uint8_t ConstructJSON_ZoneSensors_ROC1m(uint8_t json_level = 0);
    uint8_t ConstructJSON_ZoneSensors_ROC10m(uint8_t json_level = 0);

    uint8_t ConstructJSON_ProgramActive(uint8_t json_level = 0);
    uint8_t ConstructJSON_HardwareInfo(uint8_t json_level = 0);

    uint32_t tSavedSendRateOfChange10s;

    enum VOICEREQUEST_ID{VOICEREQUEST_WATERTEMP_ID=1,VOICEREQUEST_CLIMATETEMP_ID,VOICEREQUEST_SCHEDULE_ID,VOICEREQUEST_OVERVIEW_ID};
    int8_t GetVoiceRequestIDbyName(const char* c);

    int8_t GetClimateSensorIDbyShortName(const char* c);
    const char* GetClimateSensorNameLongbyIDCtr(uint8_t sensor_id, char* buffer, uint8_t buflen);
    float GetClimateTempsRawByID(uint8_t sensor_id);

    uint8_t ConstructJSON_Settings(uint8_t json_method);


    void FunctionHandler_Init();
    void FunctionHandler_Loop();
  

    struct functionhandler<mHVAC> functionhandler_status_message;
    void FunctionHandler_Program_Status();
    struct functionhandler<mHVAC> functionhandler_failsafe;
    void FunctionHandler_FailSafe(void);
    struct functionhandler<mHVAC> functionhandler_hvac_profiles;
    void FunctionHandler_HVAC_Profiles(void);
    struct functionhandler<mHVAC> functionhandler_relay_status;
    void FunctionHandler_Relay_Status(void);
    struct functionhandler<mHVAC> functionhandler_programs_timers;
    void FunctionHandler_Programs_Timers(void);
    struct functionhandler<mHVAC> functionhandler_programs_temps;
    void FunctionHandler_Programs_Temps(void);

    struct functionhandler<mHVAC>* functionhandler_list[5] = {
      &functionhandler_failsafe,
      &functionhandler_status_message,
      #ifdef USE_HVAC_PROFILE_ESTIMATION
      &functionhandler_hvac_profiles,
      #endif //#ifdef USE_HVAC_PROFILE_ESTIMATION
      &functionhandler_relay_status,
      &functionhandler_programs_timers,
      &functionhandler_programs_temps
    };
    

  
  #ifdef USE_MODULE_NETWORK_MQTT

    void MQTTHandler_Init();
    void MQTTHandler_Set_fSendNow();
    void MQTTHandler_Set_TelePeriod();
    
    void MQTTHandler_Sender(uint8_t mqtt_handler_id = MQTT_HANDLER_ALL_ID);
    
    // Extra module only handlers
    enum MQTT_HANDLER_MODULE_IDS{  // Sensors need ifchanged, drivers do not, just telemetry
      MQTT_HANDLER_MODULE_PROGRAM_TIMERS_IFCHANGED_ID = MQTT_HANDLER_LENGTH_ID,
      MQTT_HANDLER_MODULE_PROGRAM_TIMERS_TELEPERIOD_ID,
      MQTT_HANDLER_MODULE_PROGRAM_TEMPS_IFCHANGED_ID,
      MQTT_HANDLER_MODULE_PROGRAM_TEMPS_TELEPERIOD_ID,
      MQTT_HANDLER_MODULE_PROGRAM_OVERVIEW_IFCHANGED_ID,
      MQTT_HANDLER_MODULE_PROGRAM_OVERVIEW_TELEPERIOD_ID,
      MQTT_HANDLER_MODULE_SENSOR_ZONE_IFCHANGED_ID,
      MQTT_HANDLER_MODULE_SENSOR_ZONE_TELEPERIOD_ID,
      MQTT_HANDLER_MODULE_SENSOR_ZONE_ROC1M_ID,
      MQTT_HANDLER_MODULE_SENSOR_ZONE_ROC10M_ID,
      // MQTT_HANDLER_MODULE_SENSOR_PIPES_COLOURS_IFCHANGED_ID,
      // MQTT_HANDLER_MODULE_SENSOR_PIPES_COLOURS_TELEPERIOD_ID,
      MQTT_HANDLER_MODULE_DRIVERS_RELAYS_IFCHANGED_ID,
      MQTT_HANDLER_MODULE_DRIVERS_RELAYS_TELEPERIOD_ID,
      MQTT_HANDLER_MODULE_LENGTH_ID, // id count
    };

    struct handler<mHVAC> mqtthandler_settings_teleperiod;
    struct handler<mHVAC> mqtthandler_program_timers_ifchanged;
    struct handler<mHVAC> mqtthandler_program_timers_teleperiod;
    struct handler<mHVAC> mqtthandler_program_temps_ifchanged;
    struct handler<mHVAC> mqtthandler_program_temps_teleperiod;
    struct handler<mHVAC> mqtthandler_program_overview_ifchanged;
    struct handler<mHVAC> mqtthandler_program_overview_teleperiod;
    struct handler<mHVAC> mqtthandler_sensor_zone_ifchanged;
    struct handler<mHVAC> mqtthandler_sensor_zone_teleperiod;
    struct handler<mHVAC> mqtthandler_sensor_zone_roc1m;
    struct handler<mHVAC> mqtthandler_sensor_zone_roc10m;
    // struct handler<mHVAC> mqtthandler_sensor_pipes_colours_ifchanged;
    // struct handler<mHVAC> mqtthandler_sensor_pipes_colours_teleperiod;
    struct handler<mHVAC> mqtthandler_relays_ifchanged;
    struct handler<mHVAC> mqtthandler_relays_teleperiod;
  
  struct handler<mHVAC>* mqtthandler_list[13] = {
    &mqtthandler_settings_teleperiod,
    &mqtthandler_program_timers_ifchanged,
    &mqtthandler_program_timers_teleperiod,
    &mqtthandler_program_temps_ifchanged,
    &mqtthandler_program_temps_teleperiod,
    &mqtthandler_program_overview_ifchanged,
    &mqtthandler_program_overview_teleperiod,
    &mqtthandler_sensor_zone_ifchanged,
    &mqtthandler_sensor_zone_teleperiod,
    &mqtthandler_sensor_zone_roc1m,
    &mqtthandler_sensor_zone_roc10m,
    // &mqtthandler_sensor_pipes_colours_ifchanged,
    // &mqtthandler_sensor_pipes_colours_teleperiod,
    &mqtthandler_relays_ifchanged,
    &mqtthandler_relays_teleperiod
  };

  #endif // USE_MODULE_NETWORK_MQTT


};

#endif

#endif
