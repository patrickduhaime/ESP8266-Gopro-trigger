#include <ESP8266WiFi.h>
#include <WiFiClient.h>
 
  const char* gopro_ssid = "GP24588273"; //Your Wifi name (SSID)
  const char* gopro_password = "goprohero"; //Your WiFi password
 
//Do not modify below this line//
const char* gopro_host = "10.5.5.9"; //GoPro Hero 4 IP Address
 
//Create variables for 1GPIO (can be modified for multiple GPIO)

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
  
  /* todo
  1- connect to reach M+ wifi network
  
	See connexion code above
  
  2- synchronize ESP8266 time with Reach M+ time
  
	//todo: research on how to get time from reach M+
  
  3- disconnect from Reach M+ wifi network
  
	WiFi.disconnect();
	
	see:  https://www.arduino.cc/en/Reference/WiFiDisconnect  ( not tested )
	
  4- connect to Gopro wifi network
  
	See connexion code above
  
  5- synchronize  GoPro time with ESP8266 time
	
	http://10.5.5.9/gp/gpControl/command/setup/date_time?p=%11%0b%10%11%29%2c
	The hex string at the end is the same as for HERO3, so in the example: 
	11 = (20)17, 0b = 11 (November), 10 = 16, 11 = 17, 29 = 41, 2c = 44. 
	
	Example bash code for date string, see: https://github.com/ztzhang/GoProWifiCommand/issues/3.

  6- put gopro into appropriate photo mode
  
	Primary PHOTO modes: 			http://10.5.5.9/gp/gpControl/command/mode?p=1
	Secondary Single(PHOTO) modes:  http://10.5.5.9/gp/gpControl/command/sub_mode?mode=1&sub_mode=0
	Photo resolution for Photo Modes (incl. SubModes): 12MP Wide: http://10.5.5.9/gp/gpControl/setting/17/0
	...
	See other settings you would like to ajust at: https://github.com/KonradIT/goprowifihack/blob/master/HERO4/WifiCommands.md
  */
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
	if (pinState == HIGH) { triggerState = 0; } else
	{
		triggerState = 1;
		pressTimer = pressTimer + 1;
	}
   
	if (triggerState == 1 && pressTimer == 1)
	{
		RequestGoProURL("/gp/gpControl/command/shutter?p=1");
		delay(1000);
		triggerState = 0;
		pressTimer = 0;
	}
 }