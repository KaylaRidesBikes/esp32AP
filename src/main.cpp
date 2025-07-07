#include <Arduino.h>
#include <stdio.h>
#include <WiFi.h>

#include <iostream>
#include <string>

#include "config.h"
#include "webpage.h"

WiFiServer server(PORT);
String header;

String state[] = {OFF,OFF,OFF,OFF,OFF};
uint8_t pins[] = {WHITE_OUT, BLUE_OUT, GREEN_OUT, YELLOW_OUT, RED_OUT};
uint8_t pins_size = sizeof(pins)/sizeof(pins[0]);

void setup() {
  Serial.begin(115200);
  //initialize all pins to output mode
  for(int i = 0; i < pins_size; i++){
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }

  Serial.print("Setting AP...");
  WiFi.softAP(SSID, PASSWORD);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP: ");
  Serial.println(IP);
  server.begin();

}

void loop() {
  WiFiClient client = server.available();

  if(client) {
    Serial.println("New Client");
    String currentLine = "";
    while(client.connected()){
      //if bytes need to be read from client
      if(client.available()){
        char c = client.read();
        Serial.write(c);
        header += c;
        if(c == '\n'){
          if(currentLine.length() == 0){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            for(int i = 0; i < pins_size; i++){
              char pinStr[4];
              snprintf(pinStr, 4, "%d", pins[i]);

              if (header.indexOf("GET /" + String(pinStr) + "/on") >= 0) {
                Serial.println("GPIO " + String(pinStr) + " on");
                state[i] = ON;
                digitalWrite(pins[i], HIGH);
              } else if (header.indexOf("GET /" + String(pinStr) + "/off") >= 0) {
                Serial.println("GPIO " + String(pinStr) + " off");
                state[i] = OFF;
                digitalWrite(pins[i], LOW);
              }
            }
            
            // main page data stored in const to reduce
            // println statements
            client.println(PAGE_MAIN);

            for(int i = 0; i < pins_size; i++){
              uint8_t pin = pins[i];
              char buffer[128];

              client.println("<div class=\"pin-block\">");
              snprintf(buffer, sizeof(buffer), "<p>GPIO %d - State %s</p>", pin, state[i]);
              client.println(buffer);
              if (state[i] == OFF) {
                snprintf(buffer, sizeof(buffer), "<a href=\"/%d/on\"><button class=\"button\">ON</button></a>", pin);
              } else {
                snprintf(buffer, sizeof(buffer), "<a href=\"/%d/off\"><button class=\"button button2\">OFF</button></a>", pin);
              }
              client.println(buffer); 
              client.println("</div>");
            }
            client.println("</div></body></html>\n");
            break;
          } else {
            currentLine = "";
          }  
        } else if (c != '\r'){
          currentLine += c;
        }
      }
    }
  }
  header = "";
  // Close the connection
  client.stop();
  //Serial.println("Client disconnected.");
  //Serial.println("");
}