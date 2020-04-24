#include "SparkFun_Si7021_Breakout_Library.h"
#include <Wire.h>
#include "SparkFunMPL3115A2.h"
float humidity = 0;
float tempf = 0;
float pressure = 0;
float val_2602 = 0;
float val_2600 = 0;

int gasSensor2602 = A1; // select input pin for gasSensor
int gasSensor2600 = A2; // select input pin for gasSensor
int power = A3;
int GND = A2;


//Create Instance of HTU21D or SI7021 temp and humidity sensor and MPL3115A2 barrometric sensor
Weather sensor;
MPL3115A2 myPressure;

void setup()
{
    Serial.begin(9600);   // open serial over USB at 9600 baud

    pinMode(power, OUTPUT);
    pinMode(GND, OUTPUT);

    digitalWrite(power, HIGH);
    digitalWrite(GND, LOW);

    sensor.begin();
    Wire.begin(); 
    myPressure.begin();
    myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa
  
    myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
    myPressure.enableEventFlags(); // Enable all three pressure and temp event flags
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
  val_2602 = analogRead(gasSensor2602); // read the value from the pot
  val_2602 = (val_2602/1023)*100;
  val_2600 = analogRead(gasSensor2600); // read the value from the pot
  val_2600 = (val_2600/1023)*100;
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
