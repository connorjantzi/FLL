
//
// FLL City Shaper " The Wild Goats"
//  Oct 21 2019
//
// Smart Recycling Sorter project
//    Our smart recycling project uses a Pixy2 Camera sensor to detect garbage vs recycling to automaticly sort them.
//    It uses a NEMA 17 stepper motor with DRV8825 motor driver.
//
//
//  Pixy2: https://pixycam.com/pixy2/
//  Stepper Motor: https://www.makerguides.com/drv8825-stepper-motor-driver-arduino-tutorial/
//  LCD: https://www.makerguides.com/character-i2c-lcd-arduino-tutorial/
//  Machine Vision Camera with Arduino: https://www.youtube.com/watch?v=tnYIb5YlFMM
//  Arduino101: https://www.youtube.com/watch?v=nL34zDTPkcs
  
#include <Pixy2.h>

// Define stepper motor connections and steps per revolution:
#define dirPin 2
#define dirPinTwo 4
#define stepPin 3
#define stepsPerRevolution 50

// This is the main Pixy object 
Pixy2 pixy;

//this is for the LCD screen
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");
  pixy.init();

  // For LED initialization
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  // Declare pins as output for stepper motor direction and step:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(dirPinTwo, OUTPUT);


  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("1 at a time");
  lcd.setCursor(1,1);
  lcd.print("The Wild Goats");

  
}

void loop()
{ 
  int i; 
  uint16_t blocks;

while (1)
{
  blocks = pixy.ccc.getBlocks();

  if (blocks)
  {
    for (i=0; i<blocks;i++)
    {

    // If there are detect blocks, print them!
    // Open up Tools-> Serial Monitor to view.
    if (pixy.ccc.numBlocks)
    {
      Serial.print("Detected ");
      Serial.println(pixy.ccc.numBlocks);
      for (i=0; i<pixy.ccc.numBlocks; i++)
      {
        Serial.print("  block ");
        Serial.print(i);
        Serial.print(": ");
        pixy.ccc.blocks[i].print();
      


//    Code below determines if it is signature 1 or signature 2 detected by Pixy2 Camera.
//    If signature 1 is determined it turns the LED1 on and stepper motor clockwise.
//    If signature 2 is determined it turns the LED2 on and stepper motor counterclockwise.
//   
//
      // *** SIGNATURE 1 IF STATEMENT ***
      if (pixy.ccc.blocks[i].m_signature == 1)
      {
      // do stuff for sig number one
      digitalWrite(7, HIGH);  // turn on build in LED
      //  delay (5000);  // Wait 5 seconds then turn off LED

   lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print("Recycling       "); //You can write 16 Characters per line .

      delay(2000);
      // Set the spinning direction clockwise:
      digitalWrite(dirPin, HIGH);
      digitalWrite(dirPinTwo, LOW);
      // Spin the stepper motor 1 revolution slowly:
      for (int i = 0; i < stepsPerRevolution; i++) 
      {
        // These four lines result in 1 step:
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(2000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2000);
       }
       
      delay(2000); // wait 5 seconds while dumping recycling with signature 1

      // Set the spinning direction counterclockwise to reset:
      digitalWrite(dirPin, LOW);
        digitalWrite(dirPinTwo, HIGH);
      // Spin the stepper motor 1 revolution quickly:
      for (int i = 0; i < stepsPerRevolution; i++) 
      {
        // These four lines result in 1 step:
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(2000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2000);
      }
      
      digitalWrite(7, LOW);  // turn off build in LED
      lcd.setCursor(0,0); //Defining positon to write from first row,first column .
      lcd.print("READY FOR MORE"); //You can write 16 Characters per line .
      
      }

      // *** SIGNATURE 2 IF STATEMENT ***
      if (pixy.ccc.blocks[i].m_signature == 2  || pixy.ccc.blocks[i].m_signature == 3 )
      {
      // do stuff for sig number two
      digitalWrite(6, HIGH);  // turn on build in LED
      // delay (5000);

    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print("Garbage         "); //You can write 16 Characters per line .

    delay(2000);

       // Set the spinning direction counterclockwise:
      digitalWrite(dirPin, LOW);
      digitalWrite(dirPinTwo, HIGH);
      // Spin the stepper motor 1 revolution quickly:
      for (int i = 0; i < stepsPerRevolution; i++) 
      {
        // These four lines result in 1 step:
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(2000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2000);
      }

      delay(2000);   // wait 5 seconds while dumping recycling with signature 2

      // Set the spinning direction clockwise to reset:
      digitalWrite(dirPin, HIGH);
      digitalWrite(dirPinTwo, LOW);
      // Spin the stepper motor 1 revolution slowly:
      for (int i = 0; i < stepsPerRevolution; i++) 
      {
        // These four lines result in 1 step:
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(2000);
      
        digitalWrite(stepPin, LOW);
        delayMicroseconds(2000);
       }
      
      digitalWrite(6, LOW);  // turn off build in LED

      lcd.setCursor(0,0); //Defining positon to write from first row,first column .
      lcd.print("READY FOR MORE"); //You can write 16 Characters per line .
      
      }
      }
      }
    }
    
  }
}
}
