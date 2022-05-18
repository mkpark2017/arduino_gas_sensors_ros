#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle  nh;

std_msgs::Float32 float_msg;
ros::Publisher gas_sensor_value("gas_sensor_value_1", &float_msg);

int sensorValue0;
int sensorValue1;
int sensorValue2;
int sensorValue3;
int sensorValue4;


void setup()
{
  nh.initNode();
  nh.advertise(gas_sensor_value);
  Serial.begin(9600); // sets the serial port to 9600
  nh.getHardware()->setBaud(9600);
}

void loop()
{
  sensorValue0 = analogRead(0);       // read analog input pin 0
  sensorValue1 = analogRead(1);       // read analog input pin 1
  sensorValue2 = analogRead(2);       // read analog input pin 2
  sensorValue3 = analogRead(3);       // read analog input pin 3
  sensorValue4 = analogRead(4);       // read analog input pin 4
  float_msg.data = (sensorValue0+sensorValue1+sensorValue2+sensorValue3+sensorValue4);
  gas_sensor_value.publish(&float_msg);
  nh.spinOnce();
    Serial.print("sensor 0 : ");
    Serial.println(sensorValue0);
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
  delay(500);                        // wait 100ms for next reading
}
