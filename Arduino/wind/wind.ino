#include <ros.h>
#include <sensor_msgs/Range.h>
#include "ros/node_handle.h"
#include "ArduinoHardware.h"

#include <SoftwareSerial.h>

SoftwareSerial mySerial(11,10);


ros::NodeHandle_<ArduinoHardware, 5, 5, 0, 256> nh;

sensor_msgs::Range sensor_msg0;
ros::Publisher wind_value0("wind_data", &sensor_msg0);
float sensorValue0;
float sensorValue1;

char                 databuffer[35];
double               temp;

void getBuffer()                                                                    //Get weather status data
{
  int index;
  for (index = 0;index < 35;index ++)
  {
    if(mySerial.available())
    {
      databuffer[index] = mySerial.read();
      if (databuffer[0] != 'c')
      {
        index = -1;
      }
    }
    else
    {
      index --;
    } 
  }
}

int transCharToInt(char *_buffer,int _start,int _stop)                               //char to int）
{
  int _index;
  int result = 0;
  int num = _stop - _start + 1;
  int _temp[num];
  for (_index = _start;_index <= _stop;_index ++)
  {
    _temp[_index - _start] = _buffer[_index] - '0';
    result = 10*result + _temp[_index - _start];
  }
  return result;
}

int WindDirection()                                                                  //Wind Direction
{
  return transCharToInt(databuffer,1,3);
}

float WindSpeedAverage()                                                             //air Speed (1 minute)
{
  temp = 0.44704 * transCharToInt(databuffer,5,7);
  return temp;
}

float WindSpeedMax()                                                                 //Max air speed (5 minutes)
{
  temp = 0.44704 * transCharToInt(databuffer,9,11);
  return temp;
}

/*void setup()
{
  nh.initNode();
  nh.advertise(wind_sensor_value0);
  
  Serial.begin(9600);
  nh.getHardware()->setBaud(9600);
}*/
/*void loop()
{
  getBuffer();                                                                      //Begin!
  Serial.print("Wind Direction: ");
  Serial.print(WindDirection());
  Serial.println("  ");
  Serial.print("Average Wind Speed (One Minute): ");
  Serial.print(WindSpeedAverage());
  Serial.println("m/s  ");
//  Serial.print("Max Wind Speed (Five Minutes): ");
//  Serial.print(WindSpeedMax());
//  Serial.println("m/s");
//  Serial.print("Rain Fall (One Hour): ");
//  Serial.print(RainfallOneHour());
//  Serial.println("mm  ");
//  Serial.print("Rain Fall (24 Hour): ");
//  Serial.print(RainfallOneDay());
//  Serial.println("mm");
//  Serial.print("Temperature: ");
//  Serial.print(Temperature());
//  Serial.println("C  ");
//  Serial.print("Humidity: ");
//  Serial.print(Humidity());
//  Serial.println("%  ");
//  Serial.print("Barometric Pressure: ");
//  Serial.print(BarPressure());
//  Serial.println("hPa");
//  Serial.println("");
//   Serial.println("");

  sensor_msg0.header.stamp = nh.now();
  sensorValue0 = WindDirection();
  sensorValue1 = WindSpeedAverage();
  sensor_msg0.min_range = sensorValue0;
  sensor_msg0.max_range = sensorValue1;

//  sensor_msg0.min_range = 0;
//  sensor_msg0.max_range = 1;


  wind_sensor_value0.publish(&sensor_msg0);

  nh.spinOnce();
  delay(100); 
}*/

void setup()
{
  nh.initNode();
  nh.advertise(wind_value0);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
  mySerial.begin(9600); // sets the serial port to 9600
  nh.getHardware()->setBaud(9600);
  sensor_msg0.header.stamp = nh.now();
  sensor_msg0.range = 0;
  wind_value0.publish(&sensor_msg0);
}

void loop()
{
  printf("1");
  getBuffer();                                     //Begin!
  Serial.print(databuffer);
  Serial.print("Wind Direction: ");
  Serial.print(WindDirection());
  Serial.println("  ");
  sensor_msg0.header.stamp = nh.now();
  sensorValue0 = WindDirection();
  sensor_msg0.range = sensorValue0;
  wind_value0.publish(&sensor_msg0);

  nh.spinOnce();
  
  delay(100);                        // wait 100ms for next reading
}

