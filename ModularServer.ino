

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include "Page_Configuration.h"

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
    if (req.indexOf("/gpio/0") != -1){
      val = 0;
      // Prepare the response
    String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
    s += (val)?"high":"low";
    s += "</html>\n";

    // Send the response to the client
    client.print(s);
    }
    else if (req.indexOf("/gpio/1") != -1){
      val = 1;
      // Prepare the response
    String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
    s += (val)?"high":"low";
    s += "</html>\n";

    // Send the response to the client
    client.print(s);
    }
    else if (req.indexOf("/modulename") != -1){
      client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nmodule{\r\ntype:relay\r\n}\n</html>\n"); 
      
    }else if (req.indexOf("/image") != -1){
      client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>");

      client.print(" <img src=\"https://siluxmedia.files.wordpress.com/2014/04/img_20140409_165718.jpg\" alt=\"arduino\" height=\"612\" width=\"816\"> ");
      
      client.print("</html>");   
  }
    else if (req.indexOf("/slider-input") != -1){
      client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>");

      //first slider
      client.print("<form method=get><br>Red:  <input type='range' min='1' max='100' name=redVal value=redTemp oninput='showValue(this.value)'>");
      client.println("<span id='range'>0</span>");
      client.println("<script type='text/javascript'>\r\nfunction showValue(newValue)\r\n{\r\ndocument.getElementById('range').innerHTML=newValue;\r\n}\r\n</script>\r\n");

      //second slider
      client.print("<br><br>Green:  <input type='range' min='1' max='100' name=greVal value=greTemp oninput='showValue1(this.value)'>");
      client.println("<span id='range1'>0</span>");
      client.println("<script type='text/javascript'>\r\nfunction showValue1(newValue)\r\n{\r\ndocument.getElementById('range1').innerHTML=newValue;\r\n}\r\n</script>\r\n");
      
      //third slider
      client.print("<br><br>Blue:  <input type='range' min='1' max='100' name=bluVal value=bluTemp oninput='showValue2(this.value)'>");
      client.println("<span id='range2'>0</span>");
      client.println("<script type='text/javascript'>\r\nfunction showValue2(newValue)\r\n{\r\ndocument.getElementById('range2').innerHTML=newValue;\r\n}\r\n</script>\r\n");
      
      client.println("&nbsp;<br><br><input name=H type=submit value=submit><br><br>");  //</form>
      client.println("</form>");
      client.println("<script type='text/javascript'></script>\r\n");
      client.print("</html>");   
  }else {
      Serial.println("invalid request");
      client.stop();
      return;
    }

    // Set GPIO2 according to the request
    digitalWrite(2, val);
  
    client.flush();

    
    delay(1);
    Serial.println("Client disconnected");
  }

}
