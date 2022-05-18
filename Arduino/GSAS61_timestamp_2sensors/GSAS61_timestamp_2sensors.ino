#include <ros.h>
#include <sensor_msgs/Range.h>
#include "ros/node_handle.h"
#include "ArduinoHardware.h"

ros::NodeHandle_<ArduinoHardware, 0, 5, 0, 256> nh;

sensor_msgs::Range sensor_msg3;
ros::Publisher gas_sensor_value3("gas_sensor_value_3", &sensor_msg3);
int sensorValue3;

sensor_msgs::Range sensor_msg4;
ros::Publisher gas_sensor_value4("gas_sensor_value_4", &sensor_msg4);
int sensorValue4;

void setup()
{
  nh.initNode();
  nh.advertise(gas_sensor_value3);
  nh.advertise(gas_sensor_value4);

  Serial.begin(9600); // sets the serial port to 115200
  nh.getHardware()->setBaud(9600);
}

void loop()
{
  for(int i=0; i<5; i++)
  {
    delay(10);
    sensorValue3 = analogRead(0);       // read analog input pin 0
  }
  sensor_msg3.header.stamp = nh.now();
  sensor_msg3.range = sensorValue3;
  gas_sensor_value3.publish(&sensor_msg3);

  for(int i=0; i<5; i++)
  {
    delay(10);
    sensorValue4 = analogRead(3);       // read analog input pin 0
  }
  sensor_msg4.header.stamp = nh.now();
  sensor_msg4.range = sensorValue4;
  gas_sensor_value4.publish(&sensor_msg4);

  nh.spinOnce();
  delay(100);                        // wait 100ms for next reading
  Serial.print(sensorValue3);
  Serial.print("\n");
}
