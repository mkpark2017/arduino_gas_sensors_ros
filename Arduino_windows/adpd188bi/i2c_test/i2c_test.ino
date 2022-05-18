#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  while(!Serial);
  Serial.println("\n I2C Scanner");
}

void loop() {
  // put your main code here, to run repeatedly:
  byte error, address;
  int nDevices;
  Serial.println("Scanning");
  nDevices = 0;
  for(address=1; address<127; address++){
    error  = 0;
    Serial.print("Origin: ");
    Serial.println(error);
    //Wire.beginTransmission(1);
    //Wire.endTransmission();
    //Wire.beginTransmission(address << 1 | 0x01);
    Wire.beginTransmission(address << 1 | 0x01);
    //Wire.write(address);
    //Wire.write(1);
    error = Wire.endTransmission();
    Serial.print("Error: ");
    Serial.println(error);
    if (error == 0){
      if (address < 16){
        Serial.print("I2C device found at address 0x");
        Serial.println(address, HEX);
      }
    }
    else if (error == 4){
      Serial.print("Unknown error at address 0x");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found \n");
  else
    Serial.println("Done \n");

  delay(1000);
}
