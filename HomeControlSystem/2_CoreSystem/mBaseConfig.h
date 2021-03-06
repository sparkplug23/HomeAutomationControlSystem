/**
  @brief mBaseConfig.h - minimum defines required for default builds
  @note Users "may" edit this file, but it is instead recommended to redefine them in "mUserConfig_Secret.h"

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
**/
#ifndef MUSERCONFIG_DEFAULTS_H
#define MUSERCONFIG_DEFAULTS_H

#include "stdint.h"
#include "2_CoreSystem/mSystemConfig.h"
#include "0_ConfigUser/mFirmwareCustom_Secret.h"
#include "0_ConfigUser/mFirmwareCustom_Secret_DevLogging.h"

/*********************************************************************************************\
 * This file is one of two user configurable files
 * 
 * ATTENTION: Changes to this file WILL be erased with each git pull
 * 
 * "mUserConfig.h" lists all the parameters that users can set as default state when the device is reset.
 * To assert these settings after the initial flash, the SETTINGS_HOLDER should be changed to another number (1-65000)
 * Subsequent flashing will NOT erase these settings IF SETTINGS_HOLDER is not changed.
 * hh
 * Although the user can edit these values directly, it is advised to edit the "mUserConfig_Override.h" file instead, which is
 * called AFTER this file, and will overwrite any settings performed here if they are defined. 
 * 
 * All parameters contained within here can be edited by the user during runtime using mqtt or webui commands, and are stored in memory.
 * 
 * IMPORTANT: If you are not confident in changing values, please leave these as default and configure through the webui or mqtt commands, 
 * these values are intended for advanced users to create defaults for flashing multiple devices for easier configuring.
\*********************************************************************************************/

#define USE_CONFIG_OVERRIDE                      // Uncomment to use mUserConfig_Override.h file. See README.md

/*********************************************************************************************\
 * This MUST BE CHANGED for ANY parameters in this file to overwrite those saved in settings
\*********************************************************************************************/
#ifndef SETTINGS_HOLDER
#define SETTINGS_HOLDER             1              // [Reset 1] Change this value (max 32000) to load SECTION1 configuration parameters to flash
#endif

#define SERIALD Serial //serial debug
#ifndef SERIAL_DEBUG_BAUD_DEFAULT
#define SERIAL_DEBUG_BAUD_DEFAULT 115200
#endif // SERIAL_DEBUG_BAUD_DEFAULT

/*********************************************************************************************\
 * CAUTION! Only select from values defined in the comments next to (right hand side) the parameter. 
 * Some protection is added on value ranges, but it is not guarenteed especially during the development phase.
 * 
 * The names of parameters are suffixed by a shorthand for the type of value it MUST be adhered to:
 * "_CTR"     String (word or phrase) eg. "ON" or "This Value"
 * "_NUM"     Number that is an integer only (no decimel points!) eg 1 or 1023
 * "_FLT"     Float number, which is any number that MAY include a decimel, but does not need to. eg. 1 or 1.0 or 1.234
 * "_ID"      Same as "_NUM"
\*********************************************************************************************/

/*********************************************************************************************\
 *  Module Settings
\*********************************************************************************************/
#define MODULE                        MODULE_WEMOS_ID      // [Module] Select default model from mHardwareTemplates.h

#define SAVE_DATA                     1                 // [SaveData] Save changed parameters to Flash (0 = disable, 1 - 3600 seconds)
#define SAVE_STATE                    1                 // [SetOption0] Save changed power state to Flash (0 = disable, 1 = enable)
#define BOOT_LOOP_OFFSET              1                 // [SetOption36] Number of boot loops before starting restoring defaults (0 = disable, 1..200 = boot loops offset)

/*********************************************************************************************\
 *  Wifi
\*********************************************************************************************/
#define WIFI_IP_ADDRESS               "0.0.0.0"         // [IpAddress1] Set to 0.0.0.0 for using DHCP or enter a static IP address
#define WIFI_GATEWAY                  "192.168.1.1"     // [IpAddress2] If not using DHCP set Gateway IP address
#define WIFI_SUBNETMASK               "255.255.255.0"   // [IpAddress3] If not using DHCP set Network mask
#define WIFI_DNS                      "192.168.1.1"     // [IpAddress4] If not using DHCP set DNS IP address (might be equal to WIFI_GATEWAY)

#define STA_SSID1                     ""                // [Ssid1] Wifi SSID
#define STA_PASS1                     ""                // [Password1] Wifi password
#define STA_SSID2                     ""                // [Ssid2] Optional alternate AP Wifi SSID
#define STA_PASS2                     ""                // [Password2] Optional alternate AP Wifi password
#define STA_SSID3                     ""                // [Ssid2] Optional alternate AP Wifi SSID
#define STA_PASS3                     ""                // [Password2] Optional alternate AP Wifi password

#define WIFI_CONFIG_TOOL              WIFI_RETRY        // [WifiConfig] Default tool if wifi fails to connect
                                                        //   (WIFI_RESTART, WIFI_SMARTCONFIG, WIFI_MANAGER, WIFI_WPSCONFIG, WIFI_RETRY, WIFI_WAIT, WIFI_SERIAL)
#define WIFI_CONFIG_NO_SSID           WIFI_WPSCONFIG    // Default tool if wifi fails to connect and no SSID is configured
                                                        //   (WIFI_SMARTCONFIG, WIFI_MANAGER, WIFI_WPSCONFIG, WIFI_SERIAL)
                                                        //   *** NOTE: When WPS is disabled by USE_WPS below, WIFI_WPSCONFIG will execute WIFI_MANAGER ***
                                                        //   *** NOTE: When WIFI_MANAGER is disabled by USE_MODULE_CORE_WEBSERVER below, WIFI_MANAGER will execute WIFI_SMARTCONFIG ***
                                                        //   *** NOTE: When WIFI_SMARTCONFIG is disabled by USE_SMARTCONFIG below, WIFI_SMARTCONFIG will execute WIFI_SERIAL ***

/*********************************************************************************************\
 *  Logging
\*********************************************************************************************/
#define SYS_LOG_HOST                  ""                      // [LogHost] (Linux) syslog host
#define SYS_LOG_PORT                  514                     // [LogPort] default syslog UDP port
#define SYS_LOG_LEVEL                 LOG_LEVEL_DEBUG_MORE    // [SysLog] (LOG_LEVEL_NONE, LOG_LEVEL_ERROR, LOG_LEVEL_INFO, LOG_LEVEL_DEBUG, LOG_LEVEL_DEBUG_MORE)
#define SERIAL_LOG_LEVEL              LOG_LEVEL_DEBUG         // [SerialLog] (LOG_LEVEL_NONE, LOG_LEVEL_ERROR, LOG_LEVEL_INFO, LOG_LEVEL_DEBUG, LOG_LEVEL_DEBUG_MORE)
#define SERIAL_LOG_LEVEL_DURING_BOOT  LOG_LEVEL_DEBUG         // [SerialLogBoot] LOG_LEVEL_TEST//LOG_LEVEL_ALL
#define WEB_LOG_LEVEL                 LOG_LEVEL_INFO          // [WebLog] (LOG_LEVEL_NONE, LOG_LEVEL_ERROR, LOG_LEVEL_INFO, LOG_LEVEL_DEBUG, LOG_LEVEL_DEBUG_MORE)
#define TELNET_LOG_LEVEL              LOG_LEVEL_DEBUG
#define LOGTIME_DEFAULT_FORMAT        1                       //  true == short

/*********************************************************************************************\
 *  OTA
\*********************************************************************************************/
#define OTA_URL                       "http://minimal.bin"  // [OtaUrl]

/*********************************************************************************************\
 *  MQTT
\*********************************************************************************************/

// #ifndef DISABLE_NETWORK
// #define USE_MODULE_NETWORK_MQTT
// #define USE_MQTT
// #endif // DISABLE_NETWORK

#define MQTT_HOST                     "192.168.1.65"    // [MqttHost] Defined as either "X.X.X.X" for IP, or "NAME" for MDNS. 
#define D_MQTTSERVER_IP_ADDRESS_COMMA_DELIMITED       192,168,1,65   //TEMPORARY FIX, WILL BE REPLACED BY ABOVE PARSED STRING
#define MQTT_HOST_DISCOVERY
#ifdef USE_NETWORK_MDNS
#define MDNS_MQTT_HOSTNAME1   "TOWER.local" 
#define MDNS_MQTT_HOSTNAME2   "rasbpi.local" 
#endif // #ifdef USE_NETWORK_MDNS

#define MQTT_FINGERPRINT1             "A5 02 FF 13 99 9F 8B 39 8E F1 83 4F 11 23 65 0B 32 36 FC 07"  // [MqttFingerprint1]
#define MQTT_FINGERPRINT2             "A5 02 FF 13 99 9F 8B 39 8E F1 83 4F 11 23 65 0B 32 36 FC 07"  // [MqttFingerprint2]
#define MQTT_PORT                     1884              // [MqttPort] MQTT port (10123 on CloudMQTT)
#define MQTT_USER                     "DVES_USER"       // [MqttUser] MQTT user
#define MQTT_PASS                     "DVES_PASS"       // [MqttPassword] MQTT password
#define MQTT_MAX_PACKET_SIZE          2000

#define ENABLE_MQTT_DEBUG_TELEMETRY
#define USE_MQTT_RETAINED_VERSION_HISTORY_CHECK
#define ENABLE_MQTT_SEND_DISCONNECT_ON_RECONNECT

#define D_MQTT_COMMAND                "set"
#define D_MQTT_SYNC                   "sync"


// -- MQTT - TLS ----------------------------------
  // !!! TLS uses a LOT OF MEMORY so be careful to enable other options at the same time !!!
//#define USE_MQTT_TLS                             // Use TLS for MQTT connection (+53k code, +15k mem)
//  #define USE_MQTT_TLS_CA_CERT                   // Use LetsEncrypt Certificate from sonoff_letsencrypt.h - Not supported with core 2.3.0

// -- MQTT - Telemetry ----------------------------
#define TELE_PERIOD            300               // [TelePeriod] Telemetry (0 = disable, 10 - 3600 seconds)
#define TELE_ON_POWER          0                 // [SetOption59] send tele/STATE together with stat/RESULT (0 = Disable, 1 = Enable)

/*********************************************************************************************\
 *  HTTP Webserver
\*********************************************************************************************/
#define WEB_SERVER             2                 // [WebServer] Web server (0 = Off, 1 = Start as User, 2 = Start as Admin)
#define WEB_PASSWORD           ""                // [WebPassword] Web server Admin mode Password for WEB_USERNAME (empty string = Disable)
#define FRIENDLY_NAME          DEVICENAME_FRIENDLY_CTR   // [FriendlyName] Friendlyname up to 32 characters used by webpages and Alexa
// HTML hex color codes. Only 3 and 6 digit hex string values are supported!! See https://www.w3schools.com/colors/colors_hex.asp
#define COLOR_TEXT                  "#fff"       // [WebColor1] Global text color - Black
#define COLOR_BACKGROUND            "#000"       // [WebColor2] Global background color - White
#define COLOR_FORM                  "#000000"    // [WebColor3] Form background color - Greyish
#define COLOR_INPUT_TEXT            "#fff"       // [WebColor4] Input text color - Black
#define COLOR_INPUT                 "#000"       // [WebColor5] Input background color - White
#define COLOR_CONSOLE_TEXT          "#fff"       // [WebColor6] Console text color - Black
#define COLOR_CONSOLE               "#000"       // [WebColor7] Console background color - White
#define COLOR_TEXT_WARNING          "#f00"       // [WebColor8] Warning text color - Red
#define COLOR_TEXT_SUCCESS          "#008000"    // [WebColor9] Success text color - Green
#define COLOR_BUTTON_TEXT           "#000"       // [WebColor10] Button text color - White
#ifndef COLOR_BUTTON
  #define COLOR_BUTTON                "#ec7d1f"    // [WebColor11] Button color - Blueish
#endif
#ifndef COLOR_BUTTON_HOVER
  #define COLOR_BUTTON_HOVER          "#7a4111"    // [WebColor12] Button color when hovered over - Darker blueish
#endif
#define COLOR_BUTTON2                "#ec7d1f"    // [WebColor11] Button color - Orange-ish
#define COLOR_BUTTON2_HOVER          "#7a4111"    // [WebColor12] Button color when hovered over - Darker Orange-ish
#define COLOR_BUTTON_RESET          "#d43535"    // [WebColor13] Restart/Reset/Delete button color - Redish
#define COLOR_BUTTON_RESET_HOVER    "#931f1f"    // [WebColor14] Restart/Reset/Delete button color when hovered over - Darker redish
#define COLOR_BUTTON_SAVE           "#47c266"    // [WebColor15] Save button color - Greenish
#define COLOR_BUTTON_SAVE_HOVER     "#5aaf6f"    // [WebColor16] Save button color when hovered over - Darker greenish
#define COLOR_TIMER_TAB_TEXT        "#000"       // [WebColor17] Config timer tab text color - White
#define COLOR_TIMER_TAB_BACKGROUND  "#999"       // [WebColor18] Config timer tab background color - Light grey
#ifndef D_COL_TEXT_MODULE_TITLE_CTR
  #define D_COL_TEXT_MODULE_TITLE_CTR "#fff"
#endif

#define PWM_MAX_SLEEP          10                // Sleep will be lowered to this value when light is on, to avoid flickering


// -- Time - Up to three NTP servers in your region
#define NTP_SERVER1            "pool.ntp.org"       // [NtpServer1] Select first NTP server by name or IP address (129.250.35.250)
#define NTP_SERVER2            "nl.pool.ntp.org"    // [NtpServer2] Select second NTP server by name or IP address (5.39.184.5)
#define NTP_SERVER3            "0.nl.pool.ntp.org"  // [NtpServer3] Select third NTP server by name or IP address (93.94.224.67)

// -- Time - Start Daylight Saving Time and timezone offset from UTC in minutes
#define TIME_DST_HEMISPHERE    North             // [TimeDst] Hemisphere (0 or North, 1 or South)
#define TIME_DST_WEEK          Last              // Week of month (0 or Last, 1 or First, 2 or Second, 3 or Third, 4 or Fourth)
#define TIME_DST_DAY           Sun               // Day of week (1 or Sun, 2 or Mon, 3 or Tue, 4 or Wed, 5 or Thu, 6 or Fri, 7 or Sat)
#define TIME_DST_MONTH         Mar               // Month (1 or Jan, 2 or Feb, 3 or Mar, 4 or Apr, 5 or May, 6 or Jun, 7 or Jul, 8 or Aug, 9 or Sep, 10 or Oct, 11 or Nov, 12 or Dec)
#define TIME_DST_HOUR          2                 // Hour (0 to 23)
#define TIME_DST_OFFSET        +0              // Offset from UTC in minutes (-780 to +780)

// -- Time - Start Standard Time and timezone offset from UTC in minutes
#define TIME_STD_HEMISPHERE    North             // [TimeStd] Hemisphere (0 or North, 1 or South)
#define TIME_STD_WEEK          Last              // Week of month (0 or Last, 1 or First, 2 or Second, 3 or Third, 4 or Fourth)
#define TIME_STD_DAY           Sun               // Day of week (1 or Sun, 2 or Mon, 3 or Tue, 4 or Wed, 5 or Thu, 6 or Fri, 7 or Sat)
#define TIME_STD_MONTH         Oct               // Month (1 or Jan, 2 or Feb, 3 or Mar, 4 or Apr, 5 or May, 6 or Jun, 7 or Jul, 8 or Aug, 9 or Sep, 10 or Oct, 11 or Nov, 12 or Dec)
#define TIME_STD_HOUR          3                 // Hour (0 to 23)
#define TIME_STD_OFFSET        0                 // Offset from UTC in minutes (-780 to +780)

// -- Location ------------------------------------
#ifndef LATITUDE              // eg. Belfast, Northern Ireland
#define LATITUDE               54.6         // [Latitude] Your location to be used with sunrise and sunset
#define LONGITUDE              -5.92        // [Longitude] Your location to be used with sunrise and sunset
#endif


// -- Application ---------------------------------
#define APP_TIMEZONE           0                 // [Timezone] +1 hour (Amsterdam) (-13 .. 14 = hours from UTC, 99 = use TIME_DST/TIME_STD)
#define APP_LEDSTATE           LED_POWER         // [LedState] Function of led
                                                 //   (LED_OFF, LED_POWER, LED_MQTTSUB, LED_POWER_MQTTSUB, LED_MQTTPUB, LED_POWER_MQTTPUB, LED_MQTT, LED_POWER_MQTT)
#define APP_LEDMASK            0xFFFF            // [LedMask] Assign Relay to Power led (0xFFFF is default)
#define APP_PULSETIME          0                 // [PulseTime] Time in 0.1 Sec to turn off power for relay 1 (0 = disabled)
#define APP_POWERON_STATE      POWER_ALL_SAVED   // [PowerOnState] Power On Relay state
                                                 //   (POWER_ALL_OFF, POWER_ALL_ON, POWER_ALL_SAVED_TOGGLE, POWER_ALL_SAVED, POWER_ALL_ALWAYS_ON, POWER_ALL_OFF_PULSETIME_ON)
#define APP_BLINKTIME          10                // [BlinkTime] Time in 0.1 Sec to blink/toggle power for relay 1
#define APP_BLINKCOUNT         10                // [BlinkCount] Number of blinks (0 = 32000)
#define DEFAULT_LOOP_SLEEP     20                // [Sleep] Sleep time to lower energy consumption (0 = Off, 1 - 250 mSec)

#define KEY_CHECK_TIME         1000
#define KEY_DEBOUNCE_TIME      50                // [ButtonDebounce] Number of mSeconds button press debounce time
#define KEY_HOLD_TIME          40                // [SetOption32] Number of 0.1 seconds to hold Button or external Pushbutton before sending HOLD message
#define SWITCH_DEBOUNCE_TIME   50                // [SwitchDebounce] Number of mSeconds switch press debounce time
#define SWITCH_MODE            TOGGLE            // [SwitchMode] TOGGLE, FOLLOW, FOLLOW_INV, PUSHBUTTON, PUSHBUTTON_INV, PUSHBUTTONHOLD, PUSHBUTTONHOLD_INV, PUSHBUTTON_TOGGLE (the wall switch state)
#define WS2812_LEDS            20                // [Pixels] Number of WS2812 ledout.index to start with (max is 512)

#define TEMP_CONVERSION        0                 // [SetOption8] Return temperature in (0 = Celsius or 1 = Fahrenheit)
#define PRESSURE_CONVERSION    0                 // [SetOption24] Return pressure in (0 = hPa or 1 = mmHg)
#define TEMP_RESOLUTION        1                 // [TempRes] Maximum number of decimals (0 - 3) showing sensor Temperature
#define HUMIDITY_RESOLUTION    1                 // [HumRes] Maximum number of decimals (0 - 3) showing sensor Humidity
#define PRESSURE_RESOLUTION    1                 // [PressRes] Maximum number of decimals (0 - 3) showing sensor Pressure
#define ENERGY_RESOLUTION      3                 // [EnergyRes] Maximum number of decimals (0 - 5) showing energy usage in kWh
#define CALC_RESOLUTION        3                 // [CalcRes] Maximum number of decimals (0 - 7) used in commands ADD, SUB, MULT and SCALE


#define FLAG_ENABLE_DEFAULT_PERIODIC_SENSOR_MQTT_MESSAGES   false


/*********************************************************************************************\
 * END OF SECTION 1
 *
 * SECTION 2
 * - Enable a feature by removing both // in front of it
 * - Disable a feature by preceding it with //
\*********************************************************************************************/

// -- Wifi Config tools ---------------------------
#define WIFI_SOFT_AP_CHANNEL   1                 // Soft Access Point Channel number between 1 and 13 as used by Wifi Manager web GUI
//#define USE_WPS                                  // Add support for WPS as initial wifi configuration tool (+33k code, 1k mem (5k mem with core v2.4.2+))
//#define USE_SMARTCONFIG                          // Add support for Wifi SmartConfig as initial wifi configuration tool (+23k code, +0.6k mem)

// -- OTA -----------------------------------------
#define USE_ARDUINO_OTA                          // Add optional support for Arduino OTA (+13k code)

// -- HTTP ----------------------------------------
// #ifndef DISABLE_WEBSERVER
//   #define USE_MODULE_CORE_WEBSERVER                            // Enable web server and Wifi Manager (+66k code, +8k mem)
//   #define WEB_PORT             80                // Web server Port for User and Admin mode
//   #define WEB_USERNAME         "admin"           // Web server Admin mode user name
// #endif

// -- mDNS ----------------------------------------
#define USE_DISCOVERY                            // Enable mDNS for the following services (+8k code, +0.3k mem)
  //#define USE_NETWORK_MDNS                    // Provide access to webserver by name <Hostname>.local/
  #define MQTT_HOST_DISCOVERY                    // Find MQTT host server (overrides MQTT_HOST if found)
// -- mDNS ----------------------------------------
// #define USE_NETWORK_MDNS           1                 // [SetOption55] Use mDNS (0 = Disable, 1 = Enable)



// -- Time ----------------------------------------
#define USE_RTC
//#define USE_TIMERS                               // Add support for up to 16 timers (+2k2 code)
//  #define USE_TIMERS_WEB                         // Add timer webpage support (+4k5 code)
  #define USE_SUNRISE                            // Add support for Sunrise and sunset tools (+16k)
    #define SUNRISE_DAWN_ANGLE DAWN_NORMAL       // Select desired Dawn Angle from (DAWN_NORMAL, DAWN_CIVIL, DAWN_NAUTIC, DAWN_ASTRONOMIC)

// -- Rules ---------------------------------------
#define USE_ACTIONS                                // Add support for rules (+4k4 code)
//  #define USE_EXPRESSION                         // Add support for expression evaluation in rules (+3k2 code, +64 bytes mem)

// -- Internal Analog input -----------------------
#ifndef USE_MODULE_CUSTOM_BLINDS
  //#define USE_ADC_VCC                              // Display Vcc in Power status. Disable for use as Analog input on selected devices
#endif

// -- One wire sensors ----------------------------
                                                 // WARNING: Select none for default one DS18B20 sensor or enable one of the following two options for multiple sensors
//#define USE_DS18x20_LEGACY                       // Optional for more than one DS18x20 sensors with dynamic scan using library OneWire (+1k5 code)
#define USE_DS18x20                              // Optional for more than one DS18x20 sensors with id sort, single scan and read retry (+1k3 code)
//  #define W1_PARASITE_POWER                      // If using USE_DS18x20 then optimize for parasite powered sensors
//  #define DS18B20_INTERNAL_PULLUP                // Use INPUT_PULLUP internal pullup resistors for single DS18B20

// -- I2C sensors ---------------------------------
#define USE_I2C                                  // I2C using library wire (+10k code, 0k2 mem, 124 iram)
#define I2CDRIVERS_0_31        0xFFFFFFFF          // Enable I2CDriver0  to I2CDriver31
#define I2CDRIVERS_32_63       0xFFFFFFFF          // Enable I2CDriver32 to I2CDriver63
#define I2CDRIVERS_64_95       0xFFFFFFFF          // Enable I2CDriver64 to I2CDriver95

#ifdef USE_I2C
  #define USE_SHT                                // Enable SHT1X sensor (+1k4 code)
  #define USE_HTU                                // Enable HTU21/SI7013/SI7020/SI7021 sensor (I2C address 0x40) (+1k5 code)
  #define USE_BMP                                // Enable BMP085/BMP180/BMP280/BME280 sensors (I2C addresses 0x76 and 0x77) (+4k4 code)
//    #define USE_BME680                           // Enable support for BME680 sensor using Bosch BME680 library (+4k code)
  #define USE_BH1750                             // Enable BH1750 sensor (I2C address 0x23 or 0x5C) (+0k5 code)
//  #define USE_VEML6070                           // Enable VEML6070 sensor (I2C addresses 0x38 and 0x39) (+1k5 code)
    #define USE_VEML6070_RSET    270000          // VEML6070, Rset in Ohm used on PCB board, default 270K = 270000ohm, range for this sensor: 220K ... 1Meg
    #define USE_VEML6070_SHOW_RAW                // VEML6070, shows the raw value of UV-A
//  #define USE_ADS1115                            // Enable ADS1115 16 bit A/D converter (I2C address 0x48, 0x49, 0x4A or 0x4B) based on Adafruit ADS1x15 library (no library needed) (+0k7 code)
//  #define USE_ADS1115_I2CDEV                     // Enable ADS1115 16 bit A/D converter (I2C address 0x48, 0x49, 0x4A or 0x4B) using library i2cdevlib-Core and i2cdevlib-ADS1115 (+2k code)
//  #define USE_INA219                             // Enable INA219 (I2C address 0x40, 0x41 0x44 or 0x45) Low voltage and current sensor (+1k code)
  #define USE_SHT3X                              // Enable SHT3x (I2C address 0x44 or 0x45) or SHTC3 (I2C address 0x70) sensor (+0k7 code)
//  #define USE_TSL2561                            // Enable TSL2561 sensor (I2C address 0x29, 0x39 or 0x49) using library Joba_Tsl2561 (+2k3 code)
//  #define USE_MGS                                // Enable Xadow and Grove Mutichannel Gas sensor using library Multichannel_Gas_Sensor (+10k code)
    #define MGS_SENSOR_ADDR    0x04              // Default Mutichannel Gas sensor i2c address
  #define USE_SGP30                              // Enable SGP30 sensor (I2C address 0x58) (+1k1 code)
//  #define USE_SI1145                             // Enable SI1145/46/47 sensor (I2C address 0x60) (+1k code)
  #define USE_LM75AD                             // Enable LM75AD sensor (I2C addresses 0x48 - 0x4F) (+0k5 code)
//  #define USE_APDS9960                           // Enable APDS9960 Proximity Sensor (I2C address 0x39). Disables SHT and VEML6070 (+4k7 code)
//  #define USE_MCP230xx                           // Enable MCP23008/MCP23017 - Must define I2C Address in #define USE_MCP230xx_ADDR below - range 0x20 - 0x27 (+4k7 code)
//    #define USE_MCP230xx_ADDR 0x20               // Enable MCP23008/MCP23017 I2C Address to use (Must be within range 0x20 through 0x27 - set according to your wired setup)
//    #define USE_MCP230xx_OUTPUT                  // Enable MCP23008/MCP23017 OUTPUT support through sensor29 commands (+1k5 code)
//    #define USE_MCP230xx_DISPLAYOUTPUT           // Enable MCP23008/MCP23017 to display state of OUTPUT pins on Web UI (+0k2 code)
//  #define USE_PCA9685                            // Enable PCA9685 I2C HW PWM Driver - Must define I2C Address in #define USE_PCA9685_ADDR below - range 0x40 - 0x47 (+1k4 code)
//    #define USE_PCA9685_ADDR 0x40                // Enable PCA9685 I2C Address to use (Must be within range 0x40 through 0x47 - set according to your wired setup)
//    #define USE_PCA9685_FREQ 50                  // Define default PWM frequency in Hz to be used (must be within 24 to 1526) - If other value is used, it will rever to 50Hz
//  #define USE_MPR121                             // Enable MPR121 controller (I2C addresses 0x5A, 0x5B, 0x5C and 0x5D) in input mode for touch buttons (+1k3 code)
//  #define USE_CCS811                             // Enable CCS811 sensor (I2C address 0x5A) (+2k2 code)
//  #define USE_MPU6050                            // Enable MPU6050 sensor (I2C address 0x68 AD0 low or 0x69 AD0 high) (+3K3 of code and 188 Bytes of RAM)
//    #define USE_MPU6050_DMP                      // Enable in MPU6050 to use the DMP on the chip, should create better results (+8k6 of code)
//  #define USE_DS3231                             // Enable DS3231 external RTC in case no Wifi is avaliable. See docs in the source file (+1k2 code)
//    #define USE_RTC_ADDR  0x68                   // Default I2C address 0x68
//  #define USE_MGC3130                            // Enable MGC3130 Electric Field Effect Sensor (I2C address 0x42) (+2k7 code, 0k3 mem)
//  #define USE_MAX44009                           // Enable MAX44009 Ambient Light sensor (I2C addresses 0x4A and 0x4B) (+0k8 code)
//  #define USE_SCD30                              // Enable Sensiron SCd30 CO2 sensor (I2C address 0x61) (+3k3 code)
  #define USE_ADE7953                            // Enable ADE7953 Energy monitor as used on Shelly 2.5 (I2C address 0x38) (+1k5)
#endif  // USE_I2C

// -- SPI sensors ---------------------------------
//#define USE_SPI                                  // Hardware SPI using GPIO12(MISO), GPIO13(MOSI) and GPIO14(CLK) in addition to two user selectable GPIOs(CS and DC)

#ifdef USE_SPI
  #ifndef USE_DISPLAY
  #define USE_DISPLAY                            // Add SPI Display support for 320x240 and 480x320 TFT
  #endif
    #define USE_DISPLAY_ILI9341                  // [DisplayModel 4] Enable ILI9341 Tft 480x320 display (+19k code)
//    #define USE_DISPLAY_EPAPER_29                 // [DisplayModel 5] Enable e-paper 2.9 inch display (+19k code)
#endif  // USE_SPI

#define USE_PWM

// -- Serial sensors ------------------------------
#define USE_MHZ19                                // Add support for MH-Z19 CO2 sensor (+2k code)
#define USE_SENSEAIR                             // Add support for SenseAir K30, K70 and S8 CO2 sensor (+2k3 code)
  #define CO2_LOW              800               // Below this CO2 value show green light (needs PWM or WS2812 RG(B) led and enable with SetOption18 1)
  #define CO2_HIGH             1200              // Above this CO2 value show red light (needs PWM or WS2812 RG(B) led and enable with SetOption18 1)
#define USE_PMS5003                              // Add support for PMS5003 and PMS7003 particle concentration sensor (+1k3 code)
#define USE_NOVA_SDS                             // Add support for SDS011 and SDS021 particle concentration sensor (+0k7 code)
  #define WORKING_PERIOD       5                 // Working period of the SDS Sensor, Takes a reading every X Minutes
#define USE_SERIAL_BRIDGE                        // Add support for software Serial Bridge (+0k8 code)
//#define USE_SDM120                               // Add support for Eastron SDM120-Modbus energy meter (+1k7 code)
  #define SDM120_SPEED         9600              // SDM120-Modbus RS485 serial speed (default: 2400 baud)
  #define USE_SDM220                             // Add extra parameters for SDM220 (+0k1 code)
//#define USE_SDM630                               // Add support for Eastron SDM630-Modbus energy meter (+2k code)
  #define SDM630_SPEED         9600              // SDM630-Modbus RS485 serial speed (default: 9600 baud)
//#define USE_MP3_PLAYER                           // Use of the DFPlayer Mini MP3 Player RB-DFR-562 commands: play, volume and stop
  #define MP3_VOLUME           10                // Set the startup volume on init, the range can be 0..30(max)
#define USE_TUYA_DIMMER                          // Add support for Tuya Serial Dimmer
  #define TUYA_DIMMER_ID       0                 // Default dimmer Id
#define USE_ARMTRONIX_DIMMERS                    // Add support for Armtronix Dimmers (+1k4 code)
#define USE_PS_16_DZ                             // Add support for PS-16-DZ Dimmer
//#define ROTARY_V1                                // Add support for MI Desk Lamp
//#define USE_AZ7798                               // Add support for AZ-Instrument 7798 CO2 datalogger (+1k6 code)
//#define USE_PN532_HSU                            // Add support for PN532 using HSU (Serial) interface (+1k8 code, 140 bytes mem)
//  #define USE_PN532_CAUSE_EVENTS                 // Cause event execution for PN532_UID= and PN532_DATA=[if defined] (+ 30 bytes code)
//  #define USE_PN532_DATA_FUNCTION                // Add sensor40 command support for erase, setting data block content (+1k7 code, 388 bytes mem)
//  #define USE_PN532_DATA_RAW                     // Allow DATA block to be used by non-alpha-numberic data (+ 80 bytes code, 48 bytes ram)

// Power monitoring sensors -----------------------
// #define USE_PZEM004T                             // Add support for PZEM004T Energy monitor (+2k code)
// #define USE_PZEM_AC                              // Add support for PZEM014,016 Energy monitor (+1k1 code)
// #define USE_PZEM_DC                              // Add support for PZEM003,017 Energy monitor (+1k1 code)
// #define USE_MCP39F501                            // Add support for MCP39F501 Energy monitor as used in Shelly 2 (+3k1 code)

// -- Low level interface devices -----------------
//#define USE_MAX31855                             // Add support for MAX31855 K-Type thermocouple sensor using softSPI

// #define USE_IR_REMOTE                            // Send IR remote commands using library IRremoteESP8266 and ArduinoJson (+4k3 code, 0k3 mem, 48 iram)
// //  #define USE_IR_HVAC                            // Support for HVAC (Toshiba, Mitsubishi and LG) system using IR (+3k5 code)
//   #define USE_IR_RECEIVE                         // Support for IR receiver (+7k2 code, 264 iram)
//     #define IR_RCV_BUFFER_SIZE      100          // Max number of packets allowed in capture buffer (default 100 (*2 bytes ram))
//     #define IR_RCV_TIMEOUT          15           // Number of milli-Seconds of no-more-data before we consider a message ended (default 15)
//     #define IR_RCV_MIN_UNKNOWN_SIZE 6            // Set the smallest sized "UNKNOWN" message packets we actually care about (default 6)

// #define USE_WS2812                               // WS2812 Led string using library NeoPixelBus (+5k code, +1k mem, 232 iram) - Disable by //
// #define USE_WS28XX_CTYPE     NEO_GRB           // WS2812 Color type (NEO_RGB, NEO_GRB, NEO_BRG, NEO_RBG, NEO_RGBW, NEO_GRBW)
// #define USE_WS2812_DMA                         // DMA supports only GPIO03 (= Serial RXD) (+1k mem). When USE_WS2812_DMA is enabled expect Exceptions on Pow

// By type of light I own //PHASE OUT
#ifdef USE_RGB_LIGHTS_TYPE_MICRO
  #define USE_WS28XX_HARDWARE_WS2812
  #define USE_WS28XX_FEATURE_GRB
  #define USE_WS28XX_METHOD_800KBPS
#endif
#ifdef USE_RGB_LIGHTS_TYPE_ONEWIRE_STRIP
  #define USE_WS28XX_HARDWARE_WS2812
  #define USE_WS28XX_FEATURE_GRB
  #define USE_WS28XX_METHOD_800KBPS
#endif
#ifdef USE_RGB_LIGHTS_TYPE_ONEWIRE_STRING
  #define USE_WS28XX_HARDWARE_WS2811
  #define USE_WS28XX_FEATURE_DEFAULT
  #define USE_WS28XX_METHOD_800KBPS
#endif
#ifdef USE_RGB_LIGHTS_TYPE_TWOWIRE_STRIP
  #define USE_WS28XX_HARDWARE_WS2801
#endif
#ifdef USE_RGB_LIGHTS_TYPE_WS2801_STRING
  #define USE_WS28XX_HARDWARE_WS2811 //01
  #define USE_WS28XX_FEATURE_RGB
  #define USE_WS28XX_METHOD_800KBPS
#endif
#ifdef USE_RGB_LIGHTS_TYPE_DEFAULT
  #define USE_WS28XX_HARDWARE_WS2812 //01
  #define USE_WS28XX_FEATURE_RGB
  #define USE_WS28XX_METHOD_800KBPS
#endif


#define USE_ARILUX_RF                            // Add support for Arilux RF remote controller (+0k8 code, 252 iram (non 2.3.0))

//#define USE_SR04                                 // Add support for HC-SR04 ultrasonic devices (+1k code)

//#define USE_TM1638                               // Add support for TM1638 switches copying Switch1 .. Switch8 (+1k code)
#define USE_HX711                                // Add support for HX711 load cell (+1k5 code)
//  #define USE_HX711_GUI                          // Add optional web GUI to HX711 as scale (+1k8 code)

#define USE_RF_FLASH                             // Add support for flashing the EFM8BB1 chip on the Sonoff RF Bridge. C2CK must be connected to GPIO4, C2D to GPIO5 on the PCB (+3k code)

#define USE_TX20_WIND_SENSOR                     // Add support for La Crosse TX20 anemometer (+2k code)

#define USE_RC_SWITCH                            // Add support for RF transceiver using library RcSwitch (+2k7 code, 460 iram)

//#define USE_RF_SENSOR                            // Add support for RF sensor receiver (434MHz or 868MHz) (+0k8 code)
//  #define USE_THEO_V2                            // Add support for decoding Theo V2 sensors as documented on https://sidweb.nl using 434MHz RF sensor receiver (+1k4 code)
//  #define USE_ALECTO_V2                          // Add support for decoding Alecto V2 sensors like ACH2010, WS3000 and DKW2012 weather stations using 868MHz RF sensor receiver (+1k7 code)

#define USE_SM16716                              // Add support for SM16716 RGB LED controller (+0k7 code)

//#define USE_HRE                                  // Add support for Badger HR-E Water Meter (+1k4 code)

/*********************************************************************************************\
 * Debug features are only supported in development branch
\*********************************************************************************************/

//#define USE_DEBUG_DRIVER                         // Use xdrv_99_debug.ino providing commands CpuChk, CfgXor, CfgDump, CfgPeek and CfgPoke

/*********************************************************************************************\
 * Optional firmware configurations
 * Select none or just one for optional features and sensors as configured in mFirmwareDefaults.h
 * See RELEASENOTES.md for selected features
\*********************************************************************************************/

//#define FIRMWARE_CLASSIC                         // Create sonoff-classic with initial configuration tools WPS, SmartConfig and WifiManager
//#define FIRMWARE_BASIC                           // Create sonoff-basic with no sensors
//#define FIRMWARE_SENSORS                         // Create sonoff-sensors with useful sensors enabled
//#define FIRMWARE_KNX_NO_EMULATION                // Create sonoff-knx with KNX but without Emulation
//#define FIRMWARE_DISPLAYS                        // Create sonoff-display with display drivers enabled
//#define FIRMWARE_MINIMAL                         // Create sonoff-minimal as intermediate firmware for OTA-MAGIC


// Anything added by this file must "undef" then "ifdef" to replace it
#ifdef USE_CONFIG_OVERRIDE
#include "0_ConfigUser/mUserConfig_Secret.h"
#endif


#endif


