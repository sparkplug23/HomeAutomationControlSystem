#include "arduino.h"

#include <driver/adc.h>

#include "soc/rtc_wdt.h"

//   #define DEBUG_PIN1_GPIO     23
//   #define DEBUG_PIN1_INIT()   pinMode(DEBUG_PIN1_GPIO, OUTPUT); digitalWrite(DEBUG_PIN1_GPIO, HIGH);
//   #define DEBUG_PIN1_SET(X)   digitalWrite(DEBUG_PIN1_GPIO, X);
//   #define DEBUG_PIN1_TOGGLE()   digitalWrite(DEBUG_PIN1_GPIO, !digitalRead(DEBUG_PIN1_GPIO));

// const byte interruptPin = 25;
// volatile int interruptCounter = 0;
// // volatile double interruptExecuteTime = 0;
// static int taskCore0 = 0;
// static int taskCore1 = 1;
// int numberOfInterrupts = 0;
// uint16_t adc6 = 0;
// uint16_t adc7 = 0;

// #include <soc/sens_reg.h>
// #include <soc/sens_struct.h>

//  int IRAM_ATTR local_adc1_read(int channel) {
//     uint16_t adc_value;
//     SENS.sar_meas_start1.sar1_en_pad = (1 << channel); // only one channel is selected
//     while (SENS.sar_slave_addr1.meas_status != 0);
//     SENS.sar_meas_start1.meas1_start_sar = 0;
//     SENS.sar_meas_start1.meas1_start_sar = 1;
//     while (SENS.sar_meas_start1.meas1_done_sar == 0);
//     adc_value = SENS.sar_meas_start1.meas1_data_sar;
//     return adc_value;
// }

//   uint16_t adc_value;

// portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
// RTC_DATA_ATTR uint16_t adcValue;
// uint16_t _adcValue;
// uint16_t adcValue1;

// void IRAM_ATTR adc1_get_raw_ram(adc1_channel_t channel) {
//     SENS.sar_read_ctrl.sar1_dig_force = 0; // switch SARADC into RTC channel 
//     SENS.sar_meas_wait2.force_xpd_sar = SENS_FORCE_XPD_SAR_PU; // adc_power_on
//     // RTCIO.hall_sens.xpd_hall = false; //disable other peripherals
//     SENS.sar_meas_wait2.force_xpd_amp = SENS_FORCE_XPD_AMP_PD; // channel is set in the convert function
    
// 	// disable FSM, it's only used by the LNA.
//     SENS.sar_meas_ctrl.amp_rst_fb_fsm = 0; 
//     SENS.sar_meas_ctrl.amp_short_ref_fsm = 0;
//     SENS.sar_meas_ctrl.amp_short_ref_gnd_fsm = 0;
//     SENS.sar_meas_wait1.sar_amp_wait1 = 1;
//     SENS.sar_meas_wait1.sar_amp_wait2 = 1;
//     SENS.sar_meas_wait2.sar_amp_wait3 = 1; 

//     //set controller
//     SENS.sar_read_ctrl.sar1_dig_force = false;      //RTC controller controls the ADC, not digital controller
//     SENS.sar_meas_start1.meas1_start_force = true;  //RTC controller controls the ADC,not ulp coprocessor
//     SENS.sar_meas_start1.sar1_en_pad_force = true;  //RTC controller controls the data port, not ulp coprocessor
//     SENS.sar_touch_ctrl1.xpd_hall_force = true;     // RTC controller controls the hall sensor power,not ulp coprocessor
//     SENS.sar_touch_ctrl1.hall_phase_force = true;   // RTC controller controls the hall sensor phase,not ulp coprocessor
    
//     //start conversion
//     SENS.sar_meas_start1.sar1_en_pad = (1 << channel); //only one channel is selected.
//     while (SENS.sar_slave_addr1.meas_status != 0);
//     SENS.sar_meas_start1.meas1_start_sar = 0;
//     SENS.sar_meas_start1.meas1_start_sar = 1;
//     while (SENS.sar_meas_start1.meas1_done_sar == 0);
//     _adcValue = SENS.sar_meas_start1.meas1_data_sar; // set adc value!

//     SENS.sar_meas_wait2.force_xpd_sar = SENS_FORCE_XPD_SAR_PD; // adc power off
// }


// void core1Task(){// void * pvParameters ){
//       Serial.print("An interrupt has occurred. Total: ");
//       Serial.print(numberOfInterrupts);
//       // Serial.print(" at :");
//       // Serial.print(interruptExecuteTime);
//       Serial.print(" on Core :");
//       Serial.println(_adcValue);
//       // Serial.println(xPortGetCoreID());
// }


// void IRAM_ATTR handleInterrupt(){//void * pvParameters) {
//   portENTER_CRITICAL_ISR(&mux);
//   // Serial.print(" on Core :");
//   DEBUG_PIN1_SET(0);
//   /**
//    * adc1_ch6
//    * */
//   adc1_get_raw_ram(ADC1_CHANNEL_6);
//   adcValue1 = _adcValue;

//   DEBUG_PIN1_SET(1);
//   // interruptExecuteTime = millis(); // this is the important part for me
//   interruptCounter++;
//   portEXIT_CRITICAL_ISR(&mux);
// }

 
// void main_task(void *pvParameter)
// {
  
// rtc_wdt_protect_off();
// rtc_wdt_disable();

//   pinMode(interruptPin, INPUT_PULLUP);
//   attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);
  
//         adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11 );
//         adc1_config_width(ADC_WIDTH_BIT_12);
//         adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11 );
//         adc1_config_width(ADC_WIDTH_BIT_12);

//   while(1) {
//     // printf( "Task1 %d\n\r", interruptCounter ); //CONFIG_HELLO_MESSAGE );
//     core1Task();

//     vTaskDelay(1000 / portTICK_RATE_MS);
//   }

// }


// void setup() {
 
//   Serial.begin(115200);
//   Serial.println("Monitoring interrupts: ");
// DEBUG_PIN1_INIT();


// analogSetClockDiv(1);


//     xTaskCreatePinnedToCore(&main_task, "main_task", 2048, NULL, 1, NULL, 1);
  
// //  xTaskCreatePinnedToCore(
// //                  handleInterrupt,   /* Function to implement the task */
// //                  "handleinterrupt", /* Name of the task */
// //                  10000,      /* Stack size in words */
// //                  NULL,       /* Task input parameter */
// //                  0,          /* Priority of the task */
// //                  NULL,       /* Task handle. */
// //                  taskCore0);  /* Core where the task should run */
// //  xTaskCreatePinnedToCore(
// //                  core1Task,   /* Function to implement the task */
// //                  "core1Task", /* Name of the task */
// //                  10000,      /* Stack size in words */
// //                  NULL,       /* Task input parameter */
// //                  0,          /* Priority of the task */
// //                  NULL,       /* Task handle. */
// //                  taskCore1);  /* Core where the task should run */
// }
 
 
// void loop() {
 
//   if(interruptCounter>0){ // greater than 0 means there was a interrupt fired
//        portENTER_CRITICAL(&mux);
//       interruptCounter--; // decrease to reset the value
//       portEXIT_CRITICAL(&mux);
//       numberOfInterrupts++; // count the numbers of interrupts fired at this moment
// }
//   if (numberOfInterrupts >= 25){
//     numberOfInterrupts = 0;
//     esp_restart(); // restart example by cleaning all data and resetting MCU
//   }
// }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
   Copyright (c) 2020, my_name_here
   All rights reserved.
   https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf#uart-reg-summ
*/

#define D_USER_MICHAEL // maybe undef later?

// #define USE_DEVFEATURE_DISABLE_ALL_PROJECT_FOR_TESTING

#include "1_TaskerManager/mTaskerManager.h"

#ifdef ENABLE_DEVFEATURE_DISABLE_ALL_WDT_FOR_TESTING
void hw_wdt_disable(){
  *((volatile uint32_t*) 0x60000900) &= ~(1); // Hardware WDT OFF 
}

void hw_wdt_enable(){ 
  *((volatile uint32_t*) 0x60000900) |= 1; // Hardware WDT ON 
}
#endif


/*********************************************************************************************
 * Hardware related
\*********************************************************************************************/

#ifdef ESP32
  #include "soc/soc.h"
  #include "soc/rtc_cntl_reg.h"
  #define DISABLE_ESP32_BROWNOUT
  void DisableBrownout(void) {
    // https://github.com/espressif/arduino-esp32/issues/863#issuecomment-347179737
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);  // Disable brownout detector
  }
#endif // ESP32

/********************************************************************************************/
/*********************SETUP******************************************************************/
/********************************************************************************************/

// #define ENABLE_DEVFEATURE_BASIC_NEOPIXEL_TEST
#ifndef ENABLE_DEVFEATURE_BASIC_NEOPIXEL_TEST
void setup(void)
{ 
#ifdef ENABLE_DEVFEATURE_DISABLE_ALL_WDT_FOR_TESTING
  // hw_wdt_disable();
  hw_wdt_enable();
  #endif
    
  #ifndef USE_DEVFEATURE_DISABLE_ALL_PROJECT_FOR_TESTING
  #ifdef ESP32
  #ifdef DISABLE_ESP32_BROWNOUT
    DisableBrownout();      // Workaround possible weak LDO resulting in brownout detection during Wifi connection
  #endif
  #endif

  #ifndef DISABLE_SERIAL0_CORE
  Serial.begin(SERIAL_DEBUG_BAUD_DEFAULT);
  #endif
  
// Serial2.begin(115200);
// while(1)
// {
// Serial.println("115200 Working");
// Serial2.println("115200 Working");
// delay(1000);

// }

// Serial2.flush();

// DEBUG_HOLD_POINT;




  #ifdef USE_SERIAL_ALTERNATE_TX
    Serial.set_tx(2);
  #endif
  Serial.println(F("\n\rRebooting..." DEBUG_INSERT_PAGE_BREAK));
  #ifndef DISABLE_SERIAL_LOGGING
  #ifdef ENABLE_BUG_TRACING
  Serial.println(F("DELAYED BOOT for 5 seconds...")); Serial.flush(); delay(5000);
  #endif
  #endif

  // Init Json builder with memory address and size
  JsonBuilderI->Start(data_buffer.payload.ctr,&data_buffer.payload.len,DATA_BUFFER_PAYLOAD_MAX_LENGTH);
  BufferWriterI->Start(data_buffer.payload.ctr,&data_buffer.payload.len,DATA_BUFFER_PAYLOAD_MAX_LENGTH);

  // msup.WDT_Begin();
  
  pCONT->Instance_Init();

  // Set boot method
  pCONT_set->seriallog_level_during_boot = SERIAL_LOG_LEVEL_DURING_BOOT;
  pCONT_set->Settings.seriallog_level = pCONT_set->seriallog_level_during_boot;
  
  RESET_BOOT_STATUS();
    
  pCONT_set->RtcRebootLoad();
  if(!pCONT_set->RtcRebootValid()) { pCONT_set->RtcReboot.fast_reboot_count = 0; }
  pCONT_set->RtcReboot.fast_reboot_count++;
  pCONT_set->RtcRebootSave();

  pCONT_sup->init_FirmwareVersion();

  #ifdef USE_MODULE_DRIVERS_FILESYSTEM
  pCONT_mfile->UfsInit();  // xdrv_50_filesystem.ino
  #endif

  // Load config from memory
 // #ifndef DEBUG_NUM1

  DEBUG_LINE_HERE;

  pCONT_set->SettingsDefault(); //preload minimal required
  
  // DEBUG_HOLD_POINT;

 // #endif // DEBUG_NUM1
  #ifdef ENABLE_SETTINGS_STORAGE
  // Overwrite with latest values, including template if new SETTINGS_CONFIG exists
  pCONT_set->SettingsLoad();    //overwrite stored settings from defaults
  // Check Load was successful
  pCONT_set->SettingsLoad_CheckSuccessful();
  #endif

  // if (1 == RtcReboot.fast_reboot_count) {      // Allow setting override only when all is well
  //   UpdateQuickPowerCycle(true);
  // }

   
  pCONT->Tasker_Interface(FUNC_POINTER_INIT); // confirgure any memory address needed as part of module init or templates
  
  #ifdef FORCE_TEMPLATE_LOADING
  // This will overwrite the settings, temporary, will use a second flag to force template loads "TEMPLATE_HOLDER"
  // need to if template not provided, load defaults else use settings -- add protection in settings defaults to use templates instead (progmem or user desired)
  // Load template before init
  #ifdef ENABLE_LOG_LEVEL_INFO
  AddLog(LOG_LEVEL_WARN,PSTR(D_LOG_MEMORY D_LOAD " Temporary loading any progmem templates"));
  #endif
  pCONT->Tasker_Interface(FUNC_TEMPLATE_MODULE_LOAD); // loading module, only interface modules will have these
  // load
  // pCONT->Tasker_Interface(FUNC_TEMPLATE_DEVICE_LOAD);  //load/overwrite names AFTER init (FUNC_TEMPLATE_DEVICE_CONFIG_BEFORE_INIT)
  #endif
  
  // Set boot method
  pCONT_set->seriallog_level_during_boot = SERIAL_LOG_LEVEL_DURING_BOOT;
  pCONT_set->Settings.seriallog_level = pCONT_set->seriallog_level_during_boot;
  

  // Init the GPIOs
  pCONT_pins->GpioInit();
  // Start pins in modules
  pCONT->Tasker_Interface(FUNC_PRE_INIT);
  // Init devices
  pCONT->Tasker_Interface(FUNC_INIT);
  // Init devices after others have been configured fully
  pCONT->Tasker_Interface(FUNC_POST_INIT);
  // Run system functions 
  pCONT->Tasker_Interface(FUNC_FUNCTION_LAMBDA_INIT);
  // Preload any templates defined in mFirmwareCustom.h
  // pCONT->Tasker_Interface(FUNC_TEMPLATE_MODULE_LOAD); // Note both below may need checks to ignore if this occured
  // Load the minimal default settings in modules (hard coded) before loading any stored user values
  pCONT->Tasker_Interface(FUNC_SETTINGS_PRELOAD_DEFAULT_IN_MODULES); // load the minimal
  // Load any stored user values into module
  pCONT->Tasker_Interface(FUNC_SETTINGS_LOAD_VALUES_INTO_MODULE);
  // load
  pCONT->Tasker_Interface(FUNC_TEMPLATE_DEVICE_LOAD);//load/overwrite names AFTER init (FUNC_TEMPLATE_DEVICE_CONFIG_AFTER_INIT)
  // Configure sensor/drivers to values desired for modules
  pCONT->Tasker_Interface(FUNC_CONFIGURE_MODULES_FOR_DEVICE);
  // init mqtt handlers from memory
  pCONT->Tasker_Interface(FUNC_MQTT_HANDLERS_INIT);  
  #ifdef ENABLE_FUNCTION_DEBUG
    pCONT->Tasker_Interface(FUNC_DEBUG_CONFIGURE);
  #endif
  // Init any dynamic memory buffers
  pCONT->Tasker_Interface(FUNC_REFRESH_DYNAMIC_MEMORY_BUFFERS_ID);
  // Used to show progress of boot in logs
  pCONT->Tasker_Interface(FUNC_ON_BOOT_COMPLETE);

  #endif // USE_DEVFEATURE_DISABLE_ALL_PROJECT_FOR_
  // pinMode(21, OUTPUT);

}

void LoopTasker()
{

  #ifdef USE_ARDUINO_OTA
    pCONT_sup->ArduinoOtaLoop();
  #endif  // USE_ARDUINO_OTA
   
  pCONT->Tasker_Interface(FUNC_LOOP); DEBUG_LINE;
  
  if(pCONT_time->uptime.seconds_nonreset > 30){ pCONT->Tasker_Interface(FUNC_FUNCTION_LAMBDA_LOOP); } // Only run after stable boot
 
  //move into support, or into time, to align with every_minute, hour, etc
  if(mTime::TimeReached(&pCONT_sup->tSavedLoop50mSec ,50  )){ pCONT->Tasker_Interface(FUNC_EVERY_50_MSECOND);  }  DEBUG_LINE;
  if(mTime::TimeReached(&pCONT_sup->tSavedLoop100mSec,100 )){ pCONT->Tasker_Interface(FUNC_EVERY_100_MSECOND); }  DEBUG_LINE;
  if(mTime::TimeReached(&pCONT_sup->tSavedLoop250mSec,250 )){ pCONT->Tasker_Interface(FUNC_EVERY_250_MSECOND); }  DEBUG_LINE;
  if(mTime::TimeReached(&pCONT_sup->tSavedLoop1Sec   ,1000)){ pCONT->Tasker_Interface(FUNC_EVERY_SECOND);      }  DEBUG_LINE;


// check pinused here to see if they are set properly

// if(pCONT_pins->PinUsed(GPIO_RGB_DATA_ID))
// {
//   Serial.println("PinUsed RGB");
//   Serial.println(pCONT_pins->GetPin(GPIO_RGB_DATA_ID));
// }

}

/********************************************************************************************/
/*********************loop*******************************************************************/
/********************************************************************************************/

void loop(void)
{
  pCONT_sup->activity.loop_counter++;
  pCONT_sup->loop_start_millis = millis();
  WDT_RESET();
  

  LoopTasker();
    
  pCONT_sup->loop_runtime_millis = millis() - pCONT_sup->loop_start_millis;

  if(mTime::TimeReached(&pCONT_set->runtime_var.tSavedUpdateLoopStatistics, 1000)){
    pCONT_sup->activity.cycles_per_sec = pCONT_sup->activity.loop_counter; 
    #ifdef ENABLE_LOG_LEVEL_INFO
    AddLog(LOG_LEVEL_DEBUG_MORE,PSTR("LOOPSEC = %d %d"), pCONT_sup->activity.loop_counter, pCONT_sup->activity.cycles_per_sec);
    #endif // ENABLE_LOG_LEVEL_INFO
    pCONT_sup->activity.loop_counter=0;
  }

  if(pCONT_sup->loop_runtime_millis > 40){
    DEBUG_PRINTF("loop_runtime_millis=%d\n\r", pCONT_sup->loop_runtime_millis);
  }

  //  pCONT_mqtt->flag_uptime_reached_reduce_frequency = true;

  // Change this to my own way
  // DO THIS NEXT
  //SmartLoopDelay()
  #ifndef DISABLE_SLEEP
  if(pCONT_set->Settings.enable_sleep){
    if (pCONT_set->Settings.flag_network.sleep_normal) {
      pCONT_sup->SleepDelay(pCONT_set->runtime_var.sleep);
    } else {

      // Loop time < sleep length of time
      if (pCONT_sup->loop_runtime_millis < (uint32_t)pCONT_set->runtime_var.sleep) {
        //delay by loop time
        pCONT_sup->SleepDelay((uint32_t)pCONT_set->runtime_var.sleep - pCONT_sup->loop_runtime_millis);  // Provide time for background tasks like wifi
      } else {

        // if loop takes longer than sleep period, no delay, IF wifi is down, devote half loop time to wifi connect
        if (pCONT_set->global_state.wifi_down) {
          pCONT_sup->SleepDelay(pCONT_sup->loop_runtime_millis /2); // If wifi down and loop_runtime_millis > setoption36 then force loop delay to 1/3 of loop_runtime_millis period
        }
      }
    }
  }
  #endif

  // delay(100);

  DEBUG_LINE;
  if (!pCONT_sup->loop_runtime_millis) { pCONT_sup->loop_runtime_millis++; }            // We cannot divide by 0
  pCONT_sup->loop_delay_temp = pCONT_set->runtime_var.sleep; 
  if (!pCONT_sup->loop_delay_temp) { pCONT_sup->loop_delay_temp++; }              // We cannot divide by 0
  pCONT_sup->loops_per_second = 1000 / pCONT_sup->loop_delay_temp;  // We need to keep track of this many loops per second, 20ms delay gives 1000/20 = 50 loops per second (50hz)
  pCONT_sup->this_cycle_ratio = 100 * pCONT_sup->loop_runtime_millis / pCONT_sup->loop_delay_temp;
  pCONT_set->loop_load_avg = pCONT_set->loop_load_avg - (pCONT_set->loop_load_avg / pCONT_sup->loops_per_second) + (pCONT_sup->this_cycle_ratio / pCONT_sup->loops_per_second); // Take away one loop average away and add the new one

  DEBUG_LINE;
  // Create a debug mqtt packet for timings, of main loop and interface loops
  // DEBUG_PRINTF("%s=%d\r\n","tick",pCONT_sup->loop_runtime_millis);
  // DEBUG_PRINTF("%s=%d\r\n","tick",pCONT_sup->activity.cycles_per_sec);
  // uint32_t start_millis = millis();
  // AddLog(LOG_LEVEL_TEST,PSTR("LOOPSEC = %d \t %d"),loops_per_second,mtel.activity.cycles_per_sec);
  // DEBUG_PRINTF("ADD TIME = %d\n\r",millis()-start_millis);

  pCONT_set->fSystemRestarted = false; //phase out and use module flag instead

  DEBUG_LINE;

  // #endif // USE_DEVFEATURE_DISABLE_ALL_PROJECT_FOR_TESTING

}

#endif // ENABLE_DEVFEATURE_BASIC_NEOPIXEL_TEST
#ifdef ENABLE_DEVFEATURE_BASIC_NEOPIXEL_TEST

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>

#include <WiFi.h>

const char* ssid     = STA_SSID2;
const char* password = STA_PASS2;

WiFiServer server(80);

const uint16_t PixelCount = 256; // make sure to set this to the number of pixels in your strip
const uint8_t PixelPin = 23;  // make sure to set this to the correct pin, ignored for Esp8266
const RgbColor CylonEyeColor(HtmlColor(0x000001));

NeoPixelBus<NeoRgbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);
// for esp8266 omit the pin
//NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);

NeoPixelAnimator animations(2); // only ever need 2 animations

uint16_t lastPixel = 0; // track the eye position
int8_t moveDir = 1; // track the direction of movement

// uncomment one of the lines below to see the effects of
// changing the ease function on the movement animation
AnimEaseFunction moveEase =
//      NeoEase::Linear;
//      NeoEase::QuadraticInOut;
//      NeoEase::CubicInOut;
        NeoEase::QuarticInOut;
//      NeoEase::QuinticInOut;
//      NeoEase::SinusoidalInOut;
//      NeoEase::ExponentialInOut;
//      NeoEase::CircularInOut;

void FadeAll(uint8_t darkenBy)
{
    RgbColor color;
    for (uint16_t indexPixel = 0; indexPixel < strip.PixelCount(); indexPixel++)
    {
        color = strip.GetPixelColor(indexPixel);
        color.Darken(darkenBy);
        strip.SetPixelColor(indexPixel, color);
    }
}

void FadeAnimUpdate(const AnimationParam& param)
{
    if (param.state == AnimationState_Completed)
    {
        FadeAll(10);
        animations.RestartAnimation(param.index);
    }
}

void MoveAnimUpdate(const AnimationParam& param)
{
    // apply the movement animation curve
    float progress = moveEase(param.progress);

    // use the curved progress to calculate the pixel to effect
    uint16_t nextPixel;
    if (moveDir > 0)
    {
        nextPixel = progress * PixelCount;
    }
    else
    {
        nextPixel = (1.0f - progress) * PixelCount;
    }

    // if progress moves fast enough, we may move more than
    // one pixel, so we update all between the calculated and
    // the last
    if (lastPixel != nextPixel)
    {
        for (uint16_t i = lastPixel + moveDir; i != nextPixel; i += moveDir)
        {
            strip.SetPixelColor(i, CylonEyeColor);
        }
    }
    strip.SetPixelColor(nextPixel, CylonEyeColor);

    lastPixel = nextPixel;

    if (param.state == AnimationState_Completed)
    {
        // reverse direction of movement
        moveDir *= -1;

        // done, time to restart this position tracking animation/timer
        animations.RestartAnimation(param.index);
    }
}

void setup()
{
  
    #ifdef ENABLE_DEVFEATURE_NEOPIXEL_TEST_WIFI_ON
   Serial.begin(115200);
    pinMode(2, OUTPUT);      // set the LED pin mode

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();


    #endif// ENABLE_DEVFEATURE_NEOPIXEL_TEST_WIFI_ON

    strip.Begin();
    strip.Show();
// fade all pixels providing a tail that is longer the faster
    // the pixel moves.
    animations.StartAnimation(0, 5, FadeAnimUpdate);

    // take several seconds to move eye fron one side to the other
    animations.StartAnimation(1, 2000, MoveAnimUpdate);
}

int value = 0;
void loop()
{
    // this is all that is needed to keep it running
    // and avoiding using delay() is always a good thing for
    // any timing related routines
    animations.UpdateAnimations();
    strip.Show();

    #ifdef ENABLE_DEVFEATURE_NEOPIXEL_TEST_WIFI_ON
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(2, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(2, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
  #endif //  ENABLE_DEVFEATURE_NEOPIXEL_TEST_WIFI_ON
}
#endif // ENABLE_DEVFEATURE_BASIC_NEOPIXEL_TEST