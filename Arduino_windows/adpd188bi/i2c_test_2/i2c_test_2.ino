#include<Wire.h>
const int ADPD_ADDR=0x64;  // I2C address of the MPU-6050
void setup(){
  Wire.begin();
  Wire.beginTransmission(ADPD_ADDR);
  Serial.begin(9600);
}
void loop(){
    Wire.beginTransmission(ADPD_ADDR);
    Wire.write(0x4F);                   //  The command byte, sets pointer to register with address of 0x32
    Wire.requestFrom(ADPD_ADDR,2);        // Read 1 byte from slave ADPD_ADDR
    byte error = Wire.read();
    byte error1 = Wire.read();
    Wire.endTransmission();
    Serial.print("Error: ");
    Serial.print(error, HEX);
    Serial.print("  |  Error: ");
    Serial.println(error1, HEX);
    if (error == 0){
      
    }
    delay(100);
}
