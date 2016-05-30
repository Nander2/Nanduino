#include <Button.h>
#include <LiquidCrystal.h>

#include <Wire.h>
#include <Adafruit_AM2315.h>
#include <DS3232RTC.h>
#include <Time.h>

#include <EEPROM.h>
#include <EEPROMAnything.h>
#include <MyHmi.h>

#include <LM35.h>

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);
Adafruit_AM2315 am2315;
Button UpBtn = Button(52,PULLDOWN);
Button EnterBtn = Button(53,PULLDOWN);
Button DownBtn = Button(51,PULLDOWN);
LM35 AmbientTemp(A0);
config_t configuration;


void setup()
{
    Serial.begin(9600);
    EEPROM_readAnything(0, configuration);
    
    //configuration LCD backlight
    pinMode(BlkPwmPin, OUTPUT);
    analogWrite(BlkPwmPin,map(configuration.BlkPwmValue,100,0,0,255));
    
    setSyncProvider(RTC.get);
    
    am2315.begin();
    
    // set up the LCD's number of columns and rows:
    lcd.begin(20, 2);

    Regul.begin();
    Navigation.ShowPage(HmiNavigation::eStartUpPage);
}

void loop()
{
  Navigation.Run();
  Regul.run();
}
