#include <Wire.h>
#include <ros.h>
#include <std_msgs/Float32.h>
#include "ros/node_handle.h"
#include "ArduinoHardware.h"

int i;
unsigned int data[10];
char buff[128];

ros::NodeHandle_<ArduinoHardware, 5, 5, 125, 125> nh;
std_msgs::Float32 float_msg;
ros::Publisher gas_sensor_value("gas_sensor_value_1", &float_msg);

int sensorValue;
 
void setup()
{
  nh.advertise(gas_sensor_value);
  nh.getHardware()->setBaud(9600);
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);
}
void loop()
{
  Wire.beginTransmission(0x70); // transmit to device #4
  Wire.write(0x0C);        // sends CMD to read
  Wire.write(0x00);              // sends one byte 
  Wire.write(0x00);              // sends one byte 
  Wire.write(0x00);              // sends one byte 
  Wire.write(0x00);              // sends one byte 
  Wire.write(0xF3);              // sends CRC (refer to manual)
  Wire.endTransmission();    // stop transmitting
   
  Wire.requestFrom(0x70, 7);    // request 7 bytes from slave device #2
  i = 0;
  while(Wire.available())    // slave may send less than requested
  {
    data[i++] = Wire.read(); // receive a byte as character
  }
  //int CO2 = (data[2]-13)*(1600/229)+400;
  //int VOC = (data[1]-13)*(1000/229);
  int VOC = (data[1]-13)*(1000/229);
  float_msg.data = VOC;
  gas_sensor_value.publish(&float_msg);
  nh.spinOnce();  
//  unsigned long RAW = 10*(data[3] + (256*data[4]) + (65536*data[5]));
//  sprintf(buff, "VOC:%d, CO2:%d\t\tRAW:%04x\t\t%02x,%02x,%02x", VOC, CO2, RAW, data[0], data[1], data[2]);
//  sprintf(buff, "VOC:%d, CO2:%d\t\t%02x,%02x,%02x", VOC, CO2, data[0], data[1], data[2]);
//  sprintf(buff, "VOC:%d, \t\t%02x,%02x,%02x", VOC, data[0], data[1], data[2]);
//  Serial.println(buff);
  delay(1000);
}
