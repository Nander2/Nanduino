#include <Wire.h>
#include <Adafruit_AM2315.h>
#include <Button.h>
#include <LiquidCrystal.h>

Adafruit_AM2315 am2315;
LiquidCrystal lcd(22, 23, 24, 25, 26, 27);
Button Up = Button(51,PULLDOWN);
Button Enter = Button(52,PULLDOWN);
Button Down = Button(53,PULLDOWN);


byte Degree[8] = 
{
  B01100,
  B10010,
  B10010,
  B01100,
  B00000,
  B00000,
  B00000,
};

void setup() 
{
  delay(1000);
  
  lcd.createChar(0, Degree);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 2);
  
  if (!am2315.begin()) 
  {
    // Print a message to the LCD.
     lcd.print("AM2315 not found!");
     while (1);
  }
}

int LoopCount = 0;

void loop() 
{
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  
  lcd.print("Up:");
  lcd.print(Up.isPressed());
  lcd.print("  ");
  lcd.print("Enter:");
  lcd.print(Enter.isPressed());
  lcd.print(" ");
  lcd.print("Down:");
  lcd.print(Down.isPressed());
  
  if(LoopCount == 10)
  {
    // set the cursor to column 0, line 1
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print("   ");
    lcd.print(am2315.readTemperature());
    lcd.write(byte(0));
    lcd.print("C  ");
    lcd.print(am2315.readHumidity());
    lcd.print("%");
    LoopCount = 0;
  }
  LoopCount++;
  delay(10);
}
