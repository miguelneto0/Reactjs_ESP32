# Reactjs_ESP32

This project consists of a Simple Home Automation example, that uses a temperature and humidity sensor with LEDs activated by Mobile APP.

Thus, is presented an implementation of a Web Server using the ESP32 device, which receives requests from a Web/Mobile App and updates the status and data sensed directly in the mobile and web browser. For this, the NodeMCU board model is used and the particular pinout is explained. In addition, the Mobile App is implemented using React Native Framework in JavaScript, which defines the buttons and labels responsible for managing the sensor data collected and the LEDs attached.

First of all, the hardware used is listed follows:
- _ESP32-NodeMCU_;
- _1 DHT 11 sensor_;
- _2 LEDs_;
- _Breadboard_;
- _7 jumpers (2 male-to-male and 5 female-to-male)_;
- _3 resistors (1 with 1k Ohm and 2 with 150 Ohms)_;
- _1 USB-C cable_; 

## Hardware Settings

The components are connected as shown in Image 1:

<img src="https://github.com/miguelneto0/Reactjs_ESP32/blob/main/images/hardware_settings.png"  width="550" height="300">
<p align = "left"><sup>
Image 1</sup></p>

## C-like code for WebServer on ESP32

In the following, the code that implements the WebServer is written in C-like language using Arduino IDE to record the ESP32 board. The code is described in a file named **"*esp32_code_temp_humi.ino*"** and is shown in Image 2 and Image 3 below (2, left and 3, right). For this, were used the following libraries:
- <code>_"DHT.h"_</code>
- <code>_"WiFi.h"_</code>
- <code>_<WebServer.h>_</code>

<img src="https://github.com/miguelneto0/Reactjs_ESP32/blob/main/images/code_part1.png"  height="230" > <img src="https://github.com/miguelneto0/Reactjs_ESP32/blob/main/images/code_part2.png"  height="230">
<p align = "left"><sup>Image 2 and Image 3</sup></p>

As observed in Image 2, the **"DHT.h"** library is responsible for configuring the temperature and humidity sensor **DHT11** from the statement of the object dht from the DHT class. In this statement, the type (**DHT_type**) and the pin (**DHT_pin**) are passed as parameters. In this case, the DHT11 is specifically written (as alterantive DHT22) and the pin chosen was 4. Pin 4 can be statemented for the number of the pin or by the name of the pin (for this NodeMCU board, in particular, **T0** represents the **GPIO4** and on the board is marked as **P4 port**).

After, the server is statemented through the object server from **WebServer** class, passing as a parameter the port for the internet access (port 80, is the default port for HTTP). In the same way, is defined as the timeout (*WIFI_TIMEOUT*, total time for waiting for connecting the devices with the server), in this case, 10000 (milliseconds) represents 10 seconds for waiting until the ESP32 connection. This connection is established in the **"conectar()"** function presented below, using the *ssid* and *pswd* data described in lines 19 and 20, respectively. The blurred fields must contain the wifi network name (**ssid**) and password (**pswd**), enclosed in quotes. In addition, ports 26 (**GPIO26**) and 27 (**GPIO27**), respectively, receive the output of red LED and green LED. The **temp** and **humi** float variables are used to hold the data sensed by the **DHT11** and managed by the String **valor** when the definition of routes by the server object.

In Image 3, the connection function initializes the WiFi module of the ESP32 from the method **WiFi.mode(WIFI_STA)**, which defines that the module will perform in STATION mode. Then, the **WiFi.begin(ssid, pswd)** start the connection attempt. In the following, the while command prints the loading symbol (" #") to ilustrate the connection attempt while the status **(WiFi.status)** is different of the **WL_CONNECTED**. And if-else command defines when the connection is reached, printing the success message with the IP assigned for the ESP32 or fail message in case of **WiFi.status()** different of **WL_CONNECTED**.

In following, the **setup()** and **loop()** are described. First, the setup function has two parts, been the first in Image 3 ilustrated by the red part (definition of pin used, dht methods and the call of the connection function). In second, the blue part describes the behavior of the server, which uses the method "on" to define the routes and the "send" method to represent the HTTP requests. In this case, the root route is defined as **"/"**, the data sensor routes defined as **"/sensor"** can be **"/sensor/temp"** and **"/senor/humi"** as subroutes. For LEDs, were used **"ledR/on"** and **"ledR/off"** for activating and deactivating the red LED, while **"ledG"** was used for the green LED with the same subroute, respectively.

<img src="https://github.com/miguelneto0/Reactjs_ESP32/blob/main/images/code_part3.png"  width="600">
<p align = "left"><sup>Image 4</sup></p>

Finishing the ESP32 programming, the **loop()** function basically executes the function that manages the requests of each client that accesses the server, through the **server.handleClient()** method. In addition, some tests are performed to check the status of the board.

  ## Mobile APP with ReactJS and Expo
  
Now, for implementing the Mobile Application, was used the **React JS** with **Expo** (an open-source platform for building web and mobile apps). In this way, it is needed to install the **Node.js**, from at this point to install **Yarn** and **Expo**, via terminal or cmd prompt, as follow:
- _<pre><code>npm install -g yarn_</code></pre>
- <pre><code>_npm install --global expo-cli_</code></pre>

Thus, after these steps, chose a folder to create the application project, for example, if you create a folder named "mobileApp", you must enter in this folder and run the following command:
  - <code>_expo init mobileApp_</code>

  In this way, a structure will be created containing all resources for running the app. This structure can be observed on the left side of the Image 4 below. In addition, for running the app we have using the command:

  - <code>_expo start mobileApp_</code>

This command will open a page with localhost in the 19002 port, that allows we monitoring the status and behavior of the app. In the smartphone, we can download the Expo application and scan the QR code for running the app and in the web browser can access the web version from the option **Run in web browser** at the left side.

<img src="https://github.com/miguelneto0/Reactjs_ESP32/blob/main/images/codeApp_part1.png"  width="540">
<p align = "left"><sup>Image 5</sup></p>

As observed, inside of the structure we have a JavaScript file named **App.js**, which is the unique file modified for this project. The first part of the code of App.js shows the libraries imported for this project, such as **MaterialIcons**, for application icons; **Switch**, for LED buttons; **TouchableOpacity**, for buttons and label of sensed data; **Axios**, for magement of the request and response messages on HTTP protocol; and others. In addition, the interval of lines 8-29 presents the definition of the behavior of the red LED from the route identified from the IP of the ESP32, in this case, **192.168.1.29**.

Finally, the remainder of the code consists of the all routes statement and the visual application is described in the return of the App function, which have View tags and Text tags that will to design the mobile application like the Image 5-7 below.

<img src="https://github.com/miguelneto0/Reactjs_ESP32/blob/main/images/codeApp_part2.png"  height="280"> <img src="https://github.com/miguelneto0/Reactjs_ESP32/blob/main/images/codeApp_part3.png"  height="280">
<p align = "left"><sup>Image 6 and Image 7</sup></p>

The result of the project is shown in the animation in Image 8:

Enjoy this project.
