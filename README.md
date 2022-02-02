# Reactjs_ESP32

This project consists of an implementation of a Web Server using the ESP32 device, which receive requests from a Web/Mobile App.
For this, the NodeMCU board model is used and the particular pinout is explained. In addition, the Mobile App is implemented using React Native Framework in JavaScript, which defines the buttons and labels responsible for manage the sensor data collected and the LEDs attached.

Fist of all, the hardware used is listed follow:
- _ESP32-NodeMCU_;
- _Breadboard_;
- _5 cables male_;
- _3 resistors (1 with 1k Ohm and 2 with 100 Ohm)_;
- _1 USB-C cable_; 

The components are conected as shown in the Image 1.

In the following, the code that implements the WebServer is written in C-like language using Arduino IDE to record the ESP32 board. The code is described in file named "*esp32_code_temp_humi.ino*".
