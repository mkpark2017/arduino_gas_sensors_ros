#include <ros.h>
#include <sensor_msgs/Range.h>
#include "ros/node_handle.h"
#include "ArduinoHardware.h"

ros::NodeHandle_<ArduinoHardware, 0, 5, 0, 256> nh;

sensor_msgs::Range sensor_msg0;
ros::Publisher gas_sensor_value0("gas_sensor_value_0", &sensor_msg0);

sensor_msgs::Range sensor_msg1;
ros::Publisher gas_sensor_value1("gas_sensor_value_1", &sensor_msg1);

sensor_msgs::Range sensor_msg2;
ros::Publisher gas_sensor_value2("gas_sensor_value_2", &sensor_msg2);

sensor_msgs::Range sensor_msg3;
ros::Publisher gas_sensor_value3("gas_sensor_value_3", &sensor_msg3);
int sensorValue[4];

void setup()
{
  nh.initNode();
  nh.advertise(gas_sensor_value0);
  nh.advertise(gas_sensor_value1);
  nh.advertise(gas_sensor_value2);
  nh.advertise(gas_sensor_value3);
  Serial.begin(9600); // sets the serial port to 115200
  nh.getHardware()->setBaud(9600);
}

void read_gas(int i)
{
  
}

void loop()
{
  for(int i=0; i<5; i++)
  {
    sensorValue0 = analogRead(0);       // read analog input pin 0
    delay(20);
  }
  sensor_msg0.header.stamp = nh.now();
  sensor_msg0.range = sensorValue0;
  gas_sensor_value0.publish(&sensor_msg0);

  for(int i=0; i<5; i++)
  {
    sensorValue1 = analogRead(1);       // read analog input pin 0
    delay(20);
  }
  sensor_msg1.header.stamp = nh.now();
  sensor_msg1.range = sensorValue1;
  gas_sensor_value1.publish(&sensor_msg1);

  for(int i=0; i<5; i++)
  {
    sensorValue2 = analogRead(2);       // read analog input pin 0
    delay(20);
  }
  sensor_msg2.header.stamp = nh.now();
  sensor_msg2.range = sensorValue2;
  gas_sensor_value2.publish(&sensor_msg2);

  for(int i=0; i<5; i++)
  {
    sensorValue3 = analogRead(3);       // read analog input pin 0
    delay(20);
  }
  sensor_msg3.header.stamp = nh.now();
  sensor_msg3.range = sensorValue3;
  gas_sensor_value3.publish(&sensor_msg3);
  
  nh.spinOnce();
  delay(300);                        // wait 100ms for next reading
}
