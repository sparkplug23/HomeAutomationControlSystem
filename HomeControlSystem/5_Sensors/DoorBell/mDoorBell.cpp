#include "mDoorBell.h"

#ifdef USE_MODULE_SENSORS_DOORCHIME


void mDoorBell::pre_init(void){

  if(pCONT_set->pin[GPIO_CHIME_INPUT_ID] < 99) {  // not set when 255
    pin_doorbell_button = pCONT_set->pin[GPIO_CHIME_INPUT_ID];
  }

  if(pin_doorbell_button>=0){
    pinMode(pin_doorbell_button,INPUT_PULLUP);
  }else{
    AddLog_P(LOG_LEVEL_ERROR,PSTR(D_LOG_PIR "Pin Invalid %d"),pin_doorbell_button);
    //disable pir code
  }

  if(pCONT_set->pin[GPIO_CHIME_RINGER_ID] < 99) {  // not set when 255
    pin_relay_chime = pCONT_set->pin[GPIO_CHIME_RINGER_ID];
  }

  if(pin_relay_chime>=0){
    pinMode(pin_relay_chime,OUTPUT);
    digitalWrite(pin_relay_chime,HIGH); //active low
  }else{
    AddLog_P(LOG_LEVEL_ERROR,PSTR(D_LOG_PIR "Pin Invalid %d"),pin_relay_chime);
    //disable pir code
  }

}



void mDoorBell::init(void){

  // BELLSWITCH_INIT();
  // BELLCHIME_INIT();   BELLCHIME_SET(0);

  sprintf(ringer.friendly_name_ctr,"Hallway Wall");
  sprintf(doorbell_switch.friendly_name_ctr,"Front");

  sprintf(ringer.trigger_time_ctr,"%s\0","--:--:--");
  sprintf(doorbell_switch.trigger_time_ctr,"%s\0","--:--:--");

}




// Set parameters to ring it
void mDoorBell::RingDoorBellSet(uint8_t freq, uint8_t seconds){
  ringer.fIsRinging = true;
  ringer.start_millis = millis();
  ringer.end_millis = millis()+(seconds*1000);
  ringer.freq = freq;
  ringer.seconds = seconds;
  AddLog_P(LOG_LEVEL_TEST,PSTR(D_LOG_CHIME "Set"));
  memcpy(ringer.trigger_time_ctr,pCONT->mt->mtime.hhmmss_ctr,sizeof(pCONT->mt->mtime.hhmmss_ctr)); 
}

// Function called each time
// Return if ring is not finished
uint8_t mDoorBell::RingDoorBellLoop(uint8_t reset){

  if(ringer.fIsRinging){ //not finished

    //calculate toggle as seconds/freq
    if(mSupport::MillisReached(&ringer.toggle_millis)){
      BellChime_Toggle();
      if(BellSwitch_OnOff()){
        ringer.closed_millis_end = millis()+500;
      }
      ringer.toggle_millis = millis()+(ringer.freq*500); //set new toggle millis
      AddLog_P(LOG_LEVEL_TEST,PSTR(D_LOG_CHIME "Toggled"));
    }

    //timeout/finished reset
    if(mSupport::MillisReached(&ringer.end_millis)){
      BellChime_Set(BELLCHIME_OFF); // turn off
      ringer.fIsRinging = false;
      AddLog_P(LOG_LEVEL_TEST,PSTR(D_LOG_CHIME "Ended ringer.end_millis"));
    }

    //Only have relay on for short time
    if(mSupport::TimeReached(&ringer.closed_millis_end,500)){
      //BELLCHIME_SET(BELLCHIME_OFF); // turn off
      AddLog_P(LOG_LEVEL_TEST,PSTR(D_LOG_CHIME "Ended ringer.closed_millis_end"));
    }

  }

}






void mDoorBell::WebCommand_Parse(void)
{
  char tmp[100];

//  selectorlist.amount = 0;
  uint8_t  arg_value = 0;

  if(pCONT_web->request_web_command == nullptr){ return; }

  char arg_ctr[10]; memset(arg_ctr,0,sizeof(arg_ctr));

  // check palette selector
  sprintf(arg_ctr,"doorbell_ring\0");
  if (pCONT_web->request_web_command->hasParam("doorbell_ring")) {
    pCONT_web->WebGetArg(pCONT_web->request_web_command, arg_ctr, tmp, sizeof(tmp));
    arg_value = (!strlen(tmp)) ? 0 : atoi(tmp);
    // animation.palette = arg_value;
    // update_all = true; //refresh all
    RingDoorBellSet(1,2);

    AddLog_P(LOG_LEVEL_TEST, PSTR(D_LOG_NEO "hasParam(\"%s\")=%d"),arg_ctr,arg_value);
  }

  

}

void mDoorBell::BellChime_Set(uint8_t onoff){
  digitalWrite(pin_relay_chime,!onoff);
}

void mDoorBell::BellChime_Toggle(){
  digitalWrite(pin_relay_chime,!digitalRead(pin_relay_chime));
}



uint8_t mDoorBell::BellSwitch_OnOff(){
  return !digitalRead(pin_doorbell_button);
}


const char* mDoorBell::BellSwitch_OnOff_Ctr(){
  return BellSwitch_OnOff() ? "ON" : "OFF";
}



int8_t mDoorBell::parse_JSONCommand(void){

  // Check if instruction is for me
  if(mSupport::mSearchCtrIndexOf(data_buffer2.topic.ctr,"set/doorbell")>=0){
      AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_MQTT D_PARSING_MATCHED D_TOPIC_COMMAND D_TOPIC_PIXELS));
      pCONT->fExitTaskerWithCompletion = true; // set true, we have found our handler
  }else{
    return 0; // not meant for here
  }

  int8_t isserviced = 0;
    
  //new topic names must include pixels
  
  if(strstr(data_buffer2.topic.ctr,"/settings")){
    AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_NEO D_PARSING_MATCHED D_TOPIC "settings"));    
    isserviced += parsesub_Settings();
  }else 
  if(strstr(data_buffer2.topic.ctr,"/command")){
    AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_NEO D_PARSING_MATCHED D_TOPIC "command"));    
    isserviced += parsesub_Command();
  }else 
  {
    AddLog_P(LOG_LEVEL_ERROR, PSTR(D_LOG_NEO D_PARSING_MATCHED D_TOPIC "INVALID"));    
  }

  return isserviced;

}

int8_t mDoorBell::parsesub_Command(){

  #ifdef JSONDOCUMENT_STATIC
    StaticJsonDocument<800> doc;
  #else
    DynamicJsonDocument doc(600);
  #endif
  DeserializationError error = deserializeJson(doc, data_buffer2.payload.ctr);
  if(error){
    AddLog_P(LOG_LEVEL_ERROR, PSTR(D_LOG_NEO D_ERROR_JSON_DESERIALIZATION));
    Response_mP(S_JSON_COMMAND_SVALUE, D_ERROR,D_ERROR_JSON_DESERIALIZATION);
    return 0;
  }
  JsonObject obj = doc.as<JsonObject>();

  int8_t tmp_id = 0;
  int8_t isserviced = 0;

  // Ring Door bell manually
  if(!obj["doorbell"].isNull()){ 
    // const char* scenectr = obj[D_JSON_NAME];
    // if((tmp_id=GetSceneIDbyName(scenectr))>=0){
    //   scene.name_id = tmp_id;
    //   animation.mode = ANIMATION_MODE_SCENE_ID;
    //   AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_NEO D_PARSING_MATCHED D_JSON_COMMAND_SVALUE),D_JSON_NAME,GetSceneName());
    //   Response_mP(S_JSON_COMMAND_SVALUE,D_JSON_NAME,GetSceneName());
    //   isserviced++;
    // }else{
    //   AddLog_P(LOG_LEVEL_ERROR, PSTR(D_LOG_NEO D_PARSING_MATCHED D_JSON_COMMAND_SVALUE),D_JSON_NAME,scenectr);
    // }
  }
  
  return isserviced;

} // END FUNCTION


int8_t mDoorBell::parsesub_Settings(){

  #ifdef JSONDOCUMENT_STATIC
    StaticJsonDocument<800> doc;
  #else
    DynamicJsonDocument doc(600);
  #endif
  DeserializationError error = deserializeJson(doc, data_buffer2.payload.ctr);
  if(error){
    AddLog_P(LOG_LEVEL_ERROR, PSTR(D_LOG_NEO D_ERROR_JSON_DESERIALIZATION));
    Response_mP(S_JSON_COMMAND_SVALUE, D_ERROR,D_ERROR_JSON_DESERIALIZATION);
    return 0;
  }
  JsonObject obj = doc.as<JsonObject>();

  int8_t tmp_id = 0;
  int8_t isserviced = 0;

  if(!obj["doorbell_output_binding"].isNull()){ 
    settings.fEnable_Switch_Relay_Binding = obj["doorbell_output_binding"];
    AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_DOORBELL D_PARSING_MATCHED D_JSON_COMMAND_NVALUE),"doorbell_output_binding",settings.fEnable_Switch_Relay_Binding);
    isserviced++;
  }
  
  return isserviced;

} // END FUNCTION




//#ifdef USE_MQTT

// NEW METHOD -- first senders then on internals
void mDoorBell::SubTasker_MQTTSender(){

  //DEBUGL("mDoorBell::SubTasker_MQTTSender");
  if((abs(millis()-tSavedSendDoorSensor)>=(60000*10))||(fUpdateSendDoorSensor)){ tSavedSendDoorSensor=millis(); fUpdateSendDoorSensor = false;
    MQQTSendDoorUpdate();
  }

  MQTTSendDoorSensorIfChanged(); // No timed delay

}

void mDoorBell::MQTTSendDoorSensorIfChanged(){

  if(doorbell_switch.ischanged){doorbell_switch.ischanged=false;

    memset(&data_buffer2,0,sizeof(data_buffer2));

    StaticJsonDocument<MQTT_MAX_PACKET_SIZE> doc;
    JsonObject root = doc.to<JsonObject>();

    root["location"] = DOORALERT_PAYLOAD_CTR;
    root["time"] = pCONT->mt->mtime.hhmmss_ctr;

    data_buffer2.payload.len = measureJson(root)+1;
    serializeJson(doc,data_buffer2.payload.ctr);

    if(doorbell_switch.isactive){
      pCONT->mqt->ppublish("status/doorbell/detected",data_buffer2.payload.ctr,false);
    }else{
      pCONT->mqt->ppublish("status/doorbell/over",data_buffer2.payload.ctr,false);
    }

  }

} // END function




void mDoorBell::MQQTSendDoorUpdate(void){

  memset(&data_buffer2,0,sizeof(data_buffer2));

    StaticJsonDocument<MQTT_MAX_PACKET_SIZE> doc;
    JsonObject root = doc.to<JsonObject>();

  JsonObject doorobj = root.createNestedObject("door");
    doorobj["position"] = BellSwitch_OnOff_Ctr();
    char timectr[12]; memset(timectr,0,sizeof(timectr));
    sprintf(timectr,"%sT%02d:%02d:%02d",
      pCONT->mt->GetDOWShortctr(doorbell_switch.changedtime.Wday),
      doorbell_switch.changedtime.hour,
      doorbell_switch.changedtime.minute,
      doorbell_switch.changedtime.second
    );
    doorobj["changedtime"] = timectr;

  #ifdef DOORLOCK_SWITCH_PIN
  JsonObject lockobj = root.createNestedObject("lock");
    lockobj["position"] = LOCKOPENCTR;
    char timectr2[15]; memset(timectr2,0,sizeof(timectr2));
    sprintf(timectr2,"%sT%02d:%02d:%02d",
      pCONT->mt->GetDOWShortctr(lock_detect.changedtime.Wday),
      lock_detect.changedtime.hour,
      lock_detect.changedtime.minute,
      lock_detect.changedtime.second
    );
    lockobj["changedtime"] = timectr2;
  #endif

  data_buffer2.payload.len = measureJson(root)+1;
  serializeJson(doc,data_buffer2.payload.ctr);

  pCONT->mqt->ppublish("status/door/status",data_buffer2.payload.ctr,false);

}



int8_t mDoorBell::Tasker(uint8_t function){
  
  switch(function){
    case FUNC_PRE_INIT:
      pre_init();
    break;
    case FUNC_INIT:
      init();
    break;
    case FUNC_LOOP: 

      AddLog_P(LOG_LEVEL_DEBUG_MORE, PSTR("Tasker::mDoorBell"));

      if((BellSwitch_OnOff()!=doorbell_switch.state)
          &&mSupport::TimeReachedNonReset(&doorbell_switch.tDetectTimeforDebounce,100)
        ){
        doorbell_switch.state = BellSwitch_OnOff(); //tDetectTime = millis();
        
        if(doorbell_switch.state){ Serial.print("Active high doorbell_switch");
          doorbell_switch.isactive = true;
          doorbell_switch.tDetectTimeforDebounce = millis();   

          memcpy(doorbell_switch.trigger_time_ctr,pCONT->mt->mtime.hhmmss_ctr,sizeof(pCONT->mt->mtime.hhmmss_ctr)); 

          if(settings.fEnable_Switch_Relay_Binding){
            RingDoorBellSet(1,2); //1 per sec for 2 secs (2 rings)
          }

        }else{ Serial.print("Active low doorbell_switch");
          doorbell_switch.isactive = false;
        }
        doorbell_switch.ischanged = true;
        doorbell_switch.changedtime = pCONT->mt->mtime;
        fUpdateSendDoorSensor = true;
        
      }

      // Handle ringer
      RingDoorBellLoop();

    break;



    case FUNC_MQTT_SENDER:
      SubTasker_MQTTSender();
    break;
    case FUNC_JSON_COMMAND:
      parse_JSONCommand();
    break;  




    case FUNC_WEB_COMMAND:
      WebCommand_Parse();
    break;

    case FUNC_WEB_APPEND_ROOT_BUTTONS:{
      char relay_handle_ctr[20]; 
      pCONT_web->AppendBuffer_PI2(PSTR("%s"),PSTR("{t}<tr>"));
      // for(uint8_t relay_id=0;relay_id<relays_connected;relay_id++){
        memset(relay_handle_ctr,0,sizeof(relay_handle_ctr));
        sprintf(relay_handle_ctr,"doorbell_ring");//,relay_id);
        pCONT_web->AppendBuffer_PI2(HTTP_DEVICE_CONTROL_BUTTON_VARIABLE2_HANDLE, 
                                      100, 
                                      "doorbell_ring",
                                      relay_handle_ctr, 
                                      DEVICE_CONTROL_BUTTON_ON_ID, 
                                      "Ring Doorbell", ""
                                    );
      // }
      pCONT_web->AppendBuffer_PI2("%s",PSTR("</tr>{t2}"));
    }break;

    // case FUNC_WEB_ADD_MAIN_BUTTON:{

    //     // Power Toggle
    //     // pCONT_web->WSBufferAppend_P(HTTP_TABLE100);
    //     // pCONT_web->WSBufferAppend_P(PSTR("<tr>"));
    //     // pCONT_web->WSBufferAppend_P(HTTP_DEVICE_CONTROL_BUTTON_VARIABLE_HANDLE, 36, "doorbell_ring", 1, "Ring Doorbell", "");
    //     // pCONT_web->WSBufferAppend_P(PSTR("</tr></table>"));

    // }
    // break;
    case FUNC_WEB_SHOW_PARAMETERS:{
    
      // uint8_t fsize = 16;
      // char title_ctr[50];
        
      // memset(title_ctr,0,sizeof(title_ctr));
      // sprintf(title_ctr,"Chime %s Rang",ringer.friendly_name_ctr);
      // pCONT_web->WSBufferAppend_P(HTTP_SNS_GENERIC, 
      //   title_ctr,
      //   ringer.trigger_time_ctr
      // );

      // memset(title_ctr,0,sizeof(title_ctr));
      // sprintf(title_ctr,"Doorbell %s Pressed",doorbell_switch.friendly_name_ctr);
      // pCONT_web->WSBufferAppend_P(HTTP_SNS_GENERIC, 
      //   title_ctr,
      //   doorbell_switch.trigger_time_ctr
      // );

    }
    break;
    
    /************
     * WEBPAGE SECTION * 
    *******************/
    #ifdef USE_WEBSERVER
    case FUNC_WEB_ADD_HANDLER:
      WebPage_Root_AddHandlers();
    break;
    case FUNC_WEB_ADD_ROOT_TABLE_ROWS:
      WebAppend_Root_Status_Table_Draw();
    break;
    case FUNC_WEB_APPEND_ROOT_STATUS_TABLE_IFCHANGED:
      WebAppend_Root_Status_Table_Data();
    break;
    #endif //USE_WEBSERVER



  }


} // END function


void mDoorBell::WebAppend_Root_Status_Table_Draw(){

      // char title_ctr[50];
        
      // memset(title_ctr,0,sizeof(title_ctr));
      // sprintf(title_ctr,"Chime %s Rang",ringer.friendly_name_ctr);

  // for(int ii=0;ii<fSensorCount;ii++){ //add number in name? List needed? also hold user defined name?
    pCONT_web->AppendBuffer_PI2(PSTR("<tr>"));
      pCONT_web->AppendBuffer_PI2(PSTR("<td>Chime %s Rang</td>"), ringer.friendly_name_ctr);//pCONT_sup->GetTextIndexed_P(listheading, sizeof(listheading), ii, kTitle_TableTitles_Root));//"Animation List Tester");      //titles are fixed, so send them here using getindex
      pCONT_web->AppendBuffer_PI2(PSTR("<td><div class='%s'>%s</div></td>"),"tab_dbl","?");   
    pCONT_web->AppendBuffer_PI2(PSTR("</tr>"));
    pCONT_web->AppendBuffer_PI2(PSTR("<tr>"));
      pCONT_web->AppendBuffer_PI2(PSTR("<td>Doorbell %s Pressed</td>"), doorbell_switch.friendly_name_ctr);//pCONT_sup->GetTextIndexed_P(listheading, sizeof(listheading), ii, kTitle_TableTitles_Root));//"Animation List Tester");      //titles are fixed, so send them here using getindex
      pCONT_web->AppendBuffer_PI2(PSTR("<td><div class='%s'>%s</div></td>"),"tab_dbl","?");   
    pCONT_web->AppendBuffer_PI2(PSTR("</tr>"));
  // }
}


//append to internal buffer if any root messages table
void mDoorBell::WebAppend_Root_Status_Table_Data(){
  
  uint8_t sensor_counter = 0;

  pCONT_web->AppendBuffer_PI2(PSTR("\"%s\":["),PSTR("tab_dbl")); 
  for(int row=0;row<2;row++){
    switch(row){
      default:
      case 0:{
        
        char float_ctr[10];
        char colour_ctr[10];
        char table_row[25]; memset(table_row,0,sizeof(table_row));       

        sprintf(table_row,"%s",ringer.trigger_time_ctr);
        
        // if(sensor[sensor_counter].temperature<=25){
        //   sprintf(colour_ctr,"%s","#00ff00"); //create variable/use webcolour ids
        // }else
        // if(sensor[sensor_counter].temperature>25){
        //   sprintf(colour_ctr,"%s","#fcba03");
        // }else{
          sprintf(colour_ctr,"%s","#ffffff");
        // }
    
        pCONT_web->AppendBuffer_PI2(PSTR("{\"id\":%d,\"ih\":\"%s\",\"fc\":\"%s\"},"),row,
          table_row, colour_ctr
        );
      }break;
      case 1:{      

        char float_ctr[10];
        char colour_ctr[10];
        char table_row[25]; memset(table_row,0,sizeof(table_row));        
        sprintf(table_row,"%s",doorbell_switch.trigger_time_ctr);
        
        // if(sensor[sensor_counter].humidity>70){
        //   sprintf(colour_ctr,"%s","#ff0000"); //create variable/use webcolour ids
        // }else
        // {
          sprintf(colour_ctr,"%s","#ffffff");
        // }
    
        pCONT_web->AppendBuffer_PI2(PSTR("{\"id\":%d,\"ih\":\"%s\",\"fc\":\"%s\"},"),row,
          table_row, colour_ctr
        );
        sensor_counter++;
      }break;
    }
  }
  *pCONT_web->buffer_writer_internal = (*pCONT_web->buffer_writer_internal) - 1;// remove extra comma
  pCONT_web->AppendBuffer_PI2(PSTR("],")); 

}


void mDoorBell::WebPage_Root_AddHandlers(){

  /**
   * Pages
   * */

}




#endif
