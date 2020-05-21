
#include "heltec.h"

#define BAND    433E6  //you can set band here directly,e.g. 868E6,915E6
String x;
const char* ipAddr = "X0";
//const char* node = "X1";
//const char* node = "X2";

void setup() {
    //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Serial.begin(115200);
}

void loop() {
  // try to parse packet
  if (LoRa.parsePacket()) {
    // received a packet
    //Serial.print("Received packet '");
    // read packet
    while (LoRa.available()) {
      if(LoRa.find(ipAddr)){  // ip address this device
        x = LoRa.readString();
        Serial.println(x);            //ส่ง Data ให้ VB 
      }
    }   
  }

    while(Serial.available()){
      String i = Serial.readString();
      loraSend(i);
    }
}


void loraSend(String datasend){
        LoRa.beginPacket();
        LoRa.print(datasend);
        LoRa.endPacket();
}
