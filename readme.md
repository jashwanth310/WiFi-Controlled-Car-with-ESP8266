# WiFi-Controlled Car with ESP8266

This project allows you to control a car wirelessly using WiFi, using an ESP8266 microcontroller as the brain of the car. The system consists of a client code running on the car and a server code running on a separate device, such as a computer or smartphone. The server code provides a web-based interface for sending commands to control the car's movements.

## Features

- Control the car's movements remotely: The server provides a web page where you can send commands to control the car. You can make it go forward, backward, turn left, turn right, or stop.
- Real-time communication: The client and server communicate using UDP (User Datagram Protocol) for fast and responsive control of the car.
- Easy setup: The client connects to an existing WiFi network using provided credentials, and the server creates its own access point, making it simple to establish a connection between the two.

## Hardware Requirements

To build and run this project, you will need the following components:

- ESP8266-based microcontroller board
- Motor driver board or H-bridge module
- DC motors for the car's propulsion
- Power supply for the motors and the ESP8266 board
- WiFi-enabled device (computer or smartphone) to host the server code

## Installation and Usage

1. Set up the ESP8266 client:
   - Install the necessary libraries (ESP8266WiFi, WiFiUdp, ESP8266WebServer) in your Arduino IDE.
   - Open the client code in the Arduino IDE and upload it to the ESP8266 board.
   - Modify the WiFi credentials (SSID and password) in the client code to match your network.

2. Set up the server:
   - Ensure you have the necessary libraries (ESP8266WiFi, WiFiUdp, ESP8266WebServer) installed in your Arduino IDE.
   - Open the server code in the Arduino IDE and upload it to a WiFi-enabled device.
   - Connect the WiFi-enabled device to the power supply.

3. Connect the hardware:
   - Connect the motors to the motor driver board or H-bridge module.
   - Connect the motor driver board to the ESP8266 board following the pin configuration in the code.

4. Control the car:
   - Once the server code is running, it will create a WiFi access point with the SSID and password specified in the code.
   - Connect your computer or smartphone to the access point created by the server.
   - Open a web browser and enter the IP address displayed on the server's serial monitor.
   - You should see a web page with control buttons for the car. Click on the buttons to send commands and control the car's movements.

## License

This project is licensed under the [MIT License](LICENSE). Feel free to modify and distribute it according to your needs.

## Acknowledgments

This project was inspired by the growing field of IoT and the need for wireless control of devices. It makes use of the ESP8266 microcontroller and various open-source libraries that have made WiFi connectivity and web server capabilities accessible to hobbyists and developers alike.