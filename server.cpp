#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
 
// Set AP credentials
#define AP_SSID "TheOtherESP"
#define AP_PASS "flashmeifyoucan"
#define RIGHT_MOTOR_PIN1  D8           
#define RIGHT_MOTOR_PIN2  D7                  
#define LEFT_MOTOR_PIN1   D6                  
#define LEFT_MOTOR_PIN2   D5                
#define RIGHT_MOTOR_SPEED 1023                
#define LEFT_MOTOR_SPEED  1023
#define LED_PIN           2  
 
// UDP
WiFiUDP UDP;
IPAddress local_IP(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);
#define UDP_PORT 4210
 int t=0;
  char buttonState = HIGH;
// UDP Buffer
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];

ESP8266WebServer server(80);

int car_mode = 0;                             // set car drive mode (0 = stop)

 
void setup() {

 pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
  pinMode(LEFT_MOTOR_PIN1, OUTPUT);
  pinMode(LEFT_MOTOR_PIN2, OUTPUT);
  // Setup LED pin
  pinMode(2, OUTPUT);
   car_control(); // stop the car 
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
 
  // Begin Access Point
  Serial.println("Starting access point...");
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.println(WiFi.localIP());

  // setup web server to handle specific HTTP requests
  server.on("/", HTTP_GET, handle_OnConnect);
  server.on("/forward", HTTP_GET, handle_forward);
  server.on("/backward", HTTP_GET, handle_backward);
  server.on("/left", HTTP_GET, handle_left);
  server.on("/right", HTTP_GET, handle_right);
  server.on("/stop", HTTP_GET, handle_stop);
  server.onNotFound(handle_NotFound);

  //start server
  server.begin();
  Serial.println("ESP8266 car server started.");
  digitalWrite(LED_PIN, LOW);
 
  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);
  
 
}
 
void loop() {
  
  server.handleClient();
  car_control();   
  // Send Packet
  UDP.beginPacket(local_IP, UDP_PORT);
  UDP.write(buttonState);
  UDP.endPacket();
  delay(100);

} 

// HTTP request: on connect
void handle_OnConnect() {
  car_mode = 0;
  Serial.println("Client connected");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: stop car
void handle_stop() {
  car_mode = 0;
  Serial.println("Stopped");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: go forward
void handle_forward() {
  car_mode = 1;
  Serial.println("Go forward...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: go backward
void handle_backward() {
  car_mode = 2;
  Serial.println("Go backward...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: turn left
void handle_left() {
  car_mode = 3;
  Serial.println("Turn left...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: turn right
void handle_right() {
  car_mode = 4;
  Serial.println("Turn right...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: other
void handle_NotFound() {
  car_mode = 0;
  Serial.println("Page error");
  server.send(404, "text/plain", "Not found");
}

// control car movement
void car_control() {
  switch (car_mode) {
    case 0: // stop car
      digitalWrite(RIGHT_MOTOR_PIN1, LOW);
      digitalWrite(RIGHT_MOTOR_PIN2, LOW);
      digitalWrite(LEFT_MOTOR_PIN1, LOW);
      digitalWrite(LEFT_MOTOR_PIN2, LOW);
      break;
    case 1: // go forward
      analogWrite(RIGHT_MOTOR_PIN1, RIGHT_MOTOR_SPEED);
      digitalWrite(RIGHT_MOTOR_PIN2, LOW);
      analogWrite(LEFT_MOTOR_PIN1, LEFT_MOTOR_SPEED);
      digitalWrite(LEFT_MOTOR_PIN2, LOW);
      break;
    case 2: // go backward
      digitalWrite(RIGHT_MOTOR_PIN1, LOW);
      analogWrite(RIGHT_MOTOR_PIN2, RIGHT_MOTOR_SPEED);
      digitalWrite(LEFT_MOTOR_PIN1, LOW);
      analogWrite(LEFT_MOTOR_PIN2, LEFT_MOTOR_SPEED);
      break;
    case 3: // turn left
      analogWrite(RIGHT_MOTOR_PIN1, RIGHT_MOTOR_SPEED);
      digitalWrite(RIGHT_MOTOR_PIN2, LOW);
      digitalWrite(LEFT_MOTOR_PIN1, LOW);
      analogWrite(LEFT_MOTOR_PIN2, LEFT_MOTOR_SPEED);
      break;
    case 4: // turn right
      digitalWrite(RIGHT_MOTOR_PIN1, LOW);
      analogWrite(RIGHT_MOTOR_PIN2, RIGHT_MOTOR_SPEED);
      analogWrite(LEFT_MOTOR_PIN1, LEFT_MOTOR_SPEED);
      digitalWrite(LEFT_MOTOR_PIN2, LOW);

  }
}

// output HTML web page for user
String SendHTML() {
  String html = "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";
  html += "<title>ESP8266 WiFi Car</title>";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<style>body {background-color: Moccasin;} h1 {color: SaddleBrown;} h2 {color: Olive;}</style>";
  html += "</head>";
  html += "<body>";
  html += "<div align=\"center\">";
  html += "<h1>ESP8266 WiFi Car</h1>";
  html += "<h2>Press \"stop\" after the server has been reset</h2>";
  html += "<br>\n";
  html += "<form method=\"GET\">";
  html += "<input type=\"button\" value=\"Go forward\" onclick=\"window.location.href='/forward'\">";
  html += "<br><br>\n";
  html += "<input type=\"button\" value=\"Go backward\" onclick=\"window.location.href='/backward'\">";
  html += "<br><br>\n";
  html += "<input type=\"button\" value=\"Turn left\" onclick=\"window.location.href='/left'\">";
  html += "<br><br>\n";
  html += "<input type=\"button\" value=\"Turn right\" onclick=\"window.location.href='/right'\">";
  html += "<br><br>\n";
  html += "<input type=\"button\" value=\"Car stop\" onclick=\"window.location.href='/stop'\">";
  html += "</form>\n";
  html += "</div>\n";
  html += "</body>\n";
  html += "</html>\n";
  return html;