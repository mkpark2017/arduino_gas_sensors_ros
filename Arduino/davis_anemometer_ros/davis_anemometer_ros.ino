#include "TimerOne.h" // Timer Interrupt set to 2 second for read sensors
#include <math.h>

#include <ros.h>
#include <sensor_msgs/Range.h>
#include "ros/node_handle.h"
#include "ArduinoHardware.h"

#define WindSensorPin (2) // The pin location of the anemometer sensor
#define WindVanePin (A4) // The pin the wind vane sensor is connected to
#define VaneOffset 0; // define the anemometer offset from magnetic north

int VaneValue; // raw analog value from wind vane
int Direction; // translated 0 - 360 direction
int CalDirection; // converted value with offset applied
int LastValue; // last direction value
short sensing_t = 1; // in seconds

volatile bool IsSampleRequired; // this is set true every 2.5s. Get wind speed
volatile unsigned int TimerCount; // used to determine 2.5sec timer count
volatile unsigned long Rotations; // cup rotation counter used in interrupt routine
volatile unsigned long ContactBounceTime; // Timer to avoid contact bounce in isr

float WindSpeed; // speed miles per hour

ros::NodeHandle_<ArduinoHardware, 5, 5, 0, 256> nh;
sensor_msgs::Range sensor_msg0;
ros::Publisher wind_data("wind_data", &sensor_msg0);
float sensorValue0;
float sensorValue1;

void setup() {
  nh.initNode();
  nh.advertise(wind_data);
  nh.getHardware()->setBaud(9600);

  LastValue = 0;

  IsSampleRequired = false;

  TimerCount = 0;
  Rotations = 0; // Set Rotations to 0 ready for calculations

  Serial.begin(9600);

  pinMode(WindSensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(WindSensorPin), isr_rotation, FALLING);

  Serial.println("Davis Anemometer Test");
  Serial.println("Speed (MPH)\tm/s\tDirection\tStrength");

  // Setup the timer interupt
  Timer1.initialize(sensing_t*1000000);// //타이머 간격 500000us = 500ms = 0.5 sec
  Timer1.attachInterrupt(isr_timer);
}

void loop() {

  getWindDirection();

// Only update the display if change greater than 5 degrees.
//if(abs(CalDirection - LastValue) > 5) {
//LastValue = CalDirection;
//}
  if(IsSampleRequired) {
// convert to mp/h using the formula V=P(2.25/T)
// V = P(2.25/2.5) = P * 0.9
    WindSpeed = Rotations * (2.25/sensing_t);
    Rotations = 0; // Reset count for next sample

    IsSampleRequired = false;

    Serial.print(WindSpeed); Serial.print("\t\t");
    Serial.print(getMperS(WindSpeed)); Serial.print("\t");
    Serial.print(CalDirection); Serial.print("\n");

    sensorValue0 = getMperS(WindSpeed);
    sensorValue1 = CalDirection;
    sensor_msg0.header.stamp = nh.now();
    sensor_msg0.range = sensorValue0;
    sensor_msg0.max_range = sensorValue1;
    wind_data.publish(&sensor_msg0);
    nh.spinOnce();
    delay(10);    
//getHeading(CalDirection); Serial.print("\t\t");
//getWindStrength(WindSpeed);
  }
}

// isr handler for timer interrupt
void isr_timer() {
  TimerCount++;

  if(TimerCount == 1)
  {
    IsSampleRequired = true;
    TimerCount = 0;
  }
}

// This is the function that the interrupt calls to increment the rotation count
void isr_rotation() {
  if((millis() - ContactBounceTime) > 15 ) { // debounce the switch contact.
    Rotations++;
    ContactBounceTime = millis();
  }
}

// Convert MPH to m/s
float getMperS(float speed) {
  return speed * 0.44704;
}

// Get Wind Direction
void getWindDirection() {
  VaneValue = analogRead(WindVanePin);
  Direction = map(VaneValue, 0, 1023, 0, 359);
  CalDirection = Direction + VaneOffset;

  if(CalDirection > 360)
    CalDirection = CalDirection - 360;
  if(CalDirection < 0)
    CalDirection = CalDirection + 360;
}
