#include <Button.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <EEPROMAnything.h>
#include <MyHmi.h>

struct config_t
{
    byte BlkPwmValue;
    byte TempConsigne;
} configuration;

#define BlkPwmPin  9

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);
Button Up = Button(52,PULLDOWN);
Button Enter = Button(53,PULLDOWN);
Button Down = Button(51,PULLDOWN);

void setup()
{
    EEPROM_readAnything(0, configuration);
    
    //configuration LCD backlight
    pinMode(BlkPwmPin, OUTPUT);
    analogWrite(BlkPwmPin,map(configuration.BlkPwmValue,100,0,0,255));
    
    // set up the LCD's number of columns and rows:
    lcd.begin(20, 2);
}
void loop()
{
  byte LastBlkPwmValue = configuration.BlkPwmValue;
  
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  lcd.print("Luminosite Backlight");
  
  lcd.setCursor(9, 1);
  
  if(configuration.BlkPwmValue < 100)
    lcd.print("0");
  if(configuration.BlkPwmValue < 10)
    lcd.print("0");
  
  lcd.print(configuration.BlkPwmValue);
  
  if(Up.isPressed() && configuration.BlkPwmValue < 100)
  {
    configuration.BlkPwmValue++;
    analogWrite(BlkPwmPin,map(configuration.BlkPwmValue,100,0,0,255));
  }
  else if(Down.isPressed() && configuration.BlkPwmValue > 0)
  {
    configuration.BlkPwmValue--;
    analogWrite(BlkPwmPin,map(configuration.BlkPwmValue,100,0,0,255));
  }
   
  if(Enter.isPressed())
        EEPROM_writeAnything(0, configuration);
        
  delay(100);
}
