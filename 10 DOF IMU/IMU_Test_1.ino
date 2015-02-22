//IMU Test 1
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_10DOF.h> 

//create objects for each sensor
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_BMP085_Unified       bmp   = Adafruit_BMP085_Unified(18001);
Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);

void setup()
{
  Serial.begin(9600);
  
  accel.begin(); mag.begin(); bmp.begin(); gyro.begin();

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
  //read data from each sensor
  sensors_event_t event;
  
  getAccelData(event);
  getMagData(event);
  getGyroData(event);
  getBmpData(event);

  delay(1000);
  
}//end loop
