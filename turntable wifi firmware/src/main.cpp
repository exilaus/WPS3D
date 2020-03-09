#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Stepper.h>
using namespace std;

// ESP-12F(WeMos D1 mini)
#define IN1 14 //GPIO 14
#define IN2 12 //GPIO 12
#define IN3 13 //GPIO 13
#define IN4 15 //GPIO 15
Stepper stepper(2048, IN4, IN2, IN3, IN1);
//////////////////////
// WiFi Definitions //
//////////////////////
const char WiFiAPPSK[] = "scanner12123";

/////////////////////
// Pin Definitions //
/////////////////////


WiFiServer server(80);

void setup() 
{
 Serial.begin(115200);
  Serial.println("Starting...");
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ttable", WiFiAPPSK);
  server.begin();
  stepper.setSpeed(10);
  
}


const int NBSTEPS = 4095;

int Step = 0;


    

void loop() 
{ yield();
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
yield();
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
yield();
  // Match the request
  int val = -1; // We'll use 'val' to keep track of both the
                // request type (read/set) and value if set.
  if (req.indexOf("/move") != -1) {
       for (int x=0;x<=req.substring(req.indexOf("?")+1).toInt();x++){
       stepper.step(1);
       yield();
       } }
  if (req.indexOf("/off") != -1)  {
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,LOW);
          }
  client.flush();
  delay(20);
  yield();

  // Prepare the response. Start with the common header:
  String s = "HTTP/1.1 200 OK\r\n";
  s += "Content-Type: text/html\r\n\r\n";
  s += "<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "move stepper";
  s+= req.substring(req.indexOf("?")+1);
  s += "</html>\n";
  
  // Send the response to the client
  client.print(s);
  delay(20);
  yield();
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}






