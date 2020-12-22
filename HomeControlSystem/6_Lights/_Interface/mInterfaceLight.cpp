#include "mInterfaceLight.h"

#ifdef USE_MODULE_LIGHTS_INTERFACE // interface is the gateway


void mInterfaceLight::Init_NeoPixelAnimator(uint16_t size, uint8_t timebase){

  animator_controller = new NeoPixelAnimator(size, timebase); // NeoPixel animation management object
  
}  


void mInterfaceLight::Settings_Default(){

  // #ifdef ENABLE_LOG_LEVEL_INFO
  // AddLog_P(LOG_LEVEL_TEST,PSTR("mInterfaceLight::Settings_Default"));
  // #endif

  // #ifdef USE_LIGHTING_TEMPLATE
  //   settings.flags.TemplateProvidedInProgMem = true;
  // #endif
  
  // if(settings.flags.TemplateProvidedInProgMem){// use template provided in progmem || override template
  
  //   Template_Load();

  // }else{
    
  //   #ifdef DEFAULT_LIGHTING_ANIMATION_MODE_ID
  //     animation.mode_id = DEFAULT_LIGHTING_ANIMATION_MODE_ID<ANIMATION_MODE_LENGTH_ID?
  //                           DEFAULT_LIGHTING_ANIMATION_MODE_ID:ANIMATION_MODE_FLASHER_ID;
  //   #else
  //     animation.mode_id = ANIMATION_MODE_FLASHER_ID;
  //   #endif

  // }

}


/*******************************************************************************************************************
********************************************************************************************************************
************ START OF SCENES DEFINITIONS ********************************************************************************************
********************************************************************************************************************
********************************************************************************************************************/

void mInterfaceLight::init_Scenes(){

  mode_singlecolour.name_id = mode_singlecolour_stored.name_id = MODE_SINGLECOLOUR_COLOURSCENE_ID;

  mode_singlecolour.name_id = MODE_SINGLECOLOUR_PALETTE_SINGLE_ID;

  // changeHSB(120,100,0);
  
} //end "init_Scenes"


void mInterfaceLight::StartFadeToNewColour(RgbcctColor targetColor, uint16_t _time_to_newcolour,  RgbcctColor fromcolor){ 

      #ifdef ENABLE_LOG_LEVEL_COMMANDS
  AddLog_P(LOG_LEVEL_INFO, PSTR("BEFORE1 _briCT, _briRGB %d %d"), _briCT, _briRGB);
      #endif ENABLE_LOG_LEVEL_COMMANDS

  #ifdef USE_MODULE_LIGHTS_ADDRESSABLE
  pCONT_ladd->FadeToNewColour(targetColor, _time_to_newcolour);
  #endif // USE_MODULE_LIGHTS_ADDRESSABLE
  #ifdef USE_MODULE_LIGHTS_PWM
  pCONT_lPWM->FadeToNewColour(targetColor, _time_to_newcolour);
  #endif // USE_MODULE_LIGHTS_PWM

}

// This will handle various colour palettes that are not "user lights" in nature (random colours or flashes per pixel)
// Instead, whole colour designs, changes over time (sunrise/wakeup light)
void mInterfaceLight::SubTask_SingleColour(){ 
  // #ifdef ENABLE_LOG_LEVEL_DEBUG
  // AddLog_P(LOG_LEVEL_DEBUG_MORE, PSTR(D_LOG_LIGHT D_CLASS_NAME_mInterfaceLight "SubTask_SingleColour"));
  // #endif
  
  // // Check for reseting SCENES
  // if(mode_singlecolour_stored.fActive){
  //   // if(abs(millis()-scene_stored.tStart)>scene_stored.tOnTime){
  //   //   scene.name_id = scene_stored.name_id; // restore mode
  //   //   scene_stored.fActive = false;   // finish
  //   // }
  // }

  //if enable scene sleep

  switch(mode_singlecolour.name_id){
    case MODE_SINGLECOLOUR_COLOURSCENE_ID:{

      //Need running flag AND update flag
      if(mode_singlecolour.flag.generate_new_colours){
        #ifdef ENABLE_LOG_LEVEL_COMMANDS
          AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_LIGHT "mode_singlecolour.generate_new_colours == true"));
        #endif ENABLE_LOG_LEVEL_COMMANDS
          
        // if(mode_singlecolour.update == true){
        
        // adjusted for brightness
        RgbcctColor targetColor = RgbcctColor(0);
        targetColor.R = current_color[0];
        targetColor.G = current_color[1];
        targetColor.B = current_color[2];
        targetColor.WC = current_color[3];
        targetColor.WW = current_color[4];

        #ifdef ENABLE_LOG_LEVEL_COMMANDS
        AddLog_P(LOG_LEVEL_TEST, PSTR("animation.transition.time_ms.val=%d"),animation.transition.time_ms.val);
        #endif ENABLE_LOG_LEVEL_COMMANDS

        // AddLog_P(LOG_LEVEL_TEST, PSTR("[%d|%d] colour\t%d\t%d\t%d\t%d\t%d"),mode_singlecolour.parts,pixels_in_map,colour.R,colour.G,colour.B,colour.WW,colour.WC);                        
        StartFadeToNewColour(targetColor, animation.transition.time_ms.val);

        // mode_singlecolour.name_id = MODE_SINGLECOLOUR_NOCHANGE_ID;
        #ifdef ENABLE_LOG_LEVEL_DEBUG
        AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT "mode_singlecolour.name_id=MODE_SINGLECOLOUR_COLOURSCENE_ID Executing"));
        #endif

        //disable future update
        animation.flags.fForceUpdate = true; // update output
        // mode_singlecolour.update = false;
        // memcpy(last_colour, current_color, sizeof(last_colour)); //temp fix
        // AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_LIGHT "mode_singlecolour.update == false"));

        mode_singlecolour.flag.generate_new_colours = false; // as this runs ONCE
      }
      

    }break;
    case MODE_SINGLECOLOUR_PALETTE_SINGLE_ID:{
      
      if(mode_singlecolour.flag.generate_new_colours){

        if(mTime::TimeReached(&mode_singlecolour_tSaved,animation.transition.time_ms.val)){
          
      #ifdef ENABLE_LOG_LEVEL_COMMANDS
          AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_LIGHT "mode_singlecolour.generate_new_colours == true"));    
      #endif //ENABLE_LOG_LEVEL_COMMANDS

          // Update pointer of struct
          SetPaletteListPtrFromID(animation.palette_id);
          
          uint8_t pixels_in_map = GetPixelsInMap(palettelist.ptr);
          
          #ifdef ENABLE_LOG_LEVEL_DEBUG
          AddLog_P(LOG_LEVEL_DEBUG_MORE,PSTR(D_LOG_LIGHT "pixels_in_map %d"),pixels_in_map);
          #endif
        
          uint16_t desired_pixel = mode_singlecolour.parts < pixels_in_map ? mode_singlecolour.parts : pixels_in_map;
          int16_t start_pixel_position = -1;
          RgbcctColor colour = GetColourFromPalette(palettelist.ptr, desired_pixel, &start_pixel_position);

          ApplyGlobalBrightnesstoColour(&colour);

          // force instant change on first part
          if(mode_singlecolour.parts == 0){ animation_override.time_ms = 1;}
          
          #ifdef ENABLE_LOG_LEVEL_COMMANDS
          AddLog_P(LOG_LEVEL_TEST, PSTR("[%d|%d] colour\t%d\t%d\t%d\t%d\t%d"),mode_singlecolour.parts,pixels_in_map,colour.R,colour.G,colour.B,colour.WW,colour.WC);                        
          #endif // ENABLE_LOG_LEVEL_COMMANDS
      
          StartFadeToNewColour(colour, animation.transition.time_ms.val);
    
          mode_singlecolour.parts++;
          if(mode_singlecolour.parts>=pixels_in_map){
            mode_singlecolour.parts = 0;
            // mode_singlecolour.name_id = MODE_SINGLECOLOUR_NOCHANGE_ID;
            // mode_singlecolour.update = false;
            mode_singlecolour.flag.generate_new_colours = false; // as this runs ONCE
            // memcpy(last_colour, current_color, sizeof(last_colour)); //temp fix
          }else{
            
            #ifdef ENABLE_LOG_LEVEL_COMMANDS
            AddLog_P(LOG_LEVEL_TEST, PSTR("mode_singlecolour.update = false NOT CLEARED %d %d"),mode_singlecolour.parts,pixels_in_map);
            #endif // ENABLE_LOG_LEVEL_COMMANDS

          }
        }

      }

    }break;
    default:
      #ifdef ENABLE_LOG_LEVEL_COMMANDS

      AddLog_P(LOG_LEVEL_INFO, PSTR("default"));
      
      #endif //  ENABLE_LOG_LEVEL_COMMANDS
    case MODE_SINGLECOLOUR_FADE_OFF_ID:{
      changeRGB(0,0,0);
      #ifdef USE_MODULE_LIGHTS_ADDRESSABLE
      pCONT_ladd->FadeToNewColour(mode_singlecolour.colour,animation.transition.time_ms.val);
      #endif // USE_MODULE_LIGHTS_ADDRESSABLE
      // mode_singlecolour.name_id = MODE_SINGLECOLOUR_NOCHANGE_ID;
      mode_singlecolour.update = false;
      memcpy(last_colour, current_color, sizeof(last_colour)); //temp fix
    }break;

    // case MODE_SINGLECOLOUR_FLASHCOLOUR_ID:
    //   // stripbus->ClearTo(HsbColor(scene_stored.colour)); // instant
    //   // scene_stored.tOnTime = 200;
    //   // scene_stored.name_id = scene.name_id; // save mode to return to
    //   // scene_stored.fActive = true;
    //   // scene_stored.tStart = millis();
    // break;
    // case MODE_SINGLECOLOUR_NOCHANGE_ID: break;
  }

} // END FUNCTION






RgbTypeColor mInterfaceLight::Color32bit2RgbColour(uint32_t colour32bit){
  RgbTypeColor rgb;
  // #if RgbTypeColor == RgbwColor
    rgb.R = colour32bit >> 24; //RGB
    rgb.G = colour32bit >> 16; //RGB
    rgb.B = colour32bit >> 8 & 0xFF; //RGB
  //   rgb.W = colour32bit & 0xFF; //RGB
  // #else
  //   rgb.R = colour32bit >> 16; //RGB
  //   rgb.G = colour32bit >> 8 & 0xFF; //RGB
  //   rgb.B = colour32bit & 0xFF; //RGB
  // #endif
  return rgb;
}

uint32_t mInterfaceLight::RgbColorto32bit(RgbColor rgb){
  return (rgb.R << 16) | (rgb.G << 8) | rgb.B;
}



uint8_t mInterfaceLight::ConstructJSON_Scene(uint8_t json_method){

  char buffer[30];
  
  JsonBuilderI->Start();
    JsonBuilderI->Add_P(PM_JSON_SCENE_NAME, GetSceneName(buffer, sizeof(buffer)));
    JsonBuilderI->Add_P(PM_JSON_HUE, getHue());
    JsonBuilderI->Add_P(PM_JSON_SAT, getSat());
    JsonBuilderI->Add_P(PM_JSON_BRIGHTNESS_RGB, getBriRGB());
    JsonBuilderI->Add_P(PM_JSON_TIME, (uint16_t)round(animation.transition.time_ms.val/1000));
    JsonBuilderI->Add_P(PM_JSON_TIME_MS, animation.transition.time_ms.val);
  return JsonBuilderI->End();

}

/*******************************************************************************************************************
********************************************************************************************************************
************ END OF SCENES DEFINITIONS ********************************************************************************************
********************************************************************************************************************
********************************************************************************************************************/

bool mInterfaceLight::LightModuleInit(void)
{
  pCONT_set->Settings.light_settings.type = LT_BASIC;                    // Use basic PWM control if SetOption15 = 0

  if (pCONT_set->Settings.flag_system.pwm_control) {          // SetOption15 - Switch between commands PWM or COLOR/DIMMER/CT/CHANNEL
    for (uint32_t i = 0; i < MAX_PWMS; i++) {
      if (pCONT_pins->PinUsed(GPIO_PWM1_ID, i)) { 
        pCONT_set->Settings.light_settings.type++; 
      #ifdef ENABLE_LOG_LEVEL_COMMANDS
        AddLog_P(LOG_LEVEL_DEBUG,PSTR("LightModuleInit PWM%d"),i);    
      #endif ENABLE_LOG_LEVEL_COMMANDS    
      }  // Use Dimmer/Color control for all PWM as SetOption15 = 1
    }
  }

  //temp fix
  if (pCONT_pins->PinUsed(GPIO_RGB_DATA_ID)) { 
    // AddLog_P(LOG_LEVEL_TEST,PSTR("pCONT_set->Settings.light_settings.type=%d"),pCONT_set->Settings.light_settings.type);
    pCONT_set->Settings.light_settings.type = LT_WS2812; 
  }


  if (pCONT_set->Settings.light_settings.type > LT_BASIC) {
    pCONT_set->devices_present++;
  }

  // // post-process for lights
  // if (Settings.flag3.pwm_multi_channels) {  // SetOption68 - Enable multi-channels PWM instead of Color PWM
  //   uint32_t pwm_channels = (Settings.light_settings.type & 7) > LST_MAX ? LST_MAX : (Settings.light_settings.type & 7);
  //   if (0 == pwm_channels) { pwm_channels = 1; }
  //   devices_present += pwm_channels - 1;    // add the pwm channels controls at the end
  // } else if ((Settings.param[P_RGB_REMAP] & 128) && (LST_RGBW <= (Settings.light_settings.type & 7))) {
  //   // if RGBW or RGBCW, and SetOption37 >= 128, we manage RGB and W separately, hence adding a device
  //   devices_present++;
  // }

  return (pCONT_set->Settings.light_settings.type > LT_BASIC);
}


void mInterfaceLight::Template_Load(){

  #ifdef ENABLE_LOG_LEVEL_DEBUG_MORE
  AddLog_P(LOG_LEVEL_DEBUG, PSTR("mInterfaceLight::Template_Load()"));
  #endif

  #ifdef USE_LIGHTING_TEMPLATE
  // load from progmem
  uint16_t progmem_size = sizeof(LIGHTING_TEMPLATE);
  progmem_size = progmem_size>1500?1500:progmem_size;
  // create parse buffer
  // char buffer[progmem_size];
  // Read into local
  D_DATA_BUFFER_CLEAR();
  memcpy_P(data_buffer.payload.ctr,LIGHTING_TEMPLATE,sizeof(LIGHTING_TEMPLATE));
  data_buffer.payload.len = strlen(data_buffer.payload.ctr);

  #ifdef ENABLE_LOG_LEVEL_COMMANDS
  AddLog_P(LOG_LEVEL_DEBUG, PSTR("LIGHTING_TEMPLATE" " READ = \"%s\""), data_buffer.payload.ctr);
  #endif // ENABLE_LOG_LEVEL_COMMANDS

  pCONT->Tasker_Interface(FUNC_JSON_COMMAND_ID);
  #endif // USE_LIGHTING_TEMPLATE

}


void mInterfaceLight::Init(void) //LightInit(void)
{

  // if(function == FUNC_INIT){
    //colour_arr_ptr = reinterpret_cast<uint8_t*>(&scene_colour);
  // }

  device = pCONT_set->devices_present;
  
  //subtype = (pCONT_set->Settings.light_settings.type & 7) > LST_MAX ? LST_MAX : (pCONT_set->Settings.light_settings.type & 7); // Always 0 - LST_MAX (5)
  subtype = LST_RGBCW;
  
  pwm_multi_channels = 0;//pCONT_set->Settings.flag3.pwm_multi_channels;  // SetOption68 - Enable multi-channels PWM instead of Color PWM

  pCONT_set->Settings.pwm_range = PWM_RANGE; //tmp

  // pCONT_set->Settings.dimmer_hw_min = 0;
  // pCONT_set->Settings.dimmer_hw_max =100;
  // pCONT_set->Settings.light_correction = 0;
  
  pCONT_set->Settings.light_settings.light_fade = 1;
  pCONT_set->Settings.light_settings.light_speed = 5*2;
  pCONT_set->power = 1;

  auto_time_off_secs = 0;
  


  init_Scenes();

  init_PresetColourPalettes();
  init_Animations();

  #ifdef USE_MODULE_LIGHTS_PWM
    settings.flags.enable_cct_channel_sliders = true;
  #else
    settings.flags.enable_cct_channel_sliders = false;
  #endif // USE_MODULE_LIGHTS_PWM

  //new_color[0] = 255;
  // LightApplyPower(new_color, 1);

  // if (LST_RGBW <= subtype) {
  //   // only change if RGBW or RGBCW
  //   // do not allow independant RGB and WC colors
  //   bool ct_rgb_linked = 0;// !(pCONT_set->Settings.param[P_RGB_REMAP] & 128);
  //   CommandSet_RGBCT_Linked(ct_rgb_linked);
  // }
  CommandSet_RGBCT_Linked(false); //temp
  setCT(CT_MIN);

  if ((LST_SINGLE <= subtype) && pwm_multi_channels) {
    // we treat each PWM channel as an independant one, hence we switch to
    setPWMMultiChannel(true);
    device = pCONT_set->devices_present - subtype + 1; // adjust if we also have relays
  } else if (!isCTRGBLinked()) {
    // if RGBW or RGBCW, and SetOption37 >= 128, we manage RGB and W separately
    device--;   // we take the last two devices as lights
  }

  LightCalcPWMRange();
  #ifdef DEBUG_LIGHT
    AddLog_P(LOG_LEVEL_TEST, "LightInit pwm_multi_channels=%d subtype=%d device=%d devices_present=%d",
      pwm_multi_channels, subtype, device, pCONT_set->devices_present);
  #endif

  setSubType(subtype);
  // loadSettings();
  UpdateFinalColourComponents();    // calculate the initial values (#8058)

  // Serial.println("UpdateFinalColourComponents DONE"); Serial.flush();

  if (LST_SINGLE == subtype) {
    //pCONT_set->Settings.light_settings.light_color[0] = 255;      // One channel only supports Dimmer but needs max color
  }
  // if (Settings.light_settings.type < LT_PWM6) {           // PWM
  //   for (uint32_t i = 0; i < Settings.light_settings.type; i++) {
  //     Settings.pwm_value[i] = 0;        // Disable direct PWM control
  //     if (PinUsed(GPIO_PWM1, i)) {
  //       pinMode(Pin(GPIO_PWM1, i), OUTPUT);
  //     }
  //   }
  // }

  // Set light mode
  if(pCONT_set->Settings.light_settings.type == LT_WS2812){ //RGB only
    setColorMode(LCM_RGB);
  }else{
    setColorMode(LCM_BOTH);
  }


  uint32_t max_scheme = max_scheme;
  if (subtype < LST_RGB) {
    max_scheme = LS_POWER;
  }
  if ((LS_WAKEUP == pCONT_set->Settings.light_settings.light_scheme) || (pCONT_set->Settings.light_settings.light_scheme > max_scheme)) {
    pCONT_set->Settings.light_settings.light_scheme = LS_POWER;
  }
  pCONT_set->power = 1;
  update = true;
  wakeup_active = 0;
  // if (pCONT_set->Settings.flag4.fade_at_startup) {
    fade_initialized = true;      // consider fade intialized starting from black
  // }

//   pCONT_set->Settings.light_settings.type = LT_BASIC;                    // Use basic PWM control if SetOption15 = 0

  // if (pCONT_set->Settings.flag.pwm_control) {          // SetOption15 - Switch between commands PWM or COLOR/DIMMER/CT/CHANNEL
  //   for (uint32_t i = 0; i < MAX_PWMS; i++) {
  //     if (PinUsed(pCONT_set->GPIO_PWM1, i)) { pCONT_set->Settings.light_settings.type++; }  // Use Dimmer/Color control for all PWM as SetOption15 = 1
  //   }
  // }

//   // post-process for lights
//   if (Settings.flag3.pwm_multi_channels) {  // SetOption68 - Enable multi-channels PWM instead of Color PWM
//     uint32_t pwm_channels = (Settings.light_settings.type & 7) > LST_MAX ? LST_MAX : (Settings.light_settings.type & 7);
//     if (0 == pwm_channels) { pwm_channels = 1; }
//     devices_present += pwm_channels - 1;    // add the pwm channels controls at the end
//   } else if ((Settings.param[P_RGB_REMAP] & 128) && (LST_RGBW <= (Settings.light_settings.type & 7))) {
//     // if RGBW or RGBCW, and SetOption37 >= 128, we manage RGB and W separately, hence adding a device
//     devices_present++;
//   }

//   return (Settings.light_settings.type > LT_BASIC);
// }

// changeBri(0); //default off

  //create copy for pCONT_iLight->animation stored
  memcpy(&animation_stored,&animation,sizeof(animation_stored));// RESTORE copy of state

} //light_init



void mInterfaceLight::init_Animations(){

// add these into settings as defaults as these currently overwrite templates

  // // Set default values (ifdef below sets specific)
  // #ifdef USE_MODULE_LIGHTS_ADDRESSABLE
  // animation.transition.order_id = TRANSITION_ORDER_INORDER_ID;
  // #endif // USE_MODULE_LIGHTS_ADDRESSABLE
  // // animation.palette_id = PALETTELIST_VARIABLE_USER_01_ID;
  // animation.mode_id = ANIMATION_MODE_FLASHER_ID;
  // // flashersettings.function = FLASHER_FUNCTION_SLOW_GLOW_ID;
  // #ifdef USE_MODULE_LIGHTS_ADDRESSABLE
  // animation.transition.method_id = TRANSITION_METHOD_BLEND_ID;
  // #endif // USE_MODULE_LIGHTS_ADDRESSABLE
  // animation.flags.fForceUpdate = true;
  // animation.transition.time_ms.val = 1000;
  // animation.transition.rate_ms.val = 20*1000;
  animation.flags.fEnable_Animation = true;
  animation.flags.NewAnimationRequiringCompleteRefresh = true;

}




// Colours etc will be made or called using a func_update_light_Values
// Another func will push those values to the output, which each hardware class will handle

// // Used for timed on or off events
int8_t mInterfaceLight::Tasker(uint8_t function){
  
  int8_t function_result = 0;

  // return 0;
 
  // As interface module, the parsing of module_init takes precedence over the Settings.light_settings.type
  switch(function){
    case FUNC_TEMPLATE_MODULE_LOAD:
      Template_Load();
      break;
    case FUNC_MODULE_INIT:
      LightModuleInit();
      break;
    case FUNC_PRE_INIT:
      return FUNCTION_RESULT_HANDLED_ID;
    case FUNC_BOOT_MESSAGE:
      BootMessage();
      break;
  }

  switch(function){
    case FUNC_INIT:
      Init();
    break;    
    case FUNC_POINTER_INIT:
      init_PresetColourPalettes();
    break;
    /************
     * SETTINGS SECTION * 
    *******************/
    case FUNC_SETTINGS_LOAD_VALUES_INTO_MODULE: 
      // Settings_Load();
    break;
    case FUNC_SETTINGS_SAVE_VALUES_FROM_MODULE: 
      //Settings_Save();
    break;
    case FUNC_SETTINGS_PRELOAD_DEFAULT_IN_MODULES:
      Settings_Default();
      // Module_Init(); // User defined values in progmem, later to be parsed via webcommand
    break;
    case FUNC_SETTINGS_OVERWRITE_SAVED_TO_DEFAULT:
      Settings_Default();
      //pCONT_set->SettingsSave(2);
    break;
    /************
     * PERIODIC SECTION * 
    *******************/
    case FUNC_LOOP:
      EveryLoop();
    break;
    case FUNC_EVERY_SECOND:{

      // #ifdef ENABLE_LOG_LEVEL_COMMANDS
      // AddLog_P(LOG_LEVEL_TEST, PSTR("_briRGB=%d"),_briRGB);
      // #endif ENABLE_LOG_LEVEL_COMMANDS

      // mode_singlecolour.name_id = MODE_SINGLECOLOUR_PALETTE_SINGLE_ID;

      //Temp fix until proper monitoring of on/off states
      #ifdef USE_MODULE_LIGHTS_ADDRESSABLE
      light_power_state = getBri()?1:0;
      //AddLog_P(LOG_LEVEL_TEST, PSTR("light_power_state=%d"),light_power_state);
      #endif // USE_MODULE_LIGHTS_ADDRESSABLE
    
    }break;
    case FUNC_EVERY_MINUTE:

    break;
    /************
     * COMMANDS SECTION * 
    *******************/
    case FUNC_JSON_COMMAND_CHECK_TOPIC_ID:
      CheckAndExecute_JSONCommands();
    break;
    case FUNC_JSON_COMMAND_ID:
      parse_JSONCommand();
    break;
    // case FUNC_SET_POWER:
    //   LightSetPower();
    // break;
    /************
     * MQTT SECTION * 
    *******************/
    #ifdef USE_MQTT
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
    case FUNC_MQTT_CONNECTED:
      MQTTHandler_Set_fSendNow();
    break;
    #endif //USE_MQTT
  } // end switch
  
  /************
   * WEBPAGE SECTION * 
  *******************/
  #ifdef USE_MODULE_CORE_WEBSERVER
  return Tasker_Web(function);
  #endif // USE_MODULE_CORE_WEBSERVER

} // END function




int8_t mInterfaceLight::CheckAndExecute_JSONCommands(){

  // Check if instruction is for me
  if(mSupport::SetTopicMatch(data_buffer.topic.ctr,D_MODULE_LIGHTS_INTERFACE_CTR)>=0){
    #ifdef ENABLE_LOG_LEVEL_COMMANDS
    AddLog_P(LOG_LEVEL_COMMANDS, PSTR(D_LOG_MQTT D_TOPIC_COMMAND D_MODULE_LIGHTS_INTERFACE_CTR));
    #endif // #ifdef ENABLE_LOG_LEVEL_COMMANDS
    pCONT->fExitTaskerWithCompletion = true; // set true, we have found our handler
    parse_JSONCommand();
    return FUNCTION_RESULT_HANDLED_ID;
  }else{
    return FUNCTION_RESULT_UNKNOWN_ID; // not meant for here
  }

}

void mInterfaceLight::parse_JSONCommand(void){

  #ifdef ENABLE_LOG_LEVEL_COMMANDS
  AddLog_P(LOG_LEVEL_TEST, PSTR(D_LOG_LIGHT D_TOPIC "Checking all commands"));
  #endif // #ifdef ENABLE_LOG_LEVEL_COMMANDS

  #ifdef USE_MODULE_LIGHTS_PWM
  pCONT_lPWM->parse_JSONCommand();
  #endif // USE_MODULE_LIGHTS_PWM

  #ifdef USE_MODULE_LIGHTS_ADDRESSABLE
  pCONT_ladd->parse_JSONCommand();
  #endif // USE_MODULE_LIGHTS_ADDRESSABLE

  char buffer[50];

  // Need to parse on a copy
  char parsing_buffer[data_buffer.payload.len+1];
  memcpy(parsing_buffer,data_buffer.payload.ctr,sizeof(char)*data_buffer.payload.len+1);
  JsonParser parser(parsing_buffer);
  JsonParserObject obj = parser.getRootObject();   
  if (!obj) { 
    #ifdef ENABLE_LOG_LEVEL_COMMANDS
    AddLog_P(LOG_LEVEL_ERROR, PSTR(D_JSON_DESERIALIZATION_ERROR));
    #endif //ENABLE_LOG_LEVEL_COMMANDS
    return;
  }  
  JsonParserToken jtok = 0; 
  int8_t tmp_id = 0;
  
  if(jtok = obj[PM_JSON_HARDWARE_TYPE]){
    if(jtok.isStr()){
      if((tmp_id=GetPixelHardwareTypeIDbyName(jtok.getStr()))>=0){
        CommandSet_PixelHardwareTypeID(tmp_id);
        data_buffer.isserviced++;
      }
    }else
    if(jtok.isNum()){
      CommandSet_PixelHardwareTypeID(jtok.getInt());
      data_buffer.isserviced++;
    }
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_SVALUE_K(D_JSON_HARDWARE_TYPE)), GetPixelHardwareTypeName(buffer));
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }
  
  if(jtok = obj[PM_JSON_HUE]){ // Assume range 0-359
    CommandSet_Hue_360(jtok.getInt());
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_HUE)), getHue());
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }

  if(jtok = obj[PM_JSON_SAT]){ // Assume range 0-100
    CommandSet_Sat_255(mapvalue(jtok.getInt(), 0,100, 0,255));
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_SAT)), getSat());
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }else
  if(jtok = obj[PM_JSON_SAT_255]){ // alternate full range 0-255
    CommandSet_Sat_255(jtok.getInt());
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_SAT_255)), getSat());
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }

  if(jtok = obj[PM_JSON_BRIGHTNESS]){ // Assume range 0-100
    CommandSet_Brt_255(mapvalue(jtok.getInt(), 0,100, 0,255));
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_BRIGHTNESS)), brt);
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }else
  if(jtok = obj[PM_JSON_BRIGHTNESS_255]){ // alternate full range 0-255
    CommandSet_Brt_255(jtok.getInt());
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_BRIGHTNESS_255)), getBri());
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }

  if(jtok = obj[PM_JSON_BRIGHTNESS_RGB]){ // Assume range 0-100
    CommandSet_BrtRGB_255(mapvalue(jtok.getInt(), 0,100, 0,255));
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_BRIGHTNESS_RGB)), getBriRGB());
    #endif //#ifdef ENABLE_LOG_LEVEL_DEBUG
  }else
  if(jtok = obj[PM_JSON_BRIGHTNESS_RGB_255]){ // alternate full range 0-255
    CommandSet_BrtRGB_255(jtok.getInt());
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_BRIGHTNESS_RGB_255)), getBriRGB());
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }

  if(jtok = obj[PM_JSON_BRIGHTNESS_CCT]){ // Assume range 0-100
    CommandSet_BrtCT_255(mapvalue(jtok.getInt(), 0,100, 0,255));
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_BRIGHTNESS_CCT)), getBriCT());
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }else
  if(jtok = obj[PM_JSON_BRIGHTNESS_RGB_255]){ // alternate full range 0-255
    CommandSet_BrtCT_255(jtok.getInt());
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_BRIGHTNESS_RGB_255)), getBriCT());
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }

  if(jtok = obj[PM_JSON_CCT_PERCENTAGE]){ // Assume range 0-100
    CommandSet_ColourTemp(mapvalue(jtok.getInt(), 0,100, _ct_min_range,_ct_max_range));
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_CCT_TEMP)), LightGetColorTemp());
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }else
  if(jtok = obj[PM_JSON_CCT_TEMP]){ // Assume range 0-100
    CommandSet_ColourTemp(jtok.getInt());
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_CCT_TEMP)), LightGetColorTemp());
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }

  if(jtok = obj[PM_JSON_RGBCCT_LINKED]){
    CommandSet_RGBCT_Linked(jtok.getInt());
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_RGBCCT_LINKED)), value);
    #endif // ENABLE_LOG_LEVEL_DEBUG
  } 

  if(jtok = obj[PM_JSON_TRANSITION].getObject()[PM_JSON_TIME]){ // default to secs
    CommandSet_Animation_Transition_Time_Ms(jtok.getInt()*1000);
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_SVALUE_NVALUE_K(D_JSON_TRANSITION, D_JSON_TIME)),animation.transition.time_ms.val);  
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }else
  if(jtok = obj[PM_JSON_TRANSITION].getObject()[PM_JSON_TIME_MS]){
    CommandSet_Animation_Transition_Time_Ms(jtok.getInt());
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_SVALUE_NVALUE_K(D_JSON_TRANSITION, D_JSON_TIME)),animation.transition.time_ms.val);  
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }
  
  if(jtok = obj[PM_JSON_TRANSITION].getObject()[PM_JSON_RATE]){ // default to secs
    CommandSet_Animation_Transition_Rate_Ms(jtok.getInt()*1000);
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_SVALUE_NVALUE_K(D_JSON_TRANSITION, D_JSON_RATE)),animation.transition.rate_ms.val);  
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }else
  if(jtok = obj[PM_JSON_TRANSITION].getObject()[PM_JSON_RATE_MS]){
    CommandSet_Animation_Transition_Rate_Ms(jtok.getInt());
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_SVALUE_NVALUE_K(D_JSON_TRANSITION, D_JSON_RATE_MS)),animation.transition.rate_ms.val);  
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }
  
  if(jtok = obj[PM_JSON_TRANSITION].getObject()[PM_JSON_PIXELS_UPDATE_NUMBER]){
    CommandSet_LightsCountToUpdateAsNumber(jtok.getInt());
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_SVALUE_NVALUE_K(D_JSON_TRANSITION,D_JSON_PIXELS_UPDATE_PERCENTAGE)), animation.transition.pixels_to_update_as_percentage.val);
    #endif
  }else
  if(jtok = obj[PM_JSON_TRANSITION].getObject()[PM_JSON_PIXELS_UPDATE_PERCENTAGE]){ 
    CommandSet_LightsCountToUpdateAsPercentage(jtok.getInt());
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_SVALUE_NVALUE_K(D_JSON_TRANSITION,D_JSON_PIXELS_UPDATE_NUMBER)), animation.transition.pixels_to_update_as_number.val);
    #endif
  }
  
  if(jtok = obj[PM_JSON_TRANSITION].getObject()[PM_JSON_ORDER]){
    if(jtok.isStr()){
      if((tmp_id=GetTransitionOrderIDbyName(jtok.getStr()))>=0){
        CommandSet_TransitionOrderID(tmp_id);
        data_buffer.isserviced++;
      }
    }else
    if(jtok.isNum()){
      CommandSet_TransitionOrderID(jtok.getInt());
      data_buffer.isserviced++;
    }
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_SVALUE_SVALUE_K(D_JSON_TRANSITION,D_JSON_ORDER)), GetTransitionOrderName(buffer, sizeof(buffer)));
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }

  if(jtok = obj[PM_JSON_TIME_ON]){ // default to secs
    CommandSet_Auto_Time_Off_Secs(jtok.getInt());
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_TIME_ON)),auto_time_off_secs);  
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }

  if(jtok = obj[PM_JSON_SCENE_NAME]){
    if(jtok.isStr()){
      if((tmp_id=GetSceneIDbyName(jtok.getStr()))>=0){
        CommandSet_SingleColourMode_ID(tmp_id);
        data_buffer.isserviced++;
      }
    }else
    if(jtok.isNum()){
      CommandSet_SingleColourMode_ID(jtok.getInt());
      data_buffer.isserviced++;
    }
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_SVALUE_K(D_JSON_SCENE_NAME)), GetSceneName(buffer, sizeof(buffer)));
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }

  if(jtok = obj[PM_JSON_LIGHTPOWER]){
    int8_t state = 0;
    if(jtok.isStr()){
      state = pCONT_sup->GetStateNumber(jtok.getStr());
    }else
    if(jtok.isNum()){
      state = jtok.getInt(); 
    }
    ModifyStateNumberIfToggled(&state, light_power_state);
    CommandSet_LightPowerState(state);
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_LIGHTPOWER)), light_power_state);
    #endif // ENABLE_LOG_LEVEL_DEBUG       
  }
 
  if(jtok = obj[PM_JSON_COLOUR_PALETTE]){
    if(jtok.isStr()){
      if((tmp_id=GetPaletteIDbyName(jtok.getStr()))>=0){
        CommandSet_PaletteID(tmp_id);
        data_buffer.isserviced++;
      }
    }else
    if(jtok.isNum()){
      CommandSet_PaletteID(jtok.getInt());
      data_buffer.isserviced++;
    }
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_SVALUE_K(D_JSON_COLOUR_PALETTE)), GetPaletteNameByID(animation.palette_id, buffer, sizeof(buffer)));
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }

  if(jtok = obj[PM_JSON_ANIMATIONMODE]){
    if(jtok.isStr()){
      if((tmp_id=GetAnimationModeIDbyName(jtok.getStr()))>=0){
        CommandSet_AnimationModeID(tmp_id);
        data_buffer.isserviced++;
      }
    }else
    if(jtok.isNum()){      
      CommandSet_AnimationModeID(jtok.getInt());
      data_buffer.isserviced++;
    }
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_SVALUE_K(D_JSON_ANIMATIONMODE)), GetAnimationModeName(buffer, sizeof(buffer)));
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }

  
  if(jtok = obj[PM_JSON_ANIMATIONENABLE]){ 
    int8_t state = 0;
    if(jtok.isStr()){
      state = pCONT_sup->GetStateNumber(jtok.getStr());
    }else
    if(jtok.isNum()){
      state = jtok.getInt(); 
    }
    ModifyStateNumberIfToggled(&state, animation.flags.fEnable_Animation);
    CommandSet_Flag_EnabledAnimation(state);
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_NEO D_PARSING_MATCHED D_JSON_COMMAND_NVALUE_K(D_JSON_ANIMATIONENABLE)), pCONT_iLight->animation.flags.fEnable_Animation);    
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }

  
  if(jtok = obj[PM_JSON_RGB_COLOUR_ORDER]){
    if(jtok.isStr()){
      if((tmp_id=GetHardwareColourTypeIDbyName(jtok.getStr()))>=0){
        CommandSet_HardwareColourTypeID(tmp_id);
        data_buffer.isserviced++;
      }
    }else
    if(jtok.isNum()){      
      CommandSet_HardwareColourTypeID(jtok.getInt());
      data_buffer.isserviced++;
    }
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_SVALUE_K(D_JSON_RGB_COLOUR_ORDER)), GetHardwareColourTypeName(buffer, sizeof(buffer)));
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }

  if(jtok = obj[PM_JSON_STRIP_SIZE]){
    CommandSet_LightSizeCount(jtok.getInt());
    data_buffer.isserviced++;
    #ifdef ENABLE_LOG_LEVEL_DEBUG
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_STRIP_SIZE)), light_size_count);
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }

  if(jtok = obj[PM_JSON_SCENE].getObject()[PM_JSON_COLOUR]){

    uint8_t colour_array[5];
    memset(colour_array,0,sizeof(colour_array));
    uint8_t jsonpair_count = jtok.size();

    for(int index = 0; index < jsonpair_count; index++){
      jtok.nextOne(); //skip start of object
      Serial.println(jtok.getInt());
      colour_array[index] = jtok.getInt();
    }
    
    CommandSet_SceneColour_Raw(colour_array);
    data_buffer.isserviced++;

    #ifdef ENABLE_LOG_LEVEL_DEBUG
    snprintf_P(buffer, sizeof(buffer), PSTR("[%d,%d,%d,%d,%d]"),colour_array[0],colour_array[1],colour_array[2],colour_array[3],colour_array[4]);
    AddLog_P(LOG_LEVEL_DEBUG, PSTR(D_LOG_LIGHT D_JSON_COMMAND_SVALUE_SVALUE_K(D_JSON_SCENE,D_JSON_COLOUR)), buffer);
    #endif // ENABLE_LOG_LEVEL_DEBUG
  }

  //allowing directly feeding the rgb string (desired pixel) (also for designing colours)
  
  mode_singlecolour.flag.generate_new_colours = true;
  mqtthandler_debug_teleperiod.flags.SendNow = true;
  animation.flags.fForceUpdate = true;

}



 



void mInterfaceLight::EveryLoop(){
      
  // AddLog_P(LOG_LEVEL_TEST, PSTR(D_LOG_LIGHT "settings.type == EveryLoop"));
  SubTask_AutoOff();

  // if(animation.flags.fForceUpdate){
  //  if(animation.mode_id == ANIMATION_MODE_SCENE_ID){ //if scene, with colour change push output (change this to be a flag "animation.force" then do this check)
  //     mode_singlecolour.name_id = MODE_SINGLECOLOUR_COLOURSCENE_ID;
  //   }
  // }


  // Check if update is needed, ONLY update output, not new numbers
  // if(!memcmp(last_colour, current_color, sizeof(last_colour))){
  //   // memcpy(last_colour, current_color, sizeof(last_colour)); //temp fix
  //   AddLog_P(LOG_LEVEL_INFO, PSTR("!memcmp(last_colour, current_color, 5)"));
  //   animation.flags.fForceUpdate = true;
  //   if(!mode_singlecolour.flag.running){ 
  //     mode_singlecolour.flag.running = true; 
  //     AddLog_P(LOG_LEVEL_INFO, PSTR("mode_singlecolour.flag.running"));
  //   }
  // }

  //   // If not running, I need to run this to
  //   if(!mode_singlecolour.flag.running){ mode_singlecolour.flag.running = true; }
  //   animation_override.time_ms = 1;
  //   //based on current mode, other flags need to be set
  //   if(animation.mode_id == ANIMATION_MODE_SCENE_ID){      
  //     mode_singlecolour.update = true;
  //     //mode_singlecolour.name_id = MODE_SINGLECOLOUR_COLOURSCENE_ID;
  //   }
  // }

    // AddLog_P(LOG_LEVEL_TEST, PSTR("Invalid Light LT_WS2812 HERE %d"),pCONT_set->Settings.light_settings.type);
  // Single colour methods
  if((pCONT_set->Settings.light_settings.type < LT_LIGHT_INTERFACE_END)||
     (pCONT_set->Settings.light_settings.type == LT_WS2812)){
     
    switch(animation.mode_id){
      case ANIMATION_MODE_SCENE_ID:
        SubTask_SingleColour();             //scenes to be moved into interface
        
        //CHANGE TO LIGHTPOWER
        // light_power_state = true;

        //AddLog_P(LOG_LEVEL_DEBUG, PSTR("ANIMATION_MODE_SCENE_ID"));
      break;
      // case ANIMATION_MODE_AMBILIGHT_ID:
      //   SubTask_Ambilight();
      //   light_power_state = true;
      // break;
      case ANIMATION_MODE_NONE_ID: default: break; // resting position
    }
  
  }

  if(pCONT_set->Settings.light_settings.type == LT_WS2812){ 
    
    AddLog_P(LOG_LEVEL_DEBUG_MORE, PSTR("Invalid Light LT_WS2812"));
    #ifdef USE_MODULE_LIGHTS_ADDRESSABLE
    switch(animation.mode_id){
      #ifdef ENABLE_PIXEL_FUNCTION_FLASHER
      case ANIMATION_MODE_FLASHER_ID:
        // AddLog_P(LOG_LEVEL_TEST,PSTR(D_LOG_LIGHT "ANIMATION_MODE_FLASHER_ID"));
        pCONT_ladd->SubTask_Flasher_Main();
        // light_power_state = true;
      break;
      #endif
      #ifdef USE_TASK_RGBLIGHTING_NOTIFICATIONS
      case ANIMATION_MODE_NOTIFICATIONS_ID:
        SubTask_NotificationPanel();
        // light_power_state = true;
      break;
      #endif
      #ifdef ENABLE_PIXEL_FUNCTION_AMBILIGHT // Basic colours around boxed objects
      case ANIMATION_MODE_AMBILIGHT_ID:
        // AddLog_P(LOG_LEVEL_TEST,PSTR(D_LOG_LIGHT "ANIMATION_MODE_AMBILIGHT_ID"));
        pCONT_ladd->SubTask_Ambilight_Main();
        // light_power_state = true;
      break;
      #endif
      #ifdef ENABLE_PIXEL_FUNCTION_ADALIGHT // serial, wifi udp connection
      case ANIMATION_MODE_FLASHER_ID:
        // AddLog_P(LOG_LEVEL_TEST,PSTR(D_LOG_LIGHT "ANIMATION_MODE_FLASHER_ID"));
        pCONT_ladd->SubTask_Flasher_Main();
        // light_power_state = true;
      break;
      #endif
      #ifdef ENABLE_PIXEL_FUNCTION_MANUAL_SETPIXEL // serial, wifi udp connection
      case ANIMATION_MODE_MANUAL_SETPIXEL_ID:
        // AddLog_P(LOG_LEVEL_TEST,PSTR(D_LOG_LIGHT "ANIMATION_MODE_FLASHER_ID"));
        pCONT_ladd->SubTask_Manual_SetPixel();
        // light_power_state = true;
      break;
      #endif
      case ANIMATION_MODE_NONE_ID: default: break; // resting position
    }
    #endif
      
  }
  else
  {
    AddLog_P(LOG_LEVEL_DEBUG_MORE, PSTR("Invalid Light Type"));
  }

  // Clear any flags now it should have been handled
  // if(animation.flags.fForceUpdate){
  //   animation.flags.fForceUpdate = false;
  // }

} // END everyloop




void mInterfaceLight::SubTask_AutoOff(){

  if(mTime::TimeReached(&tSavedAutoOff,1000)){
    //AddLog_P(LOG_LEVEL_DEBUG_MORE, PSTR(D_LOG_LIGHT "scene.tSavedAutoOff [%d]"),animation.auto_time_off_secs);
    if(auto_time_off_secs==1){ //if =1 then turn off and clear to 0
      // animation.name_id = MODE_SINGLECOLOUR_FADE_OFF_ID;
      #ifdef ENABLE_LOG_LEVEL_COMMANDS
      AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_LIGHT "animation.auto_time_off_secs==1 and disable"));
      #endif       

      CommandSet_LightPowerState(LIGHT_POWER_STATE_OFF_ID);
      //#ifdef ENABLE_LOG_LEVEL_INFO
      auto_time_off_secs=0;
      //#endif
    }else
    if(auto_time_off_secs>1){ //if =1 then turn off and clear to 0
      auto_time_off_secs--; //decrease
      
      #ifdef ENABLE_LOG_LEVEL_COMMANDS
      AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_LIGHT "auto_time_off_secs=%d dec"),auto_time_off_secs);
      #endif
    }
  }

}// END SubTask_AutoOff


/*******************************************************************************************************************
********************************************************************************************************************
************MQTT**************************************************************************************************
********************************************************************************************************************
********************************************************************************************************************/



void mInterfaceLight::ApplyGlobalBrightnesstoColour(RgbcctColor* colour){

  colour->R  = mapvalue(colour->R,  0, 255, 0, _briRGB);
  colour->G  = mapvalue(colour->G,  0, 255, 0, _briRGB);
  colour->B  = mapvalue(colour->B,  0, 255, 0, _briRGB);
  colour->WW = mapvalue(colour->WW, 0, 255, 0, _briCT);
  colour->WC = mapvalue(colour->WC, 0, 255, 0, _briCT);

}

float mInterfaceLight::HueN2F(uint16_t hue){
  return hue/360.0f;
}
// S at100toFloat
float mInterfaceLight::SatN2F(uint8_t sat){
  return sat/100.0f;
}
// B rt100toFloat
float mInterfaceLight::BrtN2F(uint8_t brt){
  return brt/100.0f;
}

// H ueFloatto360
uint16_t mInterfaceLight::HueF2N(float hue){
  return round(hue*360.0f);
}
// S atFloatto100
uint8_t mInterfaceLight::SatF2N(float sat){
  return round(sat*100.0f);
}
// B rtFloatto100
uint8_t mInterfaceLight::BrtF2N(float brt){
  return round(brt*100.0f);
}



// Generate random colour between two hsb colours
RgbTypeColor mInterfaceLight::GetRandomColour(RgbTypeColor colour1, RgbTypeColor colour2){
  // int random_hue = random(HueF2N(colour1.H),HueF2N(colour2.H));
  // int random_sat = random(SatF2N(colour1.S),SatF2N(colour2.S));
  // int random_brt = random(BrtF2N(colour1.B),BrtF2N(colour2.B));
  return RgbTypeColor(0);//HueN2F(random_hue),SatN2F(random_sat),BrtN2F(random_brt));
}








uint8_t mInterfaceLight::ConstructJSON_Settings(uint8_t json_method){

  char buffer[30];
  
  JsonBuilderI->Start();

  JsonBuilderI->Add_P(PM_JSON_TYPE, pCONT_set->Settings.light_settings.type);
  
  JsonBuilderI->Add_P(PM_JSON_HUE, getHue());
  JsonBuilderI->Add_P(PM_JSON_SAT, getSat());

  JsonBuilderI->Add_P(PM_JSON_BRIGHTNESS_RGB, getBriRGB());
  JsonBuilderI->Add_P(PM_JSON_BRIGHTNESS_CCT, getBriCT());


  JsonBuilderI->Add_P(PM_JSON_PIXELS_UPDATE_PERCENTAGE, animation.transition.pixels_to_update_as_percentage.val);
  #ifdef USE_MODULE_LIGHTS_ADDRESSABLE
  JsonBuilderI->Add_P(PM_JSON_PIXELS_UPDATE_NUMBER, GetPixelsToUpdateAsNumberFromPercentage(animation.transition.pixels_to_update_as_percentage.val));
  #endif // USE_MODULE_LIGHTS_ADDRESSABLE

  //   _subtype,
  //   _ct,
  //   scene.colour.WC,
  //   scene.colour.WW,
  //   _briCT,
  //   _color_mode,
  //   _ct_rgb_linked,
  //   fade.running,
  //   fade.start_ms,
  //   fade.duration_ms,
  //   fade.end_ms, //   pCONT_lPWM->fade_duration,
  //   pCONT_lPWM->fade_start,
  //   pwm_min,
  //   pwm_max,
  //   _pwm_multi_channels,
  //   _ct_min_range,
  //   _ct_max_range
  return JsonBuilderI->End();

}

uint8_t mInterfaceLight::ConstructJSON_Debug(uint8_t json_method){

  char buffer[30];
  
  JsonBuilderI->Start();

  // JsonBuilderI->Level_Start("singlecolour");
  //   JsonBuilderI->Add_P(PM_R", mode_singlecolour.colour.R);
  //   JsonBuilderI->Add_P(PM_G", mode_singlecolour.colour.G);
  //   JsonBuilderI->Add_P(PM_B", mode_singlecolour.colour.B);
  //   JsonBuilderI->Add_P(PM_WW", mode_singlecolour.colour.WW);
  //   JsonBuilderI->Add_P(PM_WC", mode_singlecolour.colour.WC);
  //   JsonBuilderI->Add_P(PM_WC", mode_singlecolour.colour.WC);
  // JsonBuilderI->Level_End();
  // JsonBuilderI->Level_Start("tasint_colour");
  //   JsonBuilderI->Add_P(PM_R", tasint_colour.R);
  //   JsonBuilderI->Add_P(PM_G", tasint_colour.G);
  //   JsonBuilderI->Add_P(PM_B", tasint_colour.B);
  //   JsonBuilderI->Add_P(PM_WW", tasint_colour.WW);
  //   JsonBuilderI->Add_P(PM_WC", tasint_colour.WC);
  //   JsonBuilderI->Add_P(PM_WC", tasint_colour.WC);
  // JsonBuilderI->Level_End();


  // JsonBuilderI->Array_AddArray("singlecolour", current_color, 5);   


  // JsonBuilderI->Level_Start("fade");
  //   JsonBuilderI->Add("running", fade.running);
  // JsonBuilderI->Level_End();
  
  //   _sat,
  //   _briRGB,
  //   scene.colour.R,
  //   scene.colour.G,
  //   scene.colour.B,
  //   _subtype,
  //   _ct,
  //   scene.colour.WC,
  //   scene.colour.WW,
  //   _briCT,
  //   _color_mode,
  //   _ct_rgb_linked,
  //   fade.start_ms,
  //   fade.duration_ms,
  //   fade.end_ms,
  //   entry_color[0],entry_color[1],entry_color[2],entry_color[3],entry_color[4],
  //   current_color[0],current_color[1],current_color[2],current_color[3],current_color[4],
  //   new_color[0],new_color[1],new_color[2],new_color[3],new_color[4],
  //   last_color[0],last_color[1],last_color[2],last_color[3],last_color[4],
  //   // color_remap[0],color_remap[1],color_remap[2],color_remap[3],color_remap[4],
  //   pCONT_lPWM->fade_start_10[0],pCONT_lPWM->fade_start_10[1],pCONT_lPWM->fade_start_10[2],pCONT_lPWM->fade_start_10[3],pCONT_lPWM->fade_start_10[4],
  //   pCONT_lPWM->fade_cur_10[0],pCONT_lPWM->fade_cur_10[1],pCONT_lPWM->fade_cur_10[2],pCONT_lPWM->fade_cur_10[3],pCONT_lPWM->fade_cur_10[4],
  //   pCONT_lPWM->fade_end_10[0],pCONT_lPWM->fade_end_10[1],pCONT_lPWM->fade_end_10[2],pCONT_lPWM->fade_end_10[3],pCONT_lPWM->fade_end_10[4],
  //   pCONT_lPWM->fade_duration,
  //   pCONT_lPWM->fade_start,
  //   pwm_min,
  //   pwm_max,
  //   _pwm_multi_channels,
  //   _ct_min_range,
  //   _ct_max_range,
  //   pCONT_set->Settings.light_settings.type
  // );
  return JsonBuilderI->End();

}






////////////////////// START OF MQTT /////////////////////////

void mInterfaceLight::MQTTHandler_Init(){

  mqtthandler_ptr = &mqtthandler_settings_teleperiod;
  mqtthandler_ptr->tSavedLastSent = millis();
  mqtthandler_ptr->flags.PeriodicEnabled = true;
  mqtthandler_ptr->flags.SendNow = true;
  mqtthandler_ptr->tRateSecs = pCONT_set->Settings.sensors.configperiod_secs; 
  mqtthandler_ptr->topic_type = MQTT_TOPIC_TYPE_TELEPERIOD_ID;
  mqtthandler_ptr->json_level = JSON_LEVEL_DETAILED;
  mqtthandler_ptr->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_SETTINGS_CTR;
  mqtthandler_ptr->ConstructJSON_function = &mInterfaceLight::ConstructJSON_Settings;

  
  mqtthandler_ptr = &mqtthandler_scene_teleperiod;
  mqtthandler_ptr->tSavedLastSent = millis();
  mqtthandler_ptr->flags.PeriodicEnabled = true;
  mqtthandler_ptr->flags.SendNow = true;
  mqtthandler_ptr->tRateSecs = pCONT_set->Settings.sensors.ifchanged_secs; 
  mqtthandler_ptr->topic_type = MQTT_TOPIC_TYPE_TELEPERIOD_ID;
  mqtthandler_ptr->json_level = JSON_LEVEL_DETAILED;
  mqtthandler_ptr->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_SCENE_CTR;
  mqtthandler_ptr->ConstructJSON_function = &mInterfaceLight::ConstructJSON_Scene;

  mqtthandler_ptr = &mqtthandler_debug_teleperiod;
  mqtthandler_ptr->tSavedLastSent = millis();
  mqtthandler_ptr->flags.PeriodicEnabled = true;
  mqtthandler_ptr->flags.SendNow = true;
  mqtthandler_ptr->tRateSecs = pCONT_set->Settings.sensors.ifchanged_secs; 
  mqtthandler_ptr->topic_type = MQTT_TOPIC_TYPE_TELEPERIOD_ID;
  mqtthandler_ptr->json_level = JSON_LEVEL_DETAILED;
  mqtthandler_ptr->postfix_topic = PM_MQTT_HANDLER_POSTFIX_TOPIC_DEBUG_CTR;
  mqtthandler_ptr->ConstructJSON_function = &mInterfaceLight::ConstructJSON_Debug;

} //end "MQTTHandler_Init"


void mInterfaceLight::MQTTHandler_Set_fSendNow(){

  mqtthandler_settings_teleperiod.flags.SendNow = true;
  // mqtthandler_animation_teleperiod.flags.SendNow = true;
  // mqtthandler_ambilight_teleperiod.flags.SendNow = true;
  mqtthandler_scene_teleperiod.flags.SendNow = true;

} //end "MQTTHandler_Init"


void mInterfaceLight::MQTTHandler_Set_TelePeriod(){

  mqtthandler_settings_teleperiod.tRateSecs = pCONT_set->Settings.sensors.teleperiod_secs;
  // // mqtthandler_animation_teleperiod.tRateSecs = pCONT_set->Settings.sensors.teleperiod_secs;
  // // mqtthandler_ambilight_teleperiod.tRateSecs = pCONT_set->Settings.sensors.teleperiod_secs;
  mqtthandler_scene_teleperiod.tRateSecs = pCONT_set->Settings.sensors.teleperiod_secs;
  
} //end "MQTTHandler_Set_TelePeriod"


void mInterfaceLight::MQTTHandler_Sender(uint8_t mqtt_handler_id){

  uint8_t mqtthandler_list_ids[] = {
    MQTT_HANDLER_SETTINGS_ID, MQTT_HANDLER_MODULE_SCENE_TELEPERIOD_ID, MQTT_HANDLER_MODULE_DEBUG_PARAMETERS_TELEPERIOD_ID
  };
  
  struct handler<mInterfaceLight>* mqtthandler_list_ptr[] = {
    &mqtthandler_settings_teleperiod, &mqtthandler_scene_teleperiod, &mqtthandler_debug_teleperiod
  };

  pCONT_mqtt->MQTTHandler_Command_Array_Group(*this, D_MODULE_LIGHTS_INTERFACE_ID,
    mqtthandler_list_ptr, mqtthandler_list_ids, 
    sizeof(mqtthandler_list_ids)/sizeof(mqtthandler_list_ids[0]),
    mqtt_handler_id
  );

}







/****
 * 
 * 
 * 
 * 
 * NOT NEEDED
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * */


void mInterfaceLight::LightSetPower(void)
{
// //  power = XdrvMailbox.index;
//   old_power = power;
//   //power = bitRead(XdrvMailbox.index, device -1);
//   uint32_t mask = 1;  // default mask
//   if (pwm_multi_channels) {
//     mask = (1 << subtype) - 1;   // wider mask
//   } else if (!light_controller.isCTRGBLinked()) {
//     mask = 3;   // we got 2 devices, for RGB and White
//   }
//   uint32_t shift = device - 1;
//   // If PWM multi_channels
//   // Ex: 3 Relays and 4 PWM - devices_present = 7, device = 4, subtype = 4
//   // Result: mask = 0b00001111 = 0x0F, shift = 3.
//   // Power bits we consider are: 0b01111000 = 0x78
//   // If regular situation: devices_present == subtype
//   power = (XdrvMailbox.index & (mask << shift)) >> shift;
//   if (wakeup_active) {
//     wakeup_active--;
//   }
// #ifdef DEBUG_LIGHT
//   AddLog_P2(LOG_LEVEL_TEST, "LightSetPower XdrvMailbox.index=%d old_power=%d power=%d mask=%d shift=%d",
//     XdrvMailbox.index, old_power, power, mask, shift);
// #endif
//   if (power != old_power) {
//     update = true;
//   }
//   LightAnimate();
}


void mInterfaceLight::LightPreparePower(power_t channels) {    // 1 = only RGB, 2 = only CT, 3 = both RGB and CT

#ifdef DEBUG_LIGHT
  // AddLog_P2(LOG_LEVEL_DEBUG, "LightPreparePower power=%d power=%d", power, power);
#endif
  // If multi-channels, then we only switch off channels with a value of zero
  // if (pwm_multi_channels) {
  //   for (uint32_t i = 0; i < subtype; i++) {
  //     if (bitRead(channels, i)) {
  //       // if channel is non-null, channel is supposed to be on, but it is off, do Power On
  //       if ((current_color[i]) && (!bitRead(power, i))) {
  //         if (!Settings.flag.not_power_linked) {  // SetOption20 - Control power in relation to Dimmer/Color/Ct changes
  //           ExecuteCommandPower(device + i, POWER_ON_NO_STATE, SRC_LIGHT);
  //         }
  //       } else {
  //         // if channel is zero and channel is on, set it off
  //         if ((0 == current_color[i]) && bitRead(power, i)) {
  //           ExecuteCommandPower(device + i, POWER_OFF_NO_STATE, SRC_LIGHT);
  //         }
  //       }
  // #ifdef USE_DOMOTICZ
  //       DomoticzUpdatePowerState(device + i);
  // #endif  // USE_DOMOTICZ
  //     }
  //   }
  // } else {
    // if (light_controller.isCTRGBLinked()) {   // linked, standard
    //   if (light_state.getBri() && !(power)) {
    //     if (!Settings.flag.not_power_linked) {  // SetOption20 - Control power in relation to Dimmer/Color/Ct changes
    //       ExecuteCommandPower(device, POWER_ON_NO_STATE, SRC_LIGHT);
    //     }
    //   } else if (!light_state.getBri() && power) {
    //     ExecuteCommandPower(device, POWER_OFF_NO_STATE, SRC_LIGHT);
    //   }
    // } else {
    //   // RGB
    //   if (channels & 1) {
    //     if (light_state.getBriRGB() && !(power & 1)) {
    //       if (!Settings.flag.not_power_linked) {  // SetOption20 - Control power in relation to Dimmer/Color/Ct changes
    //         ExecuteCommandPower(device, POWER_ON_NO_STATE, SRC_LIGHT);
    //       }
    //     } else if (!light_state.getBriRGB() && (power & 1)) {
    //       ExecuteCommandPower(device, POWER_OFF_NO_STATE, SRC_LIGHT);
    //     }
    //   }
    //   // White CT
    //   if (channels & 2) {
    //     if (light_state.getBriCT() && !(power & 2)) {
    //       if (!Settings.flag.not_power_linked) {  // SetOption20 - Control power in relation to Dimmer/Color/Ct changes
    //         ExecuteCommandPower(device + 1, POWER_ON_NO_STATE, SRC_LIGHT);
    //       }
    //     } else if (!light_state.getBriCT() && (power & 2)) {
    //       ExecuteCommandPower(device + 1, POWER_OFF_NO_STATE, SRC_LIGHT);
    //     }
    //   }
    // }

    // ExecuteCommandPower(0, POWER_ON_NO_STATE, SRC_LIGHT);


// #ifdef USE_DOMOTICZ
//     DomoticzUpdatePowerState(device);
// #endif  // USE_DOMOTICZ
//   }

//   if (Settings.flag3.hass_tele_on_power) {  // SetOption59 - Send tele/%topic%/STATE in addition to stat/%topic%/RESULT
//     MqttPublishTeleState();
//   }

// #ifdef DEBUG_LIGHT
//   AddLog_P2(LOG_LEVEL_DEBUG, "LightPreparePower End power=%d power=%d", power, power);
// #endif
//   power = power >> (device - 1);  // reset next state, works also with unlinked RGB/CT
  // LightState(0);
  
}




// convert channels to string, use Option 17 to foce decimal, unless force_hex
char* mInterfaceLight::LightGetColor(char* scolor, boolean force_hex)
{
  // if ((0 == Settings.light_scheme) || (!pwm_multi_channels)) {
  //   light_controller.UpdateFinalColourComponents();      // recalculate levels only if Scheme 0, otherwise we mess up levels
  // }
  // scolor[0] = '\0';
  // for (uint32_t i = 0; i < subtype; i++) {
  //   if (!force_hex && Settings.flag.decimal_text) {  // SetOption17 - Switch between decimal or hexadecimal output
  //     snprintf_P(scolor, LIGHT_COLOR_SIZE, PSTR("%s%s%d"), scolor, (i > 0) ? "," : "", current_color[i]);
  //   } else {
  //     snprintf_P(scolor, LIGHT_COLOR_SIZE, PSTR("%s%02X"), scolor, current_color[i]);
  //   }
  // }
  return scolor;
}

void mInterfaceLight::LightPowerOn(void)
{
//   if (light_state.getBri() && !(power)) {
//     ExecuteCommandPower(device, POWER_ON, SRC_LIGHT);
//   }
}

void mInterfaceLight::LightState(uint8_t append)
{
//   char scolor[LIGHT_COLOR_SIZE];
//   char scommand[33];
//   bool unlinked = !light_controller.isCTRGBLinked() && (subtype >= LST_RGBW);  // there are 2 power and dimmers for RGB and White

//   if (append) {
//     ResponseAppend_P(PSTR(","));
//   } else {
//     Response_P(PSTR("{"));
//   }
//   if (!pwm_multi_channels) {
//     if (unlinked) {
//       // RGB and W are unlinked, we display the second Power/Dimmer
//       ResponseAppend_P(PSTR("\"" D_RSLT_POWER "%d\":\"%s\",\"" D_JSON_DIMMER "%d\":%d"
//                            ",\"" D_RSLT_POWER "%d\":\"%s\",\"" D_JSON_DIMMER "%d\":%d"),
//                             device, GetStateText(power & 1), device, light_state.getDimmer(1),
//                             device + 1, GetStateText(power & 2 ? 1 : 0), device + 1, light_state.getDimmer(2));
//     } else {
//       GetPowerDevice(scommand, device, sizeof(scommand), Settings.flag.device_index_enable);  // SetOption26 - Switch between POWER or POWER1
//       ResponseAppend_P(PSTR("\"%s\":\"%s\",\"" D_JSON_DIMMER "\":%d"), scommand, GetStateText(power & 1),
//                       light_state.getDimmer());
//     }


//     if (subtype > LST_SINGLE) {
//       ResponseAppend_P(PSTR(",\"" D_JSON_COLOR "\":\"%s\""), LightGetColor(scolor));
//       if (LST_RGB <= subtype) {
//         uint16_t hue;
//         uint8_t  sat, bri;
//         light_state.getHSB(&hue, &sat, &bri);
//         sat = mapvalue(sat, 0, 255, 0, 100);
//         bri = mapvalue(bri, 0, 255, 0, 100);

//         ResponseAppend_P(PSTR(",\"" D_JSON_HSBCOLOR "\":\"%d,%d,%d\""), hue,sat,bri);
//       }
//       // Add White level
//       if ((LST_COLDWARM == subtype) || (LST_RGBW <= subtype)) {
//         ResponseAppend_P(PSTR(",\"" D_JSON_WHITE "\":%d"), light_state.getDimmer(2));
//       }
//       // Add CT
//       if ((LST_COLDWARM == subtype) || (LST_RGBCW == subtype)) {
//         ResponseAppend_P(PSTR(",\"" D_JSON_COLORTEMPERATURE "\":%d"), light_state.getCT());
//       }
//       // Add status for each channel
//       ResponseAppend_P(PSTR(",\"" D_JSON_CHANNEL "\":[" ));
//       for (uint32_t i = 0; i < subtype; i++) {
//         uint8_t channel_raw = current_color[i];
//         uint8_t channel = mapvalue(channel_raw,0,255,0,100);
//         // if non null, force to be at least 1
//         if ((0 == channel) && (channel_raw > 0)) { channel = 1; }
//         ResponseAppend_P(PSTR("%s%d" ), (i > 0 ? "," : ""), channel);
//       }
//       ResponseAppend_P(PSTR("]"));
//     }

//     if (append) {
//       if (subtype >= LST_RGB) {
//         ResponseAppend_P(PSTR(",\"" D_JSON_SCHEME "\":%d"), Settings.light_scheme);
//       }
//       if (max_scheme > LS_MAX) {
//         ResponseAppend_P(PSTR(",\"" D_JSON_WIDTH "\":%d"), Settings.light_width);
//       }
//       ResponseAppend_P(PSTR(",\"" D_JSON_FADE "\":\"%s\",\"" D_JSON_SPEED "\":%d,\"" D_JSON_LEDTABLE "\":\"%s\""),
//         GetStateText(Settings.light_fade), Settings.light_speed, GetStateText(Settings.light_correction));
//     }
//   } else {  // pwm_multi_channels
//     for (uint32_t i = 0; i < subtype; i++) {
//       GetPowerDevice(scommand, device + i, sizeof(scommand), 1);
//       uint32_t light_power_masked = power & (1 << i);    // the power value for this device
//       light_power_masked = light_power_masked ? 1 : 0;                    // convert to on/off
//       ResponseAppend_P(PSTR("\"%s\":\"%s\",\"" D_JSON_CHANNEL "%d\":%d,"), scommand, GetStateText(light_power_masked), device + i,
//         mapvalue(current_color[i], 0, 255, 0, 100));
//     }
//     ResponseAppend_P(PSTR("\"" D_JSON_COLOR "\":\"%s\""), LightGetColor(scolor));
//   }   // pwm_multi_channels

//   if (!append) {
//     ResponseJsonEnd();
//   }
}



// On entry we take the 5 channels 8 bits entry, and we apply Power modifiers
// I.e. shut down channels that are powered down
void mInterfaceLight::LightApplyPower(uint8_t new_color[LST_MAX], power_t power) {
  // If SetOption68, multi_channels

  //tmp 
  // uint8_t pwm_multi_channels= false;

  // if (pwm_multi_channels) {
  //   // if multi-channels, specifically apply the power bits
  //   for (uint32_t i = 0; i < LST_MAX; i++) {
  //     if (0 == bitRead(power,i)) {  // if power down bit is zero
  //       new_color[i] = 0;   // shut down this channel
  //     }
  //   }
  //   #ifdef DEBUG_LIGHT
  //   AddLog_P(LOG_LEVEL_TEST, PSTR("Animate>> power=%d new_color=[%d,%d,%d,%d,%d]"),
  //     pCONT_set->power, new_color[0], new_color[1], new_color[2],
  //     new_color[3], new_color[4]);
  //   #endif
  // } else {
    if (!isCTRGBLinked()) {
      // we have 2 power bits for RGB and White
      if (0 == (pCONT_set->power & 1)) {
        new_color[0] = new_color[1] = new_color[2] = 0;
      }
      if (0 == (pCONT_set->power & 2)) {
        new_color[3] = new_color[4] = 0;
      }
    } else 
    if (!pCONT_set->power) {
      for (uint32_t i = 0; i < LST_MAX; i++) {
        new_color[i] = 0;
      }
    }
  // }
}



void mInterfaceLight::BootMessage(){
  
  #ifdef ENABLE_LOG_LEVEL_COMMANDS
  AddLog_P(LOG_LEVEL_INFO, PSTR("BOOT: " "LightCount=%d"), light_size_count);
  #endif ENABLE_LOG_LEVEL_COMMANDS

}


//   void loadSettings() {
// #ifdef DEBUG_LIGHT
//     AddLog_P2(LOG_LEVEL_TEST, "LightControllerClass::loadSettings Settings.light_color (%d %d %d %d %d - %d)",
//       Settings.light_color[0], Settings.light_color[1], Settings.light_color[2],
//       Settings.light_color[3], Settings.light_color[4], Settings.light_dimmer);
//     AddLog_P2(LOG_LEVEL_TEST, "LightControllerClass::loadSettings Settings.light_settings.type/sub (%d %d)",
//       Settings.light_settings.type, subtype);
// #endif
//     if (_pwm_multi_channels) {
//     //   _state->setChannelsRaw(Settings.LightSettings.light_color);
//     } else {
//       // first try setting CW, if zero, it select RGB mode
//     //   _state->setCW(Settings.light_color[3], Settings.light_color[4], true);
//     //   _state->setRGB(Settings.light_color[0], Settings.light_color[1], Settings.light_color[2]);

//       // only if non-multi channel
//       // We apply dimmer in priority to RGB
//     //   uint8_t bri = _state->DimmerToBri(Settings.light_dimmer);

//     //   // The default values are #FFFFFFFFFF, in this case we avoid setting all channels
//     //   // at the same time, see #6534 and #8120
//     //   if ((DEFAULT_LIGHT_COMPONENT == Settings.light_color[0]) &&
//     //       (DEFAULT_LIGHT_COMPONENT == Settings.light_color[1]) &&
//     //       (DEFAULT_LIGHT_COMPONENT == Settings.light_color[2]) &&
//     //       (DEFAULT_LIGHT_COMPONENT == Settings.light_color[3]) &&
//     //       (DEFAULT_LIGHT_COMPONENT == Settings.light_color[4]) &&
//     //       (DEFAULT_LIGHT_DIMMER    == Settings.light_dimmer) ) {
//     //     if ((LST_COLDWARM == subtype) || (LST_RGBCW == subtype)) {
//     //       _state->setCW(255, 0);       // avoid having both white channels at 100%, zero second channel (#see 8120)
//     //     }
//     //     _state->setBriCT(bri);
//     //     _state->setBriRGB(bri);
//     //     _state->setColorMode(LCM_RGB);
//       }
//     //   if (Settings.light_color[0] + Settings.light_color[1] + Settings.light_color[2] > 0) {
//     //     _state->setBriRGB(bri);
//     //   } else {
//     //     _state->setBriCT(bri);
//     //   }
//     //}
//   }


// save the current light state to Settings.
void mInterfaceLight::saveSettings() {
// //     if (pwm_multi_channels) {
// //       // simply save each channel
// //       _state->getChannelsRaw(Settings.light_color);
// //       Settings.light_dimmer = 100;    // arbitrary value, unused in this mode
// //     } else {
// //       uint8_t cm = _state->getColorMode();

// //       memset(&Settings.light_color[0], 0, sizeof(Settings.light_color));    // clear all channels
// //       if (LCM_RGB & cm) {   // can be either LCM_RGB or LCM_BOTH
// //         _state->getRGB(&Settings.light_color[0], &Settings.light_color[1], &Settings.light_color[2]);
// //         Settings.light_dimmer = _state->BriToDimmer(_state->getBriRGB());
// //         // anyways we always store RGB with BrightnessRGB
// //         if (LCM_BOTH == cm) {
// //           // then store at actual brightness CW/WW if dual mode
// //           _state->getActualRGBCW(nullptr, nullptr, nullptr, &Settings.light_color[3], &Settings.light_color[4]);
// //         }
// //       } else if (LCM_CT == cm) {    // cm can only be LCM_CT
// //         _state->getCW(&Settings.light_color[3], &Settings.light_color[4]);
// //         Settings.light_dimmer = _state->BriToDimmer(_state->getBriCT());
// //       }
// //     }
// // #ifdef DEBUG_LIGHT
// //     AddLog_P2(LOG_LEVEL_TEST, "LightControllerClass::saveSettings Settings.light_color (%d %d %d %d %d - %d)",
// //       Settings.light_color[0], Settings.light_color[1], Settings.light_color[2],
// //       Settings.light_color[3], Settings.light_color[4], Settings.light_dimmer);
// // #endif
}


/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/****************MOVED FROM ADDRESABLE and deemed "common" ***********************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************
/***************************************************************************************************************************************************************************/







uint32_t mInterfaceLight::WebColorFromColourMap(uint8_t i)
{
  RgbColor rgb = RgbColor(GetHsbColour(i));
  uint32_t tcolor = (rgb.R << 16) | (rgb.G << 8) | rgb.B;
  return tcolor;
}
uint32_t mInterfaceLight::WebColorFromColourType(RgbColor rgb)
{
  uint32_t tcolor = (rgb.R << 16) | (rgb.G << 8) | rgb.B;
  return tcolor;
}



















































































































/****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ************************************************************************** 
 ************************************************************************** 
 ************************************************************************** 
 *START                  "Setters" aka internal as "light_controller", dont use directly
 *****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ************************************************************************* 
 ************************************************************************** 
 ************************************************************************** 
 *******************************************************************************/



// This function is a bit hairy, it will try to match the required
// colormode with the features of the device:
//   LST_NONE:      LCM_RGB
//   LST_SINGLE:    LCM_RGB
//   LST_COLDWARM:  LCM_CT
//   LST_RGB:       LCM_RGB
//   LST_RGBW:      LCM_RGB, LCM_CT or LCM_BOTH
//   LST_RGBCW:     LCM_RGB, LCM_CT or LCM_BOTH
uint8_t mInterfaceLight::setColorMode(uint8_t cm) {
  uint8_t prev_cm = _color_mode;
  if (cm < LCM_RGB) { cm = LCM_RGB; }
  if (cm > LCM_BOTH) { cm = LCM_BOTH; }
  uint8_t maxbri = (_briRGB >= _briCT) ? _briRGB : _briCT;

  switch (_subtype) {
    case LST_COLDWARM:
      _color_mode = LCM_CT;
      break;
    case LST_NONE:
    case LST_SINGLE:
    case LST_RGB:
    default:
      _color_mode = LCM_RGB;
      break;
    case LST_RGBW:
    case LST_RGBCW:
      _color_mode = cm;
      break;
  }
  if (LCM_RGB == _color_mode) {
    _briCT = 0;
    if (0 == _briRGB) { _briRGB = maxbri; }
  }
  if (LCM_CT == _color_mode) {
    _briRGB = 0;
    if (0 == _briCT) { _briCT = maxbri; }
  }
#ifdef DEBUG_LIGHT
  AddLog_P(LOG_LEVEL_DEBUG_MORE, PSTR("setColorMode prev_cm (%d) req_cm (%d) new_cm (%d) subtype (%d)"), prev_cm, cm, _color_mode, _subtype);
#endif
  return prev_cm;
}


uint8_t mInterfaceLight::getColorMode() {
  return _color_mode;
}

void mInterfaceLight::addRGBMode() {  
  // AddLog_P(LOG_LEVEL_TEST, PSTR("f::addRGBMode"));
  setColorMode(_color_mode | LCM_RGB);
}
void mInterfaceLight::addCTMode() {
  // AddLog_P(LOG_LEVEL_TEST, PSTR("f::addCTMode"));
  setColorMode(_color_mode | LCM_CT);
}

// Get RGB color, always at full brightness (ie. one of the components is 255)
void mInterfaceLight::getRGB(uint8_t *r, uint8_t *g, uint8_t *b) {
  if (r) { *r = tasint_colour.R; }
  if (g) { *g = tasint_colour.G; }
  if (b) { *b = tasint_colour.B; }
}

// get full brightness values for warm and cold channels.
// either w=c=0 (off) or w+c >= 255
void mInterfaceLight::getCW(uint8_t *rc, uint8_t *rw) {
  if (rc) { *rc = tasint_colour.WC; }
  if (rw) { *rw = tasint_colour.WW; }
}

// Get the actual values for each channel, ie multiply with brightness
void mInterfaceLight::getActualRGBCW(uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *c, uint8_t *w) {

  bool rgb_channels_on = _color_mode & LCM_RGB;
  bool ct_channels_on =   _color_mode & LCM_CT;

  #ifdef ENABLE_LOG_LEVEL_INFO
    AddLog_P(LOG_LEVEL_DEBUG_MORE, PSTR("bgetActualRGBCW result %d,%d,%d,%d,%d %d,%d"),
    tasint_colour.R,
    tasint_colour.G,
    tasint_colour.B,
    tasint_colour.WC,
    tasint_colour.WW,
    // *r,*g,*b,*w,*c,  
     _briRGB,_briCT);
  #endif
  
  if (r) { *r = rgb_channels_on ? mapvalue(tasint_colour.R, 0, 255, 0, _briRGB) : 0; }
  if (g) { *g = rgb_channels_on ? mapvalue(tasint_colour.G, 0, 255, 0, _briRGB) : 0; }
  if (b) { *b = rgb_channels_on ? mapvalue(tasint_colour.B, 0, 255, 0, _briRGB) : 0; }

  if (c) { *c = ct_channels_on  ? mapvalue(tasint_colour.WC, 0, 255, 0, _briCT) : 0; }
  if (w) { *w = ct_channels_on  ? mapvalue(tasint_colour.WW, 0, 255, 0, _briCT) : 0; }

  #ifdef ENABLE_LOG_LEVEL_INFO
    AddLog_P(LOG_LEVEL_DEBUG_MORE, PSTR("agetActualRGBCW result %d,%d,%d,%d,%d %d,%d"),*r,*g,*b,*w,*c,   _briRGB,_briCT);
  #endif

}

uint8_t mInterfaceLight::getChannels(uint8_t *channels) {
  getActualRGBCW(&channels[0], &channels[1], &channels[2], &channels[3], &channels[4]);
}

void mInterfaceLight::getChannelsRaw(uint8_t *channels) {
    channels[0] = tasint_colour.R;
    channels[1] = tasint_colour.G;
    channels[2] = tasint_colour.B;
    channels[3] = tasint_colour.WC;
    channels[4] = tasint_colour.WW;
}

void mInterfaceLight::getHSB(uint16_t *hue, uint8_t *sat, uint8_t *bri) {
  if (hue) { *hue = _hue; }
  if (sat) { *sat = _sat; }
  if (bri) { *bri = _briRGB; }
}

// getBri() is guaranteed to give the same result as setBri() - no rounding errors.
uint8_t mInterfaceLight::getBri(void) {
  // return the max of _briCT and _briRGB
  return (_briRGB >= _briCT) ? _briRGB : _briCT;
}

// get the white Brightness
uint8_t mInterfaceLight::getBriCT() {
  return _briCT;
}


uint8_t mInterfaceLight::DimmerToBri(uint8_t dimmer) {
  return mapvalue(dimmer, 0, 100, 0, 255);  // 0..255
}

uint8_t mInterfaceLight::BriToDimmer(uint8_t bri) {
  uint8_t dimmer = mapvalue(bri, 0, 255, 0, 100);
  // if brightness is non zero, force dimmer to be non-zero too
  if ((dimmer == 0) && (bri > 0)) { dimmer = 1; }
  return dimmer;
}

uint8_t mInterfaceLight::getDimmer(uint32_t mode) {
  uint8_t bri;
  switch (mode) {
    case 1:
      bri = getBriRGB();
      break;
    case 2:
      bri = getBriCT();
      break;
    default:
      bri = getBri();
      break;
  }
  return BriToDimmer(bri);
}


uint16_t mInterfaceLight::getCT(){
  return _ct; // 153..500, or CT_MIN..CT_MAX
}

// get the CT value within the range into a 10 bits 0..1023 value
uint16_t mInterfaceLight::getCT10bits() {
  return mapvalue(_ct, _ct_min_range, _ct_max_range, 0, 1023);
}

void mInterfaceLight::setCTRange(uint16_t ct_min_range, uint16_t ct_max_range) {
  _ct_min_range = ct_min_range;
  _ct_max_range = ct_max_range;
}

void mInterfaceLight::getCTRange(uint16_t *ct_min_range, uint16_t *ct_max_range) {
  if (ct_min_range) { *ct_min_range = _ct_min_range; }
  if (ct_max_range) { *ct_max_range = _ct_max_range; }
}



// setters -- do not use directly, use the light_controller instead
// sets both master Bri and whiteBri
void mInterfaceLight::setBri(uint8_t bri) {
  setBriRGB(_color_mode & LCM_RGB ? bri : 0);
  setBriCT(_color_mode & LCM_CT ? bri : 0);
#ifdef DEBUG_LIGHT
  AddLog_P(LOG_LEVEL_TEST, PSTR("setBri RGB raw (%d %d %d) HS (%d %d) bri (%d)"), tasint_colour.R, tasint_colour.G, tasint_colour.B, _hue, _sat, _briRGB);
#endif
}

// changes the RGB brightness alone
uint8_t mInterfaceLight::setBriRGB(uint8_t bri_rgb) {
  uint8_t prev_bri = _briRGB;
  _briRGB = bri_rgb;

//needs to map in to RGB? or I need to keep RGBCCT as colour only, with these brightness separate


  if (bri_rgb > 0) { addRGBMode(); }
  return prev_bri;
}

// changes the RGB brightness alone
uint8_t mInterfaceLight::setBriRGB_As_Percentage(uint8_t bri_rgb) {
  return setBriRGB(mapvalue(bri_rgb, 0,100, 0,255));
}

// changes the white brightness alone
uint8_t mInterfaceLight::setBriCT(uint8_t bri_ct) {
  uint8_t prev_bri = _briCT;
  _briCT = bri_ct;
  if (bri_ct > 0) { addCTMode(); }
  return prev_bri;
}

uint8_t mInterfaceLight::getBriRGB() {
  return _briRGB;
}

void mInterfaceLight::setDimmer(uint8_t dimmer) {
  setBri(DimmerToBri(dimmer));
}

void mInterfaceLight::setCT(uint16_t ct) {
  if (0 == ct) {
    // disable ct mode
    setColorMode(LCM_RGB);  // try deactivating CT mode, setColorMode() will check which is legal
  } else {
    ct = (ct < CT_MIN ? CT_MIN : (ct > CT_MAX ? CT_MAX : ct));
    tasint_colour.WW = mapvalue(ct, _ct_min_range, _ct_max_range, 0, 255);
    tasint_colour.WC = 255 - tasint_colour.WW;
    _ct = ct;
    addCTMode();
  }
#ifdef DEBUG_LIGHT
  AddLog_P(LOG_LEVEL_INFO, PSTR("setCT RGB raw (%d %d %d) HS (%d %d) briRGB (%d) briCT (%d) CT (%d)"), tasint_colour.R, tasint_colour.G, tasint_colour.B, _hue, _sat, _briRGB, _briCT, _ct);
#endif
}


// Manually set Cold/Warm channels.
// There are two modes:
// 1. (free_range == false, default)
//    In this mode there is only one virtual white channel with color temperature
//    As a side effect, WC+WW = 255. It means also that the sum of light power
//    from white LEDs is always equal to briCT. It is not possible here
//    to set both white LEDs at full power, hence protecting power supplies
//    from overlaoding.
// 2. (free_range == true)
//    In this mode, values of WC and WW are free -- both channels can be set
//    at full power.
//    In this mode, we always scale both channels so that one at least is 255.
// We automatically adjust briCT to have the right values of channels
void mInterfaceLight::setCW(uint8_t c, uint8_t w, bool free_range) {
  uint16_t max = (w > c) ? w : c;   // 0..255
  uint16_t sum = c + w;
  if (sum <= 257) { free_range = false; }    // if we don't allow free range or if sum is below 255 (with tolerance of 2)

  if (0 == max) {
    _briCT = 0;       // brightness set to null
      #ifdef ENABLE_LOG_LEVEL_COMMANDS
  AddLog_P(LOG_LEVEL_TEST, PSTR("f::addCTMode (LCM_RGB)"));
      #endif //  ENABLE_LOG_LEVEL_COMMANDS
    setColorMode(LCM_RGB);  // try deactivating CT mode, setColorMode() will check which is legal
  } else {
    if (!free_range) {
      // we need to normalize to sum = 255
      tasint_colour.WW = mapvalue(w, 0, sum, 0, 255);
      tasint_colour.WC = 255 - tasint_colour.WW;
    } else {  // we normalize to max = 255
      tasint_colour.WW = mapvalue(w, 0, max, 0, 255);
      tasint_colour.WC = mapvalue(c, 0, max, 0, 255);
    }
    _ct = mapvalue(w, 0, sum, _ct_min_range, _ct_max_range);
    addCTMode();   // activate CT mode if needed
    if (_color_mode & LCM_CT) { _briCT = free_range ? max : (sum > 255 ? 255 : sum); }
  }
  #ifdef DEBUG_LIGHT
  AddLog_P(LOG_LEVEL_DEBUG, PSTR("setCW CW (%d %d) CT (%d) briCT (%d)"), c, w, _ct, _briCT);
  #endif
}

// sets RGB and returns the Brightness. Bri is updated unless keep_bri is true
uint8_t mInterfaceLight::setRGB(uint8_t r, uint8_t g, uint8_t b, bool keep_bri) {
  
  uint16_t hue;
  uint8_t  sat;
  #ifdef DEBUG_LIGHT
    AddLog_P(LOG_LEVEL_DEBUG_MORE, PSTR("setRGB RGB input (%d %d %d)"), r, g, b);
  #endif

  uint8_t max = (r > g && r > b) ? r : (g > b) ? g : b;   // 0..255

  if (0 == max) {
    r = g = b = 255;
    setColorMode(LCM_CT);   // try deactivating RGB, setColorMode() will check if this is legal
  } else {
    if (255 > max) {        // we need to normalize rgb
      r = mapvalue(r, 0, max, 0, 255);
      g = mapvalue(g, 0, max, 0, 255);
      b = mapvalue(b, 0, max, 0, 255);
    }
    addRGBMode();
  }
  if (!keep_bri) {
    _briRGB = (_color_mode & LCM_RGB) ? max : 0;
  }

  RgbToHsb(r, g, b, &hue, &sat, nullptr);
  tasint_colour.R = r;
  tasint_colour.G = g;
  tasint_colour.B = b;
  _hue = hue;
  _sat = sat;
#ifdef DEBUG_LIGHT
  AddLog_P(LOG_LEVEL_DEBUG, PSTR("setRGB RGB raw (%d %d %d) HS (%d %d) bri (%d)"), tasint_colour.R, tasint_colour.G, tasint_colour.B, _hue, _sat, _briRGB);
#endif
  return max;
}

void mInterfaceLight::setHS(uint16_t hue, uint8_t sat) {
  uint8_t r, g, b;
  HsToRgb(hue, sat, &r, &g, &b);
  
  tasint_colour.R = r;
  tasint_colour.G = g;
  tasint_colour.B = b;

  _hue = hue;
  _sat = sat;
  addRGBMode();
#ifdef DEBUG_LIGHT
  AddLog_P(LOG_LEVEL_DEBUG, PSTR("setHS HS (%d %d) rgb (%d %d %d)"), hue, sat, r, g, b);
  AddLog_P(LOG_LEVEL_DEBUG, PSTR("setHS RGB raw (%d %d %d) HS (%d %d) bri (%d)"), tasint_colour.R, tasint_colour.G, tasint_colour.B, _hue, _sat, _briRGB);
#endif
}

// set all 5 channels at once, don't modify the values in ANY way
// Channels are: R G B CW WW
void mInterfaceLight::setChannelsRaw(uint8_t *channels) {
  tasint_colour.R = channels[0];
  tasint_colour.G = channels[1];
  tasint_colour.B = channels[2];
  tasint_colour.WC = channels[3];
  tasint_colour.WW = channels[4];
}


void mInterfaceLight::setChannelsRaw(uint8_t r, uint8_t g, uint8_t b, uint8_t wc, uint8_t ww) {
  tasint_colour.R = r;
  tasint_colour.G = g;
  tasint_colour.B = b;
  tasint_colour.WC = wc;
  tasint_colour.WW = ww;

}


void mInterfaceLight::setChannels(uint8_t r, uint8_t g, uint8_t b, uint8_t wc, uint8_t ww) {

  uint8_t buffer[5];
  buffer[0] = r; 
  buffer[1] = g; 
  buffer[2] = b; 
  buffer[3] = wc; 
  buffer[4] = ww; 
  setChannels(buffer);

}

// set all 5 channels at once.
// Channels are: R G B CW WW
// Brightness is automatically recalculated to adjust channels to the desired values
void mInterfaceLight::setChannels(uint8_t *channels) {
  setRGB(channels[0], channels[1], channels[2]);
  setCW(channels[3], channels[4], true);  // free range for WC and WW
#ifdef DEBUG_LIGHT
  AddLog_P(LOG_LEVEL_DEBUG, PSTR("setChannels (%d %d %d %d %d)"), channels[0], channels[1], channels[2], channels[3], channels[4]);
  AddLog_P(LOG_LEVEL_DEBUG, PSTR("setChannels CT (%d) briRGB (%d) briCT (%d)"), _ct, _briRGB, _briCT);
  AddLog_P(LOG_LEVEL_DEBUG, PSTR("setChannels Actuals (%d %d %d %d %d)"), tasint_colour.R, tasint_colour.G, tasint_colour.B, tasint_colour.WC, tasint_colour.WW);
#endif
}

// // new version with only integer computing
// // brightness is not needed, it is controlled via Dimmer
void mInterfaceLight::RgbToHsb(uint8_t ir, uint8_t ig, uint8_t ib, uint16_t *r_hue, uint8_t *r_sat, uint8_t *r_bri) {
  uint32_t r = ir;
  uint32_t g = ig;
  uint32_t b = ib;
  uint32_t max = (r > g && r > b) ? r : (g > b) ? g : b;   // 0..255
  uint32_t min = (r < g && r < b) ? r : (g < b) ? g : b;   // 0..255
  uint32_t d = max - min;   // 0..255

  uint16_t hue = 0;   // hue value in degrees ranges from 0 to 359
  uint8_t sat = 0;    // 0..255
  uint8_t bri = max;  // 0..255

  if (d != 0) {
    sat = mapvalue(d, 0, max, 0, 255);
    if (r == max) {
      hue = (g > b) ?       mapvalue(g-b,0,d,0,60) : 360 - mapvalue(b-g,0,d,0,60);
    } else if (g == max) {
      hue = (b > r) ? 120 + mapvalue(b-r,0,d,0,60) : 120 - mapvalue(r-b,0,d,0,60);
    } else {
      hue = (r > g) ? 240 + mapvalue(r-g,0,d,0,60) : 240 - mapvalue(g-r,0,d,0,60);
    }
    hue = hue % 360;    // 0..359
  }

  if (r_hue) *r_hue = hue;
  if (r_sat) *r_sat = sat;
  if (r_bri) *r_bri = bri;
#ifdef DEBUG_LIGHT
  AddLog_P(LOG_LEVEL_DEBUG_MORE, "RgbToHsb rgb (%d %d %d) hsb (%d %d %d)", r, g, b, hue, sat, bri);
#endif
}

// uint32_t to uint8_t might cause issues
void mInterfaceLight::HsToRgb(uint16_t hue, uint8_t sat, uint8_t *r_r, uint8_t *r_g, uint8_t *r_b) {
  uint8_t r = 255; // default to white
  uint8_t g = 255;
  uint8_t b = 255; // we take brightness at 100%, brightness should be set separately
  hue = hue % 360;  // normalize to 0..359
  if (sat > 0) {
    uint8_t i = hue / 60;   // quadrant 0..5
    uint8_t f = hue % 60;   // 0..59
    uint8_t q = 255 - mapvalue(f, 0, 60, 0, sat);  // 0..59
    uint8_t p = 255 - sat;
    uint8_t t = 255 - mapvalue(60 - f, 0, 60, 0, sat);
    switch (i) {
      case 0: g = t; b = p; break;
      case 1: r = q; b = p; break;
      case 2: r = p; b = t; break;
      case 3: r = p; g = q; break;
      case 4: r = t; g = p; break;
      default: g = p; b = q; break;
      }
    }
  if (r_r)  *r_r = r;
  if (r_g)  *r_g = g;
  if (r_b)  *r_b = b;
}


// Matrix 3x3 multiplied to a 3 vector, result in a 3 vector
// void mInterfaceLight::mat3x3(const float *mat33, const float *vec3, float *res3) {
//   for (uint8_t i = 0; i < 3; i++) {
//     const float * v = vec3;
//     *res3 = 0.0f;
//     for (uint8_t j = 0; j < 3; j++) {
//       *res3 += *mat33++ * *v++;
//     }
//     res3++;
//   }
// }


void mInterfaceLight::setSubType(uint8_t sub_type) {
  _subtype = sub_type;
}


bool mInterfaceLight::CommandSet_RGBCT_Linked(bool ct_rgb_linked) {
  
  #ifdef ENABLE_LOG_LEVEL_COMMANDS
  AddLog_P(LOG_LEVEL_COMMANDS, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_RGBCCT_LINKED)), ct_rgb_linked);
  #endif // ENABLE_LOG_LEVEL_COMMANDS

  bool prev = _ct_rgb_linked;
  if (_pwm_multi_channels) {
    _ct_rgb_linked = false;   // force to false if _pwm_multi_channels is set
  } else {
    _ct_rgb_linked = ct_rgb_linked;
  }
  return prev;
}


bool mInterfaceLight::isCTRGBLinked() {
  return _ct_rgb_linked;
}


bool mInterfaceLight::setPWMMultiChannel(bool pwm_multi_channels) {
  bool prev = _pwm_multi_channels;
  _pwm_multi_channels = pwm_multi_channels;
  if (pwm_multi_channels)  CommandSet_RGBCT_Linked(false);    // if pwm multi channel, then unlink RGB and CT
  return prev;
}


bool mInterfaceLight::isPWMMultiChannel(void) {
  return _pwm_multi_channels;
}



// If SetOption68 is set, get the brightness for a specific device
uint8_t mInterfaceLight::LightGetBri(uint8_t device) {
  uint8_t bri = 254;   // default value if relay
  if (pwm_multi_channels) {
    if ((device >= device) && (device < device + LST_MAX) && (device <= pCONT_set->devices_present)) {
      bri = current_color[device - device];
    }
  } else if (isCTRGBLinked()) {   // standard behavior
    if (device == device) {
      bri = getBri();
    }
  } else {    // unlinked
    if (device == device) {
      bri = getBriRGB();
    } else if (device == device + 1) {
      bri = getBriCT();
    }
  }
  return bri;
}

// If SetOption68 is set, set the brightness for a specific device
void mInterfaceLight::LightSetBri(uint8_t device, uint8_t bri) {
  if (pwm_multi_channels) {
    if ((device >= device) && (device < device + LST_MAX) && (device <= pCONT_set->devices_present)) {
      current_color[device - device] = bri;
      changeChannels(current_color);
    }
  } else if (isCTRGBLinked()) {  // standard
    if (device == device) {
      changeBri(bri);
    }
  } else {  // unlinked
    if (device == device) {
      CommandSet_BrtRGB_255(bri);
    } else if (device == device + 1) {
      CommandSet_BrtCT_255(bri);
    }
  }
}

void mInterfaceLight::CommandSet_ColourTemp(uint16_t ct)
{
  
  #ifdef ENABLE_LOG_LEVEL_COMMANDS
  AddLog_P(LOG_LEVEL_COMMANDS, PSTR(D_LOG_LIGHT D_JSON_COMMAND_NVALUE_K(D_JSON_CCT_TEMP)), LightGetColorTemp());
  #endif //#ifdef ENABLE_LOG_LEVEL_COMMANDS

/* Color Temperature (https://developers.meethue.com/documentation/core-concepts)
 * ct = 153 = 6500K = Cold = CCWW = FF00
 * ct = 600 = 2000K = Warm = CCWW = 00FF  */
  // don't set CT if not supported
  if ((LST_COLDWARM != subtype) && (LST_RGBCW != subtype)) {
    return;
  }
  changeCTB(ct, getBriCT());
}

uint16_t mInterfaceLight::LightGetColorTemp(void)
{
  // don't calculate CT for unsupported devices
  if ((LST_COLDWARM != subtype) && (LST_RGBCW != subtype)) {
    return 0;
  }
  return (getColorMode() & LCM_CT) ? getCT() : 0;
}


// is the channel a regular PWM or ColorTemp control
bool mInterfaceLight::isChannelCT(uint32_t channel) {
  // if (
  //   // (MODULE_PHILIPS_ID == pCONT_set->my_module_type) || 
  //   (pCONT_set->Settings.flag4.pwm_ct_mode)) {
    if ((LST_COLDWARM == subtype) && (1 == channel)) { return true; }   // PMW reserved for CT
    if ((LST_RGBCW == subtype) && (4 == channel)) { return true; }   // PMW reserved for CT
  // }
  return false;
}





void mInterfaceLight::changeCTB(uint16_t new_ct, uint8_t briCT) {
  /* Color Temperature (https://developers.meethue.com/documentation/core-concepts)
    * ct = 153 = 6500K = Cold = CCWW = FF00
    * ct = 500 = 2000K = Warm = CCWW = 00FF
    */
  // don't set CT if not supported
  if ((LST_COLDWARM != subtype) && (LST_RGBW > subtype)) {
    return;
  }
  setCT(new_ct);
  setBriCT(briCT);
  if (_ct_rgb_linked) { setColorMode(LCM_CT); }   // try to force CT
  // saveSettings();
  UpdateFinalColourComponents();
  //debugLogs();
}


void mInterfaceLight::changeDimmer(uint8_t dimmer, uint32_t mode) {
  uint8_t bri = mapvalue(dimmer, 0, 100, 0, 255);
  switch (mode) {
    case 1:
      CommandSet_BrtRGB_255(bri);
      if (_ct_rgb_linked) { 
      #ifdef ENABLE_LOG_LEVEL_COMMANDS
        AddLog_P(LOG_LEVEL_TEST, PSTR("f::addCTMode rgb linked rgb"));
      #endif // ENABLE_LOG_LEVEL_COMMANDS
        setColorMode(LCM_RGB);
      }   // try to force CT
      break;
    case 2:
      CommandSet_BrtCT_255(bri);
      if (_ct_rgb_linked) { 
      #ifdef ENABLE_LOG_LEVEL_COMMANDS
        AddLog_P(LOG_LEVEL_TEST, PSTR("f::addCTMode ct linked rgb"));
      #endif// ENABLE_LOG_LEVEL_COMMANDS
        setColorMode(LCM_CT); 
      }   // try to force CT
      break;
    default:
      changeBri(bri);
      break;
  }
}

void mInterfaceLight::changeBri(uint8_t bri) {
  setBri(bri);
  // saveSettings();
  UpdateFinalColourComponents();
}


void mInterfaceLight::CommandSet_BrtCT_255(uint8_t bri) {
  setBriCT(bri);
  // saveSettings();
  UpdateFinalColourComponents();
}

void mInterfaceLight::changeRGB(uint8_t r, uint8_t g, uint8_t b, bool keep_bri) {
  setRGB(r, g, b, keep_bri);
  if (_ct_rgb_linked) { 
    #ifdef ENABLE_LOG_LEVEL_INFO
    AddLog_P(LOG_LEVEL_TEST, PSTR("f::addCTMode ct linked rgb changeRGB"));
    #endif// ENABLE_LOG_LEVEL_INFO
    setColorMode(LCM_RGB); 
  }   // try to force RGB
  // saveSettings();
  UpdateFinalColourComponents();
}

//   calculate the levels for each channel
//   if no parameter, results are stored in current_color
void mInterfaceLight::UpdateFinalColourComponents(uint8_t *_current_color) {

  // AddLog_P(LOG_LEVEL_INFO, PSTR("UpdateFinalColourComponents"));

  if(mode_singlecolour.flag.update_colour_on_input_command){
      #ifdef ENABLE_LOG_LEVEL_COMMANDS
    AddLog_P(LOG_LEVEL_INFO, PSTR("mode_singlecolour.flag.update_colour_on_input_command"));
      #endif // ENABLE_LOG_LEVEL_COMMANDS
    mode_singlecolour.name_id = MODE_SINGLECOLOUR_COLOURSCENE_ID;
  }

  DEBUG_LINE;

  uint8_t r,g,b,c,w,briRGB,briCT;
  if (_current_color == nullptr) { 
    //AddLog_P(LOG_LEVEL_TEST, PSTR("f:_current_color == nullptr use global"));    
    _current_color = current_color; 
  }else{
   // AddLog_P(LOG_LEVEL_TEST, PSTR("NOT f:_current_color == nullptr use global"));    
  }


  // if (_pwm_multi_channels) { // if PWM multi channel, no more transformation required
  //   _state->getChannelsRaw(current_color);
  //   return;
  // }

  DEBUG_LINE;

  // #ifdef ENABLE_LOG_LEVEL_DEBUG
  // AddLog_P(LOG_LEVEL_DEBUG_MORE, "BEFORE brightness _current_color (%d %d %d %d %d)",
  //   tasint_colour.R,tasint_colour.G,tasint_colour.B,tasint_colour.WW,tasint_colour.WC
  // );
  // #endif // ENABLE_LOG_LEVEL_DEBUG_MORE

  getActualRGBCW(&r,&g,&b,&c,&w);
  briRGB = getBriRGB();
  briCT  = getBriCT();
  
  #ifdef ENABLE_LOG_LEVEL_DEBUG
  AddLog_P(LOG_LEVEL_DEBUG_MORE, "After1 brightness _current_color (%d %d %d %d %d -- rgb%d ct%d)",
    r,g,b,c,w,briRGB,briCT
  );
  #endif // ENABLE_LOG_LEVEL_DEBUG_MORE

  // record previous colour
  memcpy(last_colour, current_color, sizeof(last_colour));

  DEBUG_LINE;

  _current_color[0] = _current_color[1] = _current_color[2] = 0;
  _current_color[3] = _current_color[4] = 0;
  switch (subtype) {
    case LST_NONE:
      _current_color[0] = 255;
      break;
    case LST_SINGLE:
      _current_color[0] = briRGB;
      break;
    case LST_COLDWARM:
      _current_color[0] = c;
      _current_color[1] = w;
      break;
    case LST_RGBW:
    case LST_RGBCW:
      if (LST_RGBCW == subtype) {
        _current_color[3] = c;
        _current_color[4] = w;
      } else {
        _current_color[3] = briCT;
      }
      // continue
    case LST_RGB:
      _current_color[0] = r;
      _current_color[1] = g;
      _current_color[2] = b;
      break;
  }

  animation.flags.ColourComponentsUpdatedButNotYetApplied = true;
   
  // #endif // ENABLE_LOG_LEVEL_DEBUG_MORE
  #ifdef ENABLE_LOG_LEVEL_DEBUG
  AddLog_P(LOG_LEVEL_DEBUG_MORE, "AFTER2 brightness _current_color (%d %d %d %d %d)",
    _current_color[0],_current_color[1],_current_color[2],_current_color[3],_current_color[4]
  );
  #endif // ENABLE_LOG_LEVEL_DEBUG_MORE

  // mqtthandler_debug_teleperiod.flags.SendNow = true;

  DEBUG_LINE;

}

void mInterfaceLight::changeHSB(uint16_t hue, uint8_t sat, uint8_t briRGB) {
  setHS(hue, sat);
  setBriRGB(briRGB);
  if (_ct_rgb_linked) { setColorMode(LCM_RGB); }   // try to force RGB
  // saveSettings();
  UpdateFinalColourComponents();
}


// set all 5 channels at once.
// Channels are: R G B CW WW
// Brightness is automatically recalculated to adjust channels to the desired values
void mInterfaceLight::changeChannels(uint8_t *channels) {
  if (pwm_multi_channels) {
    setChannelsRaw(channels);
  } else if (LST_COLDWARM == subtype) {
    // remap channels 0-1 to 3-4 if cold/warm
    uint8_t remapped_channels[5] = {0,0,0,channels[0],channels[1]};
    setChannels(remapped_channels);
  } else {
    setChannels(channels);
  }

  // saveSettings();
  UpdateFinalColourComponents();
}

uint16_t mInterfaceLight::getHue(){
  return _hue;
}
uint8_t mInterfaceLight::getSat(){
  return _sat;
}

HsbColor mInterfaceLight::GetColour_HSB(void){
  uint16_t hue = 0;
  uint8_t  sat = 0;
  uint8_t  brt = 0;
  getHSB(&hue,&sat,&brt);  
  return HsbColor(HueN2F(hue),SatN2F(sat),BrtN2F(brt));
}


// void mInterfaceLight::Change_RgbcctColor_Hue(){

// }


/*********************************************************************************************\
 * Change scales from 8 bits to 10 bits and vice versa
\*********************************************************************************************/
// 8 to 10 to 8 is garanteed to give the same result
uint16_t mInterfaceLight::change8to10(uint8_t v) {
  return mapvalue(v, 0, 255, 0, 1023);
}
// change from 10 bits to 8 bits, but any non-zero input will be non-zero
uint8_t mInterfaceLight::change10to8(uint16_t v) {
  return (0 == v) ? 0 : mapvalue(v, 4, 1023, 1, 255);
}

/*********************************************************************************************\
 * Gamma correction
\*********************************************************************************************/
#ifdef ENABLE_PIXEL_LIGHTING_GAMMA_CORRECTION
// Calculate the gamma corrected value for LEDS
uint16_t mInterfaceLight::ledGamma_internal(uint16_t v, const struct gamma_table_t *gt_ptr) {
  uint16_t from_src = 0;
  uint16_t from_gamma = 0;

  for (const gamma_table_t *gt = gt_ptr; ; gt++) {
    uint16_t to_src = gt->to_src;
    uint16_t to_gamma = gt->to_gamma;
    if (v <= to_src) {
      return mapvalue(v, from_src, to_src, from_gamma, to_gamma);
    }
    from_src = to_src;
    from_gamma = to_gamma;
  }
}
// Calculate the reverse gamma value for LEDS
uint16_t mInterfaceLight::ledGammaReverse_internal(uint16_t vg, const struct gamma_table_t *gt_ptr) {
  uint16_t from_src = 0;
  uint16_t from_gamma = 0;

  for (const gamma_table_t *gt = gt_ptr; ; gt++) {
    uint16_t to_src = gt->to_src;
    uint16_t to_gamma = gt->to_gamma;
    if (vg <= to_gamma) {
      return mapvalue(vg, from_gamma, to_gamma, from_src, to_src);
    }
    from_src = to_src;
    from_gamma = to_gamma;
  }
}

// 10 bits in, 10 bits out
uint16_t mInterfaceLight::ledGamma10_10(uint16_t v) {
  return ledGamma_internal(v, gamma_table);
}
// 10 bits resolution, 8 bits in
uint16_t mInterfaceLight::ledGamma10(uint8_t v) {
  return ledGamma10_10(change8to10(v));
}

// Legacy function
uint8_t mInterfaceLight::ledGamma(uint8_t v) {
  return change10to8(ledGamma10(v));
}



// Just apply basic Gamma to each channel
void mInterfaceLight::calcGammaMultiChannels(uint16_t cur_col_10[5]) {
  // Apply gamma correction for 8 and 10 bits resolutions, if needed
  if (pCONT_set->Settings.light_settings.light_correction) {
    for (uint32_t i = 0; i < LST_MAX; i++) {
      cur_col_10[i] = ledGamma10_10(cur_col_10[i]);
    }
  }
}

void mInterfaceLight::calcGammaBulbs(uint16_t cur_col_10[5]) {
//   // Apply gamma correction for 8 and 10 bits resolutions, if needed

//   // First apply combined correction to the overall white power
//   if ((LST_COLDWARM == subtype) || (LST_RGBCW == subtype)) {
//     // channels for white are always the last two channels
//     uint32_t cw1 = subtype - 1;       // address for the ColorTone PWM
//     uint32_t cw0 = subtype - 2;       // address for the White Brightness PWM
//     uint16_t white_bri10 = cur_col_10[cw0] + cur_col_10[cw1];   // cumulated brightness
//     uint16_t white_bri10_1023 = (white_bri10 > 1023) ? 1023 : white_bri10;    // max 1023

// #ifdef ESP8266
//     if (
//       // (MODULE_PHILIPS_ID == pCONT_set->my_module_type) || 
//       (pCONT_set->Settings.flag4.pwm_ct_mode)) {   // channel 1 is the color tone, mapped to cold channel (0..255)
//       // Xiaomi Philips bulbs follow a different scheme:
//       cur_col_10[cw1] = getCT10bits();
//       // channel 0=intensity, channel1=temperature
//       if (pCONT_set->Settings.light_settings.light_correction) { // gamma correction
//         cur_col_10[cw0] = ledGamma10_10(white_bri10_1023);    // 10 bits gamma correction
//       } else {
//         cur_col_10[cw0] = white_bri10_1023;  // no gamma, extend to 10 bits
//       }
//     } else
// #endif  // ESP8266
//     if (pCONT_set->Settings.light_settings.light_correction) {
//       // if sum of both channels is > 255, then channels are probably uncorrelated
//       if (white_bri10 <= 1031) {      // take a margin of 8 above 1023 to account for rounding errors
//         // we calculate the gamma corrected sum of CW + WW
//         uint16_t white_bri_gamma10 = ledGamma10_10(white_bri10_1023);
//         // then we split the total energy among the cold and warm leds
//         cur_col_10[cw0] = mapvalue(cur_col_10[cw0], 0, white_bri10_1023, 0, white_bri_gamma10);
//         cur_col_10[cw1] = mapvalue(cur_col_10[cw1], 0, white_bri10_1023, 0, white_bri_gamma10);
//       } else {
//         cur_col_10[cw0] = ledGamma10_10(cur_col_10[cw0]);
//         cur_col_10[cw1] = ledGamma10_10(cur_col_10[cw1]);
//       }
//     }
//   }

//   if (pCONT_set->Settings.light_settings.light_correction) {
//     // then apply gamma correction to RGB channels
//     if (LST_RGB <= subtype) {
//       for (uint32_t i = 0; i < 3; i++) {
//         cur_col_10[i] = ledGamma10_10(cur_col_10[i]);
//       }
//     }
//     // If RGBW or Single channel, also adjust White channel
//     if ((LST_SINGLE == subtype) || (LST_RGBW == subtype)) {
//       cur_col_10[subtype - 1] = ledGamma10_10(cur_col_10[subtype - 1]);
//     }
//   }
}


bool mInterfaceLight::isChannelGammaCorrected(uint32_t channel) {
  if (!pCONT_set->Settings.light_settings.light_correction) { return false; }   // Gamma correction not activated
  if (channel >= subtype) { return false; }     // Out of range
#ifdef ESP8266
//   if (
//     // (MODULE_PHILIPS_ID == pCONT_set->my_module_type) || 
//   (pCONT_set->Settings.flag4.pwm_ct_mode)) {
//     if ((LST_COLDWARM == subtype) && (1 == channel)) { return false; }   // PMW reserved for CT
//     if ((LST_RGBCW == subtype) && (4 == channel)) { return false; }   // PMW reserved for CT
//   }
#endif  // ESP8266
  return true;
}


// Calculate the Gamma correction, if any, for fading, using the fast Gamma curve (10 bits in+out)
uint16_t mInterfaceLight::fadeGamma(uint32_t channel, uint16_t v) {
  if (isChannelGammaCorrected(channel)) {
    return ledGamma_internal(v, gamma_table_fast);
  } else {
    return v;
  }
}
uint16_t mInterfaceLight::fadeGammaReverse(uint32_t channel, uint16_t vg) {
  if (isChannelGammaCorrected(channel)) {
    return ledGammaReverse_internal(vg, gamma_table_fast);
  } else {
    return vg;
  }
}

#endif // ENABLE_PIXEL_LIGHTING_GAMMA_CORRECTION

void mInterfaceLight::LightPwmOffset(uint32_t offset)
{
  pwm_offset = offset;
}


// compute actual PWM min/max values from DimmerRange
// must be called when DimmerRange is changed or LedTable
void mInterfaceLight::LightCalcPWMRange(void) {
  uint16_t pwm_min=0, pwm_max=1023;

  // pwm_min = change8to10(DimmerToBri(pCONT_set->Settings.dimmer_hw_min));   // default 0
  // pwm_max = change8to10(DimmerToBri(pCONT_set->Settings.dimmer_hw_max));   // default 100
  // if (pCONT_set->Settings.light_correction) {
  //   pwm_min = ledGamma10_10(pwm_min);       // apply gamma correction
  //   pwm_max = ledGamma10_10(pwm_max);       // 0..1023
  // }
  // pwm_min = pwm_min > 0 ? mapvalue(pwm_min, 1, 1023, 1, Settings.pwm_range) : 0;  // adapt range but keep zero and non-zero values
  // pwm_max = mapvalue(pwm_max, 1, 1023, 1, Settings.pwm_range);  // pwm_max cannot be zero

  pwm_min = pwm_min;
  pwm_max = pwm_max;
  //AddLog_P2(LOG_LEVEL_TEST, PSTR("LightCalcPWMRange %d %d - %d %d"), Settings.dimmer_hw_min, Settings.dimmer_hw_max, pwm_min, pwm_max);
}


/****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ************************************************************************** 
 ************************************************************************** 
 ************************************************************************** 
 *END                  "Setters" aka internal as "light_controller", dont use directly
 *****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ****************************************************************************
 ************************************************************************* 
 ************************************************************************** 
 ************************************************************************** 
 *******************************************************************************/



#endif // USE_DRIVER
