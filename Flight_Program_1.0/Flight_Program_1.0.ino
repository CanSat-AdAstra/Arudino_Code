/*
 * Mission broken up into 6 software states:
 *   0. Pre-Flight Test
 *   1. Launch Wait
 *   2. Ascent
 *   3. Stabilization
 *   4. Separation
 *   5. Descent
 *   6. Landed
 
 * Electronic components:
 *   - XBee Radio
 *   - Servo
 *   - Speaker
 *   - Mobius ActionCam (Arduino pushes buttons)
 *   - Sensors:
 *      > 10 DOF IMU (accelerometer,magnetometer,gyroscope,pressure/temp sensor)
 *      > Analog Temp
 *      > Luminosity
 *      > Micro-SD reader
 */

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h>
#include <SD.h>

//create objects for each sensor
Adafruit_10DOF                dof   = Adafruit_10DOF();
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);
Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);

//create file for SD card
File myFile;

//label pins for SD card reader
int CS_pin  = 10;

//label pin for analog temp sensor
int TMP36_pin = 0;

//variables for Mobius camera
int camera_pin = 6;

//variables to track flight state
int softwareState = 0;

//***********************************************************************************************
/*
 * Run all pre-flight tests.
 */
void setup()
{
  PreFlightTest();
  
}//end setup

/*
 * Pre-Flight Test (0) --> 1 Hz transmission
 *  - precondition: turned on switch manually
 *  - begin serial ouput (XBee radio)
 *  - turn on sensors, SD-reader
 *  - turn on video camera (Arduinon "pushes" button on Mobius)
 *  - what happen if an error occurs (either w/ wiring or broken circuitry)???
 */
void PreFlightTest()
{
  //set up serial output
  Serial.begin(9600);
  
  //setup IMU sensors
  accel.begin(); mag.begin(); bmp.begin(); gyro.begin();
    
  //set up file and pins for SD card reader
  pinMode(CS_pin,OUTPUT);
  SD.begin(CS_pin);
  myFile = SD.open("flight1.txt", FILE_WRITE);
  myFile.println("*** FLIGHT DATA ***"); myFile.println();
  myFile.println("0. PRE-FLIGHT TEST *****"); myFile.println();
  
  //turn on video camera (automatically starts recording)
  TurnOnVideo();
}//end PreFlightTest

/*
 * Push camera's ON button by heating up wire attached to button pad.
 */
void TurnOnVideo()
{
  
}//end TurnOnVideo

//***********************************************************************************************
// IMU functions: accelerometer, magnetometer, gyroscope, pressure/temp;
void getAccelData(sensors_event_t event)
{
  accel.getEvent(&event);
  Serial.print("ACCEL ");
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  
  //save 10 reading to SD card file
  if(count <= 10)
  {  
    myFile.print("X: "); myFile.print(event.acceleration.x); myFile.print("  ");
    myFile.print("Y: "); myFile.print(event.acceleration.y); myFile.print("  ");
    myFile.print("Z: "); myFile.print(event.acceleration.z); myFile.print("  ");myFile.println("m/s^2 ");
  }
  
}//end getAccelData

void getMagData(sensors_event_t event, sensors_vec_t orientation)
{
  mag.getEvent(&event);
  dof.magGetOrientation(SENSOR_AXIS_Z, &event, &orientation);
  
  Serial.print(F("Heading   "));
  Serial.print(orientation.heading);
  Serial.println();
  
}//end getMagData

void getGyroData(sensors_event_t event)
{
  gyro.getEvent(&event);
  Serial.print(F("GYRO  "));
  Serial.print("X: "); Serial.print(event.gyro.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.gyro.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.gyro.z); Serial.print("  ");Serial.println("rad/s ");
  
}//end getGyroData

void getBmpData(sensors_event_t event)
{
    bmp.getEvent(&event);

    /* Display atmospheric pressure in hPa */
    Serial.print("PRESS "); Serial.print(event.pressure); Serial.print(F(" hPa, "));
    
    /* Display ambient temperature in C */
    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print(temperature); Serial.print(F(" C, "));
    
    /* Then convert the atmospheric pressure, SLP and temp to altitude    */
    /* Update this next line with the current SLP for better results      */
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    Serial.print(bmp.pressureToAltitude(seaLevelPressure,event.pressure,temperature));Serial.println(F(" m"));
    Serial.println();
}//end getBmpData


//***********************************************************************************************

void loop()
{
  
  
  
  delay(1000);
}//end loop


