# IntruderAlert


Ce projet a pour but de détecter les intrusion par la porte principale d’une maison en détectant l’ouverture de la porte et si possible obtenir l’identité de l’intrus en capturant des images.

![Au voleur](https://www.myfancydress.ie/images/source/Men_s_Burglar_Fancy_Dress_Costume.jpg)

 Le code de la détection et de l'envoi de la détection [Event sender](./event_sender).

 Le code de la réception et de l'envoi d'email [Event receiver](./event_receiver).

Libraries Arduino utilisées :
  * ESP8266WiFiMesh (Communication sur le réseau Mesh);
  * ESP8266WiFi (Communication WIFI);	
  * ESP8266HTTPClient (Permet d'envoyer un email);
