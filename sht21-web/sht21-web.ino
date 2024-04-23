/*
    This sketch demonstrates how to set up a simple HTTP-like server.
    The server will read data from the SHT21 sensor and show it in the root page

    server_ip is the IP address of the ESP8266 module. In many modems can place a Static IP attached to the MAC address of the ESP
*/
#include <Wire.h>
#include "SHT21.h"
#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "SSID"
#define STAPSK "SSID_PASS"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

SHT21 SHT21;
// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

float temp;
float hum;

void setup() {
  Wire.begin(0,2);  //0=SDA(GPIO0)(PIN 5);; 2=SCL(GPIO2)(PIN3)
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }

  // Start the server
  server.begin();

}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.accept();
  if (!client) { return; }
  hum = SHT21.getHumidity();
  temp = SHT21.getTemperature();

  client.setTimeout(1000);  // default is 1000

  // read/ignore the rest of the request
  // do not client.flush(): it is for output only, see below
  while (client.available()) {
    // byte by byte is not very efficient
    client.read();
  }

  // Send the response to the client
  // it is OK for multiple small client.print/write,
  // because nagle algorithm will group them into one single packet
  client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nTEMP & HUM: "));
  client.print(F("<br><br>"));
  client.print("Temperatura: ");
  client.print(temp);
  client.print(" C");
  client.print(F("<br>"));
  client.print("Humedad: ");
  client.print(hum);
  client.print(" %HR");
  client.print(F("<br>"));
  client.print(WiFi.localIP());

}