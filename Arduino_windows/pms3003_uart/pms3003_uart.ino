#include <SoftwareSerial.h>        //RX, TX 통신 라이브러리 추가

const byte rxPin = 2;
const byte txPin = 3;
SoftwareSerial Serial1(rxPin,txPin);         //RX ,TX 핀을 2, 3번 핀으로 지정

long pmcf10=0;
long pmcf25=0;
long pmcf100=0;
long pmat10=0;
long pmat25=0;
long pmat100=0;

char buf[50];

void setup() {

  Serial.begin(9600);          //시리얼 통신 시작
  Serial1.begin(9600);        //RX, TX 통신 시작
  
}


void loop() {

  int count = 0;
  unsigned char c;
  unsigned char high;

  while (Serial1.available()) {               

    c = Serial1.read();           //RX, TX 통신을 통한 값을 c로 저장
    if((count==0 && c!=0x42) || (count==1 && c!=0x4d)){
      Serial.println("check failed");
      break;
    }

    if(count > 15){
      //Serial.println("complete");
      break;
    }

    else if(count == 4 || count == 6 || count == 8 || count == 10 || count == 12 || count == 14) {
      high = c;
    }

    else if(count == 5){             //pm1.0의 수치값 계산
      pmcf10 = 256*high + c;
      //Serial.print("CF=1, PM1.0=");
      Serial.print(pmcf10); // 1st
      Serial.print(" ");
      //Serial.println(" ug/m3");
    }

    else if(count == 7){           //pm2.5의 수치값 계산
      pmcf25 = 256*high + c;
      //Serial.print(" | CF=1, PM2.5=");
      Serial.print(pmcf25); // 2nd
      Serial.print(" ");
      //Serial.println(" ug/m3");
    }

    else if(count == 9){           //pm 10의 수치값 계산
      pmcf100 = 256*high + c;
      //Serial.print(" | CF=1, PM10=");
      Serial.print(pmcf100); // 3rd
      Serial.print(" ");
      //Serial.println(" ug/m3");
    }
/*
    else if(count == 11){
      pmat10 = 256*high + c;
      //Serial.print(" | atmosphere, PM1.0=");
      Serial.print(pmat10); // 4th
      Serial.print(" ");
      //Serial.println(" ug/m3");
    }

    else if(count == 13){
      pmat25 = 256*high + c;
      //Serial.print(" | atmosphere, PM2.5=");
      Serial.print(pmat25); // 5th
      Serial.print(" ");
      //Serial.println(" ug/m3");
    }

    else if(count == 15){
      pmat100 = 256*high + c;
      //Serial.print(" | atmosphere, PM10=");
      Serial.println(pmat100); // 6th
      Serial.print(" "); 
      //Serial.println(" ug/m3");
    }
*/
    count++;

  }

  while(Serial1.available()) Serial1.read();

  Serial.println();

  delay(1000);

}
