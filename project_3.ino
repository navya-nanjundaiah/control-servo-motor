#include <SoftwareSerial.h>
#include <Servo.h>
#define DEBUG true

SoftwareSerial esp8266(2,3);
Servo servo;
int servopin= 9;
int servoAngle = 0; 

void setup()
{
 Serial.begin(9600);
 esp8266.begin(9600);
 servo.attach(servopin);
 servo.write(servoAngle);

//led 1 (45 degree)
pinMode(10, OUTPUT);// maybe pin 13
digitalWrite(10, LOW);

//led 2
pinMode(11, OUTPUT);
digitalWrite(11,LOW);

//led 3
pinMode(12, OUTPUT);
digitalWrite(12, LOW);

//led 4
pinMode(13, OUTPUT);
digitalWrite(13, LOW);

sendData("AT+RST\r\n",2000,DEBUG);
sendData("AT+CWMODE=2\r\n",1000,DEBUG);
sendData("AT+CIFSR\r\n",1000,DEBUG);
sendData("AT+CIPMUX=1\r\n",1000,DEBUG);
sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG);
}

void loop() 
{ delay(2000);
  // put your main code here, to run repeatedly:
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
String sendData(String command,const int timeout,boolean debug){
  String response="";
  char z;
  esp8266.print(command);
  long int time=millis();

  while((time+timeout)>millis()){
    while(esp8266.available()){
      z=esp8266.read();
      response+=z;
    }}

    if(debug){
      Serial.print(response);
    }
    return response;
}
void sweep(int range)
{
  for(servoAngle = 0; servoAngle < range; servoAngle += 10)
{
  servo.write(servoAngle);
  delay(100);  
}
for(servoAngle = range; servoAngle>=1; servoAngle-=10)
{
  servo.write(servoAngle);
  delay(100);
}
}
