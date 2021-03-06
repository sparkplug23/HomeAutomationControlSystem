#ifndef _USE_MODULE_DRIVERS_CAMERA_OV2640_H
#define _USE_MODULE_DRIVERS_CAMERA_OV2640_H 0.1

#define D_UNIQUE_MODULE_DRIVERS_CAMERA_OV2640_ID 51

#include "1_TaskerManager/mTaskerManager.h"

#ifdef USE_MODULE_DRIVERS_CAMERA_OV2640


class mCameraOV2640 :
  public mTaskerInterface
{

  private:
  public:
    mCameraOV2640(){};
    int8_t Tasker(uint8_t function, JsonParserObject obj = 0);

    
    static const char* PM_MODULE_DRIVERS_CAMERA_OV2640_CTR;
    static const char* PM_MODULE_DRIVERS_CAMERA_OV2640_FRIENDLY_CTR;
    PGM_P GetModuleName(){          return PM_MODULE_DRIVERS_CAMERA_OV2640_CTR; }
    PGM_P GetModuleFriendlyName(){  return PM_MODULE_DRIVERS_CAMERA_OV2640_FRIENDLY_CTR; }
    uint8_t GetModuleUniqueID(){ return D_UNIQUE_MODULE_DRIVERS_CAMERA_OV2640_ID; }

    
    #ifdef USE_DEBUG_CLASS_SIZE
    uint16_t GetClassSize(){
      return sizeof(mCameraOV2640);
    };
    #endif

    
    void init();
    void Pre_Init();
    int8_t pin = -1;
    struct SETTINGS{
      uint8_t fEnableModule = false;
      uint8_t caminit = false;
    }settings;

    void EveryLoop(void);
    void HandleWebcamMjpegTask();
    void WcShowStream();
    
uint32_t WcSetStreamserver(uint32_t flag);
void WcStreamControl();
void HandleWebcamMjpeg(void);

void setup_cam();

    int8_t Tasker_Web(uint8_t id);
    
    int8_t CheckAndExecute_JSONCommands();
    void parse_JSONCommand(void);
        
    uint8_t ConstructJSON_Settings(uint8_t json_method = 0);
    uint8_t ConstructJSON_State(uint8_t json_method = 0);

    void MQTTHandler_Init();
    void MQTTHandler_Set_fSendNow();
    void MQTTHandler_Set_TelePeriod();
    
    void MQTTHandler_Sender(uint8_t mqtt_handler_id = MQTT_HANDLER_ALL_ID);
    struct handler<mCameraOV2640>* mqtthandler_ptr;
    struct handler<mCameraOV2640>  mqtthandler_settings_teleperiod;
    struct handler<mCameraOV2640>  mqtthandler_state_ifchanged;
    struct handler<mCameraOV2640>  mqtthandler_state_teleperiod;
    
    const int MQTT_HANDLER_MODULE_LENGTH_ID = MQTT_HANDLER_LENGTH_ID;
};

#endif // USE_MODULE_DRIVERS_CAMERA_OV2640
#endif // _USE_MODULE_DRIVERS_CAMERA_OV2640_H