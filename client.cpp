#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
  
// Set WiFi credentials
#define WIFI_SSID "TheOtherESP"
#define WIFI_PASS "flashmeifyoucan"
#define RIGHT_MOTOR_PIN1  D8             
#define RIGHT_MOTOR_PIN2  D7                 
#define LEFT_MOTOR_PIN1   D6                  
#define LEFT_MOTOR_PIN2   D5                
#define RIGHT_MOTOR_SPEED 1023                
#define LEFT_MOTOR_SPEED  1023 
 
// UDP
WiFiUDP UDP;
IPAddress remote_IP(192,168,4,1);
#define UDP_PORT 4210
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
IPAddress gateway(192, 168, 100, 1);          //IP for AP mode
IPAddress subnet(255, 255, 255, 0);           //IP for AP mode
ESP8266WebServer server(80);

int car_mode = 0;                             // set car drive mode (0 = stop)

 
void setup() {

  pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
  pinMode(LEFT_MOTOR_PIN1, OUTPUT);
  pinMode(LEFT_MOTOR_PIN2, OUTPUT);
  // Setup IO
  pinMode(2, OUTPUT);
   
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
  
  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  WiFi.mode(WIFI_STA);
  
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  
  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
 
      
// Begin UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Opening UDP port ");
  Serial.println(UDP_PORT);
      
  
}
  
void loop() {
  
char buttonState = HIGH;
 
  // Send Packet
  UDP.beginPacket(remote_IP, UDP_PORT);
  UDP.write(buttonState);
  UDP.endPacket();
  delay(100);

   
}