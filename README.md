# Reactjs_ESP32

This project consists of a Simple Home Automation example, that using temperature and humidity sensor with LEDs activated by Mobile APP.

Thus, is presented an implementation of a Web Server using the ESP32 device, which receive requests from a Web/Mobile App and update the status and data sensed directly in the mobile and web browser. For this, the NodeMCU board model is used and the particular pinout is explained. In addition, the Mobile App is implemented using React Native Framework in JavaScript, which defines the buttons and labels responsible for manage the sensor data collected and the LEDs attached.

Fist of all, the hardware used is listed follow:
- _ESP32-NodeMCU_;
- _1 DHT 11 sensor_;
- _2 LEDs_;
- _Breadboard_;
- _7 jumpers (2 male-to-male and 5 female-to-male)_;
- _3 resistors (1 with 1k Ohm and 2 with 150 Ohms)_;
- _1 USB-C cable_; 

The components are conected as shown in the Image 1:

<img src="https://github.com/miguelneto0/Reactjs_ESP32/blob/main/images/hardware_settings.png"  width="550" height="300">

In the following, the code that implements the WebServer is written in C-like language using Arduino IDE to record the ESP32 board. The code is described in file named **"*esp32_code_temp_humi.ino*"** and is shown in Image 2 below (2.1 left and 2.2 right). For this, were used the following libraries:
- _"DHT.h"_
- _"WiFi.h"_
- _<WebServer.h>_

<img src="https://github.com/miguelneto0/Reactjs_ESP32/blob/main/images/code_part1.png"  height="280" > <img src="https://github.com/miguelneto0/Reactjs_ESP32/blob/main/images/code_part2.png"  height="280">

As observed in Image 2.1 (left), the "DHT.h" library is responsible for configuring the temperature and humidity sensor DHT 11 from the statement of the object dht from DHT class. In this statement, the type (DHT_type) and the pin (DHT_pin) are passed as parameters. In this case, the DHT11 is specifically written (as alterantive DHT22) and the pin choosen was 4. The pin 4 can be statemented for the number of the pin or by the name of the pin (for this NodeMCU board in particular, T0 represent the GPIO4 and on the board is marked as P4 port).

After, the server is statemented through the object server from WebServer class, passing as parameter the port for the internet access (port 80, is default port for HTTP). In the same way, is defined the timeout (*WIFI_TIMEOUT*, total time for waiting connection the devices with the server), in this case, 10000 (miliseconds) represents 10 seconds for waiting until the ESP32 connection. this connection is established in the **"conectar()"** function presented below, using the *ssid* and *pswd* data described in lines 19 and 20, respectively. The blurred fields must contain the wifi network name (**ssid**) and password (**pswd**), enclosed in quotes. In addition, the port 26 (_GPIO26_) and 27 (_GPIO27_), respectively, receive the output of red LED and green LED. The **temp** and **humi** float variables are used for hold the data sensed by the DHT11 and managed by the String **valor** when the definition of routes by the server object.

In the Image 2.2 (right), the connection function initializes the WiFi module of the ESP32 from the method WiFi.mode(WIFI_STA), which defines that the module will perform in STATION mode. Then, the WiFi.begin(ssid, pswd) start the connection attempt. In following, the while print the loading symbol (" #") for ilustrate the connection attemption while the status (WiFi.status) is different of the WL_CONNECTED. And if-else code define when the connection is reached, printing the success message with the IP assigned for the ESP32 or fail message in case of WiFi.status() different of WL_CONNECTED.

In following, the setup() and loop() are described. First, the setup function have two parts, in Image 3 ilustrate by red part (definition of pin used, dht methods and the call of the connection function). The blue part describe the behavior of the server, which uses the method "on" for define the routes and the "send" method for represent the HTTP requests. In this case, the root route is defined as "/", the data sensor routes defined as "/sensor" can be "/sensor/temp" and "/senor/humi" as subroutes. For LEDs, were used "ledR/on" and "ledR/off" for activate and disactivate the red LED, while "ledG" was used for green LED with the same subroute, respectively.

<img src="https://github.com/miguelneto0/Reactjs_ESP32/blob/main/images/code_part3.png"  width="640">
