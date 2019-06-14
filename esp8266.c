#include <ESP8266WiFi.h>
#include <WiFiClient.h>
 
  const char* ssid = "GP24588273"; //Your Wifi name (SSID)
  const char* password = "goprohero"; //Your WiFi password
 
//Do not modify below this line//
const char* host = "10.5.5.9"; //GoPro Hero 4 IP Address
 
//Create variables for 1 channels (can be modified for multiple channels)

int triggerPin = 0; //Input pin
int pinState;
int lastState;
int pressTimer = 0;
int triggerState = 0;
int lastTriggerState = 0;

void setup()
{
  //Start communication to serial port
  Serial.begin(115200);
  delay(100);
  pinMode(triggerPin, INPUT);
 
  //Wifi Connect
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void RequestGoProURL(String GoProURL)
{
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort))
  {
    Serial.println("connection failed");
    return;
  }
  //String url = "/gp/gpControl/command/mode?p=1";
  client.print(String("GET ") + GoProURL + " HTTP/1.1\r\n" +
  "Host: " + host + "\r\n" +
  "Connection: close\r\n\r\n");
  return;
}
 
 
void loop()
{
  // Read trigger state
  pinState = digitalRead(triggerPin);
  if (pinState == HIGH) { triggerState = 0; } else
  {
    triggerState = 1;
    pressTimer = pressTimer + 1;
  }
   
   if (triggerState != lastTriggerState)
  {
    if (triggerState == 1)
    {
      if (pressTimer == 1)
      {
        RequestGoProURL("/gp/gpControl/command/shutter?p=1");
      }
      pressTimer = 0;
    }
    if (triggerState == 1)
    delay(1000);
    triggerState = 0;
    }
 }