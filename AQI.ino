#include "SparkFun_Si7021_Breakout_Library.h"
#include <Wire.h>
#include "SparkFunMPL3115A2.h"

// values  which store data from the sensors

float humidity = 0;
float tempf = 0;
float pressure = 0;
float val_2602 = 0;
float val_2600 = 0;

// analouge pins
int gasSensor2602 = A1;
int gasSensor2600 = A4; 
int power = A3;
int GND = A2;


// Instacnes of weather and pressure sensors
Weather sensor;
MPL3115A2 myPressure;

void setup()
{
    Serial.begin(9600);  

    pinMode(power, OUTPUT);
    pinMode(GND, OUTPUT);

    digitalWrite(power, HIGH);
    digitalWrite(GND, LOW);

    sensor.begin();
    Wire.begin(); 
    myPressure.begin();
    myPressure.setModeBarometer(); 
    myPressure.setOversampleRate(7); 
    myPressure.enableEventFlags(); 
}

void loop()
{
    GetGas();
    getWeather();
    printInfo();
    delay(1000);
}

void getWeather()
{
  humidity = sensor.getRH();
  tempf = sensor.getTemp();
  pressure = myPressure.readPressure();
  
}

void GetGas()
{
  val_2602 = analogRead(gasSensor2602);
  val_2602 = (val_2602/1023)*100; // adjust a value to show the percentage of the concetration of gasses
  val_2600 = analogRead(gasSensor2600); 
  val_2600 = (val_2600/1023)*100; // adjust a value to show the percentage of the concetration of gasses
}

void printInfo()
{
  Serial.print(tempf);
  Serial.print("|");

  Serial.print(humidity);
  Serial.print("|");
  
  Serial.print(pressure, 2);\
  Serial.print( "|" );
  
  Serial.print( val_2600 );
  Serial.print( "|" );
  
  Serial.println( val_2602 );
  Serial.println("");
  
}
