#include <ESP8266WiFi.h>
#include <ESP8266WiFiMesh.h>

unsigned int request_i = 0;

String manageRequest(String request);

/* Create the mesh node object */
ESP8266WiFiMesh mesh_node = ESP8266WiFiMesh(ESP.getChipId(), manageRequest);

void setup() {
  Serial.begin(115200);
  
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(D2, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  
  delay(10);

  Serial.println("Setting up mesh node...");

  /* Initialise the mesh node */
  mesh_node.begin();
}

void loop() {
  mesh_node.acceptRequest();
  //read the pushbutton value into a variable
  int sensorVal = digitalRead(D2);

  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  if (sensorVal == HIGH) {
    digitalWrite(LED_BUILTIN, LOW);
    
  } else {
    Serial.println("CLICK");
    digitalWrite(LED_BUILTIN, HIGH);
    
    /* Scan for other nodes and send them a message */
    char request[60];
    sprintf(request, "Hello world request #%d from Mesh_Node%d.", request_i++, ESP.getChipId());
    mesh_node.attemptScan(request);
  }

}
