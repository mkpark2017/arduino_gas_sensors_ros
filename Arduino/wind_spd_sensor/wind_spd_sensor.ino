#include <ros.h>
#include <sensor_msgs/Range.h>
#include "ros/node_handle.h"
#include "ArduinoHardware.h"

ros::NodeHandle_<ArduinoHardware, 5, 5, 0, 256> nh;

sensor_msgs::Range sensor_msg0;
ros::Publisher wind_spd("wind_speed", &sensor_msg0);
float sensorValue0;

void setup() {
  nh.initNode();
  nh.advertise(wind_spd);
  // put your setup code here, to run once:
  Serial.begin(9600);
  nh.getHardware()->setBaud(9600);
}

void loop() {
  float a =0;
  a = analogRead(A0);
  float b = 0;
  b = a/1023.0 * 5.0;
  float c = b*6.0;
  Serial.print(c);
  Serial.println("m/s");
  sensorValue0 = c;
  sensor_msg0.header.stamp = nh.now();
  sensor_msg0.range = sensorValue0;
  wind_spd.publish(&sensor_msg0);
  nh.spinOnce();
  delay(100);
}
