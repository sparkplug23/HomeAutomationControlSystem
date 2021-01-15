# Home Automation Control System (HACS)

Firmware for _ESP8266_ and _ESP32_ based devices for integration with smart home systems. The project has been written to be highly modular, but also includes some bespoke firmware options for specific use cases. The modularity, is intended to allow easy integration of additional sensors or drivers as the project expands. 

## Credits

This project started as a bespoke controller for home heating, and slowly grew over the space of a year with features and devices being added to control lights and add sensors for around the home. A year into the development, I discovered Tasmota and all it has to offer and have since started adding features found within Tasmota that are useful in my home automation environment. This has helped jump start the projects scope, and in the near term will probably include many simularities with Tasmota, but over time I aim to diverge this project into its own identity as I have time to develop it further. Nevertheless, Tasmota has been and continues to be a great inspiration and I owe a great deal to their developer team ([Tasmota](https://github.com/arendst/Tasmota/releases/latest)).

### Libraries Used (included in project)
Libraries used with HACS are:
- [ESP8266 core for Arduino](https://github.com/esp8266/Arduino)
- [BME280]()
- [IRremoteEsp8266](https://github.com/markszabo/IRremoteESP8266)
- [NeoPixelBus](https://github.com/Makuna/NeoPixelBus)<sup>1</sup>
- [OneWire](https://github.com/PaulStoffregen/OneWire)
- [rc-switch](https://github.com/sui77/rc-switch)

><sup>1</sup>Modified libraries include changes that make them operationally different to the original version, these changes are required for better integration with this project.

## Features already supported by the project

### Drivers

### Sensors

### Displays

## Features under development for future integration

## Notes
- HACS is pronounced as "Hex/Hacks".
- Written with VSCode IDE and PlatformIO.
- [x]<sup>1</sup> extra comment.

## License

This program is licensed under GPL-3.0


# How to use the project
Since this project is still under development, it requires extra steps for others to deploy it in their network. This will become easier and eventually seamless with further development time. Here, I will list the steps that are required to get the system running under different environments. 

## Configure

1) The folder ```0_ConfigUser``` holds the files to configure the project, with a file named `mUserConfigSecret.h` containing each users configuration parameters. This is not shared via github, but is generated during the first compile (via template file located in the tools folder). Subsequent compiles will not change the `mUserConfigSecret.h` file.

2) Inside the file `mUserConfigSecret.h`, the user can add their unique values for their automation system. These include the SSID and password for up to three network connections, and if enabled, the mqtt broker IP address.

3) There are a number of example configurations for popular devices provided. Some noteworthy parameters are:
  * ```DEVICENAME_CTR``` is the unique name of that device, and mqtt will use this for the topic.
  * ```MODULE_TEMPLATE``` provides the device configuration, including its name, hardware, and the required pin functionality and is formatted using JSON commands. Some of the json keys (eg. `GPIOC`) can be omited, but `MODULE_TEMPLATE` is required for compiling.
  * (*optional*) ```LIGHTING_TEMPLATE``` is also formatted as json, however, this is optional configuration for the lighting modules during boot. This accepts any command which could also be executed via mqtt, webui or serial.
  * (*optional*) ```FUNCTION_TEMPLATE``` will also run any command, including the configuration of sensors and drivers during boot time.
  * Additionally, by defining any module as enabled including its required pin function via `GPIOC`, all sensors and drivers are available. It must be noted, this is highly developmental firmware and some modules may either have bugs, or not work at all.

## Uploading firmware

4) The file named ```platformio.ini``` has a variable named `default_envs`. Each (on a new line) device in the format `esp_8266_<devicename>` will be compiled. At least one must be provided, but multiple devices can be built and flashed at once.

5) The file named ```platformio_env8266.ini``` must contain the environment named in the previous step (ie `esp_8266_<devicename>`). For serial flashing, the minimal environment should have these as a minimum.

```cpp
[env:esp_8266_rgbcustomuser01]
build_flags = ${common.build_flags} 
                -D DEVICE_RGBCUSTOM_USER_01
                -w
upload_port = COM3
```

Similarly, for OTA flashing, the `upload_port` must be changed to the IP and `upload_protocol` must be set to `espota`.

```cpp
[env:esp_8266_rgbcustomuser01]
build_flags = ${common.build_flags} 
                -D DEVICE_RGBCUSTOM_USER_01
                -w
upload_protocol = espota
upload_port = 192.168.1.79
```





