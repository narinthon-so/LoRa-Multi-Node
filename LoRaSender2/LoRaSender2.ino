
#include "heltec.h"
#define sw 12
#define led1 2
//#define led2 33
#define BAND    433E6  //you can set band here directly,e.g. 868E6,915E6
#define adcReadPin 13

byte count = 0;
byte ledState;
float voltage;
String h_led = "L";
String h_vcc = "V";
String x;
const char* ipAddr = "X2";
const char* des = "X0";

void setup() {
  Serial.begin(115200);
  //WIFI Kit series V1 not support Vext control
  Heltec.begin(1 /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  pinMode(led1, OUTPUT);
  //pinMode(led2, OUTPUT);
  pinMode(adcReadPin,INPUT);
  pinMode(sw,INPUT_PULLUP);
  //digitalWrite(sw,HIGH);
  analogReadResolution(10); 
}

void loop() {
  float Sensor = analogRead(adcReadPin);
  voltage = Sensor * (3.3/1024);
  /*if(voltage >= 1.50){
    digitalWrite(led2, HIGH);
  }else if(voltage < 1.50){
    digitalWrite(led2, LOW);
  }*/
  
  if(digitalRead(sw)==0){
    while(digitalRead(sw)==0);
      count++;
      if(count==1){
        ledState = 1;
        //digitalWrite(led,1);
       loraSend(h_led + ledState);
        //Serial.println(1);
       }
  
      if(count==2){
        ledState = 0;
        //digitalWrite(led,0);
        loraSend(h_led + ledState);
        count=0;
        //Serial.println(0);
      }
 }

 if (LoRa.parsePacket()) {
    // received a packet
    Serial.print("Received packet '");
    // read packet
    while (LoRa.available()) {
      if(LoRa.find(ipAddr)){
      x = LoRa.readString();
      String head = x.substring(0,1);
      if(head == "L"){
        int Data = x.substring(1, 2).toInt();  //L0 or V exam bata format
        if(Data == 1){
          ledState = 1;
        }else{
          ledState = 0;
        }
      }if(head == "V"){
        loraSend(h_vcc + voltage);
      }
        Serial.print(x);
      }
    }
    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }

  digitalWrite(led1, ledState);
  //Serial.println(voltage);
}

void loraSend(String datasend){
        String ip = "X2";
        LoRa.beginPacket();
        LoRa.print(des + ip + datasend);
        LoRa.endPacket();
}
