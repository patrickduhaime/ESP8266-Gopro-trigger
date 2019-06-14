#include <ESP8266WiFi.h>
#include <WiFiClient.h>
 
  const char* gopro_ssid = "GP24588273"; //Your Wifi name (SSID)
  const char* gopro_password = "goprohero"; //Your WiFi password
 
//Do not modify below this line//
const char* gopro_host = "10.5.5.9"; //GoPro Hero 4 IP Address
 
//Create variables for 1 GPIO (can be modified for multiple GPIO)

int triggerPin = 0; //Input pin
int pinState;
int triggerState = 0;

void setup()
{
  //Start communication to serial port
  Serial.begin(115200);
  delay(100);
  pinMode(triggerPin, INPUT_PULLUP);
 
  //Wifi Connect to GoPro
  Serial.print("Connecting to ");
  Serial.println(gopro_ssid);
  WiFi.begin(gopro_ssid, gopro_password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected to GoPro");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  //put gopro into appropriate photo mode
  
  //Primary mode: PHOTO
  RequestGoProURL("/gp/gpControl/command/mode?p=1");
  delay(500);
  //Secondary mode: Single(PHOTO)
  RequestGoProURL("/gp/gpControl/command/sub_mode?mode=1&sub_mode=0");
  delay(500);
  //Photo resolution for Photo Modes (incl. SubModes): 12MP Wide:
  RequestGoProURL("/gp/gpControl/setting/17/0");
  delay(500);
  //See other settings you would like to ajust at: https://github.com/KonradIT/goprowifihack/blob/master/HERO4/WifiCommands.md
}
 
void RequestGoProURL(String GoProURL)
{
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(gopro_host, httpPort))
  {
    Serial.println("connection failed");
    return;
  }
  //String url = "/gp/gpControl/command/mode?p=1";
  client.print(String("GET ") + GoProURL + " HTTP/1.1\r\n" +
  "Host: " + gopro_host + "\r\n" +
  "Connection to Gopro: closed\r\n\r\n");
  return;
}
 
 
void loop()
{
  // Read trigger state
  pinState = digitalRead(triggerPin);
  if (pinState == LOW) 
  { 
    RequestGoProURL("/gp/gpControl/command/shutter?p=1");
    delay(1000);
  }
}