#include <ros.h>
#include <sensor_msgs/Range.h>
#include "ros/node_handle.h"
#include "ArduinoHardware.h"

ros::NodeHandle_<ArduinoHardware, 0, 5, 0, 256> nh;

sensor_msgs::Range sensor_msg0;
ros::Publisher gas_sensor_value0("gas_sensor_value_0", &sensor_msg0);
int sensorValue0;

sensor_msgs::Range sensor_msg1;
ros::Publisher gas_sensor_value1("gas_sensor_value_1", &sensor_msg1);
int sensorValue1;

sensor_msgs::Range sensor_msg2;
ros::Publisher gas_sensor_value2("gas_sensor_value_2", &sensor_msg2);
int sensorValue2;

void setup()
{
  nh.initNode();
  nh.advertise(gas_sensor_value0);
  nh.advertise(gas_sensor_value1);
  nh.advertise(gas_sensor_value2);

  Serial.begin(9600); // sets the serial port to 115200
  nh.getHardware()->setBaud(9600);
}

void loop()
{
  for(int i=0; i<3; i++)
  {
    delay(10);
    sensorValue0 = analogRead(0);       // read analog input pin 0
  }
  sensor_msg0.header.stamp = nh.now();
  sensor_msg0.range = sensorValue0;
  gas_sensor_value0.publish(&sensor_msg0);

  for(int i=0; i<3; i++)
  {
    delay(10);
    sensorValue1 = analogRead(2);       // read analog input pin 0
  }
  sensor_msg1.header.stamp = nh.now();
  sensor_msg1.range = sensorValue1;
  gas_sensor_value1.publish(&sensor_msg1);

  for(int i=0; i<3; i++)
  {
    delay(10);
    sensorValue2 = analogRead(4);       // read analog input pin 0
  }
  sensor_msg2.header.stamp = nh.now();
  sensor_msg2.range = sensorValue2;
  gas_sensor_value2.publish(&sensor_msg2);


  nh.spinOnce();
  delay(100);                        // wait 100ms for next reading
  Serial.print(sensorValue2);
  Serial.print("\n");
}
