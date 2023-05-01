//Smart Parking System using IoT
//Codes for LCD 16x2 Display

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27,16,2);           // I2C address and LCD display Dimension
Servo myservo;                             // Servo Object

int IR1 = 2;                               // Pin no. of IR sensor 1
int IR2 = 4;                              // Pin no. of IR sensor 2
int servomotor = 3;                      // Pin for servo motor
int slot = 3;                           // Number of available parking slots

void setup() {
  lcd.init();                           // Initialize the LCD display
  lcd.backlight();                     // Turn on the backlight
  myservo.attach(servomotor);         // Attach the servo to the pin
  pinMode(IR1, INPUT);               // Set the IR sensor pins as inputs
  pinMode(IR2, INPUT);
}

void loop() {
  int sensor1 = digitalRead(IR1);           // Read the state of the IR sensors
  int sensor2 = digitalRead (IR2);

  if (sensor1 == HIGH && sensor2 == LOW) {                // car enters in the parking lot
    slot--;                                              // Decrease the number of available slots
    delay(500);                                         // Wait for half of a second to avoid false readings
  }

  if (sensor1 == LOW && sensor2 == HIGH) {               // If a car leaves the parking lot
    slot++;                                             // Increase the number of available slots
    delay(500);                                       
  }

  if (slot < 0) {                                     //The slot count can never be negative
    slot = 0;
  }

  if (slot > 3) {                                   //The slot count can never be higher than the number of slots available
    slot = 3;
  }

   if (slot == 0) {                               // If no parking slots are available
    myservo.write(180);                          // Setting the servo motor to the maximum angle
    lcd.clear();                                
    lcd.setCursor(0,0);                          // Set the cursor to the first row of the LCD display
    lcd.print("    SORRY :(    ");            
    lcd.setCursor(0,1);                          // Set the cursor to the second row
    lcd.print("  Parking Full  "); 
  } else { 
    myservo.write(slot * 18);                           // Map the slot count to the angle of the servo motor (180 degrees for 10 slots)
  
  lcd.setCursor(0,0);                                
  lcd.print("    WELCOME!    ");                   
  lcd.setCursor(0,1);                                                       
  lcd.print("slot Left: ");
  lcd.print(slot); 
  }                               

  delay(500); 
}


 
