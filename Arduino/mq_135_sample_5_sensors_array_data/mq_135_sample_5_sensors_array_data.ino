#include <ros.h>
#include <std_msgs/Int32.h>
#include "ros/node_handle.h"
#include "ArduinoHardware.h"


ros::NodeHandle_<ArduinoHardware, 5, 5, 125, 256> nh;

std_msgs::Int32 sensor_msg0;
std_msgs::Int32 sensor_msg1;
std_msgs::Int32 sensor_msg2;
std_msgs::Int32 sensor_msg3;
std_msgs::Int32 sensor_msg4;
ros::Publisher gas_sensor_value0("gas_sensor_value_0", &sensor_msg0);
/*
ros::Publisher gas_sensor_value1("gas_sensor_value_1", &sensor_msg1);
ros::Publisher gas_sensor_value2("gas_sensor_value_2", &sensor_msg2);
ros::Publisher gas_sensor_value3("gas_sensor_value_3", &sensor_msg3);
ros::Publisher gas_sensor_value4("gas_sensor_value_4", &sensor_msg4);
*/

int32_t sensorValue0;
/*
int32_t sensorValue1;
int32_t sensorValue2;
int32_t sensorValue3;
int32_t sensorValue4;
*/

void setup()
{
  nh.initNode();
  nh.advertise(gas_sensor_value0);
  /*
  nh.advertise(gas_sensor_value1);
  nh.advertise(gas_sensor_value2);
  nh.advertise(gas_sensor_value3);
  nh.advertise(gas_sensor_value4);
  */
  Serial.begin(9600); // sets the serial port to 9600
  nh.getHardware()->setBaud(9600);
}

void loop()
{
  sensorValue0 = analogRead(0);       // read analog input pin 0
  /*
  sensorValue1 = analogRead(1);       // read analog input pin 1
  sensorValue2 = analogRead(2);       // read analog input pin 2
  sensorValue3 = analogRead(3);       // read analog input pin 3
  sensorValue4 = analogRead(4);       // read analog input pin 4
  */
  sensor_msg0.data= sensorValue0;
  delay(50);
  /*
  sensor_msg1.data= sensorValue1;
  delay(50);
  sensor_msg2.data= sensorValue2;
  delay(50);
  sensor_msg3.data= sensorValue3;
  delay(50);
  sensor_msg4.data= sensorValue4;
  delay(50);
  */
  gas_sensor_value0.publish(&sensor_msg0);
  /*
  gas_sensor_value1.publish(&sensor_msg1);
  gas_sensor_value2.publish(&sensor_msg2);
  gas_sensor_value3.publish(&sensor_msg3);
  gas_sensor_value4.publish(&sensor_msg4);
  */
  nh.spinOnce();
    Serial.print("sensor 0 : ");
    Serial.println(sensorValue0);
    /*
    Serial.print("sensor 1 : ");
    Serial.println(sensorValue1);
    Serial.print("sensor 2 : ");
    Serial.println(sensorValue2);
    Serial.print("sensor 3 : ");
    Serial.println(sensorValue3);
    Serial.print("sensor 4 : ");
    Serial.println(sensorValue4);
    Serial.print("total = ");
    Serial.println( (sensorValue0+sensorValue1+sensorValue2+sensorValue3+sensorValue4));
    */
  delay(100);                        // wait 500ms for next reading
}
