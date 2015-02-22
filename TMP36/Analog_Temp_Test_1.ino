//Print temperature readings in degrees Celsius and Fahrenheit from the TMP36 sensor

int TMP36_pin = 0; //using pin A0 for the analog temp sensor

void setup()
{
  Serial.begin(9600);
  Serial.println("Readings From Analog Temperature Sensor:");
  Serial.println();
  
}//end setup

void loop()
{
  //get reading from sensor
  float analogReading = analogRead(TMP36_pin);
  
  //convert that reading to voltage
  float voltage = analogReading * 5.0;
  voltage /= 1024.0;
  
 // no estimate temperature in Celsius
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 // now convert to Fahrenheit
 float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
 
 //now print the temperature
 Serial.print(temperatureC); Serial.println(" degrees C");
 Serial.print(temperatureF); Serial.println(" degrees F");
 Serial.println();
 
 delay(1000);
 
}//end loop
