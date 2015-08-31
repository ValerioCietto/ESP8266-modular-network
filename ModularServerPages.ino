

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include "Page_Configuration.h"
const char *ssid1 = "Hi";
const char *password1 = "12345678";
ESP8266WebServer server(80);
// multicast DNS responder
MDNSResponder mdns;

void sendPage(){
  //helloPage
  server.send(200,"text/html",PAGE_NetworkConfiguration);
}
void sendImage(){
  //retrieve image from siluxmedia wordpress
  //server.send(200,"text/html",PAGE_Image);
}
void sendButton(){
  //server.send(200,"text/html",PAGE_Button);
}
void sendIndex(){
  server.send(200,"text/html",PAGE_Index);
}
void sendSlider(){
  server.send(200,"text/html",PAGE_Slider);
}
void sendModuleName(){
  server.send(200,"text/html",PAGE_ModuleName);
}

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
    
    if(strcmp(WiFi.SSID(i), "Primula") == 0){
     
      WiFi.begin("Primula", "tacchina97");
  
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
    else if(strcmp(WiFi.SSID(i), "wifi") == 0){
     
      WiFi.begin("wifi", "wifidicasa1");
  
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
      server.begin();
      Serial.println("HTTP server started");
    }
    else if(strcmp(WiFi.SSID(i), "wifi") == 0){
     
      WiFi.begin("siluxmedia@gmail.com", "therobot");
  
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
      server.begin();
      Serial.println("HTTP server started");
    }
    else if(strcmp(WiFi.SSID(i), "Hotel florida") == 0){
     
      WiFi.begin("Hotel florida", "12Flo");
  
      while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
      }
      Serial.println("");
      Serial.println("WiFi connected");

      server.begin();
      Serial.println("Server started");

      // Print the IP address
      Serial.println(WiFi.localIP());
      server.begin();
      Serial.println("HTTP server started");
    }
    else{
      Serial.println("no wifi");
    }
  }
  if(WiFi.status() == WL_CONNECTED){
    
  }
  else{
    Serial.println("init soft AP");
    WiFi.softAP(ssid1, password1);
    //while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
    Serial.println("done");
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.begin();
    Serial.println("Server started");
    
  }
  if (!mdns.begin("robot", WiFi.localIP())) {
    Serial.println("Error setting up MDNS responder!");
    while(1) { 
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  digitalWrite(14,HIGH);
  delay(1000);
  digitalWrite(14,LOW);
  server.on("/", sendPage);
  server.on("/image", sendImage);
  server.on("/modulename", sendModuleName);
  server.on("/index", sendIndex);
  server.on("/slider-input", sendSlider);
  server.on("/button", sendButton);
}

void loop() {
  if(WiFi.status() == WL_CONNECTED){
    server.handleClient();
  
    
  }

}
