# control-servo-motor
In this project, the  web page will contain four operational buttons that will control a servo motor. Button one should move the servo 45 degrees, button two should move the servo 90 degrees, button three should move the servo 135 degrees and button four should move the servo 180 degrees. 
## Components Required
- Arduino Microcontroller
- Type-B USB cable
- ESP8266 Wi-Fi Module
- Breadboard
- Breadboard Power Supply Module
- Jumper Wires
- Wall Wart Power Supply (9v, 1A)
## Steps Involved
- Include all the necessary libraries
```
#include <SoftwareSerial.h>
#include <Servo.h>
#define DEBUG true

SoftwareSerial esp8266(2,3);
```
- Set the corresponding baud rates using this command
```
esp8266.begin(9600);

```
- setup the LEDs for usage and configure the servo motor correctly


- Generate the code to allow the web page interface to interact with the servo motor
```
if(esp8266.available())
  {
    if(esp8266.find("+IPD,"))
    {
      delay(1000);
      int connectionid=esp8266.read()-48;
      esp8266.find("pin=");
      int pinNumber = (esp8266.read()-48)*10;
      pinNumber +=(esp8266.read()-48);

switch(pinNumber)
{
case 10: 
digitalWrite(10,HIGH);
delay(200);
sweep(45);
digitalWrite(10,LOW);
break;
case 11: 
digitalWrite(11,HIGH);
delay(200);
sweep(90);
digitalWrite(11,LOW);
break;
case 12: 
digitalWrite(12,HIGH);
delay(200);
sweep(135);
digitalWrite(12,LOW);
break;
case 13: 
digitalWrite(13,HIGH);
delay(200);
sweep(180);
digitalWrite(13,LOW);
break;
default: Serial.print("pin number error");
}
//digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
String closecommand="AT+CIPCLOSE=";
 closecommand +=connectionid;
 closecommand +="\r\n";

sendData(closecommand,1000,DEBUG); 
}
}
}
```
- Create the function that will send the commands to the ESP module.
```
String sendData(String command,const int timeout,boolean debug){
  String response="";
  char z;
  esp8266.print(command);
  long int time=millis();

  while((time+timeout)>millis()){
    while(esp8266.available()){
      z=esp8266.read();
      response+=z;
```

-  open .HTML file on browser

