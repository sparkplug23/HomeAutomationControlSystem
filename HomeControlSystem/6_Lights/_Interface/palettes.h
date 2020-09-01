// /*
//  * Color palettes for FastLED effects (65-73).
//  */

// // From ColorWavesWithPalettes by Mark Kriegsman: https://gist.github.com/kriegsman/8281905786e8b2632aeb
// // Unfortunaltely, these are stored in RAM!

// // Gradient palette "ib_jul01_gp", originally from
// // http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/xmas/tn/ib_jul01.png.index.html
// // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // Size: 16 bytes of program space.

//https://www.espressif.com/sites/default/files/documentation/save_esp8266ex_ram_with_progmem_en.pdf

#ifndef PALETTES_H
#define PALETTES_H

#include "stdint.h"
#include "2_CoreSystem/mGlobalMacros.h"

// class PALETTE{
//   public:
//     PALETTE();

    // Red;
    const char D_COLOUR_MAP_RED_CTR[] PROGMEM =                "Red 100%";
    const char D_COLOUR_MAP_RED_PASTEL95_CTR[] PROGMEM =       "Red 95%";
    const char D_COLOUR_MAP_RED_PASTEL90_CTR[] PROGMEM =       "Red 90%";
    const char D_COLOUR_MAP_RED_PASTEL80_CTR[] PROGMEM =       "Red 80%";
    const char D_COLOUR_MAP_RED_PASTEL70_CTR[] PROGMEM =       "Red 70%";
    const char D_COLOUR_MAP_RED_PASTEL60_CTR[] PROGMEM =       "Red 60%";
    const char D_COLOUR_MAP_RED_PASTEL50_CTR[] PROGMEM =       "Red 50%";
    const char D_COLOUR_MAP_RED_PASTEL40_CTR[] PROGMEM =       "Red 40%";
    const char D_COLOUR_MAP_RED_PASTEL20_CTR[] PROGMEM =       "Red 20%";
    // Orange;
    const char D_COLOUR_MAP_ORANGE_CTR[] PROGMEM =             "Orange 100%";
    const char D_COLOUR_MAP_ORANGE_PASTEL95_CTR[] PROGMEM =    "Orange 95%";
    const char D_COLOUR_MAP_ORANGE_PASTEL90_CTR[] PROGMEM =    "Orange 90%";
    const char D_COLOUR_MAP_ORANGE_PASTEL80_CTR[] PROGMEM =    "Orange 80%";
    const char D_COLOUR_MAP_ORANGE_PASTEL70_CTR[] PROGMEM =    "Orange 70%";
    const char D_COLOUR_MAP_ORANGE_PASTEL60_CTR[] PROGMEM =    "Orange 60%";
    const char D_COLOUR_MAP_ORANGE_PASTEL50_CTR[] PROGMEM =    "Orange 50%";
    const char D_COLOUR_MAP_ORANGE_PASTEL40_CTR[] PROGMEM =    "Orange 40%";
    // Light Orange    ;
    const char D_COLOUR_MAP_LIGHTORANGE_CTR[] PROGMEM =             "Light Orange 100%";
    const char D_COLOUR_MAP_LIGHTORANGE_PASTEL95_CTR[] PROGMEM =    "Light Orange 95%";
    const char D_COLOUR_MAP_LIGHTORANGE_PASTEL90_CTR[] PROGMEM =    "Light Orange 90%";
    const char D_COLOUR_MAP_LIGHTORANGE_PASTEL80_CTR[] PROGMEM =    "Light Orange 80%";
    const char D_COLOUR_MAP_LIGHTORANGE_PASTEL70_CTR[] PROGMEM =    "Light Orange 70%";
    const char D_COLOUR_MAP_LIGHTORANGE_PASTEL60_CTR[] PROGMEM =    "Light Orange 60%";
    const char D_COLOUR_MAP_LIGHTORANGE_PASTEL50_CTR[] PROGMEM =    "Light Orange 50%";
    const char D_COLOUR_MAP_LIGHTORANGE_PASTEL40_CTR[] PROGMEM =    "Light Orange 40%";
    // White;
    const char D_COLOUR_MAP_WHITE_CTR[] PROGMEM =              "White (Pure) 100%";
    const char D_COLOUR_MAP_WHITE_PASTEL95_CTR[] PROGMEM =     "White Warm 95%";
    const char D_COLOUR_MAP_WHITE_PASTEL90_CTR[] PROGMEM =     "White Warm 90%";
    const char D_COLOUR_MAP_WHITE_PASTEL80_CTR[] PROGMEM =     "White Warm 80%";
    const char D_COLOUR_MAP_WHITE_PASTEL70_CTR[] PROGMEM =     "White Warm 70%";
    const char D_COLOUR_MAP_WHITE_PASTEL60_CTR[] PROGMEM =     "White Warm 60%";
    const char D_COLOUR_MAP_WHITE_PASTEL50_CTR[] PROGMEM =     "White Warm 50%";
    const char D_COLOUR_MAP_WHITE_PASTEL40_CTR[] PROGMEM =     "White Warm 40%";
    const char D_COLOUR_MAP_WHITE_PASTEL20_CTR[] PROGMEM =     "White Warm 20%";
    // Yellow;
    const char D_COLOUR_MAP_YELLOW_CTR[] PROGMEM =             "Yellow 100%";
    const char D_COLOUR_MAP_YELLOW_PASTEL95_CTR[] PROGMEM =    "Yellow 95%";
    const char D_COLOUR_MAP_YELLOW_PASTEL90_CTR[] PROGMEM =    "Yellow 80%";
    const char D_COLOUR_MAP_YELLOW_PASTEL80_CTR[] PROGMEM =    "Yellow 80%";
    const char D_COLOUR_MAP_YELLOW_PASTEL70_CTR[] PROGMEM =    "Yellow 70%";
    const char D_COLOUR_MAP_YELLOW_PASTEL60_CTR[] PROGMEM =    "Yellow 60%";
    const char D_COLOUR_MAP_YELLOW_PASTEL50_CTR[] PROGMEM =    "Yellow 50%";
    const char D_COLOUR_MAP_YELLOW_PASTEL40_CTR[] PROGMEM =    "Yellow 40%";
    // Lime Green    ;
    const char D_COLOUR_MAP_LIMEGREEN_CTR[] PROGMEM =             "Lime Green 100%";
    const char D_COLOUR_MAP_LIMEGREEN_PASTEL95_CTR[] PROGMEM =    "Lime Green 95%";
    const char D_COLOUR_MAP_LIMEGREEN_PASTEL90_CTR[] PROGMEM =    "Lime Green 90%";
    const char D_COLOUR_MAP_LIMEGREEN_PASTEL80_CTR[] PROGMEM =    "Lime Green 80%";
    const char D_COLOUR_MAP_LIMEGREEN_PASTEL70_CTR[] PROGMEM =    "Lime Green 70%";
    const char D_COLOUR_MAP_LIMEGREEN_PASTEL60_CTR[] PROGMEM =    "Lime Green 60%";
    const char D_COLOUR_MAP_LIMEGREEN_PASTEL50_CTR[] PROGMEM =    "Lime Green 50%";
    const char D_COLOUR_MAP_LIMEGREEN_PASTEL40_CTR[] PROGMEM =    "Lime Green 40%";
    // Green    ;
    const char D_COLOUR_MAP_GREEN_CTR[] PROGMEM =             "Green 100%";
    const char D_COLOUR_MAP_GREEN_PASTEL95_CTR[] PROGMEM =    "Green 95%";
    const char D_COLOUR_MAP_GREEN_PASTEL90_CTR[] PROGMEM =    "Green 90%";
    const char D_COLOUR_MAP_GREEN_PASTEL80_CTR[] PROGMEM =    "Green 80%";
    const char D_COLOUR_MAP_GREEN_PASTEL70_CTR[] PROGMEM =    "Green 70%";
    const char D_COLOUR_MAP_GREEN_PASTEL60_CTR[] PROGMEM =    "Green 60%";
    const char D_COLOUR_MAP_GREEN_PASTEL50_CTR[] PROGMEM =    "Green 50%";
    const char D_COLOUR_MAP_GREEN_PASTEL40_CTR[] PROGMEM =    "Green 40%";
    // Cyan;
    const char D_COLOUR_MAP_CYAN_CTR[] PROGMEM =             "Cyan 100%";
    const char D_COLOUR_MAP_CYAN_PASTEL95_CTR[] PROGMEM =    "Cyan 95%";
    const char D_COLOUR_MAP_CYAN_PASTEL90_CTR[] PROGMEM =    "Cyan 90%";
    const char D_COLOUR_MAP_CYAN_PASTEL80_CTR[] PROGMEM =    "Cyan 80%";
    const char D_COLOUR_MAP_CYAN_PASTEL70_CTR[] PROGMEM =    "Cyan 70%";
    const char D_COLOUR_MAP_CYAN_PASTEL60_CTR[] PROGMEM =    "Cyan 60%";
    const char D_COLOUR_MAP_CYAN_PASTEL50_CTR[] PROGMEM =    "Cyan 50%";
    const char D_COLOUR_MAP_CYAN_PASTEL40_CTR[] PROGMEM =    "Cyan 40%";
    // Blue    ;
    const char D_COLOUR_MAP_BLUE_CTR[] PROGMEM =             "Blue 100%";
    const char D_COLOUR_MAP_BLUE_PASTEL95_CTR[] PROGMEM =    "Blue 95%";
    const char D_COLOUR_MAP_BLUE_PASTEL90_CTR[] PROGMEM =    "Blue 90%";
    const char D_COLOUR_MAP_BLUE_PASTEL80_CTR[] PROGMEM =    "Blue 80%";
    const char D_COLOUR_MAP_BLUE_PASTEL70_CTR[] PROGMEM =    "Blue 70%";
    const char D_COLOUR_MAP_BLUE_PASTEL60_CTR[] PROGMEM =    "Blue 60%";
    const char D_COLOUR_MAP_BLUE_PASTEL50_CTR[] PROGMEM =    "Blue 50%";
    const char D_COLOUR_MAP_BLUE_PASTEL40_CTR[] PROGMEM =    "Blue 40%";
    // Pink Purple;
    const char D_COLOUR_MAP_BLUEPURPLE_CTR[] PROGMEM =             "Blue Purple 100%";
    const char D_COLOUR_MAP_BLUEPURPLE_PASTEL95_CTR[] PROGMEM =    "Blue Purple 95%";
    const char D_COLOUR_MAP_BLUEPURPLE_PASTEL90_CTR[] PROGMEM =    "Blue Purple 90%";
    const char D_COLOUR_MAP_BLUEPURPLE_PASTEL80_CTR[] PROGMEM =    "Blue Purple 80%";
    const char D_COLOUR_MAP_BLUEPURPLE_PASTEL70_CTR[] PROGMEM =    "Blue Purple 70%";
    const char D_COLOUR_MAP_BLUEPURPLE_PASTEL60_CTR[] PROGMEM =    "Blue Purple 60%";
    const char D_COLOUR_MAP_BLUEPURPLE_PASTEL50_CTR[] PROGMEM =    "Blue Purple 50%";
    const char D_COLOUR_MAP_BLUEPURPLE_PASTEL40_CTR[] PROGMEM =    "Blue Purple 40%";
    // Purple;
    const char D_COLOUR_MAP_PURPLE_CTR[] PROGMEM =             "Purple 100%";
    const char D_COLOUR_MAP_PURPLE_PASTEL95_CTR[] PROGMEM =    "Purple 95%";
    const char D_COLOUR_MAP_PURPLE_PASTEL90_CTR[] PROGMEM =    "Purple 90%";
    const char D_COLOUR_MAP_PURPLE_PASTEL80_CTR[] PROGMEM =    "Purple 80%";
    const char D_COLOUR_MAP_PURPLE_PASTEL70_CTR[] PROGMEM =    "Purple 70%";
    const char D_COLOUR_MAP_PURPLE_PASTEL60_CTR[] PROGMEM =    "Purple 60%";
    const char D_COLOUR_MAP_PURPLE_PASTEL50_CTR[] PROGMEM =    "Purple 50%";
    const char D_COLOUR_MAP_PURPLE_PASTEL40_CTR[] PROGMEM =    "Purple 40%";
    // Pink;
    const char D_COLOUR_MAP_PINK_CTR[] PROGMEM =             "Pink 100%";
    const char D_COLOUR_MAP_PINK_PASTEL95_CTR[] PROGMEM =    "Pink 95%";
    const char D_COLOUR_MAP_PINK_PASTEL90_CTR[] PROGMEM =    "Pink 90%";
    const char D_COLOUR_MAP_PINK_PASTEL80_CTR[] PROGMEM =    "Pink 80%";
    const char D_COLOUR_MAP_PINK_PASTEL70_CTR[] PROGMEM =    "Pink 70%";
    const char D_COLOUR_MAP_PINK_PASTEL60_CTR[] PROGMEM =    "Pink 60%";
    const char D_COLOUR_MAP_PINK_PASTEL50_CTR[] PROGMEM =    "Pink 50%";
    const char D_COLOUR_MAP_PINK_PASTEL40_CTR[] PROGMEM =    "Pink 40%";
    // Hot Pink;
    const char D_COLOUR_MAP_HOTPINK_CTR[] PROGMEM =             "Hot Pink 100%";
    const char D_COLOUR_MAP_HOTPINK_PASTEL95_CTR[] PROGMEM =    "Hot Pink 95%";
    const char D_COLOUR_MAP_HOTPINK_PASTEL90_CTR[] PROGMEM =    "Hot Pink 90%";
    const char D_COLOUR_MAP_HOTPINK_PASTEL80_CTR[] PROGMEM =    "Hot Pink 80%";
    const char D_COLOUR_MAP_HOTPINK_PASTEL70_CTR[] PROGMEM =    "Hot Pink 70%";
    const char D_COLOUR_MAP_HOTPINK_PASTEL60_CTR[] PROGMEM =    "Hot Pink 60%";
    const char D_COLOUR_MAP_HOTPINK_PASTEL50_CTR[] PROGMEM =    "Hot Pink 50%";
    const char D_COLOUR_MAP_HOTPINK_PASTEL40_CTR[] PROGMEM =    "Hot Pink 40%";
    // Hot Pink/Almost red
    const char D_COLOUR_MAP_HOTPINKRED_CTR[] PROGMEM =    "Hot Pink Red Hue 359";

    // None = notset
    const char D_COLOUR_MAP_NONE_CTR[] PROGMEM =               "None";
    const char D_COLOUR_MAP_PALETTE_OPTIONS_END_CTR[] PROGMEM = "Nothing";

#ifdef USE_OLD_HSB_METHOD
    enum PRESET_COLOUR_MAP_IDS{
      COLOUR_MAP_NONE_ID=0,
      // Red
      COLOUR_MAP_RED_ID,
      COLOUR_MAP_RED_PASTEL95_ID,
      COLOUR_MAP_RED_PASTEL90_ID,
      COLOUR_MAP_RED_PASTEL80_ID,
      COLOUR_MAP_RED_PASTEL70_ID,
      COLOUR_MAP_RED_PASTEL60_ID,
      COLOUR_MAP_RED_PASTEL50_ID,
      COLOUR_MAP_RED_PASTEL40_ID,
      COLOUR_MAP_RED_PASTEL20_ID,
      // Orange
      COLOUR_MAP_ORANGE_ID,
      COLOUR_MAP_ORANGE_PASTEL95_ID,
      COLOUR_MAP_ORANGE_PASTEL90_ID,
      COLOUR_MAP_ORANGE_PASTEL80_ID,
      COLOUR_MAP_ORANGE_PASTEL70_ID,
      COLOUR_MAP_ORANGE_PASTEL60_ID,
      COLOUR_MAP_ORANGE_PASTEL50_ID,
      COLOUR_MAP_ORANGE_PASTEL40_ID,
      // Light Orange
      COLOUR_MAP_LIGHTORANGE_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL95_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL90_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL80_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL70_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL60_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL50_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL40_ID,
      // White
      COLOUR_MAP_WHITE_ID,
      COLOUR_MAP_WHITE_PASTEL95_ID,
      COLOUR_MAP_WHITE_PASTEL90_ID,
      COLOUR_MAP_WHITE_PASTEL80_ID,
      COLOUR_MAP_WHITE_PASTEL70_ID,
      COLOUR_MAP_WHITE_PASTEL60_ID,
      COLOUR_MAP_WHITE_PASTEL50_ID,
      COLOUR_MAP_WHITE_PASTEL40_ID,
      COLOUR_MAP_WHITE_PASTEL20_ID,
      // 
      COLOUR_MAP_YELLOW_ID,
      COLOUR_MAP_YELLOW_PASTEL95_ID,
      COLOUR_MAP_YELLOW_PASTEL90_ID,
      COLOUR_MAP_YELLOW_PASTEL80_ID,
      COLOUR_MAP_YELLOW_PASTEL70_ID,
      COLOUR_MAP_YELLOW_PASTEL60_ID,
      COLOUR_MAP_YELLOW_PASTEL50_ID,
      COLOUR_MAP_YELLOW_PASTEL40_ID,
      // 
      COLOUR_MAP_LIMEGREEN_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL95_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL90_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL80_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL70_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL60_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL50_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL40_ID,
      // 
      COLOUR_MAP_GREEN_ID,
      COLOUR_MAP_GREEN_PASTEL95_ID,
      COLOUR_MAP_GREEN_PASTEL90_ID,
      COLOUR_MAP_GREEN_PASTEL80_ID,
      COLOUR_MAP_GREEN_PASTEL70_ID,
      COLOUR_MAP_GREEN_PASTEL60_ID,
      COLOUR_MAP_GREEN_PASTEL50_ID,
      COLOUR_MAP_GREEN_PASTEL40_ID,
      // Cyan
      COLOUR_MAP_CYAN_ID,
      COLOUR_MAP_CYAN_PASTEL95_ID,
      COLOUR_MAP_CYAN_PASTEL90_ID,
      COLOUR_MAP_CYAN_PASTEL80_ID,
      COLOUR_MAP_CYAN_PASTEL70_ID,
      COLOUR_MAP_CYAN_PASTEL60_ID,
      COLOUR_MAP_CYAN_PASTEL50_ID,
      COLOUR_MAP_CYAN_PASTEL40_ID,
      // Blue
      COLOUR_MAP_BLUE_ID,
      COLOUR_MAP_BLUE_PASTEL95_ID,
      COLOUR_MAP_BLUE_PASTEL90_ID,
      COLOUR_MAP_BLUE_PASTEL80_ID,
      COLOUR_MAP_BLUE_PASTEL70_ID,
      COLOUR_MAP_BLUE_PASTEL60_ID,
      COLOUR_MAP_BLUE_PASTEL50_ID,
      COLOUR_MAP_BLUE_PASTEL40_ID,
      // Blue Purple
      COLOUR_MAP_BLUEPURPLE_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL95_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL90_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL80_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL70_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL60_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL50_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL40_ID,
      // Purple
      COLOUR_MAP_PURPLE_ID,
      COLOUR_MAP_PURPLE_PASTEL95_ID,
      COLOUR_MAP_PURPLE_PASTEL90_ID,
      COLOUR_MAP_PURPLE_PASTEL80_ID,
      COLOUR_MAP_PURPLE_PASTEL70_ID,
      COLOUR_MAP_PURPLE_PASTEL60_ID,
      COLOUR_MAP_PURPLE_PASTEL50_ID,
      COLOUR_MAP_PURPLE_PASTEL40_ID,
      // Pink
      COLOUR_MAP_PINK_ID,
      COLOUR_MAP_PINK_PASTEL95_ID,
      COLOUR_MAP_PINK_PASTEL90_ID,
      COLOUR_MAP_PINK_PASTEL80_ID,
      COLOUR_MAP_PINK_PASTEL70_ID,
      COLOUR_MAP_PINK_PASTEL60_ID,
      COLOUR_MAP_PINK_PASTEL50_ID,
      COLOUR_MAP_PINK_PASTEL40_ID,
      // Hot Pink
      COLOUR_MAP_HOTPINK_ID,
      COLOUR_MAP_HOTPINK_PASTEL95_ID,
      COLOUR_MAP_HOTPINK_PASTEL90_ID,
      COLOUR_MAP_HOTPINK_PASTEL80_ID,
      COLOUR_MAP_HOTPINK_PASTEL70_ID,
      COLOUR_MAP_HOTPINK_PASTEL60_ID,
      COLOUR_MAP_HOTPINK_PASTEL50_ID,
      COLOUR_MAP_HOTPINK_PASTEL40_ID,
      // End of palette options
      COLOUR_MAP_PALETTE_OPTIONS_END_ID, // extra unused colour, space wasted
      //
      // Unique colour storage //move these to special list location then save the id of it from above
      COLOUR_MAP_SPECIAL_ONEINMANY_ONE_ID,   //ie hearts colour
      COLOUR_MAP_SPECIAL_ONEINMANY_MANY_ID,  //ie other colours for shelf
      //
      COLOUR_MAP_LENGTH_ID //new end
    };

    #else


    #define COLOUR_FLOAT_HUE_RED            0.0000f
    #define COLOUR_FLOAT_HUE_ORANGE         0.0389f
    #define COLOUR_FLOAT_HUE_LIGHTORANGE    0.0556f
    #define COLOUR_FLOAT_HUE_WHITE          0.0833f
    #define COLOUR_FLOAT_HUE_YELLOW         0.1389f
    #define COLOUR_FLOAT_HUE_LIMEGREEN      0.2778f
    #define COLOUR_FLOAT_HUE_GREEN          120.0f/360.0f
    #define COLOUR_FLOAT_HUE_CYAN           180.0f/360.0f
    #define COLOUR_FLOAT_HUE_BLUE           240.0f/360.0f
    #define COLOUR_FLOAT_HUE_BLUEPURPLE     280.0f/360.0f
    #define COLOUR_FLOAT_HUE_PURPLE         300.0f/360.0f
    #define COLOUR_FLOAT_HUE_PINKE          340.0f/360.0f
    #define COLOUR_FLOAT_HUE_HOTPINK        350.0f/360.0f
    
    const float colour_float_map_values[] PROGMEM = {
        COLOUR_FLOAT_HUE_RED,
        COLOUR_FLOAT_HUE_ORANGE,
        COLOUR_FLOAT_HUE_LIGHTORANGE,
        COLOUR_FLOAT_HUE_WHITE,
        COLOUR_FLOAT_HUE_YELLOW,
        COLOUR_FLOAT_HUE_LIMEGREEN,
        COLOUR_FLOAT_HUE_GREEN,
        COLOUR_FLOAT_HUE_CYAN,
        COLOUR_FLOAT_HUE_BLUE,
        COLOUR_FLOAT_HUE_BLUEPURPLE,
        COLOUR_FLOAT_HUE_PURPLE,
        COLOUR_FLOAT_HUE_PINKE,
        COLOUR_FLOAT_HUE_HOTPINK
    };

    
    enum PRESET_COLOUR_MAP_IDS{
      // Red
      COLOUR_MAP_RED_ID=0,
      COLOUR_MAP_RED_PASTEL95_ID,
      COLOUR_MAP_RED_PASTEL90_ID,
      COLOUR_MAP_RED_PASTEL80_ID,
      COLOUR_MAP_RED_PASTEL70_ID,
      COLOUR_MAP_RED_PASTEL60_ID,
      COLOUR_MAP_RED_PASTEL50_ID,
      COLOUR_MAP_RED_PASTEL40_ID,
      COLOUR_MAP_RED_PASTEL30_ID,
      COLOUR_MAP_RED_PASTEL20_ID,
      COLOUR_MAP_RED_PASTEL10_ID,
      COLOUR_MAP_RED_PASTEL0_ID,
      // Orange
      COLOUR_MAP_ORANGE_ID,
      COLOUR_MAP_ORANGE_PASTEL95_ID,
      COLOUR_MAP_ORANGE_PASTEL90_ID,
      COLOUR_MAP_ORANGE_PASTEL80_ID,
      COLOUR_MAP_ORANGE_PASTEL70_ID,
      COLOUR_MAP_ORANGE_PASTEL60_ID,
      COLOUR_MAP_ORANGE_PASTEL50_ID,
      COLOUR_MAP_ORANGE_PASTEL40_ID,
      COLOUR_MAP_ORANGE_PASTEL30_ID,
      COLOUR_MAP_ORANGE_PASTEL20_ID,
      COLOUR_MAP_ORANGE_PASTEL10_ID,
      COLOUR_MAP_ORANGE_PASTEL0_ID,
      // Light Orange
      COLOUR_MAP_LIGHTORANGE_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL95_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL90_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL80_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL70_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL60_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL50_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL40_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL30_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL20_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL10_ID,
      COLOUR_MAP_LIGHTORANGE_PASTEL0_ID,
      // White
      COLOUR_MAP_WHITE_ID,
      COLOUR_MAP_WHITE_PASTEL95_ID,
      COLOUR_MAP_WHITE_PASTEL90_ID,
      COLOUR_MAP_WHITE_PASTEL80_ID,
      COLOUR_MAP_WHITE_PASTEL70_ID,
      COLOUR_MAP_WHITE_PASTEL60_ID,
      COLOUR_MAP_WHITE_PASTEL50_ID,
      COLOUR_MAP_WHITE_PASTEL40_ID,
      COLOUR_MAP_WHITE_PASTEL30_ID,
      COLOUR_MAP_WHITE_PASTEL20_ID,
      COLOUR_MAP_WHITE_PASTEL10_ID,
      COLOUR_MAP_WHITE_PASTEL0_ID,
      // 
      COLOUR_MAP_YELLOW_ID,
      COLOUR_MAP_YELLOW_PASTEL95_ID,
      COLOUR_MAP_YELLOW_PASTEL90_ID,
      COLOUR_MAP_YELLOW_PASTEL80_ID,
      COLOUR_MAP_YELLOW_PASTEL70_ID,
      COLOUR_MAP_YELLOW_PASTEL60_ID,
      COLOUR_MAP_YELLOW_PASTEL50_ID,
      COLOUR_MAP_YELLOW_PASTEL40_ID,
      COLOUR_MAP_YELLOW_PASTEL30_ID,
      COLOUR_MAP_YELLOW_PASTEL20_ID,
      COLOUR_MAP_YELLOW_PASTEL10_ID,
      COLOUR_MAP_YELLOW_PASTEL0_ID,
      // 
      COLOUR_MAP_LIMEGREEN_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL95_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL90_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL80_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL70_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL60_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL50_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL40_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL30_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL20_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL10_ID,
      COLOUR_MAP_LIMEGREEN_PASTEL0_ID,
      // 
      COLOUR_MAP_GREEN_ID,
      COLOUR_MAP_GREEN_PASTEL95_ID,
      COLOUR_MAP_GREEN_PASTEL90_ID,
      COLOUR_MAP_GREEN_PASTEL80_ID,
      COLOUR_MAP_GREEN_PASTEL70_ID,
      COLOUR_MAP_GREEN_PASTEL60_ID,
      COLOUR_MAP_GREEN_PASTEL50_ID,
      COLOUR_MAP_GREEN_PASTEL40_ID,
      COLOUR_MAP_GREEN_PASTEL30_ID,
      COLOUR_MAP_GREEN_PASTEL20_ID,
      COLOUR_MAP_GREEN_PASTEL10_ID,
      COLOUR_MAP_GREEN_PASTEL0_ID,
      // Cyan
      COLOUR_MAP_CYAN_ID,
      COLOUR_MAP_CYAN_PASTEL95_ID,
      COLOUR_MAP_CYAN_PASTEL90_ID,
      COLOUR_MAP_CYAN_PASTEL80_ID,
      COLOUR_MAP_CYAN_PASTEL70_ID,
      COLOUR_MAP_CYAN_PASTEL60_ID,
      COLOUR_MAP_CYAN_PASTEL50_ID,
      COLOUR_MAP_CYAN_PASTEL40_ID,
      COLOUR_MAP_CYAN_PASTEL30_ID,
      COLOUR_MAP_CYAN_PASTEL20_ID,
      COLOUR_MAP_CYAN_PASTEL10_ID,
      COLOUR_MAP_CYAN_PASTEL0_ID,
      // Blue
      COLOUR_MAP_BLUE_ID,
      COLOUR_MAP_BLUE_PASTEL95_ID,
      COLOUR_MAP_BLUE_PASTEL90_ID,
      COLOUR_MAP_BLUE_PASTEL80_ID,
      COLOUR_MAP_BLUE_PASTEL70_ID,
      COLOUR_MAP_BLUE_PASTEL60_ID,
      COLOUR_MAP_BLUE_PASTEL50_ID,
      COLOUR_MAP_BLUE_PASTEL40_ID,
      COLOUR_MAP_BLUE_PASTEL30_ID,
      COLOUR_MAP_BLUE_PASTEL20_ID,
      COLOUR_MAP_BLUE_PASTEL10_ID,
      COLOUR_MAP_BLUE_PASTEL0_ID,
      // Blue Purple
      COLOUR_MAP_BLUEPURPLE_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL95_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL90_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL80_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL70_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL60_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL50_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL40_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL30_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL20_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL10_ID,
      COLOUR_MAP_BLUEPURPLE_PASTEL0_ID,
      // Purple
      COLOUR_MAP_PURPLE_ID,
      COLOUR_MAP_PURPLE_PASTEL95_ID,
      COLOUR_MAP_PURPLE_PASTEL90_ID,
      COLOUR_MAP_PURPLE_PASTEL80_ID,
      COLOUR_MAP_PURPLE_PASTEL70_ID,
      COLOUR_MAP_PURPLE_PASTEL60_ID,
      COLOUR_MAP_PURPLE_PASTEL50_ID,
      COLOUR_MAP_PURPLE_PASTEL40_ID,
      COLOUR_MAP_PURPLE_PASTEL30_ID,
      COLOUR_MAP_PURPLE_PASTEL20_ID,
      COLOUR_MAP_PURPLE_PASTEL10_ID,
      COLOUR_MAP_PURPLE_PASTEL0_ID,
      // Pink
      COLOUR_MAP_PINK_ID,
      COLOUR_MAP_PINK_PASTEL95_ID,
      COLOUR_MAP_PINK_PASTEL90_ID,
      COLOUR_MAP_PINK_PASTEL80_ID,
      COLOUR_MAP_PINK_PASTEL70_ID,
      COLOUR_MAP_PINK_PASTEL60_ID,
      COLOUR_MAP_PINK_PASTEL50_ID,
      COLOUR_MAP_PINK_PASTEL40_ID,
      COLOUR_MAP_PINK_PASTEL30_ID,
      COLOUR_MAP_PINK_PASTEL20_ID,
      COLOUR_MAP_PINK_PASTEL10_ID,
      COLOUR_MAP_PINK_PASTEL0_ID,
      // Hot Pink
      COLOUR_MAP_HOTPINK_ID,
      COLOUR_MAP_HOTPINK_PASTEL95_ID,
      COLOUR_MAP_HOTPINK_PASTEL90_ID,
      COLOUR_MAP_HOTPINK_PASTEL80_ID,
      COLOUR_MAP_HOTPINK_PASTEL70_ID,
      COLOUR_MAP_HOTPINK_PASTEL60_ID,
      COLOUR_MAP_HOTPINK_PASTEL50_ID,
      COLOUR_MAP_HOTPINK_PASTEL40_ID,
      COLOUR_MAP_HOTPINK_PASTEL30_ID,
      COLOUR_MAP_HOTPINK_PASTEL20_ID,
      COLOUR_MAP_HOTPINK_PASTEL10_ID,
      COLOUR_MAP_HOTPINK_PASTEL0_ID,
      // End
      COLOUR_MAP_NONE_ID,
    //   //
    COLOUR_MAP_PALETTE_OPTIONS_END_ID,
      // Unique colour storage //move these to special list location then save the id of it from above
      COLOUR_MAP_SPECIAL_ONEINMANY_ONE_ID,   //ie hearts colour
      COLOUR_MAP_SPECIAL_ONEINMANY_MANY_ID,  //ie other colours for shelf
      //
      COLOUR_MAP_LENGTH_ID //new end
    };

    #endif

  // Default user palettes I like ()
  // must , COLOUR_MAP_NONE_ID finish with none, this is now length
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_01_IDS[] PROGMEM = {
    COLOUR_MAP_RED_ID, COLOUR_MAP_GREEN_ID, COLOUR_MAP_PINK_ID, COLOUR_MAP_BLUE_ID, COLOUR_MAP_ORANGE_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_02_IDS[] PROGMEM = {
    COLOUR_MAP_YELLOW_ID, COLOUR_MAP_RED_ID, COLOUR_MAP_ORANGE_ID, COLOUR_MAP_GREEN_ID, COLOUR_MAP_PINK_ID,
    COLOUR_MAP_BLUE_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_03_IDS[] PROGMEM {
    COLOUR_MAP_GREEN_ID, COLOUR_MAP_PINK_ID, COLOUR_MAP_ORANGE_ID, COLOUR_MAP_BLUE_ID, COLOUR_MAP_YELLOW_ID,
    COLOUR_MAP_PURPLE_ID, COLOUR_MAP_RED_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_04_IDS[] PROGMEM {
    COLOUR_MAP_PURPLE_PASTEL95_ID, COLOUR_MAP_HOTPINK_ID, COLOUR_MAP_ORANGE_PASTEL90_ID, COLOUR_MAP_BLUE_PASTEL95_ID, COLOUR_MAP_LIMEGREEN_PASTEL95_ID,
    COLOUR_MAP_PURPLE_ID, COLOUR_MAP_HOTPINK_PASTEL95_ID, COLOUR_MAP_CYAN_ID, COLOUR_MAP_PURPLE_ID, COLOUR_MAP_BLUE_PASTEL80_ID, 
    COLOUR_MAP_YELLOW_PASTEL95_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_05_IDS[] PROGMEM {
    COLOUR_MAP_YELLOW_ID, COLOUR_MAP_GREEN_ID, COLOUR_MAP_PINK_ID, COLOUR_MAP_BLUE_ID, COLOUR_MAP_RED_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_06_IDS[] PROGMEM {
    COLOUR_MAP_WHITE_PASTEL40_ID, COLOUR_MAP_GREEN_ID, COLOUR_MAP_PINK_ID, COLOUR_MAP_BLUE_ID, COLOUR_MAP_RED_ID,
    COLOUR_MAP_ORANGE_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_07_IDS[] PROGMEM {
    COLOUR_MAP_GREEN_ID, COLOUR_MAP_PINK_ID, COLOUR_MAP_ORANGE_ID, COLOUR_MAP_BLUE_ID, COLOUR_MAP_YELLOW_ID,
    COLOUR_MAP_PURPLE_ID, COLOUR_MAP_RED_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_08_IDS[] PROGMEM {
    COLOUR_MAP_WHITE_PASTEL20_ID, COLOUR_MAP_WHITE_PASTEL80_ID, COLOUR_MAP_CYAN_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_09_IDS[] PROGMEM {
    COLOUR_MAP_WHITE_PASTEL20_ID, COLOUR_MAP_WHITE_PASTEL20_ID, COLOUR_MAP_CYAN_PASTEL60_ID, COLOUR_MAP_WHITE_PASTEL20_ID, COLOUR_MAP_WHITE_PASTEL70_ID,
    COLOUR_MAP_BLUE_PASTEL60_ID, COLOUR_MAP_WHITE_PASTEL70_ID, COLOUR_MAP_CYAN_PASTEL40_ID, COLOUR_MAP_WHITE_PASTEL60_ID, COLOUR_MAP_CYAN_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_10_IDS[] PROGMEM {
    COLOUR_MAP_WHITE_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_11_IDS[] PROGMEM {
    COLOUR_MAP_WHITE_PASTEL80_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_12_IDS[] PROGMEM {
    COLOUR_MAP_GREEN_ID, COLOUR_MAP_HOTPINK_ID, COLOUR_MAP_BLUE_ID, COLOUR_MAP_PINK_ID, COLOUR_MAP_YELLOW_ID,
    COLOUR_MAP_ORANGE_ID, COLOUR_MAP_HOTPINK_ID, COLOUR_MAP_YELLOW_ID, COLOUR_MAP_PURPLE_ID, COLOUR_MAP_RED_ID,
    COLOUR_MAP_PINK_ID, COLOUR_MAP_YELLOW_ID, COLOUR_MAP_ORANGE_ID, COLOUR_MAP_HOTPINK_ID, COLOUR_MAP_YELLOW_ID,
    COLOUR_MAP_PURPLE_ID, COLOUR_MAP_RED_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_13_IDS[] PROGMEM {
    COLOUR_MAP_GREEN_ID, COLOUR_MAP_HOTPINK_ID, COLOUR_MAP_BLUE_ID, COLOUR_MAP_PINK_ID, COLOUR_MAP_HOTPINK_ID,
    COLOUR_MAP_ORANGE_ID, COLOUR_MAP_HOTPINK_ID, COLOUR_MAP_YELLOW_ID, COLOUR_MAP_PURPLE_ID, COLOUR_MAP_RED_PASTEL90_ID,
    COLOUR_MAP_PURPLE_ID, COLOUR_MAP_HOTPINK_ID, COLOUR_MAP_PINK_ID, COLOUR_MAP_GREEN_PASTEL90_ID, COLOUR_MAP_PINK_ID,
    COLOUR_MAP_CYAN_ID, COLOUR_MAP_HOTPINK_ID, COLOUR_MAP_YELLOW_ID, COLOUR_MAP_RED_PASTEL90_ID, COLOUR_MAP_PURPLE_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_14_IDS[] PROGMEM {
    COLOUR_MAP_RED_ID, COLOUR_MAP_RED_ID, COLOUR_MAP_RED_ID, COLOUR_MAP_GREEN_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_15_IDS[] PROGMEM {
    COLOUR_MAP_GREEN_ID, COLOUR_MAP_GREEN_ID, COLOUR_MAP_GREEN_ID, COLOUR_MAP_RED_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_16_IDS[] PROGMEM {
    COLOUR_MAP_GREEN_ID, COLOUR_MAP_BLUE_ID, COLOUR_MAP_RED_ID, COLOUR_MAP_PINK_ID, COLOUR_MAP_RED_PASTEL90_ID,
    COLOUR_MAP_ORANGE_ID, COLOUR_MAP_BLUE_ID, COLOUR_MAP_HOTPINK_ID, COLOUR_MAP_PURPLE_ID, COLOUR_MAP_YELLOW_ID,
    COLOUR_MAP_PINK_ID, COLOUR_MAP_RED_PASTEL90_ID, COLOUR_MAP_GREEN_ID, COLOUR_MAP_ORANGE_ID, COLOUR_MAP_HOTPINK_ID,
    COLOUR_MAP_PURPLE_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_17_IDS[] PROGMEM {
    COLOUR_MAP_GREEN_ID, COLOUR_MAP_HOTPINK_PASTEL90_ID, COLOUR_MAP_BLUE_ID, COLOUR_MAP_PINK_ID, COLOUR_MAP_HOTPINK_PASTEL90_ID,
    COLOUR_MAP_ORANGE_ID, COLOUR_MAP_HOTPINK_ID, COLOUR_MAP_YELLOW_ID, COLOUR_MAP_RED_PASTEL90_ID, COLOUR_MAP_PURPLE_ID,
    COLOUR_MAP_PINK_ID, COLOUR_MAP_GREEN_PASTEL90_ID, COLOUR_MAP_PINK_ID, COLOUR_MAP_CYAN_ID, COLOUR_MAP_HOTPINK_ID,
    COLOUR_MAP_YELLOW_PASTEL95_ID, COLOUR_MAP_PURPLE_PASTEL90_ID, COLOUR_MAP_RED_ID, COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_18_IDS[] PROGMEM {
    COLOUR_MAP_WHITE_PASTEL20_ID, COLOUR_MAP_WHITE_PASTEL20_ID, COLOUR_MAP_CYAN_PASTEL60_ID, COLOUR_MAP_WHITE_PASTEL20_ID, COLOUR_MAP_WHITE_PASTEL70_ID,
    COLOUR_MAP_BLUE_PASTEL60_ID, COLOUR_MAP_WHITE_PASTEL20_ID, COLOUR_MAP_WHITE_PASTEL70_ID, COLOUR_MAP_PURPLE_PASTEL60_ID, COLOUR_MAP_WHITE_PASTEL20_ID,
    COLOUR_MAP_WHITE_PASTEL70_ID, COLOUR_MAP_CYAN_PASTEL40_ID, COLOUR_MAP_WHITE_PASTEL60_ID, COLOUR_MAP_BLUE_ID, COLOUR_MAP_WHITE_PASTEL60_ID, COLOUR_MAP_NONE_ID
  }; 
  // Style = deep purple, pinks and a little red
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_19_IDS[] PROGMEM {
    COLOUR_MAP_HOTPINK_ID, COLOUR_MAP_PINK_PASTEL90_ID, COLOUR_MAP_PURPLE_ID, COLOUR_MAP_HOTPINK_PASTEL95_ID,
    COLOUR_MAP_RED_PASTEL80_ID,
    // END
    COLOUR_MAP_NONE_ID
  }; 
  const uint8_t DEFAULT_COLOUR_PALETTE_USER_20_IDS[] PROGMEM {  
    COLOUR_MAP_GREEN_ID, COLOUR_MAP_PINK_ID, COLOUR_MAP_ORANGE_ID, COLOUR_MAP_BLUE_ID, COLOUR_MAP_YELLOW_ID,
    COLOUR_MAP_PURPLE_ID, COLOUR_MAP_RED_ID, COLOUR_MAP_NONE_ID
  }; 

  #ifndef D_PALETTE_WINTER_NAME_CTR
  #define D_PALETTE_WINTER_NAME_CTR        "Winter"   
  #endif
  const char PM_PALETTE_WINTER_NAME_CTR[] PROGMEM = D_PALETTE_WINTER_NAME_CTR;
  const uint8_t COLOUR_PALETTE_WINTER_MAP_IDS[] PROGMEM = {
    COLOUR_MAP_CYAN_ID, COLOUR_MAP_WHITE_ID, COLOUR_MAP_CYAN_ID, COLOUR_MAP_BLUE_PASTEL60_ID,
    COLOUR_MAP_WHITE_ID
  };
  
  #ifndef D_PALETTE_PASTEL_NAME_CTR
  #define D_PALETTE_PASTEL_NAME_CTR        "Pastel Easter"   
  #endif
  const char PM_PALETTE_PASTEL_NAME_CTR[] PROGMEM = D_PALETTE_PASTEL_NAME_CTR;
  const uint8_t COLOUR_PALETTE_PASTEL_MAP_IDS[] PROGMEM = {
    COLOUR_MAP_CYAN_PASTEL80_ID, COLOUR_MAP_PINK_PASTEL80_ID, 
    COLOUR_MAP_LIGHTORANGE_PASTEL80_ID,
    COLOUR_MAP_PINK_PASTEL30_ID,
    COLOUR_MAP_GREEN_PASTEL40_ID,
    COLOUR_MAP_WHITE_PASTEL70_ID

  };

  #ifndef D_PALETTE_OCEAN_01_NAME_CTR
  #define D_PALETTE_OCEAN_01_NAME_CTR        "Ocean 01"   
  #endif
  const char PM_PALETTE_OCEAN_01_NAME_CTR[] PROGMEM = D_PALETTE_OCEAN_01_NAME_CTR;
  const uint8_t colour_map_ocean_01_id[] PROGMEM = {
    COLOUR_MAP_GREEN_ID,COLOUR_MAP_CYAN_ID,COLOUR_MAP_BLUE_ID,COLOUR_MAP_WHITE_ID
  };

  #ifndef D_PALETTE_RAINBOW_NAME_CTR
  #define D_PALETTE_RAINBOW_NAME_CTR        "Rainbow"   
  #endif          
  const char PM_PALETTE_RAINBOW_NAME_CTR[] PROGMEM = D_PALETTE_RAINBOW_NAME_CTR;
  const uint8_t colour_map_rainbow_id[] PROGMEM = {
    0,   COLOUR_MAP_RED_ID, //0
    14,  COLOUR_MAP_LIGHTORANGE_ID, //20
    35,  COLOUR_MAP_YELLOW_ID, //50
    85,  COLOUR_MAP_GREEN_ID, //120
    127,  COLOUR_MAP_CYAN_ID, //180
    170,  COLOUR_MAP_BLUE_ID, //240
    213 ,  COLOUR_MAP_PURPLE_ID, //300
    241 ,  COLOUR_MAP_PINK_ID, //340
    255, COLOUR_MAP_RED_ID //0
  };
  
  #ifndef D_PALETTE_RAINBOW_INVERTED_NAME_CTR
  #define D_PALETTE_RAINBOW_INVERTED_NAME_CTR        "Rainbow Inverted"   
  #endif          
  const char PM_PALETTE_RAINBOW_INVERTED_NAME_CTR[] PROGMEM = D_PALETTE_RAINBOW_INVERTED_NAME_CTR;
  const uint8_t colour_map_rainbow_inverted_id[] PROGMEM = {
    0,   COLOUR_MAP_BLUE_ID, //0
    14,  COLOUR_MAP_PURPLE_ID, //20
    35,  COLOUR_MAP_PINK_ID, //50
    85,  COLOUR_MAP_RED_ID, //120
    127,  COLOUR_MAP_LIGHTORANGE_ID, //180
    170,  COLOUR_MAP_YELLOW_ID, //240
    213 ,  COLOUR_MAP_GREEN_ID, //300
    241 ,  COLOUR_MAP_CYAN_ID, //340
    255, COLOUR_MAP_BLUE_ID //0
  };
  
  #ifndef D_PALETTE_AUTUMN_RED_NAME_CTR
  #define D_PALETTE_AUTUMN_RED_NAME_CTR        "Autumn Red"   
  #endif
  const char PM_PALETTE_AUTUMN_RED_NAME_CTR[] PROGMEM = D_PALETTE_AUTUMN_RED_NAME_CTR;
  const uint8_t colour_map_autumnred_id[] PROGMEM = {
    COLOUR_MAP_RED_ID,COLOUR_MAP_RED_ID,
    COLOUR_MAP_YELLOW_ID,COLOUR_MAP_YELLOW_PASTEL90_ID,
    COLOUR_MAP_ORANGE_ID
  };
  
  #ifndef D_PALETTE_AUTUMN_NAME_CTR
  #define D_PALETTE_AUTUMN_NAME_CTR        "Autumn"   
  #endif
  const char PM_PALETTE_AUTUMN_NAME_CTR[] PROGMEM = D_PALETTE_AUTUMN_NAME_CTR;
  const uint8_t colour_map_autumn_id[] PROGMEM = {
    COLOUR_MAP_RED_ID,COLOUR_MAP_GREEN_PASTEL70_ID,
    COLOUR_MAP_YELLOW_ID,COLOUR_MAP_YELLOW_PASTEL90_ID,
    COLOUR_MAP_ORANGE_ID,COLOUR_MAP_LIMEGREEN_PASTEL90_ID
  };

  
    #ifndef D_PALETTE_HOLLOWEEN_OP_NAME_CTR
    #define D_PALETTE_HOLLOWEEN_OP_NAME_CTR        "Holloween Orange-Purple"   
    #endif
    const char PM_PALETTE_HOLLOWEEN_OP_NAME_CTR[] PROGMEM = D_PALETTE_HOLLOWEEN_OP_NAME_CTR;
    const uint8_t colour_map_holloween_op_id[] PROGMEM = {
      COLOUR_MAP_LIGHTORANGE_ID, COLOUR_MAP_PURPLE_ID
    };

    #ifndef D_PALETTE_HOLLOWEEN_OGP_NAME_CTR
    #define D_PALETTE_HOLLOWEEN_OGP_NAME_CTR        "Holloween Orange-Green-Purple"   
    #endif
    const char PM_PALETTE_HOLLOWEEN_OGP_NAME_CTR[] PROGMEM = D_PALETTE_HOLLOWEEN_OGP_NAME_CTR;
    const uint8_t colour_map_holloween_ogp_id[] PROGMEM = {
      COLOUR_MAP_LIGHTORANGE_ID, COLOUR_MAP_GREEN_PASTEL90_ID, COLOUR_MAP_PURPLE_ID
    };

    #ifndef D_PALETTE_SHELF_HEARTS_NAME_CTR
    #define D_PALETTE_SHELF_HEARTS_NAME_CTR        "Shelf Hearts"   
    #endif
    const char PM_PALETTE_SHELF_HEARTS_NAME_CTR[] PROGMEM = D_PALETTE_SHELF_HEARTS_NAME_CTR;
    const uint8_t colour_map_shelf_hearts_id[] PROGMEM = { //position/colour pairs {pos0,col0, pos1,col1, pos2,col2, ... pos255,col} ie set all
      255,COLOUR_MAP_SPECIAL_ONEINMANY_MANY_ID, //255 means ALL this colour, optional
      1,  COLOUR_MAP_SPECIAL_ONEINMANY_ONE_ID, 
      6,  COLOUR_MAP_SPECIAL_ONEINMANY_ONE_ID, 
      10, COLOUR_MAP_SPECIAL_ONEINMANY_ONE_ID, 
      16, COLOUR_MAP_SPECIAL_ONEINMANY_ONE_ID, 
      21, COLOUR_MAP_SPECIAL_ONEINMANY_ONE_ID, 
      25, COLOUR_MAP_SPECIAL_ONEINMANY_ONE_ID, 
      31, COLOUR_MAP_SPECIAL_ONEINMANY_ONE_ID
    };

    // optional gradient positions to linearbelnd between, first position is percentage    
    #ifndef D_PALETTE_GRADIENT_01_NAME_CTR
    #define D_PALETTE_GRADIENT_01_NAME_CTR        "Gradient 01 - Compressed Rainbow"   
    #endif
    DEF_PGM_CTR  (PM_PALETTE_GRADIENT_01_NAME_CTR) D_PALETTE_GRADIENT_01_NAME_CTR;
    DEF_PGM_UINT8(PM_PALETTE_GRADIENT_01_COLOUR_MAP_IDS) 
    { // pos%, HSB id
      0,   COLOUR_MAP_RED_ID,
      20,  COLOUR_MAP_ORANGE_ID,
      35,  COLOUR_MAP_GREEN_ID,
      50,  COLOUR_MAP_CYAN_ID,
      65,  COLOUR_MAP_BLUE_ID,
      80,  COLOUR_MAP_PINK_ID,
      100, COLOUR_MAP_HOTPINK_ID
    };

    #ifndef D_PALETTE_GRADIENT_02_NAME_CTR
    #define D_PALETTE_GRADIENT_02_NAME_CTR        "Gradient 02"   
    #endif
    DEF_PGM_CTR  (PM_PALETTE_GRADIENT_02_NAME_CTR)        D_PALETTE_GRADIENT_02_NAME_CTR;
    DEF_PGM_UINT8(PM_PALETTE_GRADIENT_02_COLOUR_MAP_IDS)
    { // pos%,R,G,B
      0,  26,  1,  1,
      51,  67,  4,  1,
      84, 118, 14,  1,
      104, 137,152, 52,
      112, 113, 65,  1,
      122, 133,149, 59,
      124, 137,152, 52,
      135, 113, 65,  1,
      142, 139,154, 46,
      163, 113, 13,  1,
      204,  55,  3,  1,
      249,  17,  1,  1,
      255,  17,  1,  1
    };


// const RgbColor Palette[] PROGMEM = {HsbColor(0.5f, 0.5f, 0.5f), HsbColor(1.0f, 0.5f, 0.5f)};

//     #ifndef D_PALETTE_TEST_NAME_CTR
//     #define D_PALETTE_TEST_NAME_CTR        "Test"   
//     #endif      
//     static const char* PM_PALETTE_TEST_NAME_CTR = D_PALETTE_TEST_NAME_CTR;
//     static uint8_t colour_map_test_id[12] = {
//       0,  255,  0,  0,
//       50,  0, 255,  0,
//       100, 255, 0,  0
//     };

//     //others here

// };



// // // On some platforms, most notably ARM M0, unaligned access
// // // to 'PROGMEM' for multibyte values (eg read dword) is
// // // not allowed and causes a crash.  This macro can help
// // // force 4-byte alignment as needed.  The FastLED gradient
// // // palette code uses 'read dword', and now uses this macro
// // // to make sure that gradient palettes are 4-byte aligned.
// // #if defined(FASTLED_ARM) || defined(ESP32) || defined(ESP8266)
// // #define FL_ALIGN_PROGMEM  __attribute__ ((aligned (4)))
// // #else
// // #define FL_ALIGN_PROGMEM
// // #endif

// // //empty PROGMEM simulation
// // #define FL_PROGMEM

// // typedef const uint8_t TProgmemRGBGradientPalette_byte ;
// // typedef const TProgmemRGBGradientPalette_byte *TProgmemRGBGradientPalette_bytes;
// // typedef TProgmemRGBGradientPalette_bytes TProgmemRGBGradientPalettePtr;

// // #define DEFINE_GRADIENT_PALETTE(X) \
// //   FL_ALIGN_PROGMEM \
// //   extern const TProgmemRGBGradientPalette_byte X[] FL_PROGMEM =

// // #define DECLARE_GRADIENT_PALETTE(X) \
// //   FL_ALIGN_PROGMEM \
// //   extern const TProgmemRGBGradientPalette_byte X[] FL_PROGMEM

// // DEFINE_GRADIENT_PALETTE( ib_jul01_gp ) {
// //     0, 194,  1,  1,
// //    94,   1, 29, 18,
// //   132,  57,131, 28,
// //   255, 113,  1,  1};

// // // Gradient palette "es_vintage_57_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/vintage/tn/es_vintage_57.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 20 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( es_vintage_57_gp ) {
// //     0,   2,  1,  1,
// //    53,  18,  1,  0,
// //   104,  69, 29,  1,
// //   153, 167,135, 10,
// //   255,  46, 56,  4};


// // // Gradient palette "es_vintage_01_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/vintage/tn/es_vintage_01.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 32 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( es_vintage_01_gp ) {
// //     0,   4,  1,  1,
// //    51,  16,  0,  1,
// //    76,  97,104,  3,
// //   101, 255,131, 19,
// //   127,  67,  9,  4,
// //   153,  16,  0,  1,
// //   229,   4,  1,  1,
// //   255,   4,  1,  1};


// // // Gradient palette "es_rivendell_15_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/rivendell/tn/es_rivendell_15.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 20 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( es_rivendell_15_gp ) {
// //     0,   1, 14,  5,
// //   101,  16, 36, 14,
// //   165,  56, 68, 30,
// //   242, 150,156, 99,
// //   255, 150,156, 99};


// // // Gradient palette "rgi_15_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/ds/rgi/tn/rgi_15.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 36 bytes of program space.
// // // Edited to be brighter

// // DEFINE_GRADIENT_PALETTE( rgi_15_gp ) {
// //     0,   4,  1, 70,
// //    31,  55,  1, 30,
// //    63, 255,  4,  7,
// //    95,  59,  2, 29,
// //   127,  11,  3, 50,
// //   159,  39,  8, 60,
// //   191, 112, 19, 40,
// //   223,  78, 11, 39,
// //   255,  29,  8, 59};


// // // Gradient palette "retro2_16_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/ma/retro2/tn/retro2_16.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 8 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( retro2_16_gp ) {
// //     0, 188,135,  1,
// //   255,  46,  7,  1};


// // // Gradient palette "Analogous_1_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/red/tn/Analogous_1.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 20 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( Analogous_1_gp ) {
// //     0,   3,  0,255,
// //    63,  23,  0,255,
// //   127,  67,  0,255,
// //   191, 142,  0, 45,
// //   255, 255,  0,  0};


// // // Gradient palette "es_pinksplash_08_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/pink_splash/tn/es_pinksplash_08.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 20 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( es_pinksplash_08_gp ) {
// //     0, 126, 11,255,
// //   127, 197,  1, 22,
// //   175, 210,157,172,
// //   221, 157,  3,112,
// //   255, 157,  3,112};


// // // Gradient palette "es_ocean_breeze_036_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/ocean_breeze/tn/es_ocean_breeze_036.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 16 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( es_ocean_breeze_036_gp ) {
// //     0,   1,  6,  7,
// //    89,   1, 99,111,
// //   153, 144,209,255,
// //   255,   0, 73, 82};


// // // Gradient palette "departure_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/mjf/tn/departure.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 88 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( departure_gp ) {
// //     0,   8,  3,  0,
// //    42,  23,  7,  0,
// //    63,  75, 38,  6,
// //    84, 169, 99, 38,
// //   106, 213,169,119,
// //   116, 255,255,255,
// //   138, 135,255,138,
// //   148,  22,255, 24,
// //   170,   0,255,  0,
// //   191,   0,136,  0,
// //   212,   0, 55,  0,
// //   255,   0, 55,  0};


// // // Gradient palette "es_landscape_64_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/landscape/tn/es_landscape_64.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 36 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( es_landscape_64_gp ) {
// //     0,   0,  0,  0,
// //    37,   2, 25,  1,
// //    76,  15,115,  5,
// //   127,  79,213,  1,
// //   128, 126,211, 47,
// //   130, 188,209,247,
// //   153, 144,182,205,
// //   204,  59,117,250,
// //   255,   1, 37,192};


// // // Gradient palette "es_landscape_33_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/landscape/tn/es_landscape_33.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 24 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( es_landscape_33_gp ) {
// //     0,   1,  5,  0,
// //    19,  32, 23,  1,
// //    38, 161, 55,  1,
// //    63, 229,144,  1,
// //    66,  39,142, 74,
// //   255,   1,  4,  1};


// // // Gradient palette "rainbowsherbet_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/ma/icecream/tn/rainbowsherbet.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 28 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( rainbowsherbet_gp ) {
// //     0, 255, 33,  4,
// //    43, 255, 68, 25,
// //    86, 255,  7, 25,
// //   127, 255, 82,103,
// //   170, 255,255,242,
// //   209,  42,255, 22,
// //   255,  87,255, 65};


// // // Gradient palette "gr65_hult_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/hult/tn/gr65_hult.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 24 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( gr65_hult_gp ) {
// //     0, 247,176,247,
// //    48, 255,136,255,
// //    89, 220, 29,226,
// //   160,   7, 82,178,
// //   216,   1,124,109,
// //   255,   1,124,109};


// // // Gradient palette "gr64_hult_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/hult/tn/gr64_hult.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 32 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( gr64_hult_gp ) {
// //     0,   1,124,109,
// //    66,   1, 93, 79,
// //   104,  52, 65,  1,
// //   130, 115,127,  1,
// //   150,  52, 65,  1,
// //   201,   1, 86, 72,
// //   239,   0, 55, 45,
// //   255,   0, 55, 45};


// // // Gradient palette "GMT_drywet_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/gmt/tn/GMT_drywet.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 28 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( GMT_drywet_gp ) {
// //     0,  47, 30,  2,
// //    42, 213,147, 24,
// //    84, 103,219, 52,
// //   127,   3,219,207,
// //   170,   1, 48,214,
// //   212,   1,  1,111,
// //   255,   1,  7, 33};


// // // Gradient palette "ib15_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/general/tn/ib15.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 24 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( ib15_gp ) {
// //     0, 113, 91,147,
// //    72, 157, 88, 78,
// //    89, 208, 85, 33,
// //   107, 255, 29, 11,
// //   141, 137, 31, 39,
// //   255,  59, 33, 89};


// // // Gradient palette "Tertiary_01_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/vermillion/tn/Tertiary_01.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 20 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( Tertiary_01_gp ) {
// //     0,   0,  1,255,
// //    63,   3, 68, 45,
// //   127,  23,255,  0,
// //   191, 100, 68,  1,
// //   255, 255,  1,  4};


// // // Gradient palette "lava_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/neota/elem/tn/lava.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 52 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( lava_gp ) {
// //     0,   0,  0,  0,
// //    46,  18,  0,  0,
// //    96, 113,  0,  0,
// //   108, 142,  3,  1,
// //   119, 175, 17,  1,
// //   146, 213, 44,  2,
// //   174, 255, 82,  4,
// //   188, 255,115,  4,
// //   202, 255,156,  4,
// //   218, 255,203,  4,
// //   234, 255,255,  4,
// //   244, 255,255, 71,
// //   255, 255,255,255};


// // // Gradient palette "fierce_ice_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/neota/elem/tn/fierce-ice.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 28 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( fierce_ice_gp ) {
// //     0,   0,  0,  0,
// //    59,   0,  9, 45,
// //   119,   0, 38,255,
// //   149,   3,100,255,
// //   180,  23,199,255,
// //   217, 100,235,255,
// //   255, 255,255,255};


// // // Gradient palette "Colorfull_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Colorfull.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 44 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( Colorfull_gp ) {
// //     0,  10, 85,  5,
// //    25,  29,109, 18,
// //    60,  59,138, 42,
// //    93,  83, 99, 52,
// //   106, 110, 66, 64,
// //   109, 123, 49, 65,
// //   113, 139, 35, 66,
// //   116, 192,117, 98,
// //   124, 255,255,137,
// //   168, 100,180,155,
// //   255,  22,121,174};


// // // Gradient palette "Pink_Purple_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Pink_Purple.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 44 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( Pink_Purple_gp ) {
// //     0,  19,  2, 39,
// //    25,  26,  4, 45,
// //    51,  33,  6, 52,
// //    76,  68, 62,125,
// //   102, 118,187,240,
// //   109, 163,215,247,
// //   114, 217,244,255,
// //   122, 159,149,221,
// //   149, 113, 78,188,
// //   183, 128, 57,155,
// //   255, 146, 40,123};


// // // Gradient palette "Sunset_Real_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Sunset_Real.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 28 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
// //     0, 120,  0,  0,
// //    22, 179, 22,  0,
// //    51, 255,104,  0,
// //    85, 167, 22, 18,
// //   135, 100,  0,103,
// //   198,  16,  0,130,
// //   255,   0,  0,160};


// // // Gradient palette "Sunset_Yellow_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Sunset_Yellow.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 44 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( Sunset_Yellow_gp ) {
// //     0,  10, 62,123,
// //    36,  56,130,103,
// //    87, 153,225, 85,
// //   100, 199,217, 68,
// //   107, 255,207, 54,
// //   115, 247,152, 57,
// //   120, 239,107, 61,
// //   128, 247,152, 57,
// //   180, 255,207, 54,
// //   223, 255,227, 48,
// //   255, 255,248, 42};


// // // Gradient palette "Beech_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Beech.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 60 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( Beech_gp ) {
// //     0, 255,252,214,
// //    12, 255,252,214,
// //    22, 255,252,214,
// //    26, 190,191,115,
// //    28, 137,141, 52,
// //    28, 112,255,205,
// //    50,  51,246,214,
// //    71,  17,235,226,
// //    93,   2,193,199,
// //   120,   0,156,174,
// //   133,   1,101,115,
// //   136,   1, 59, 71,
// //   136,   7,131,170,
// //   208,   1, 90,151,
// //   255,   0, 56,133};


// // // Gradient palette "Another_Sunset_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/Another_Sunset.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 32 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( Another_Sunset_gp ) {
// //     0, 110, 49, 11,
// //    29,  55, 34, 10,
// //    68,  22, 22,  9,
// //    68, 239,124,  8,
// //    97, 220,156, 27,
// //   124, 203,193, 61,
// //   178,  33, 53, 56,
// //   255,   0,  1, 52};





// // // Gradient palette "es_autumn_19_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/es/autumn/tn/es_autumn_19.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 52 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( es_autumn_19_gp ) {
// //     0,  26,  1,  1,
// //    51,  67,  4,  1,
// //    84, 118, 14,  1,
// //   104, 137,152, 52,
// //   112, 113, 65,  1,
// //   122, 133,149, 59,
// //   124, 137,152, 52,
// //   135, 113, 65,  1,
// //   142, 139,154, 46,
// //   163, 113, 13,  1,
// //   204,  55,  3,  1,
// //   249,  17,  1,  1,
// //   255,  17,  1,  1};


// // // Gradient palette "BlacK_Blue_Magenta_White_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/BlacK_Blue_Magenta_White.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 28 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( BlacK_Blue_Magenta_White_gp ) {
// //     0,   0,  0,  0,
// //    42,   0,  0, 45,
// //    84,   0,  0,255,
// //   127,  42,  0,255,
// //   170, 255,  0,255,
// //   212, 255, 55,255,
// //   255, 255,255,255};


// // // Gradient palette "BlacK_Magenta_Red_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/BlacK_Magenta_Red.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 20 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( BlacK_Magenta_Red_gp ) {
// //     0,   0,  0,  0,
// //    63,  42,  0, 45,
// //   127, 255,  0,255,
// //   191, 255,  0, 45,
// //   255, 255,  0,  0};


// // // Gradient palette "BlacK_Red_Magenta_Yellow_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/BlacK_Red_Magenta_Yellow.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 28 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( BlacK_Red_Magenta_Yellow_gp ) {
// //     0,   0,  0,  0,
// //    42,  42,  0,  0,
// //    84, 255,  0,  0,
// //   127, 255,  0, 45,
// //   170, 255,  0,255,
// //   212, 255, 55, 45,
// //   255, 255,255,  0};


// // // Gradient palette "Blue_Cyan_Yellow_gp", originally from
// // // http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/basic/tn/Blue_Cyan_Yellow.png.index.html
// // // converted for FastLED with gammas (2.6, 2.2, 2.5)
// // // Size: 20 bytes of program space.

// // DEFINE_GRADIENT_PALETTE( Blue_Cyan_Yellow_gp ) {
// //     0,   0,  0,255,
// //    63,   0, 55,255,
// //   127,   0,255,255,
// //   191,  42,255, 45,
// //   255, 255,255,  0};


// // //Custom palette by Aircoookie

// // DEFINE_GRADIENT_PALETTE( Orange_Teal_gp ) {
// //     0,   0,150, 92,
// //    55,   0,150, 92,
// //   200, 255, 72,  0,
// //   255, 255, 72,  0};

// // //Custom palette by Aircoookie

// // DEFINE_GRADIENT_PALETTE( Tiamat_gp ) {
// //     0,   1,  2, 14, //gc
// //    33,   2,  5, 35, //gc from 47, 61,126
// //   100,  13,135, 92, //gc from 88,242,247
// //   120,  43,255,193, //gc from 135,255,253
// //   140, 247,  7,249, //gc from 252, 69,253
// //   160, 193, 17,208, //gc from 231, 96,237
// //   180,  39,255,154, //gc from 130, 77,213
// //   200,   4,213,236, //gc from 57,122,248
// //   220,  39,252,135, //gc from 177,254,255
// //   240, 193,213,253, //gc from 203,239,253
// //   255, 255,249,255};
  
// // //Custom palette by Aircoookie

// // DEFINE_GRADIENT_PALETTE( April_Night_gp ) {
// //     0,   1,  5, 45, //deep blue
// //    10,   1,  5, 45,
// //    25,   5,169,175, //light blue
// //    40,   1,  5, 45,
// //    61,   1,  5, 45,
// //    76,  45,175, 31, //green
// //    91,   1,  5, 45,
// //   112,   1,  5, 45,
// //   127, 249,150,  5, //yellow
// //   143,   1,  5, 45,
// //   162,   1,  5, 45,
// //   178, 255, 92,  0, //pastel orange
// //   193,   1,  5, 45,
// //   214,   1,  5, 45,
// //   229, 223, 45, 72, //pink
// //   244,   1,  5, 45,
// //   255,   1,  5, 45};

// // DEFINE_GRADIENT_PALETTE( Orangery_gp ) {
// //     0, 255, 95, 23,
// //    30, 255, 82,  0,
// //    60, 223, 13,  8,
// //    90, 144, 44,  2,
// //   120, 255,110, 17,
// //   150, 255, 69,  0,
// //   180, 158, 13, 11,
// //   210, 241, 82, 17,
// //   255, 213, 37,  4};

// // //inspired by Mark Kriegsman https://gist.github.com/kriegsman/756ea6dcae8e30845b5a
// // DEFINE_GRADIENT_PALETTE( C9_gp ) {
// //     0, 184,  4,  0, //red
// //    60, 184,  4,  0,
// //    65, 144, 44,  2, //amber
// //   125, 144, 44,  2,
// //   130,   4, 96,  2, //green
// //   190,   4, 96,  2,
// //   195,   7,  7, 88, //blue
// //   255,   7,  7, 88};

// // DEFINE_GRADIENT_PALETTE( Sakura_gp ) {
// //     0, 196, 19, 10,
// //    65, 255, 69, 45,
// //   130, 223, 45, 72,
// //   195, 255, 82,103,
// //   255, 223, 13, 17};

// // DEFINE_GRADIENT_PALETTE( Aurora_gp ) {
// //     0,   1,  5, 45, //deep blue
// //    64,   0,200, 23,
// //   128,   0,255,  0, //green
// //   170,   0,243, 45,
// //   200,   0,135,  7,
// //   255,   1,  5, 45};//deep blue
  

// // // Single array of defined cpt-city color palettes.
// // // This will let us programmatically choose one based on
// // // a number, rather than having to activate each explicitly
// // // by name every time.
// // // Since it is const, this array could also be moved
// // // into PROGMEM to save SRAM, but for simplicity of illustration
// // // we'll keep it in a regular SRAM array.
// // //
// // // This list of color palettes acts as a "playlist"; you can
// // // add or delete, or re-arrange as you wish.
// // const TProgmemRGBGradientPalettePtr gGradientPalettes[] = {
// //   Sunset_Real_gp,               //13-00 Sunset
// //   es_rivendell_15_gp,           //14-01 Rivendell
// //   es_ocean_breeze_036_gp,       //15-02 Breeze
// //   rgi_15_gp,                    //16-03 Red & Blue
// //   retro2_16_gp,                 //17-04 Yellowout
// //   Analogous_1_gp,               //18-05 Analogous
// //   es_pinksplash_08_gp,          //19-06 Splash
// //   Sunset_Yellow_gp,             //20-07 Pastel
// //   Another_Sunset_gp,            //21-08 Sunset2
// //   Beech_gp,                     //22-09 Beech
// //   es_vintage_01_gp,             //23-10 Vintage
// //   departure_gp,                 //24-11 Departure
// //   es_landscape_64_gp,           //25-12 Landscape
// //   es_landscape_33_gp,           //26-13 Beach
// //   rainbowsherbet_gp,            //27-14 Sherbet
// //   gr65_hult_gp,                 //28-15 Hult
// //   gr64_hult_gp,                 //29-16 Hult64
// //   GMT_drywet_gp,                //30-17 Drywet
// //   ib_jul01_gp,                  //31-18 Jul
// //   es_vintage_57_gp,             //32-19 Grintage
// //   ib15_gp,                      //33-20 Rewhi
// //   Tertiary_01_gp,               //34-21 Tertiary
// //   lava_gp,                      //35-22 Fire
// //   fierce_ice_gp,                //36-23 Icefire
// //   Colorfull_gp,                 //37-24 Cyane
// //   Pink_Purple_gp,               //38-25 Light Pink
// //   es_autumn_19_gp,              //39-26 Autumn
// //   BlacK_Blue_Magenta_White_gp,  //40-27 Magenta
// //   BlacK_Magenta_Red_gp,         //41-28 Magred
// //   BlacK_Red_Magenta_Yellow_gp,  //42-29 Yelmag
// //   Blue_Cyan_Yellow_gp,          //43-30 Yelblu
// //   Orange_Teal_gp,               //44-31 Orange & Teal
// //   Tiamat_gp,                    //45-32 Tiamat
// //   April_Night_gp,               //46-33 April Night
// //   Orangery_gp,                  //47-34 Orangery
// //   C9_gp,                        //48-35 C9
// //   Sakura_gp,                    //49-36 Sakura
// //   Aurora_gp,                    //50-37 Aurora
// // };


// // // Count of how many cpt-city gradients are defined:
// // const uint8_t gGradientPaletteCount =
// //   sizeof( gGradientPalettes) / sizeof( TProgmemRGBGradientPalettePtr );

// #define PROGMEM_HUE_RED_BYTES 0x00, 0x00, 0x00, 0x00,


// #define PROGMEM_SAT_100_BYTES 0x00, 0x00, 0x80, 0x3F,
// #define PROGMEM_SAT_095_BYTES 0x33, 0x33, 0x73, 0x3F,
// #define PROGMEM_SAT_090_BYTES 0x66, 0x66, 0x66, 0x3F,
// #define PROGMEM_SAT_080_BYTES 0xCD, 0xCC, 0x4C, 0x3F,
// #define PROGMEM_SAT_070_BYTES 0x33, 0x33, 0x33, 0x3F,
// #define PROGMEM_SAT_060_BYTES 0x9A, 0x99, 0x19, 0x3F,
// #define PROGMEM_SAT_050_BYTES 0x00, 0x00, 0x00, 0x3F,
// #define PROGMEM_SAT_040_BYTES 0xCD, 0xCC, 0xCC, 0x3E,
// #define PROGMEM_SAT_030_BYTES 0x9A, 0x99, 0x99, 0x3E,
// #define PROGMEM_SAT_020_BYTES 0xCD, 0xCC, 0x4C, 0x3E,
// #define PROGMEM_SAT_010_BYTES 0xCD, 0xCC, 0xCC, 0x3D,
// #define PROGMEM_SAT_000_BYTES 0x00, 0x00, 0x00, 0x00,

// #define PROGMEM_BRT_100_BYTES 0x00, 0x00, 0x80, 0x3F,
// #define PROGMEM_BRT_000_BYTES 0x00, 0x00, 0x00, 0x00,


// const uint8_t COLOUR_MAP_BYTE_ARRAY[] PROGMEM = {
                                                             
// PROGMEM_HUE_RED_BYTES PROGMEM_SAT_000_BYTES PROGMEM_BRT_000_BYTES  // COLOUR_MAP_NONE_ID

// // Red                                                                                                                               
// PROGMEM_HUE_RED_BYTES PROGMEM_SAT_100_BYTES PROGMEM_BRT_100_BYTES
// PROGMEM_HUE_RED_BYTES PROGMEM_SAT_095_BYTES PROGMEM_BRT_100_BYTES
// PROGMEM_HUE_RED_BYTES PROGMEM_SAT_090_BYTES PROGMEM_BRT_100_BYTES
// PROGMEM_HUE_RED_BYTES PROGMEM_SAT_080_BYTES PROGMEM_BRT_100_BYTES
// PROGMEM_HUE_RED_BYTES PROGMEM_SAT_070_BYTES PROGMEM_BRT_100_BYTES
// PROGMEM_HUE_RED_BYTES PROGMEM_SAT_060_BYTES PROGMEM_BRT_100_BYTES
// PROGMEM_HUE_RED_BYTES PROGMEM_SAT_050_BYTES PROGMEM_BRT_100_BYTES
// PROGMEM_HUE_RED_BYTES PROGMEM_SAT_040_BYTES PROGMEM_BRT_100_BYTES
// PROGMEM_HUE_RED_BYTES PROGMEM_SAT_030_BYTES PROGMEM_BRT_100_BYTES
// PROGMEM_HUE_RED_BYTES PROGMEM_SAT_020_BYTES PROGMEM_BRT_100_BYTES
// PROGMEM_HUE_RED_BYTES PROGMEM_SAT_010_BYTES PROGMEM_BRT_100_BYTES
// PROGMEM_HUE_RED_BYTES PROGMEM_SAT_000_BYTES PROGMEM_BRT_100_BYTES
// // Orange                                          
// 0xF5, 0x49, 0x1F, 0x3D, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xF5, 0x49, 0x1F, 0x3D, 0x66, 0x66, 0x66, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xF5, 0x49, 0x1F, 0x3D, 0xCD, 0xCC, 0x4C, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xF5, 0x49, 0x1F, 0x3D, 0x33, 0x33, 0x33, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xF5, 0x49, 0x1F, 0x3D, 0x9A, 0x99, 0x19, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xF5, 0x49, 0x1F, 0x3D, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xF5, 0x49, 0x1F, 0x3D, 0xCD, 0xCC, 0xCC, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xF5, 0x49, 0x1F, 0x3D, 0x9A, 0x99, 0x99, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xF5, 0x49, 0x1F, 0x3D, 0xCD, 0xCC, 0x4C, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xF5, 0x49, 0x1F, 0x3D, 0xCD, 0xCC, 0xCC, 0x3D, 0x00, 0x00, 0x80, 0x3F,
// 0xF5, 0x49, 0x1F, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F,


                                          
// 0x39, 0x8E, 0x63, 0x3D, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x39
// , 0x8E, 0x63, 0x3D, 0x66, 0x66, 0x66, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x39, 0x8E, 0x63, 0x3D, 0xCD, 0xCC, 0x4C, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x39, 0x8E, 
// 0x63, 0x3D, 0x33, 0x33, 0x33, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x39, 0x8E, 0x63
// , 0x3D, 0x9A, 0x99, 0x19, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x39, 0x8E, 0x63, 0x3D, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x39, 0x8E, 0x63, 0x3D, 
// 0xCD, 0xCC, 0xCC, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x39, 0x8E, 0x63, 0x3D, 0x9A
// , 0x99, 0x99, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x39, 0x8E, 0x63, 0x3D, 0xCD, 0xCC, 0x4C, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x39, 0x8E, 0x63, 0x3D, 0xCD, 0xCC, 
// 0xCC, 0x3D, 0x00, 0x00, 0x80, 0x3F,
// 0x39, 0x8E, 0x63, 0x3D, 0x00, 0x00, 0x00
// , 0x00, 0x00, 0x00, 0x80, 0x3F,


                                          
// 0xAB, 0xAA, 0xAA, 0x3D, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB
// , 0xAA, 0xAA, 0x3D, 0x66, 0x66, 0x66, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0xAA, 0x3D, 0xCD, 0xCC, 0x4C, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 
// 0xAA, 0x3D, 0x33, 0x33, 0x33, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0xAA
// , 0x3D, 0x9A, 0x99, 0x19, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0xAA, 0x3D, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0xAA, 0x3D, 
// 0xCD, 0xCC, 0xCC, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0xAA, 0x3D, 0x9A
// , 0x99, 0x99, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0xAA, 0x3D, 0xCD, 0xCC, 0x4C, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0xAA, 0x3D, 0xCD, 0xCC, 
// 0xCC, 0x3D, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0xAA, 0x3D, 0x00, 0x00, 0x00
// , 0x00, 0x00, 0x00, 0x80, 0x3F,


                                          
// 0xE4, 0x38, 0x0E, 0x3E, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xE4
// , 0x38, 0x0E, 0x3E, 0x66, 0x66, 0x66, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 0x0E, 0x3E, 0xCD, 0xCC, 0x4C, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 
// 0x0E, 0x3E, 0x33, 0x33, 0x33, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 0x0E
// , 0x3E, 0x9A, 0x99, 0x19, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 0x0E, 0x3E, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 0x0E, 0x3E, 
// 0xCD, 0xCC, 0xCC, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 0x0E, 0x3E, 0x9A
// , 0x99, 0x99, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 0x0E, 0x3E, 0xCD, 0xCC, 0x4C, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 0x0E, 0x3E, 0xCD, 0xCC, 
// 0xCC, 0x3D, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 0x0E, 0x3E, 0x00, 0x00, 0x00
// , 0x00, 0x00, 0x00, 0x80, 0x3F,

                                           
// 0xE4, 0x38, 0x8E, 0x3E, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xE4
// , 0x38, 0x8E, 0x3E, 0x66, 0x66, 0x66, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 0x8E, 0x3E, 0xCD, 0xCC, 0x4C, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 
// 0x8E, 0x3E, 0x33, 0x33, 0x33, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 0x8E
// , 0x3E, 0x9A, 0x99, 0x19, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 0x8E, 0x3E, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 0x8E, 0x3E, 
// 0xCD, 0xCC, 0xCC, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 0x8E, 0x3E, 0x9A
// , 0x99, 0x99, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 0x8E, 0x3E, 0xCD, 0xCC, 0x4C, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 0x8E, 0x3E, 0xCD, 0xCC, 
// 0xCC, 0x3D, 0x00, 0x00, 0x80, 0x3F,
// 0xE4, 0x38, 0x8E, 0x3E, 0x00, 0x00, 0x00
// , 0x00, 0x00, 0x00, 0x80, 0x3F,

                                           
// 0xAB, 0xAA, 0xAA, 0x3E, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB
// , 0xAA, 0xAA, 0x3E, 0x66, 0x66, 0x66, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0xAA, 0x3E, 0xCD, 0xCC, 0x4C, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 
// 0xAA, 0x3E, 0x33, 0x33, 0x33, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0xAA
// , 0x3E, 0x9A, 0x99, 0x19, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0xAA, 0x3E, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0xAA, 0x3E, 
// 0xCD, 0xCC, 0xCC, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0xAA, 0x3E, 0x9A
// , 0x99, 0x99, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0xAA, 0x3E, 0xCD, 0xCC, 0x4C, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0xAA, 0x3E, 0xCD, 0xCC, 
// 0xCC, 0x3D, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0xAA, 0x3E, 0x00, 0x00, 0x00
// , 0x00, 0x00, 0x00, 0x80, 0x3F,

                                           
// 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x00
// , 0x00, 0x00, 0x3F, 0x66, 0x66, 0x66, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x00, 0x00, 0x00, 0x3F, 0xCD, 0xCC, 0x4C, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x00, 0x00, 
// 0x00, 0x3F, 0x33, 0x33, 0x33, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x00, 0x00, 0x00
// , 0x3F, 0x9A, 0x99, 0x19, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x00, 0x00, 0x00, 0x3F, 
// 0xCD, 0xCC, 0xCC, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x00, 0x00, 0x00, 0x3F, 0x9A
// , 0x99, 0x99, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x00, 0x00, 0x00, 0x3F, 0xCD, 0xCC, 0x4C, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x00, 0x00, 0x00, 0x3F, 0xCD, 0xCC, 
// 0xCC, 0x3D, 0x00, 0x00, 0x80, 0x3F,
// 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00
// , 0x00, 0x00, 0x00, 0x80, 0x3F,

                                           
// 0xAB, 0xAA, 0x2A, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB
// , 0xAA, 0x2A, 0x3F, 0x66, 0x66, 0x66, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0x2A, 0x3F, 0xCD, 0xCC, 0x4C, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 
// 0x2A, 0x3F, 0x33, 0x33, 0x33, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0x2A
// , 0x3F, 0x9A, 0x99, 0x19, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0x2A, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0x2A, 0x3F, 
// 0xCD, 0xCC, 0xCC, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0x2A, 0x3F, 0x9A
// , 0x99, 0x99, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0x2A, 0x3F, 0xCD, 0xCC, 0x4C, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0x2A, 0x3F, 0xCD, 0xCC, 
// 0xCC, 0x3D, 0x00, 0x00, 0x80, 0x3F,
// 0xAB, 0xAA, 0x2A, 0x3F, 0x00, 0x00, 0x00
// , 0x00, 0x00, 0x00, 0x80, 0x3F,

                                           
// 0x72, 0x1C, 0x47, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x72
// , 0x1C, 0x47, 0x3F, 0x66, 0x66, 0x66, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x72, 0x1C, 0x47, 0x3F, 0xCD, 0xCC, 0x4C, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x72, 0x1C, 
// 0x47, 0x3F, 0x33, 0x33, 0x33, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x72, 0x1C, 0x47
// , 0x3F, 0x9A, 0x99, 0x19, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x72, 0x1C, 0x47, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x72, 0x1C, 0x47, 0x3F, 
// 0xCD, 0xCC, 0xCC, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x72, 0x1C, 0x47, 0x3F, 0x9A
// , 0x99, 0x99, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x72, 0x1C, 0x47, 0x3F, 0xCD, 0xCC, 0x4C, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x72, 0x1C, 0x47, 0x3F, 0xCD, 0xCC, 
// 0xCC, 0x3D, 0x00, 0x00, 0x80, 0x3F,
// 0x72, 0x1C, 0x47, 0x3F, 0x00, 0x00, 0x00
// , 0x00, 0x00, 0x00, 0x80, 0x3F,

                                           
// 0x55, 0x55, 0x55, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x55
// , 0x55, 0x55, 0x3F, 0x66, 0x66, 0x66, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x55, 0x55, 0x55, 0x3F, 0xCD, 0xCC, 0x4C, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x55, 0x55, 
// 0x55, 0x3F, 0x33, 0x33, 0x33, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x55, 0x55, 0x55
// , 0x3F, 0x9A, 0x99, 0x19, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x55, 0x55, 0x55, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x55, 0x55, 0x55, 0x3F, 
// 0xCD, 0xCC, 0xCC, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x55, 0x55, 0x55, 0x3F, 0x9A
// , 0x99, 0x99, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x55, 0x55, 0x55, 0x3F, 0xCD, 0xCC, 0x4C, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x55, 0x55, 0x55, 0x3F, 0xCD, 0xCC, 
// 0xCC, 0x3D, 0x00, 0x00, 0x80, 0x3F,
// 0x55, 0x55, 0x55, 0x3F, 0x00, 0x00, 0x00
// , 0x00, 0x00, 0x00, 0x80, 0x3F,

                                           
// 0x1C, 0xC7, 0x71, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x1C
// , 0xC7, 0x71, 0x3F, 0x66, 0x66, 0x66, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x1C, 0xC7, 0x71, 0x3F, 0xCD, 0xCC, 0x4C, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x1C, 0xC7, 
// 0x71, 0x3F, 0x33, 0x33, 0x33, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x1C, 0xC7, 0x71
// , 0x3F, 0x9A, 0x99, 0x19, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x1C, 0xC7, 0x71, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x1C, 0xC7, 0x71, 0x3F, 
// 0xCD, 0xCC, 0xCC, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x1C, 0xC7, 0x71, 0x3F, 0x9A
// , 0x99, 0x99, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x1C, 0xC7, 0x71, 0x3F, 0xCD, 0xCC, 0x4C, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x1C, 0xC7, 0x71, 0x3F, 0xCD, 0xCC, 
// 0xCC, 0x3D, 0x00, 0x00, 0x80, 0x3F,
// 0x1C, 0xC7, 0x71, 0x3F, 0x00, 0x00, 0x00
// , 0x00, 0x00, 0x00, 0x80, 0x3F,

                                           
// 0x8E, 0xE3, 0x78, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x8E
// , 0xE3, 0x78, 0x3F, 0x66, 0x66, 0x66, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x8E, 0xE3, 0x78, 0x3F, 0xCD, 0xCC, 0x4C, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x8E, 0xE3, 
// 0x78, 0x3F, 0x33, 0x33, 0x33, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x8E, 0xE3, 0x78
// , 0x3F, 0x9A, 0x99, 0x19, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x8E, 0xE3, 0x78, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F,
// 0x8E, 0xE3, 0x78, 0x3F, 
// 0xCD, 0xCC, 0xCC, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x8E, 0xE3, 0x78, 0x3F, 0x9A
// , 0x99, 0x99, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x8E, 0xE3, 0x78, 0x3F, 0xCD, 0xCC, 0x4C, 0x3E, 0x00, 0x00, 0x80, 0x3F,
// 0x8E, 0xE3, 0x78, 0x3F, 0xCD, 0xCC, 
// 0xCC, 0x3D, 0x00, 0x00, 0x80, 0x3F,
// 0x8E, 0xE3, 0x78, 0x3F, 0x00, 0x00, 0x00
// , 0x00, 0x00, 0x00, 0x80, 0x3F

// };
      




#endif
