#include "SystemVersion2.h"
#include "ArduinoJson.h"

long upperTemp = 40;   //set nguong nhiet do cao nhat
long lowerTemp = 20;   //set nguong nhiet do thap nhat
long upperHumid = 120;   //set nguong do am cao nhat
long lowerHumid = 60;   //set nguong do am thap nhat

int ID = 30000;     //packetID

int checkbyte = 0;      //bien dung de luu gia tri cua Serial2.read trong ham SaveToStringNguong

int FailCounter = 0;        //bien dem so lan loi cua sensor
int CorrectCounter = 0;     //bien cho biet sensor da hoat dong va chay dung

byte HNhietDo,LNhietDo,HDoAm,LDoAm;     //cac bien chua gia tri nhiet do, do am

String obj;     //khai bao 1 chuoi de gui len server

DynamicJsonBuffer jsonBuffer;

String Nguong;      //khai bao 1 chuoi de luu du lieu tu tren server gui xuong

void setup()    //khai bao va khoi dong he thong
{
    InitAll();
}

void loop()     //chay vong lap he thong
{
    ReadSensor();
    if(upperTemp != 0)
    {
        CheckLimit();
    }
    SIMSendToServer(ID, HNhietDo, HDoAm);
    SetNguong();
    ID ++;
}

void InitAll()
{
    InitLed();
    InitSerial();
    InitSensor();
}

void InitLed()
{
    pinMode(LEDR,OUTPUT);   //cai dat led do la output
    digitalWrite(LEDR,HIGH);
    delay(1000);
    digitalWrite(LEDR,LOW);
    pinMode(LEDG,OUTPUT);   //cai dat led xanh la cay la output
    digitalWrite(LEDG,HIGH);
    delay(1000);
    digitalWrite(LEDG,LOW);
    pinMode(LEDB,OUTPUT);   //cai dat led xanh duong la output
    digitalWrite(LEDB,HIGH);
    delay(1000);
    digitalWrite(LEDB,LOW);
}

void InitSerial()
{
    Serial.begin(9600);     //set toc do baund cua serial0
    Serial2.begin(9600);    //set toc do baund cua Serial2
    while(!Serial);     //doi den khi serial0 duoc khoi dong
    while(!Serial2);    //doi den khi Serial2 duoc khoi dong
    Serial.println("Serial begin");     //in ra serial0 thong bao 2 serial da duoc khoi dong
}

void InitSensor()
{
    while(1)
    {
        ReadSensor();
        if(CorrectCounter == 1)     //neu sensor doc dung thi tat led red va ngung doc gia tri
        {
            digitalWrite(LEDR,LOW);
            return;
        }
        else
        {
            while(FailCounter <= 5)     //dem du 5 lan fail thi bat led red sang
            {
                ReadSensor();
                if(CorrectCounter == 1)     //neu chua du 5 lan fail ma doc dung thi tat led red va ngung doc
                {
                    digitalWrite(LEDR,LOW);
                    return;
                }
            }
            digitalWrite(LEDR,HIGH);    //bat led red de bao hieu sensor gap van de
            Serial.println("Sensor khong khoi dong duoc hoac gap van de");      //thong bao sensor co van de
            FailCounter = 0;
        }
    }
}

void ReadSensor()
{
    int Check = 0;      //bien kiem tra sensor doc dung hay sai (hoac khong hoat dong)
    Check = DHT_GetTemHumi (HNhietDo,LNhietDo,HDoAm,LDoAm);
    if(Check == DHT_OK)
    {
        Serial.print("Nhiet Do=");      //in ra nhiet do
        Serial.print(HNhietDo);    Serial.print("; ");
        Serial.print("Do Am=");         //in ra do am
        Serial.print(HDoAm);
        Serial.print("\n");
        CorrectCounter = 1;     //bao hieu sensor doc dung
    }
    else
    {
        Serial.print("fail");   //in ra sensor doc sai hoac bi loi
        Serial.print("\n");
        FailCounter ++;     //bao hieu sensor doc sai hoac bi loi
    }
    delay(1500);    //doi 1,5s
}

byte DHT_GetTemHumi (byte &tem1,byte &tem2,byte &humi1,byte &humi2)
{
      byte buffer[5]={0,0,0,0,0};   //tao mang gom 5 phan tu, moi phan tu 1 byte
      byte j,i,checksum = 0;    //bien dem va bien kiem tra tong cua 4 byte dau tien

      pinMode(DHT_DATA,OUTPUT);     //set cong data cua DHT la cong ra
      digitalWrite(DHT_DATA,HIGH);      //binh thuong khi chua giao tiep voi cam bien DHT11 thi chan tin hieu luon o muc cao
      delayMicroseconds(60);    //cho doi 60 micro giay (o day de bao nhieu cung duoc vi la muc dau tien)
      digitalWrite(DHT_DATA,LOW);   //gui tin hieu bat dau cho cam bien
      delay(25);    // o day ta delay 25ms (ta can delay it nhat la 18ms de DHT du thoi gian nhan biet duoc kit gui tin hieu bat dau cho no)
      digitalWrite(DHT_DATA,HIGH);  //sau do MCU se keo tin hieu nay len cao va cho tu 20us-40us de DHT phan hoi lai
      pinMode(DHT_DATA,INPUT);  //set la cong vao
      delayMicroseconds(60);    //cho doi tam 60 micro giay
      if(digitalRead(DHT_DATA)==1) return DHT_ER;   //neu tin hieu nay van o muc cao nghia la DHT khong phan hoi thi bao loi
      else
      {
        while(digitalRead(DHT_DATA)==0);    //sau khi DHT11 phan hoi thi no se keo tin hieu nay ve muc thap tam 80us
      }
      delayMicroseconds(60);    //sau do DHT11 lai chuyen tin hieu nay tu muc thap len muc cao tam 80us de chuan bi bat dau gui du lieu cho MCU
      if(digitalRead(DHT_DATA)==0) return DHT_ER;   //neu duong tin hieu van o muc cao sau 80us thi bao loi
      else
      {
        while(digitalRead(DHT_DATA)==1);    //cho duong tin hieu nay ve muc thap de bat dau gui du lieu cho MCU
      }

      for(i=0;i<5;i++)
      {
        for(j=0;j<8;j++)
        {
          while(digitalRead(DHT_DATA)==0);  //doi data len 1
          delayMicroseconds(50);    //kiem tra do dai bit 0 hay la 1
          if(digitalRead(DHT_DATA)==1)
          {
              buffer[i]|=(1<<(7-j));
              while(digitalRead(DHT_DATA)==1);  //doi data xuong 0
          }
        }
      }
      checksum=buffer[0]+buffer[1]+buffer[2]+buffer[3];
      if((checksum)!=buffer[4])
        return DHT_ER;
      humi1 =   buffer[0]; //gia tri phan nguyen
      humi2 =   buffer[1]; //gia tri phan thap phan
      tem1  =   buffer[2]; //gia tri phan nguyen
      tem2  =   buffer[3]; //gia tri phan thap phan
      return DHT_OK;
}

void CheckLimit()
{
    if(HNhietDo > upperTemp)   //nhiet do qua cao
    {
        digitalWrite(LEDG,HIGH);    //sang led xanh la cay trong 7s
        delay(7000);
        digitalWrite(LEDG,LOW);
        Serial.println("Nhiet do qua cao"); //in ra serial la nhiet do qua cao
    }
    else if(HNhietDo < lowerTemp)  //nhiet do qua thap
    {
        digitalWrite(LEDG,HIGH);    //sang led xanh la cay trong 4s
        delay(4000);
        digitalWrite(LEDG,LOW);
        Serial.println("Nhiet do qua thap");    //in ra serial la nhiet do qua thap
    }
    if(HDoAm > upperHumid)      //do am qua cao
    {
        digitalWrite(LEDB,HIGH);    //sang led xanh duong trong 7s
        delay(7000);
        digitalWrite(LEDB,LOW);
        Serial.println("Do am qua cao"); //in ra serial la do am qua cao
    }
    else if(HDoAm < lowerHumid)     //do am qua thap
    {
        digitalWrite(LEDB,HIGH);    //sang led xanh duong trong 4s
        delay(4000);
        digitalWrite(LEDB,LOW);
        Serial.println("Do am qua thap"); //in ra serial la do am qua thap
    }
}

void SIMSendToServer(int packetID, int nhietdo, int doam)
{
    Serial2.println("AT");  //kiem tra SIM800L co hoat dong ko
    delay(5000);
    ShowSerial2Result();
    delay(5000);
    Serial2.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");   //cai dat GPRS
    delay(5000);
    ShowSerial2Result();
    delay(5000);
    Serial2.println("AT+SAPBR=3,1,\"APN\",\"internet\"");   //cai dat APN   (APN la cai dat cong de ket noi giua mang di dong cua dien thoai den internet cong cong)
    delay(5000);
    ShowSerial2Result();
    delay(5000);
    Serial2.println("AT+SAPBR=1,1");
    delay(5000);
    ShowSerial2Result();
    delay(5000);
    Serial2.println("AT+HTTPINIT");     //Khoi tao HTTP
    delay(5000);
    ShowSerial2Result();
    delay(5000);
    obj = "AT+HTTPPARA=\"URL\",\"hoangphuongserver.ddns.net:8000/data_collect/collectData/devid=" + String(devid) + "&packetid=" + String(packetID) + "&curr_Humid=" + String(doam) + "&curr_Temp=" + String(nhietdo) + "\"";       //tao string de gui len server bang phuogn phap HTTP get
    Serial2.println(obj); //URL de ket noi den server
    delay(5000);
    ShowSerial2Result();
    delay(5000);
    Serial2.println("AT+HTTPPARA=\"CID\",1");   //cai dat CID   (CID la quy uoc ve mang dien thoai va quoc gia su dung dien thoai do)
    delay(5000);
    ShowSerial2Result();
    delay(5000);
    Serial2.println("AT+HTTPACTION=0");  //start HTTP, bat dau ket noi (gui du lieu) toi server
    delay(5000);
    ShowSerial2Result();
    delay(5000);
    Serial2.println("AT+HTTPREAD");  //doc du lieu tu server gui lai
    delay(5000);
    SaveToStringNguong();
    delay(5000);
}

void ShowSerial2Result()
{
    while(Serial2.available()>0)
        Serial.write(char (Serial2.read()));
}

void SaveToStringNguong()
{
    while(Serial2.available()>0)
    {
        checkbyte = Serial2.read();
        if(checkbyte == 123)
        {
            Nguong = Nguong + String(char(checkbyte));
            while(1)
            {
                checkbyte = Serial2.read();
                Nguong = Nguong + String(char(checkbyte));
                if(checkbyte == 125)
                {
                    return;
                }
                delay(1);
            }
        }
        delay(1);
    }
}

void SetNguong()
{
    Serial.print("Nguong: ");
    Serial.println(Nguong);
    JsonObject& root = jsonBuffer.parseObject(Nguong);
    Nguong = "";
    upperTemp = root[String("upperTemp")];
    lowerTemp = root[String("lowerTemp")];
    upperHumid = root[String("upperHumid")];
    lowerHumid = root[String("lowerHumid")];
    Serial.print("upperTemp: ");
    Serial.println(upperTemp);
    delay(500);
    Serial.print("lowerTemp: ");
    Serial.println(lowerTemp);
    delay(500);
    Serial.print("upperHumid: ");
    Serial.println(upperHumid);
    delay(500);
    Serial.print("lowerHumid: ");
    Serial.println(lowerHumid);
    delay(500);
}



