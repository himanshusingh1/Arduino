// Create a WiFi access point and provide a web server on it. */
// For more details see http://42bots.com.


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress    apIP(1, 1, 1, 1);  // Defining a static IP address: local & gateway
                                    // Default IP in AP mode is 192.168.4.1

/* This are the WiFi access point settings. Update them to your likin */
const char *ssid = "PLANT";

// Define a web server at port 80 for HTTP
ESP8266WebServer server(8080);





void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");
  //set-up the custom IP address
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00  
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  WiFiClient client = server.client();
  
  if (client) {
    if(client.connected())
    {
      Serial.println("Client Connected");
    }
    
    while(client.connected()){      
      while(client.available()>0){
        // read data from the connected client
        Serial.write(client.read()); 
      }
      //Send Data to connected client
      while(Serial.available()>0)
      {
        client.write(Serial.read());
      }
    }
    client.stop();
    Serial.println("Client disconnected");    
  }
}
