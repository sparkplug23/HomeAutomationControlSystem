#ifndef mUserOptions_h
#define mUserOptions_h

// DO NOT EDIT
// Contains list of use options to be used in "mFirmwareCustom" and "mUserConfig" and must match
// the enums they map to.


/*******************************************************************************************************************
********************************************************************************************************************
************ LIGHTING ********************************************************************************************
********************************************************************************************************************
********************************************************************************************************************/
//UO_ user option prefix
enum PIXEL_HARDWARE_COLOR_ORDER_IDS{
  UO_PIXEL_HARDWARE_COLOR_ORDER_GRB_ID = 0, //default
  UO_PIXEL_HARDWARE_COLOR_ORDER_RGB_ID, //common for WS2811
  UO_PIXEL_HARDWARE_COLOR_ORDER_BRG_ID, 
  UO_PIXEL_HARDWARE_COLOR_ORDER_RBG_ID, 
  UO_PIXEL_HARDWARE_COLOR_ORDER_BGR_ID, 
  UO_PIXEL_HARDWARE_COLOR_ORDER_GBR_ID,
  UO_PIXEL_HARDWARE_COLOR_ORDER_GRBW_ID,
  UO_PIXEL_HARDWARE_COLOR_LENGTH_ID
};
enum UO_TRANSITION_ORDER{
  UO_TRANSITION_ORDER_NONE_ID=0,
  UO_TRANSITION_ORDER_RANDOM_ID,
  UO_TRANSITION_ORDER_CENTRE_OUT_ID, //mirror image fill from center
  UO_TRANSITION_ORDER_INORDER_ID,
  UO_TRANSITION_ORDER_ROTATE_ID,
  UO_TRANSITION_ORDER_FIXED_ID
};
enum UO_TIME_MAP_SECS_IDS{
  UO_TIME_MAP_SECS_0_ID = 0,
  UO_TIME_MAP_SECS_1_ID,
  UO_TIME_MAP_SECS_2_ID,
  UO_TIME_MAP_SECS_4_ID,
  UO_TIME_MAP_SECS_6_ID,
  UO_TIME_MAP_SECS_10_ID,
  UO_TIME_MAP_SECS_15_ID,
  UO_TIME_MAP_SECS_20_ID,
  UO_TIME_MAP_SECS_30_ID,
  UO_TIME_MAP_SECS_60_ID
};
enum UO_RATE_MAP_SECS_IDS{
  UO_RATE_MAP_SECS_0_ID = 0,
  UO_RATE_MAP_SECS_1_ID,
  UO_RATE_MAP_SECS_2_ID,
  UO_RATE_MAP_SECS_4_ID,
  UO_RATE_MAP_SECS_6_ID,
  UO_RATE_MAP_SECS_10_ID,
  UO_RATE_MAP_SECS_15_ID,
  UO_RATE_MAP_SECS_20_ID,
  UO_RATE_MAP_SECS_30_ID,
  UO_RATE_MAP_SECS_60_ID
};
enum UO_PIXELS_UPDATE_PERCENTAGE_IDS{   
  UO_PIXELS_UPDATE_PERCENTAGE_0_ID = 0,
  UO_PIXELS_UPDATE_PERCENTAGE_5_ID,
  UO_PIXELS_UPDATE_PERCENTAGE_10_ID,
  UO_PIXELS_UPDATE_PERCENTAGE_15_ID,
  UO_PIXELS_UPDATE_PERCENTAGE_20_ID,
  UO_PIXELS_UPDATE_PERCENTAGE_30_ID,
  UO_PIXELS_UPDATE_PERCENTAGE_40_ID,
  UO_PIXELS_UPDATE_PERCENTAGE_50_ID,
  UO_PIXELS_UPDATE_PERCENTAGE_60_ID,
  UO_PIXELS_UPDATE_PERCENTAGE_70_ID,
  UO_PIXELS_UPDATE_PERCENTAGE_80_ID,
  UO_PIXELS_UPDATE_PERCENTAGE_90_ID,
  UO_PIXELS_UPDATE_PERCENTAGE_100_ID
};
 enum UO_PALETTELIST_VARIABLE_USER_IDS{ // 20 TOTAL variable and can be deleted by the user, saved in memory
    UO_PALETTELIST_VARIABLE_USER_01_ID = 0,
    UO_PALETTELIST_VARIABLE_USER_02_ID,
    UO_PALETTELIST_VARIABLE_USER_03_ID,
    UO_PALETTELIST_VARIABLE_USER_04_ID,
    UO_PALETTELIST_VARIABLE_USER_05_ID,
    UO_PALETTELIST_VARIABLE_USER_06_ID,
    UO_PALETTELIST_VARIABLE_USER_07_ID,
    UO_PALETTELIST_VARIABLE_USER_08_ID,
    UO_PALETTELIST_VARIABLE_USER_09_ID,
    UO_PALETTELIST_VARIABLE_USER_10_ID, 
    UO_PALETTELIST_VARIABLE_USER_11_ID, 
    UO_PALETTELIST_VARIABLE_USER_12_ID,  
    UO_PALETTELIST_VARIABLE_USER_13_ID, 
    UO_PALETTELIST_VARIABLE_USER_14_ID, 
    UO_PALETTELIST_VARIABLE_USER_15_ID, 
    UO_PALETTELIST_VARIABLE_USER_16_ID, 
    UO_PALETTELIST_VARIABLE_USER_17_ID, 
    UO_PALETTELIST_VARIABLE_USER_18_ID, 
    UO_PALETTELIST_VARIABLE_USER_19_ID, 
    UO_PALETTELIST_VARIABLE_USER_20_ID, 
    // Count of total handlers and starting point for other modules
    UO_PALETTELIST_VARIABLE_USER_LENGTH_ID 
  };
  enum UO_PALETTELIST_STATIC_IDS{
    // Shelf Lights ie has some static leds
    UO_PALETTELIST_STATIC_SHELF_HEARTS_ID = UO_PALETTELIST_VARIABLE_USER_LENGTH_ID,
    // Special patterns
    UO_PALETTELIST_STATIC_HOLLOWEEN_OP_ID,
    UO_PALETTELIST_STATIC_HOLLOWEEN_OGP_ID,
    UO_PALETTELIST_STATIC_RAINBOW_ID,
    UO_PALETTELIST_STATIC_PASTEL_ID, //PASTEL
    UO_PALETTELIST_STATIC_WINTER_ID,
    UO_PALETTELIST_STATIC_AUTUMN_ID,
    UO_PALETTELIST_STATIC_AUTUMN_RED_ID,
    UO_PALETTELIST_STATIC_GRADIENT_01_ID,
    UO_PALETTELIST_STATIC_GRADIENT_02_ID,
    UO_PALETTELIST_STATIC_OCEAN_01_ID,

    // Count of total handlers and starting point for other modules
    UO_PALETTELIST_STATIC_LENGTH_ID 
  };
  enum UO_ANIMATION_MODE{
    UO_ANIMATION_MODE_NONE_ID = 0,
    UO_ANIMATION_MODE_TURN_ON_ID,
    UO_ANIMATION_MODE_TURN_OFF_ID,
    UO_ANIMATION_MODE_AMBILIGHT_ID,
    UO_ANIMATION_MODE_SCENE_ID,
    UO_ANIMATION_MODE_FLASHER_ID,
    UO_ANIMATION_MODE_NOTIFICATIONS_ID,
    UO_ANIMATION_MODE_LENGTH_ID
  }; 
  enum UO_FLASHER_FUNCTION_IDS{
    UO_FLASHER_FUNCTION_NONE_ID = 0,
    UO_FLASHER_FUNCTION_SLOW_GLOW_ID, // solid colours, 1 100%, moving from previous to next
    UO_FLASHER_FUNCTION_SEQUENTIAL_ID, //instant, or faded (ie INWAVES) // FLASHER_FUNCTION_SEQUENTIAL_FLASH_ID, //FLASHER_FUNCTION_CHASING_FLASH_ID,
    UO_FLASHER_FUNCTION_SLOW_FADE_BRIGHTNESS_ALL_ID, // change ALL, 0 - 100%
    UO_FLASHER_FUNCTION_SLOW_FADE_SATURATION_ALL_ID, // change ALL, 0 - 100%
    UO_FLASHER_FUNCTION_SLOW_FADE_BRIGHTNESS_RANDOM_ID, // change ALL, 0 - 100%
    UO_FLASHER_FUNCTION_SLOW_FADE_SATURATION_RANDOM_ID, // change ALL, 0 - 100%
    UO_FLASHER_FUNCTION_FLASH_TWINKLE_RANDOM_ID, //random leds flash to 100% brightness (modes=instant on/off, multiple pulses)
    UO_FLASHER_FUNCTION_FLASH_TWINKLE_SEQUENTIAL_ID, // sequential flash of white on x leds 
    //another flash to "off" or simple set flash colour to off??
    UO_FLASHER_FUNCTION_FLASH_GLIMMER_RANDOM_ID, // tinkle=leds flash independant, glimmer=leds flash with dimming effect on others
    UO_FLASHER_FUNCTION_LENGTH_ID
  };   

  
    enum UO_PRESET_COLOUR_MAP_IDS{
      UO_COLOUR_MAP_NONE_ID=0,
      // Red
      UO_COLOUR_MAP_RED_ID,
      UO_COLOUR_MAP_RED_PASTEL95_ID,
      UO_COLOUR_MAP_RED_PASTEL90_ID,
      UO_COLOUR_MAP_RED_PASTEL80_ID,
      UO_COLOUR_MAP_RED_PASTEL70_ID,
      UO_COLOUR_MAP_RED_PASTEL60_ID,
      UO_COLOUR_MAP_RED_PASTEL50_ID,
      UO_COLOUR_MAP_RED_PASTEL40_ID,
      UO_COLOUR_MAP_RED_PASTEL20_ID,
      // Orange
      UO_COLOUR_MAP_ORANGE_ID,
      UO_COLOUR_MAP_ORANGE_PASTEL95_ID,
      UO_COLOUR_MAP_ORANGE_PASTEL90_ID,
      UO_COLOUR_MAP_ORANGE_PASTEL80_ID,
      UO_COLOUR_MAP_ORANGE_PASTEL70_ID,
      UO_COLOUR_MAP_ORANGE_PASTEL60_ID,
      UO_COLOUR_MAP_ORANGE_PASTEL50_ID,
      UO_COLOUR_MAP_ORANGE_PASTEL40_ID,
      // Light Orange
      UO_COLOUR_MAP_LIGHTORANGE_ID,
      UO_COLOUR_MAP_LIGHTORANGE_PASTEL95_ID,
      UO_COLOUR_MAP_LIGHTORANGE_PASTEL90_ID,
      UO_COLOUR_MAP_LIGHTORANGE_PASTEL80_ID,
      UO_COLOUR_MAP_LIGHTORANGE_PASTEL70_ID,
      UO_COLOUR_MAP_LIGHTORANGE_PASTEL60_ID,
      UO_COLOUR_MAP_LIGHTORANGE_PASTEL50_ID,
      UO_COLOUR_MAP_LIGHTORANGE_PASTEL40_ID,
      // White
      UO_COLOUR_MAP_WHITE_ID,
      UO_COLOUR_MAP_WHITE_PASTEL95_ID,
      UO_COLOUR_MAP_WHITE_PASTEL90_ID,
      UO_COLOUR_MAP_WHITE_PASTEL80_ID,
      UO_COLOUR_MAP_WHITE_PASTEL70_ID,
      UO_COLOUR_MAP_WHITE_PASTEL60_ID,
      UO_COLOUR_MAP_WHITE_PASTEL50_ID,
      UO_COLOUR_MAP_WHITE_PASTEL40_ID,
      UO_COLOUR_MAP_WHITE_PASTEL20_ID,
      // 
      UO_COLOUR_MAP_YELLOW_ID,
      UO_COLOUR_MAP_YELLOW_PASTEL95_ID,
      UO_COLOUR_MAP_YELLOW_PASTEL90_ID,
      UO_COLOUR_MAP_YELLOW_PASTEL80_ID,
      UO_COLOUR_MAP_YELLOW_PASTEL70_ID,
      UO_COLOUR_MAP_YELLOW_PASTEL60_ID,
      UO_COLOUR_MAP_YELLOW_PASTEL50_ID,
      UO_COLOUR_MAP_YELLOW_PASTEL40_ID,
      // 
      UO_COLOUR_MAP_LIMEGREEN_ID,
      UO_COLOUR_MAP_LIMEGREEN_PASTEL95_ID,
      UO_COLOUR_MAP_LIMEGREEN_PASTEL90_ID,
      UO_COLOUR_MAP_LIMEGREEN_PASTEL80_ID,
      UO_COLOUR_MAP_LIMEGREEN_PASTEL70_ID,
      UO_COLOUR_MAP_LIMEGREEN_PASTEL60_ID,
      UO_COLOUR_MAP_LIMEGREEN_PASTEL50_ID,
      UO_COLOUR_MAP_LIMEGREEN_PASTEL40_ID,
      // 
      UO_COLOUR_MAP_GREEN_ID,
      UO_COLOUR_MAP_GREEN_PASTEL95_ID,
      UO_COLOUR_MAP_GREEN_PASTEL90_ID,
      UO_COLOUR_MAP_GREEN_PASTEL80_ID,
      UO_COLOUR_MAP_GREEN_PASTEL70_ID,
      UO_COLOUR_MAP_GREEN_PASTEL60_ID,
      UO_COLOUR_MAP_GREEN_PASTEL50_ID,
      UO_COLOUR_MAP_GREEN_PASTEL40_ID,
      // Cyan
      UO_COLOUR_MAP_CYAN_ID,
      UO_COLOUR_MAP_CYAN_PASTEL95_ID,
      UO_COLOUR_MAP_CYAN_PASTEL90_ID,
      UO_COLOUR_MAP_CYAN_PASTEL80_ID,
      UO_COLOUR_MAP_CYAN_PASTEL70_ID,
      UO_COLOUR_MAP_CYAN_PASTEL60_ID,
      UO_COLOUR_MAP_CYAN_PASTEL50_ID,
      UO_COLOUR_MAP_CYAN_PASTEL40_ID,
      // Blue
      UO_COLOUR_MAP_BLUE_ID,
      UO_COLOUR_MAP_BLUE_PASTEL95_ID,
      UO_COLOUR_MAP_BLUE_PASTEL90_ID,
      UO_COLOUR_MAP_BLUE_PASTEL80_ID,
      UO_COLOUR_MAP_BLUE_PASTEL70_ID,
      UO_COLOUR_MAP_BLUE_PASTEL60_ID,
      UO_COLOUR_MAP_BLUE_PASTEL50_ID,
      UO_COLOUR_MAP_BLUE_PASTEL40_ID,
      // Blue Purple
      UO_COLOUR_MAP_BLUEPURPLE_ID,
      UO_COLOUR_MAP_BLUEPURPLE_PASTEL95_ID,
      UO_COLOUR_MAP_BLUEPURPLE_PASTEL90_ID,
      UO_COLOUR_MAP_BLUEPURPLE_PASTEL80_ID,
      UO_COLOUR_MAP_BLUEPURPLE_PASTEL70_ID,
      UO_COLOUR_MAP_BLUEPURPLE_PASTEL60_ID,
      UO_COLOUR_MAP_BLUEPURPLE_PASTEL50_ID,
      UO_COLOUR_MAP_BLUEPURPLE_PASTEL40_ID,
      // Purple
      UO_COLOUR_MAP_PURPLE_ID,
      UO_COLOUR_MAP_PURPLE_PASTEL95_ID,
      UO_COLOUR_MAP_PURPLE_PASTEL90_ID,
      UO_COLOUR_MAP_PURPLE_PASTEL80_ID,
      UO_COLOUR_MAP_PURPLE_PASTEL70_ID,
      UO_COLOUR_MAP_PURPLE_PASTEL60_ID,
      UO_COLOUR_MAP_PURPLE_PASTEL50_ID,
      UO_COLOUR_MAP_PURPLE_PASTEL40_ID,
      // Pink
      UO_COLOUR_MAP_PINK_ID,
      UO_COLOUR_MAP_PINK_PASTEL95_ID,
      UO_COLOUR_MAP_PINK_PASTEL90_ID,
      UO_COLOUR_MAP_PINK_PASTEL80_ID,
      UO_COLOUR_MAP_PINK_PASTEL70_ID,
      UO_COLOUR_MAP_PINK_PASTEL60_ID,
      UO_COLOUR_MAP_PINK_PASTEL50_ID,
      UO_COLOUR_MAP_PINK_PASTEL40_ID,
      // Hot Pink
      UO_COLOUR_MAP_HOTPINK_ID,
      UO_COLOUR_MAP_HOTPINK_PASTEL95_ID,
      UO_COLOUR_MAP_HOTPINK_PASTEL90_ID,
      UO_COLOUR_MAP_HOTPINK_PASTEL80_ID,
      UO_COLOUR_MAP_HOTPINK_PASTEL70_ID,
      UO_COLOUR_MAP_HOTPINK_PASTEL60_ID,
      UO_COLOUR_MAP_HOTPINK_PASTEL50_ID,
      UO_COLOUR_MAP_HOTPINK_PASTEL40_ID,
      // End of palette options
      UO_COLOUR_MAP_PALETTE_OPTIONS_END_ID, // extra unused colour, space wasted
      //
      // Unique colour storage
      UO_COLOUR_MAP_SPECIAL_ONEINMANY_ONE_ID,   //ie hearts colour
      UO_COLOUR_MAP_SPECIAL_ONEINMANY_MANY_ID,  //ie other colours for shelf
      //
      UO_COLOUR_MAP_LENGTH_ID //new end
    };



#endif


