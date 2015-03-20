/* Maintaining Initial Heading by Rotating Servo
 *  Setup
 *   1. read initial heading
 *   2. set initial heading to desired heading
 *   3. read initial servo angle
 *   4. calculate require shift to equate servo + magnetometer readings
 *  Loop (collect data @ 0.5 Hz rate)
 *   5. read magnetometer heading
 *   6. command servo to match heading angle
 */
 #include <Servo.h>
 #include <Wire.h>
 #include <Adafruit_Sensor.h>
 #include <Adafruit_LSM303_U.h>
 #include <Adafruit_10DOF.h> 
 
 //setup servo and IMU objects
 Servo myServo;
 Adafruit_10DOF               imu = Adafruit_10DOF();
 Adafruit_LSM303_Mag_Unified  mag = Adafruit_LSM303_Mag_Unified(30302);
 
 //setup angle variables
 double desiredAngle = 0.0;
 double shiftAngle   = 0.0;
 
 //setup IMU event variables
 sensors_event_t event;
 sensors_vec_t orientation;
 
 double getHeading()
 {
   mag.getEvent(&event);
   imu.magGetOrientation(SENSOR_AXIS_Z, &event, &orientation);
   return orientation.heading;
   
 }//end getHeading
 
 double calcDifference(double a1, double a2)
 {
   double difference = a1 - a2;
   
   if(a1 >= a2)
   {
     difference = a1 - a2;
   }
   else
   {
     difference = a1 + 360;
   }
   
   return difference;
 }//end calcDifference
 
 double calcSum(double a1, double a2)
 {
   double sum = a1 + a2;
   
   if(sum >= 360)
     return sum - 360.0;
   return sum;
   
 }//end calcSum
 
 void setup()
 {
   Serial.begin(9600); //begin serial output with 9600 baud rate
   
   myServo.attach(9); //servo attached to digital pin 9
   mag.begin();       //turn on magnetometer
   
   //determine desired heading and shifting for servo angle
   desiredAngle = getHeading();
   shiftAngle = desiredAngle - myServo.read();
   
 }//end setup
 
 void correctAngle()
 {
   double servoAngle   = 0.0;
   double headingAngle = 0.0;
   
   
   
 }//end correctAngle
 
 void loop()
 {
   correctAngle();
   delay(500);
   
 }//end loop

