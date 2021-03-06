
//#ifdef ESP8266
#ifndef _MTELEMETRY_H_
#define _MTELEMETRY_H_

#define D_UNIQUE_MODULE_CORE_TELEMETRY_ID 4

#include "2_CoreSystem/mBaseConfig.h"

#include "2_CoreSystem/Support/mSupport.h"

#include "2_CoreSystem/JSON/mJSON.h"

#include "3_Network/MQTT/mMQTT.h"


#include "2_CoreSystem/Logging/mLogging.h"

#include "1_TaskerManager/mTaskerManager.h"


//#include "//2_CoreSystem/Languages/mLanguage.h"
#include "2_CoreSystem/HardwareTemplates/mHardwareTemplates.h"

#ifdef ESP8266
  #include <ESP8266WiFi.h>            // Wifi, MQTT, Ota, WifiManager
  #include <ESP8266httpUpdate.h>
#endif

#ifdef ESP32
#include <WiFi.h>
#ifdef USE_MODULE_NETWORK_WEBSERVER
  #include <AsyncTCP.h>
  #include <ESPAsyncWebServer.h>
#endif // DISABLE_NETWORK
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#ifdef USE_MODULE_NETWORK_WEBSERVER
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#endif
#endif





#include "2_CoreSystem/Time/mTime.h"

enum HARDWARE_STATUS_IMPORTANCE_IDS{
  // No risk to remain on
  HARDWARE_STATUS_IMPORTANCE_LOW_ID=0,
  // RGB leds, not high voltage
  HARDWARE_STATUS_IMPORTANCE_MEDIUM_ID,
  // Plugs/sockets, mains running
  HARDWARE_STATUS_IMPORTANCE_HIGHEST_ID,
};


/*********************************************************************************************\
 * Watchdog extension (https://github.com/esp8266/Arduino/issues/1532)
\*********************************************************************************************/

#include <Ticker.h>


#include "1_TaskerManager/mTaskerInterface.h"

class mTelemetry :
  public mTaskerInterface
{
  public:
    mTelemetry(){};
    
    int8_t Tasker(uint8_t function, JsonParserObject obj = 0);
    void init(void);
    void WebPage_Root_AddHandlers();

    

    static const char* PM_MODULE_CORE_TELEMETRY_CTR;
    static const char* PM_MODULE_CORE_TELEMETRY_FRIENDLY_CTR;
    PGM_P GetModuleName(){ return PM_MODULE_CORE_TELEMETRY_CTR; }
    PGM_P GetModuleFriendlyName(){ return PM_MODULE_CORE_TELEMETRY_FRIENDLY_CTR; }
    uint8_t GetModuleUniqueID(){ return D_UNIQUE_MODULE_CORE_TELEMETRY_ID; }


    #ifdef USE_DEBUG_CLASS_SIZE
    uint16_t GetClassSize(){
      return sizeof(mTelemetry);
    };
    #endif
    void parse_JSONCommand(JsonParserObject obj);

    uint8_t ConstructJSON_Health(uint8_t json_level);
    uint8_t ConstructJSON_Settings(uint8_t json_level);
    uint8_t ConstructJSON_Firmware(uint8_t json_level);
    uint8_t ConstructJSON_Log(uint8_t json_level);
    uint8_t ConstructJSON_Memory(uint8_t json_level);
    uint8_t ConstructJSON_Network(uint8_t json_level);
    uint8_t ConstructJSON_MQTT(uint8_t json_level);
    uint8_t ConstructJSON_Time(uint8_t json_level);
    uint8_t ConstructJSON_Devices(uint8_t json_level);
    uint8_t ConstructJSON_Reboot(uint8_t json_level);
    #ifdef ENABLE_MQTT_DEBUG_TELEMETRY
    uint8_t ConstructJSON_Debug_Pins(uint8_t json_level);
    uint8_t ConstructJSON_Debug_Template(uint8_t json_level);
    uint8_t ConstructJSON_Debug_ModuleInterface(uint8_t json_level);
    uint8_t ConstructJSON_Debug_Minimal(uint8_t json_level);
    #endif

  #ifdef USE_MODULE_NETWORK_WEBSERVER
    void Web_Status_Telemetry_Health_JSON(AsyncWebServerRequest *request);
    void Web_Status_Telemetry_Settings_JSON(AsyncWebServerRequest *request);
    void Web_Status_Telemetry_Firmware_JSON(AsyncWebServerRequest *request);
    void Web_Status_Telemetry_Log_JSON(AsyncWebServerRequest *request);
    void Web_Status_Telemetry_Memory_JSON(AsyncWebServerRequest *request);
    void Web_Status_Telemetry_Network_JSON(AsyncWebServerRequest *request);
    void Web_Status_Telemetry_MQTT_JSON(AsyncWebServerRequest *request);
    void Web_Status_Telemetry_Time_JSON(AsyncWebServerRequest *request);
    void Web_Status_Telemetry_Devices_JSON(AsyncWebServerRequest *request);
    void Web_Status_Telemetry_Reboot_JSON(AsyncWebServerRequest *request);
    void Web_Status_Telemetry_Debug_Minimal_JSON(AsyncWebServerRequest *request);
    void Web_Status_Telemetry_Debug_Pins_JSON(AsyncWebServerRequest *request);
    void Web_Status_Telemetry_Debug_Template_JSON(AsyncWebServerRequest *request);
    void Web_Status_Telemetry_Debug_ModuleInterface_JSON(AsyncWebServerRequest *request);
    #endif // #ifdef USE_MODULE_NETWORK_WEBSERVER
    
    #ifdef ENABLE_DEVFEATURE_HARDWARE_STATUS
    #define HARDWARE_STATUS_MAX_LENGTH 200
    struct STATUSHARDWARE{
      //make function that appends pretty simple message
      char ctr[HARDWARE_STATUS_MAX_LENGTH];
      uint8_t len = 0;
      uint8_t importance = 0; //0 low, 1 med, 2 high
    }hardwarestatus;
    void ConstructCtr_HardwareStatus();
    #endif // ENABLE_DEVFEATURE_HARDWARE_STATUS

    // uint16_t wifi_reconnects_counter = 0;

    void Init();

    // #define HARDWARE_STATUS_OFFSET_INDEX MQTT_MAX_PACKET_SIZE/2

    // uint8_t fParseTasmotaCommand = false;

    // uint32_t tSavedTest;

    // uint32_t loop_delay_temp = 100;


  #ifdef USE_MODULE_NETWORK_MQTT
  
    //use new syntax
    enum STATUS_SYSTEM_IDS{
      MQTT_HANDLER_SYSTEM_ALL_ID = 0,
      MQTT_HANDLER_SYSTEM_HEALTH_ID, // To align with "status #" type commands
      MQTT_HANDLER_SYSTEM_SETTINGS_ID,
      MQTT_HANDLER_SYSTEM_PARAMETERS_ID,
      MQTT_HANDLER_SYSTEM_LOG_ID,
      MQTT_HANDLER_SYSTEM_FIRMWARE_ID,
      MQTT_HANDLER_SYSTEM_MEMORY_ID,
      MQTT_HANDLER_SYSTEM_NETWORK_ID,
      MQTT_HANDLER_SYSTEM_MQTT_ID,
      MQTT_HANDLER_SYSTEM_TIME_ID,
      MQTT_HANDLER_SYSTEM_DEVICES_ID,
      MQTT_HANDLER_SYSTEM_REBOOT_ID,
      MQTT_HANDLER_SYSTEM_REBOOT_EVENT_ID,
      #ifdef ENABLE_MQTT_DEBUG_TELEMETRY
        MQTT_HANDLER_SYSTEM_DEBUG_PINS_ID,
        MQTT_HANDLER_SYSTEM_DEBUG_TEMPLATE_ID,
        MQTT_HANDLER_SYSTEM_DEBUG_MODULEINTERFACE_ID,
        MQTT_HANDLER_SYSTEM_DEBUG_MINIMAL_ID,
      #endif
      MQTT_HANDLER_SYSTEM_SYSTEM_LENGTH_ID // last holds length      
    };

    
    void MQTTHandler_Init();
    void MQTTHandler_Set_fSendNow();
    void MQTTHandler_Set_TelePeriod();
    void MQTTHandler_Sender(uint8_t status_id = MQTT_HANDLER_SYSTEM_ALL_ID);

    handler<mTelemetry> mqtthandler_health;
    handler<mTelemetry> mqtthandler_settings;
    handler<mTelemetry> mqtthandler_log;
    handler<mTelemetry> mqtthandler_firmware;
    handler<mTelemetry> mqtthandler_memory;
    handler<mTelemetry> mqtthandler_network;
    handler<mTelemetry> mqtthandler_mqtt;
    handler<mTelemetry> mqtthandler_time;
    handler<mTelemetry> mqtthandler_devices;
    handler<mTelemetry> mqtthandler_reboot;
    handler<mTelemetry> mqtthandler_reboot_event;
    #ifdef ENABLE_MQTT_DEBUG_TELEMETRY
      handler<mTelemetry> mqtthandler_debug_pins;
      handler<mTelemetry> mqtthandler_debug_template;
      handler<mTelemetry> mqtthandler_debug_moduleinterface;
      handler<mTelemetry> mqtthandler_debug_minimal;
    #endif
    
  struct handler<mTelemetry>* mqtthandler_list[15] = {
    &mqtthandler_health, &mqtthandler_settings,
    &mqtthandler_log, &mqtthandler_firmware, &mqtthandler_memory,
    &mqtthandler_network, &mqtthandler_mqtt, &mqtthandler_time, 
    &mqtthandler_devices, &mqtthandler_reboot, &mqtthandler_reboot_event,
    #ifdef ENABLE_MQTT_DEBUG_TELEMETRY
      &mqtthandler_debug_pins, &mqtthandler_debug_template,
      &mqtthandler_debug_moduleinterface, &mqtthandler_debug_minimal
    #endif
  };

#endif // USE_MODULE_NETWORK_MQTT

};





#endif  // _SONOFF_H_
//#endif