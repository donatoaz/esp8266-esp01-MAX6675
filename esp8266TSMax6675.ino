/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

#include "max6675.h"

float setpoint = 3.0;

int thermoDO = 3;
int thermoCS = 2;
int thermoCLK = 0;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

const char* ssid     = "your ssid";
const char* password = "your passwd";
String apiKey = "your thingspeak api key";

const char* host = "api.thingspeak.com";

void setup() {
  //Serial.begin(115200);
  //delay(100);

  // We start by connecting to a WiFi network

  //Serial.println();
  //Serial.println();
  //Serial.print("Connecting to ");
  //Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }

  //Serial.println("");
  //Serial.println("WiFi connected");  
  //Serial.println("IP address: ");
  //Serial.println(WiFi.localIP());

  pinMode(3, OUTPUT);
  pinMode(1, OUTPUT);
}

int value = 0;

void loop() {
  delay(5000);
  ++value;

  //Serial.print("connecting to ");
  //Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    //Serial.println("connection failed");
    return;
  }

  float tempMeasurement = thermocouple.readCelsius();
  String temp = String(tempMeasurement);
  String sp = String(setpoint);
  
  String url = "/update?key=";
  url += apiKey;
  url += "&field1=";
  url += temp;
  url += "&field2=";
  url += sp;
  
  //Serial.print("Requesting URL: ");
  //Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

  
  /*
  // We now create a URI for the request
  String url = "/input/";
  url += streamId;
  url += "?private_key=";
  url += privateKey;
  url += "&value=";
  url += value;
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  */
  
  delay(10);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    //Serial.print(line);
  }
  
  //Serial.println();
  //Serial.println("closing connection");

  // delays 5 secs
  delay(2500);
  delay(2500);
}

