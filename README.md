# Reactjs_ESP32

This project consists of an implementation of a Web Server using the ESP32 device, which receive requests from a Web/Mobile App.
For this, the NodeMCU board model is used and the particular pinout is explained. In addition, the Mobile App is implemented using React Native Framework in JavaScript, which defines the buttons and labels responsible for manage the sensor data collected and the LEDs attached.

Fist of all, the hardware used is listed follow:
- _ESP32-NodeMCU_;
- _1 DHT 11 sensor_;
- _2 LEDs_;
- _Breadboard_;
- _7 jumpers (2 male-to-male and 5 female-to-male)_;
- _3 resistors (1 with 1k Ohm and 2 with 150 Ohms)_;
- _1 USB-C cable_; 

The components are conected as shown in the Image 1.

![alt text](https://github.com/miguelneto0/Reactjs_ESP32/blob/main/images/hardware_settings.png?raw=true "Hardware Setting" | width=60)

In the following, the code that implements the WebServer is written in C-like language using Arduino IDE to record the ESP32 board. The code is described in file named **"*esp32_code_temp_humi.ino*"**. For this, were used the following libraries:
- _"DHT.h"_
- _"WiFi.h"_
- _<WebServer.h>_
