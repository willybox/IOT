#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMesh.h>
#include "Gsender.h"

const char* ssid = "SSID";
const char* password = "PASSWORD";
const char* mail = "xxx@xxx.xxx";

int toSend = 0;

String manageRequest(String request);

/* Create the mesh node object */
ESP8266WiFiMesh mesh_node = ESP8266WiFiMesh(ESP.getChipId(), manageRequest);

/**
   Callback for when other nodes send you data

   @request The string received from another node in the mesh
   @returns The string to send back to the other node
*/
String manageRequest(String request) {
  
  /* Print out received message */
  Serial.print("received: ");
  Serial.println(request);

  /* return a string to send back */
  char response[60];
  sprintf(response, "OK");
  aEnvoyer = 1;
  return response;
}

void setup() {
  Serial.begin(115200);
  delay(10);
  
  pinMode(LED_BUILTIN, OUTPUT);

  /* Initialise the mesh node */
  mesh_node.begin();
 
  Serial.println();
  Serial.println();
  WiFi.begin(ssid, password);   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
  
  Serial.println("Setting up mesh node...");

  
}

void loop() {
  if(toSend){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    postData();
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    toSend = 0;
  }
  digitalWrite(LED_BUILTIN, LOW);
  /* Accept any incoming connections */
  mesh_node.acceptRequest();
}

void postData(){
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "Alert!";
    if(gsender->Subject(subject)->Send(mail, "Intrusion detected !!")) {
        Serial.println("Message send.");
    } else {
        Serial.print("Error sending message: ");
        Serial.println(gsender->getError());
    }
   
 }
 else{
    Serial.println("Error in WiFi connection");   
 }
}
