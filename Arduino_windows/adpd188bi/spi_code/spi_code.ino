#include <SPI.h>

#define CSPin 10
#define SPI_DATA_RATE 100000000
#define READ_FLAG 0x00
SPISettings spiSetting(SPI_DATA_RATE, MSBFIRST, SPI_MODE3);

uint8_t buf; 

byte val[2] = {0, 0};
short val_short;

void setup() {
  SPI.begin();
  digitalWrite(CSPin, HIGH);
  Serial.begin(9600);
}

void loop() {
  val[0] = 0;
  Serial.println(val[0]);
  SPI.beginTransaction(spiSetting);
  digitalWrite(CSPin, LOW);
  byte command = (0x08 << 1) | 0x00;
  //val[0] = SPI.transfer16(command);
  SPI.transfer(command);
  //delay(100);
  val[0] = SPI.transfer(0x00);
  //val[1] = val[0] << 8;
  val[1] = SPI.transfer(0x00);
  digitalWrite(CSPin, HIGH);
  SPI.endTransaction();
  
  delay(1000);
  Serial.print("COMMAND:  ");
  Serial.print(command, BIN);
  Serial.print("  | ");
  Serial.print("REV_NUM:  ");
  Serial.print(val[0], BIN);
  Serial.print("  | ");
  Serial.print("DEV_NUM:  ");
  Serial.println(val[1], BIN);
  // put your main code here, to run repeatedly:

}
