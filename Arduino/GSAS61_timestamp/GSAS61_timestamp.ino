#include <ros.h>
#include <sensor_msgs/Range.h>
#include "ros/node_handle.h"
#include "ArduinoHardware.h"

ros::NodeHandle_<ArduinoHardware, 5, 5, 0, 256> nh;

sensor_msgs::Range sensor_msg0;
ros::Publisher gas_sensor_value0("GSAS_sensor_value_0", &sensor_msg0);
int sensorValue0;


void setup()
{
  nh.initNode();
  nh.advertise(gas_sensor_value0);
  Serial.begin(9600); // sets the serial port to 9600
  nh.getHardware()->setBaud(9600);
}

void loop()
{
  sensorValue0 = analogRead(0);       // read analog input pin 0
  sensor_msg0.header.stamp = nh.now();
  sensor_msg0.range = sensorValue0;
  gas_sensor_value0.publish(&sensor_msg0);

  nh.spinOnce();
  delay(500);                        // wait 100ms for next reading
}
