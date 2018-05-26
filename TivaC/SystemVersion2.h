#ifndef SYSTEM_H_
#define SYSTEM_H_

#define DHT_ER  0   //du lieu doc duoc bi loi
#define DHT_OK  1   //du lieu doc duoc la dung

#define DHT_DATA  PD_0  //chan du lieu cua cam bien

#define LEDR 30 //led red
#define LEDG 39 //led green
#define LEDB 40 //led blue

#define devid 7     //cai dat devide

byte DHT_GetTemHumi (byte &tem1,byte &tem2,byte &humi1,byte &humi2);    //ham thuc hien cac qua trinh lay du lieu tu moi truong cua cam bien

void InitAll();     //khoi dong he thong
void InitLed();     //khoi dong led (cai dat mode led la output) de thong bao mot so trang thai
void InitSerial();  //khoi dong Serial va Serial1
void InitSensor();  //khoi dong cam bien

void ReadSensor();  //doc du lieu tu cam bien

void CheckLimit();  //kiem tra nguong nhiet do

void SIMSendToServer(); //SIM gui du lieu doc duoc tu cam bien len server

void ShowSerial2Result();   //hien thi ket qua cua AT command tren Serial0

void SaveToStringNguong();    //luu gia tri doc duoc tu server vao string Nguong

void SetNguong();      //update nguong nhiet do, do am tu tren server gui xuong

#endif /* SYSTEM_H_ */
