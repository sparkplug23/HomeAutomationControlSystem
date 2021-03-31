#ifndef _MODULE_DRIVERS_LEDS_H
#define _MODULE_DRIVERS_LEDS_H 0.1

#include "1_TaskerManager/mTaskerManager.h"

/**
 * This module will allow status leds, control of basic digitalio pins/pwm for controlling leds using pwm driver
 * */

#ifdef USE_MODULE_DRIVERS_LEDS  //rename as "custom" as controllers

class mStatusLEDs {

  private:
  public:
    mStatusLEDs(){};
    int8_t Tasker(uint8_t function);

    void init(void);
    void pre_init(void);

    struct SETTINGS{
      uint8_t fEnableSensor = false;
    }settings;

    void EveryLoop();

    uint8_t ConstructJSON_Settings(uint8_t json_method = 0);
    uint8_t ConstructJSON_Sensor(uint8_t json_method = 0);
  
    void MQTTHandler_Init();
    void MQTTHandler_Set_fSendNow();
    void MQTTHandler_Set_TelePeriod();
    void MQTTHandler_Sender(uint8_t mqtt_handler_id = MQTT_HANDLER_ALL_ID);
    
    struct handler<mStatusLEDs> mqtthandler_settings_teleperiod;
    struct handler<mStatusLEDs> mqtthandler_sensor_ifchanged;
    struct handler<mStatusLEDs> mqtthandler_sensor_teleperiod;

    // No specialised payload therefore use system default instead of enum
    const uint8_t MQTT_HANDLER_MODULE_LENGTH_ID = MQTT_HANDLER_LENGTH_ID;
    
};

#endif

#endif