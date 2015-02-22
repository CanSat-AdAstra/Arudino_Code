//Writes to new file on SD card ONCE. Blinks green LED when complete.
#include <SD.h>

File myFile;

int CS_pin  = 10;
int LED_pin = 2;

void setup() 
{
  pinMode(CS_pin,  OUTPUT);
  pinMode(LED_pin, OUTPUT);
  
  SD.begin(CS_pin);
  
  myFile = SD.open("test.txt", FILE_WRITE);
  myFile.println("This is a test.");
  myFile.close();
     
}//end setup

void loop()
{
  digitalWrite(LED_pin, HIGH);
  delay(100);
  digitalWrite(LED_pin, LOW);
  delay(1000);
}//end loop
