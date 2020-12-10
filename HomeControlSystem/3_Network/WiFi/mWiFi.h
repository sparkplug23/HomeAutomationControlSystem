#ifndef _MWIFI_H
#define _MWIFI_H 0.4

#include "0_ConfigUser/mUserConfig.h"

// #define ENABLE_WIFI_DEVELOPMENT

#ifdef ESP32
#include <esp8266toEsp32.h>
#endif

#ifdef ENABLE_USER_CONFIG_OVERRIDE 
  #include "0_ConfigUser/mUserConfigSecret.h"
#endif
#include "2_CoreSystem/Logging/mLogging.h"

#include "1_TaskerManager/mTaskerManager.h"


//#include "//2_CoreSystem/Languages/mLanguage.h"
#include "2_CoreSystem/Settings/mSettings.h"

#ifdef ESP32
  #include <WiFi.h>
  #include "2_CoreSystem/Support/mSupport.h"
#endif
#ifdef ESP8266
  #include <ESP8266WiFi.h>            // Wifi, MQTT, Ota, WifiManager
  // #include <ESP8266mDNS.h>
#endif


#ifdef ESP8266
  #include "2_CoreSystem/Support/SupportESP8266.h"
  #define SupportHardware SupportESP8266
#endif
#ifdef ESP32
  #include "2_CoreSystem/Support/SupportESP32.h"
  #define mSupportHardware SupportESP32
#endif


    const uint8_t WIFI_CONFIG_SEC = 180;       // seconds before restart
    const uint8_t WIFI_CHECK_SEC = 20;         // seconds
    const uint8_t WIFI_RETRY_OFFSET_SEC = 20;  // seconds

    #define D_WIFI_CONFIG_SEC 180
    #define D_WIFI_cONFIG_SEC_FIRST_CONNECT 5



#include "2_CoreSystem/Time/mTime.h"

class mWiFi{
  public:
    mWiFi(){};
    
    #define D_MAX_SSIDS 3
    
    void WifiConnectAP(uint8_t ap_index);

    int8_t Tasker(uint8_t function);
    void init(void);

    int8_t GetRSSdBm();
    uint8_t GetRSSPercentage();

    

    uint32_t tSavedWiFi;
    uint32_t tSavedWiFiCheckIP;
    uint32_t tSavedWiFiReconnect;

    uint16_t wifi_counter_tester = 0;
    
    bool WifiCheckIpConnected();

    #ifndef WIFI_RSSI_THRESHOLD
      #define WIFI_RSSI_THRESHOLD     10         // Difference in dB between current network and scanned network
    #endif
    #ifndef WIFI_RESCAN_MINUTES
      #define WIFI_RESCAN_MINUTES     30         // Number of minutes between wifi network rescan
    #endif



    struct WIFI_CONNECTION{
      uint32_t last_event = 0;       // Last wifi connection event
      uint32_t downtime = 0;         // Wifi down duration
      uint16_t link_count = 0;       // Number of wifi re-connect
      uint8_t counter = 0;
      uint8_t retry_init = 0;
      uint8_t retry = 0;
      uint8_t status = 0;
      uint8_t config_type = 0;
      uint8_t config_counter = D_WIFI_cONFIG_SEC_FIRST_CONNECT; // IMPORTANT!!
      uint8_t scan_state = 0;
      uint8_t bssid[6];
      uint8_t fConnected = false;
      uint8_t fReconnect = false;
    }connection;




    uint8_t mdns_begun = 0;             // mDNS active
    uint8_t wps_result;



    void SplashWifiScan();
    void WifiConnectForced();
    int WifiGetRssiAsQuality(int rssi);
    bool WifiConfigCounter(void);
    #ifndef ESP32
    void WifiWpsStatusCallback(wps_cb_status status);
    #endif
    bool WifiWpsConfigDone(void);
    bool WifiWpsConfigBegin(void);
    void WifiConfig(uint8_t type);
    void WiFiSetSleepMode(void);
    void ScanBestAndBeginWifi();
    uint16_t WifiLinkCount();
    //String WifiDowntime();
    void WifiSetState(uint8_t state);
    void WifiBegin(uint8_t flag, uint8_t channel = 0);
    void WifiCheckIp(void);
    void WifiCheck(uint8_t param);
    int WifiState(void);
    void WifiConnect(void);
    // void WifiDisconnect(void);
    void WifiShutdown(bool option = false);
    void EspRestart(void);

    const char* GetWiFiStatusCtr(void);
    const char* GetWiFiConfigTypeCtr(void);

    enum WIFIBEGIN_Flags{ 
      WIFIBEGIN_FLAG_SSID0_ID=0,
      WIFIBEGIN_FLAG_SSID1_ID,
      WIFIBEGIN_FLAG_SSID2_ID,
      WIFIBEGIN_FLAG_TOGGLE_SSIDS_ID
    };

};

#endif
