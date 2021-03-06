
#pragma once

#include <stdint.h>

#include "5_Sensors/_Interface/mSensorType.h"


class mTaskerInterface
  {
  public:

    mTaskerInterface(){};
    virtual int8_t Tasker(uint8_t function, JsonParserObject obj);
    virtual PGM_P GetModuleName();
    virtual PGM_P GetModuleFriendlyName();
    virtual uint8_t GetModuleUniqueID();
    #ifdef USE_DEBUG_CLASS_SIZE
    virtual uint16_t GetClassSize();
    #endif
    

    /**
     * Get device count for each module that should be in module.settings
     * */
    virtual uint8_t GetSensorCount(void) {return 0;}
    
    /**
     * Push 0 if none are used, maybe internalise
     * */
    virtual void GetSensorReading(sensors_reading_t* value, uint8_t index = 0){ value->type.push_back(0); }
    
    
    // virtual void parse_JSONCommand(JsonParserObject obj);

};