//Writes to new file on SD card ONCE. Prints "Done" when complete.
#include <SD.h>

File myFile;

int CS_pin  = 10;

void setup() 
{
  Serial.begin(9600);
  pinMode(10,OUTPUT);
  
  SD.begin(10);
  
  myFile = SD.open("test.txt", FILE_WRITE);

  myFile.println("This is a test.");
  myFile.close();
     
}//end setup

void loop()
{
  Serial.println("Done");
  delay(10000);
}//end loop
