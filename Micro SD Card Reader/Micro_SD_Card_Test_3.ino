  //Writes to new file on SD card 10 times. Blinks green LED when complete.
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
  }//end setup
  
  int count = 0;
  void loop()
  {
    count++;
    if(count <= 10)
      myFile.println(count);
    else if(count == 11)
      myFile.close();
    else
    {
      digitalWrite(LED_pin, HIGH);
      delay(100);
      digitalWrite(LED_pin, LOW);
      delay(1000);
    }
    
  }//end loop
