

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

const char *ssid1 = "RSSIserver";
const char *password1 = "admin111";

WiFiServer server(80);
// multicast DNS responder
MDNSResponder mdns;


String retiDisponibili[6];
int segnaleReti[6];

void setup() {
 
  
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

  delay(1000);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  
  Serial.begin(115200);
  EEPROM.begin(512);
  
  
 

  
  // read eeprom for ssid and pass
  Serial.println("Reading EEPROM ssid");
  String esid;
  for (int i = 0; i < 32; ++i)
    {
      esid += char(EEPROM.read(i));
    }
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");
  String epass = "";
  for (int i = 32; i < 96; ++i)
    {
      epass += char(EEPROM.read(i));
    }
  Serial.print("PASS: ");
  Serial.println(epass);
  if ( esid.length() > 1 ) {
    Serial.println("network configuration exists read");
    
  }
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
  
  Serial.println("ricerca SSID named wifi");
  boolean wifiConnected= false;
  for (int i =0; i<6;i++){
    if(n<6){
      retiDisponibili[i]=WiFi.SSID(i);
      segnaleReti[i]=WiFi.RSSI(i);
    }
  }
  for (int i =0; i<n; i++){
    Serial.println(i);
    Serial.println(WiFi.SSID(i));
    
    if(strcmp(WiFi.SSID(i), "siluxmedia@gmail.com") == 0){
     
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
      wifiConnected=true;
    }
    
    else if(strcmp(WiFi.SSID(i), "FABLAB_TORINO") == 0){
     
      WiFi.begin("FABLAB_TORINO", "FablabTorino");
  
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
      wifiConnected=true;
    }
    else{
      
    }
  }
  if(!wifiConnected){
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
  if (!mdns.begin("rssi", WiFi.localIP())) {
    Serial.println("Error setting up MDNS responder!");
    
  }
  else{
    Serial.println("mDNS responder not started");
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
      yield();
    }
  
    // Read the first line of the request
    String req = client.readStringUntil('\r');
    //Serial.println(req);
    client.flush();
  
    // Match the request
    
    if (req.indexOf("/config") != -1){
      //################################################# LOGIN PAGE
      client.println("<!DOCTYPE html><html><head><style>body{background-color:lightgray;text-align:center;}</style></head>");
      client.println("<body><div class=\"popup popup-login modal-in\" style=\"display: block;\">    <div class=\"content-block\"><h4>Login Rete</h4>");
      client.println("<div class=\"loginform\"><form id=\"LoginForm\" method=\"get\"><label>SSID(nome rete):</label><br/>");
      client.println("<input class=\"form_input required\" type=\"text\" value=\"\" name=\"username\"></input><br/><label>Password:</label><br/>");
      client.println("<input class=\"form_input required\" type=\"password\" value=\"\" name=\"password\"></input><br/>");
      client.println(""+random(1, 1000));
      client.println("<input id=\"submit\" class=\"form_submit\" type=\"submit\" value=\"Login\" name=\"submit\"></input></form></div>");
      client.println("<div class=\"close_popup_button_gray\"></div></div></div></body></html>");

      String param1 = "username";
      String param2 = "password";
      
      String parametro1 = req.substring(req.indexOf(param1)+1+param1.length(), req.indexOf(param2)-1);
      String parametro2 = req.substring(req.indexOf(param2)+1+param2.length(), req.length()-22);
      String loginSSID= ""+parametro1;
      String loginPass= ""+parametro2;
      Serial.println(loginSSID);
      Serial.println(loginPass);
      client.stop();
      client.flush();
      if(parametro1!=""){
        Serial.println("scrivo!");
        for (int i = 0 ; i < 512; i++) {
          EEPROM.write(i, 0);
        }
        EEPROM.put(0,loginSSID);
        EEPROM.put(32,loginPass);
        //WiFi.disconnect();
        //WiFi.begin(loginSSID, loginPass);
      }
    }
    else if (req.indexOf("/read") != -1){
      //################################################# read eeprom
      int addr =0;
  
 

  client.println("<!DOCTYPE html><html><head><style>body{background-color:lightgray;text-align:center;}</style></head><body>");
  // read eeprom for ssid and pass
  Serial.println("Reading EEPROM ssid");
  String esid;
  for (int i = 0; i < 32; ++i)
    {
      esid += char(EEPROM.read(i));
    }
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");
  String epass = "";
  for (int i = 32; i < 96; ++i)
    {
      epass += char(EEPROM.read(i));
    }
  Serial.print("PASS: ");
  Serial.println(epass);
  if ( esid.length() > 1 ) {
    Serial.println("network configuration exists read");
    
  }
      client.println(esid);
      client.println(epass);
 client.println("</body></html>");
      
      client.stop();
      client.flush();
      
    }
    /*
    }else {
      //INDEX PAGE
      client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>");
      int n1 = WiFi.scanNetworks();
      
      client.println(WiFi.localIP());
    
        for (int i = 0; i < n1 ; ++i){
      // Print SSID and RSSI for each network found
      client.print(i + 1);
      client.print(": ");
      client.print(WiFi.SSID(i));
      client.print(" (");
      client.print(WiFi.RSSI(i));
      client.print(")");
      client.print((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"no encryption found");
      client.print("<br>");
      
    
       }
      for(int i =0; i<6;i++){
        
        client.print(retiDisponibili[i]);
        client.print(" ");
        client.println(segnaleReti[i]);
        client.println("<br>");
        
      }
      
      client.print("</html>");
      
      client.stop();
      client.flush();
      return;
    }
    */

    
    
  
  }

}
