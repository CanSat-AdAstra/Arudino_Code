/*
 * IMU Test 2: read in data from acclerometer, magnetometer, gyroscope, and pressure/temp sensor. Save 10 accelerometer
 * readings to file on SD card.
 */
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h> 

#include <SD.h>

//create objects for each sensor
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);
Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);

//create file for SD card
File myFile;

//label pins for SD card reader
int CS_pin  = 10;
int LED_pin_1 = 2;
int LED_pin_2 = 3;
int count = 0;   //number of readings writtent to file

void setup()
{
  Serial.begin(9600);
  
  //setup IMU sensors
  accel.begin(); mag.begin(); bmp.begin(); gyro.begin();
  
  //set up file and pins for SD card reader
  pinMode(CS_pin,    OUTPUT);
  pinMode(LED_pin_1, OUTPUT); 
  pinMode(LED_pin_2, OUTPUT); 
  SD.begin(CS_pin);
  myFile = SD.open("imu1.txt", FILE_WRITE);
  myFile.println("Accelerometer Data (10 readings)"); myFile.println();
}//end setup
//***************************************************************************
//Data collection functions

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

void getMagData(sensors_event_t event)
{
  mag.getEvent(&event);
  Serial.print(F("MAG   "));
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");
  
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

//***************************************************************************
void loop()
{  
  //increment number of readings taken
  count++;
  
  //turn on LED while sensors being read
  digitalWrite(LED_pin_1, HIGH);
  
  //read data from each sensor
  sensors_event_t event;
  
  getAccelData(event);
  getMagData(event);
  getGyroData(event);
  getBmpData(event);
  
  //turn off LED when done reading sensors
  digitalWrite(LED_pin_1, LOW);
  
  //turn on 2nd LED if done writing to file
  if(count == 11)
  {
    myFile.close();
    digitalWrite(LED_pin_2, HIGH);
  }
  
  delay(1000);
  
}//end loop
