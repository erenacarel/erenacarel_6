#include <Arduino.h>
#include <TheThingsNetwork.h>
#include "UNIT_LoRaWAN.h"
#include <SoftwareSerial.h>

#define DEBUG true

const int rxPin = 4;
const int txPin = 2;

SoftwareSerial mySerial(rxPin, txPin);
UNIT_LoRaWAN LoRaWAN;

String response;


void setup() {
  // put your setup code here, to run once:
  Serial.println("Module Connecting !");
  Serial.begin(115200);
  mySerial.begin(115200);
  LoRaWAN.Init(&Serial, rxPin, txPin);
  while(!LoRaWAN.checkDeviceConnect());
  Serial.println("Module Connected !");

  LoRaWAN.writeCMD("AT\r\n");

  LoRaWAN.writeCMD("AT+CRESTORE\r\n");
  LoRaWAN.writeCMD("AT+ILOGLVL=0\r\n");
  LoRaWAN.writeCMD("AT+CSAVE\r\n");
  LoRaWAN.writeCMD("AT+IREBOOT=0\r\n");

  LoRaWAN.setClass("2");
  LoRaWAN.writeCMD("AT+CWORKMODE=2\r\n");
  LoRaWAN.setRxWindow("869525000");
  LoRaWAN.setFreqMask("0001");
  
  LoRaWAN.writeCMD("AT+CSAVE\r\n");
  LoRaWAN.writeCMD("AT+CRESTORE\r\n");
  //LoRaWAN.configABP("2", "6672237A", "EF6D6E2503F57AE2FA151CDA87455F18", "2E8C8650B4041672BBB9A399F2DEB427");
  LoRaWAN.configOTTA("70B3D57ED005D402", "58A0CBFFF0803C26", "F8ED2FBE45F6D68A0116204365B98E81", "2");
  ///////configOTTA(String device_eui, String app_eui, String app_key, String ul_dl_mode)

  // configOTTA(String device_eui, String app_eui, String app_key, String ul_dl_mode)
  // configABP(String device_addr, String app_skey, String net_skey, String ul_dl_mode)

  delay(1000);

  response = LoRaWAN.waitMsg(1000);
  Serial.println(response);

  LoRaWAN.startJoin();
  Serial.println("Start Join.....");
    // while (!LoRaWAN.checkJoinStatus()) {
    //     delay(100);
    // };
  Serial.println("Join success.....");


}

int hum, temp;
char msg[30];

void loop() {
  // put your main code here, to run repeatedly:


  //sprintf(msg, "AT+DTRX = 1,2,5, %f%f", hum, temp);
  sprintf(msg, "AT+DTRX=1,2,4,%d%d", 15, 30);
  Serial.println(msg);
  //LoRaWAN.sendMsg(1, 15, strlen(msg), msg);
  LoRaWAN.sendMsg(1,15, 4, "3D3C");
  delay(1000);

}
