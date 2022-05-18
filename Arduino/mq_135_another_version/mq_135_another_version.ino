#include <ros.h>
#include <std_msgs/Float32.h>

ros::NodeHandle  nh;

std_msgs::Float32 float_msg;
ros::Publisher gas_sensor_value("gas_sensor_value_1", &float_msg);

int sensorValue;
void setup()
{
nh.initNode();
nh.advertise(gas_sensor_value);
Serial.begin(9600); // sets the serial port to 9600
pinMode(13, OUTPUT);
pinMode( 3, INPUT);

}


void loop()

{

sensorValue = analogRead(0); // read analog input pin 0


Serial.println(sensorValue, DEC); // prints the value read

delay(1000); // wait 100ms for next reading

}
