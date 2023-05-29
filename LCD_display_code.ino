//Smart Parking System using IoT
//Codes for LCD 16x2 Display

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);   // I2C address and LCD display Dimension
Servo myservo;                       // Servo Object

int IR1 = 2;                          // Pin no. of IR sensor 1
int IR2 = 4;                          // Pin no. of IR sensor 2
int slot = 3;                         // Number of available parking slots
int servo = 3;
bool isEntryGateOpen = false;

void setup() {
  Serial.begin(9600);                 // Initialize serial communication
  lcd.init();                         // Initialize the LCD display
  lcd.backlight();                    // Turn on the backlight
  myservo.attach(servo);                  // Attach the servo to the pin
  pinMode(IR1, INPUT);                // Set the IR sensor pins as inputs
  pinMode(IR2, INPUT);
  myservo.write(0);              // Set the servo to 0 degrees (fully closed)
  delay(300);  
  lcd.setCursor(2, 0);                // Setting the cursor on 3rd column and 1st row
  lcd.print("SMART PARKING");
  lcd.setCursor(0, 1);                // Setting the cursor on 1st column and 2nd row
  lcd.print("SYSTEM using IOT");
  delay(3000);
  lcd.clear();
}

void loop() {
  int sensor1 = digitalRead(IR1);     // Read the state of the IR sensors
  int sensor2 = digitalRead(IR2);

  if (sensor1 == HIGH && sensor2 == LOW) {     // Car enters the parking lot
    slot++;                                   // Increment the number of available slots
    delay(500);                               // Wait for half a second to avoid false readings
  }

  if (sensor2 == HIGH && sensor1 == LOW) {     // If a car leaves the parking lot
   
    myservo.write(180);    // Set the servo to 180 degrees (fully open)
    delay(300); 
    isEntryGateOpen = true;    // Set the exit gate flag
    delay(3000); 
    myservo.write(0);      // Set the servo to 0 degrees (fully closed)
    delay(300);               // Delay to allow the servo to reach the position
    isEntryGateOpen = false;
     slot--;                                   // Decrement the number of available slots
    delay(500);
}

  if (slot < 0) {                             // The slot count can never be negative
    slot = 0;
  }

  if (slot > 3) {                             // The slot count can never be higher than the number of slots available
    slot = 3;
  }

  if (slot == 0) {                            // If no parking slots are available

    lcd.clear();
    lcd.setCursor(4, 0);                      // Setting the cursor on the 5th column and 1st row
    lcd.print("SORRY :(");
    lcd.setCursor(2, 1);                      // Setting the cursor on the 3rd column and 2nd row
    lcd.print("Parking Full");
    delay(1000);
  } else {
    
    lcd.setCursor(4, 0);                      // Setting the cursor on the 5th column and 1st row
    lcd.print("WELCOME!");
    lcd.setCursor(2, 1);                      // Setting the cursor on the 3rd column and 2nd row
    lcd.print("Slot Left: ");
    lcd.print(slot);
    delay(1000);
  }
    Serial.println(slot);
    delay(1000);
}
