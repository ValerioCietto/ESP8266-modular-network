/*
*scan available networks
*connect to a known network if available
*
*
*This code can be applied if i have more known networks(home, work and friend's home for example),
*and want the module to connect just with the strongest known network.
*/

#include "ESP8266WiFi.h"

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"no encryption found");
      delay(10);
    }
  }
  Serial.println("");
  n = WiFi.scanNetworks();
  Serial.println(n);
  Serial.println("ricerca SSID named wifi");
  for (int i =0; i<n; i++){
    Serial.println(i);
    Serial.println(WiFi.SSID(i));
    
    if(strcmp(WiFi.SSID(i), "wifi") == 0){
      Serial.println("wifi c'è!");
      WiFi.begin("wifi", "wifidicasa1111");//not my real password :P
  
      while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      }
      Serial.println("");
      Serial.println("WiFi connected");

      server.begin();
      Serial.println("Server started");

      // Print the IP address
      Serial.println(WiFi.localIP());
    }
    else{
      Serial.println("no wifi");
    }
  }

}

void loop() {
  if(WiFi.status() == WL_CONNECTED){
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client) {
      return;
    }
  
    // Wait until the client sends some data
    Serial.println("new client");
    while(!client.available()){
      delay(1);
    }
  
    // Read the first line of the request
    String req = client.readStringUntil('\r');
    Serial.println(req);
    client.flush();
  
    // Match the request
    int val;
    if (req.indexOf("/gpio/0") != -1)
      val = 0;
    else if (req.indexOf("/gpio/1") != -1)
      val = 1;
    else {
      Serial.println("invalid request");
      client.stop();
      return;
    }

    // Set GPIO2 according to the request
    digitalWrite(2, val);
  
    client.flush();

    // Prepare the response
    String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
    s += (val)?"high":"low";
    s += "</html>\n";

    // Send the response to the client
    client.print(s);
    delay(1);
    Serial.println("Client disonnected");
  }

}
