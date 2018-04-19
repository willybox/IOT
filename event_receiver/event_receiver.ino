#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMesh.h>
#include "Gsender.h"

const char* ssid = "AndroidAPes";
const char* password = "2310572207";
String manageRequest(String request);

/* Create the mesh node object */
ESP8266WiFiMesh mesh_node = ESP8266WiFiMesh(ESP.getChipId(), manageRequest);

void setup() {
  Serial.begin(115200);
  delay(10);
  
  pinMode(LED_BUILTIN, OUTPUT);
 
  WiFi.begin(ssid, password);   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
  
  Serial.println("Setting up mesh node...");

  /* Initialise the mesh node */
  mesh_node.begin();
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  /* Accept any incoming connections */
  mesh_node.acceptRequest();

  /* Scan for other nodes and send them a message */
  //char request[60];
  //sprintf(request, "Hello world request from Mesh_Node%d.", ESP.getChipId());
  //mesh_node.attemptScan(request);
  //delay(1000);
}

void postData(){
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance
    String subject = "Alerte!";
    if(gsender->Subject(subject)->Send("jordan.dahbi@gmail.com", "Une intrusion a été détectée")) {
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

