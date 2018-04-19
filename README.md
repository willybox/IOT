# IntruderAlert

This project was made in order to detect intruders coming from the main entrance of your home when you left in order to go to work or in vacation. It would have been associated with a camera in order to get pictures of the intruder that would have been sent by mail in your mail box.

![Au voleur](https://www.myfancydress.ie/images/source/Men_s_Burglar_Fancy_Dress_Costume.jpg)

Code of the detection with the sending of the event detection [Event sender](./event_sender).

Code of the reception of the event detection with the email sending. [Event receiver](./event_receiver).

Libraries Arduino :
  * ESP8266WiFiMesh (Communication with Mesh network);
  * ESP8266WiFi (Communication with WIFI);	
  
Problems encountered:
The use of the camera OV2640 is more complex than expected, the deadline is too short in order to fully understand and know to use this component
  
Alternative way to get pictures: Instead of using OV2640, try IP Cam