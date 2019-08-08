/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "Topio";

int status = WL_IDLE_STATUS;

WiFiServer server(2323);

void setup() 
{
   Serial.begin(115200);
   Serial.println();
   Serial.print("Configuring access point...");
   WiFi.softAP(ssid);
//delay(10000);
   IPAddress myIP = WiFi.softAPIP();
   Serial.print("AP IP address: ");
   Serial.println(myIP);

   Serial.println("\nStarting server...");
  // start the server:
  server.begin();
}




WiFiClient client;
void loop() 
{
 WiFiClient client = server.available(); 
  while(client.available()){
    delay(1000);
  char c = client.read();
  Serial.print(c);
    }
  client.stop();
}
