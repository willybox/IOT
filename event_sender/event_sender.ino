#include <ESP8266WiFi.h>
#include <ESP8266WiFiMesh.h>
#include <ESP8266WebServer.h>

int enabled = 1;
int nbIntrusion = 0;

const char *AP_ssid = "intrusion_detector"; 
const char *AP_password = "aaaaaaaa";

String manageRequest(String request);

/* Create the mesh node object */
ESP8266WiFiMesh mesh_node = ESP8266WiFiMesh(ESP.getChipId(), manageRequest);

ESP8266WebServer server(80);
  
String manageRequest(String request) {
  /* Print out received message */
  Serial.print("received: ");
  Serial.println(request);

  /* return a string to send back */
  char response[60];
  sprintf(response, "Undefined");
  return response;
}

void setup() {
  Serial.begin(115200);
  
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(D2, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  
  delay(10);

  Serial.println("Setting up mesh node...");

  /* Initialise the mesh node */
  mesh_node.begin();

  Serial.println();
  Serial.println();
  Serial.print("Share AP: ");
  Serial.println(AP_ssid);
  Serial.print("The password is: ");
  Serial.println(AP_password);
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_ssid, AP_password);
  Serial.println("");
  Serial.println(WiFi.softAPIP());

  server.on("/enable", HTTP_GET, sensorEnable);
  server.on("/disable", HTTP_GET, sensorDisable);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Server started");
}

void handleNotFound(){
  server.send(200, "text/html", getPage());
}

void sensorEnable(){
  enabled = 1;
  digitalWrite(LED_BUILTIN, LOW);
  server.send(200, "text/html", getPage());
}

void sensorDisable(){
  enabled = 0;
  digitalWrite(LED_BUILTIN, HIGH);
  server.send(200, "text/html", getPage());
}

String getPage(){
  if(enabled){
    String page = "<html lang=fr-FR><head><meta http-equiv='refresh' content='10'/>";
    page += "<title>Intrusion Detector</title>";
    page += "<style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style>";
    page += "</head><body><h1>Intrusion detector !</h1>";
    page += "<p>Number of intrusions :</p>" + String(nbIntrusion);
    page += "<h3>He's on</h3>";
    page += "<a href='/disable'>Disable</p>";
    page += "</body></html>";
    return page;
  }
  else{
    String page = "<html lang=fr-FR><head><meta http-equiv='refresh' content='10'/>";
    page += "<title>Intrusion Detector</title>";
    page += "<style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style>";
    page += "</head><body><h1>Intrusion detector !</h1>";
    page += "<p>Number of intrusions :</p>" + String(nbIntrusion);
    page += "<h3>He's off</h3>";
    page += "<a href='/enable'>Enable</p>";
    page += "</body></html>";
    return page;
  }
}

void loop() {
  server.handleClient();

  if(enabled){
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
      nbIntrusion++;
      
      /* Scan for other nodes and send them a message */
      char request[60];
      sprintf(request, "Alert");
      mesh_node.attemptScan(request);
    }  
  }
  

}