#include <Button.h>
#include <LiquidCrystal.h>

#include <Wire.h>
#include <Adafruit_AM2315.h>
#include <DS3232RTC.h>
#include <Time.h>

#include <EEPROM.h>
#include <EEPROMAnything.h>
#include <MyHmi.h>

#include <KeyBoard.h>
#include <LM35.h>

LiquidCrystal lcd(22, 23, 24, 25, 26, 27);
Adafruit_AM2315 am2315;

LM35 AmbientTemp(A0);
config_t configuration;

//element for shceduling
#define SCHED_DEBUG_PRINTF  0

#define ShortPeriode  10
#define MedianPeriode 40
#define LongPeriode   160

long LastShortPeriodeRunMillis;
long LastMedianPeriodeRunMillis;
long LastLongPeriodeRunMillis;

void setup()
{
    Serial.begin(250000);
    EEPROM_readAnything(0, configuration);
    
    //configuration LCD backlight
    pinMode(BlkPwmPin, OUTPUT);
    analogWrite(BlkPwmPin,map(configuration.BlkPwmValue,100,0,0,255));

    //changing the timer frequency to avoid fan noise
    int myEraser = 7;             // this is 111 in binary and is used as an eraser
    TCCR3B &= ~myEraser;   // this operation (AND plus NOT),  set the three bits in TCCR2B to 0
    int myPrescaler = 1;         // this could be a number in [1 , 6]. In this case, 1 corresponds in binary to 001.   
    TCCR3B |= myPrescaler;  //this operation (OR), replaces the last three bits in TCCR2B with our new value 001
    
    //configuration CoolFanPwm
    pinMode(CoolFanPwmPin, OUTPUT);
    analogWrite(CoolFanPwmPin,map(configuration.PwmCoolFan,100,0,0,255));

    //configuration HeatFanPwm
    pinMode(HeatFanPwmPin, OUTPUT);;
    analogWrite(HeatFanPwmPin,map(configuration.pwmHeatFan,100,0,0,255));
    
    setSyncProvider(RTC.get);
    
    am2315.begin();
    
    // set up the LCD's number of columns and rows:
    lcd.begin(20, 2);

    Regul.begin();
    Navigation.ShowPage(HmiNavigation::eStartUpPage);

    long StartMillis = millis();
    LastShortPeriodeRunMillis = StartMillis;
    LastMedianPeriodeRunMillis = StartMillis;
    LastLongPeriodeRunMillis = StartMillis;
}


void loop()
{
  long StartLoopMillis = millis();

  long DeltaShortPeriode = StartLoopMillis - LastShortPeriodeRunMillis;
  if(DeltaShortPeriode >= ShortPeriode)
  {
    #if (SCHED_DEBUG_PRINTF == 1)
    Serial.print("Run Short Task after ");
    Serial.println(DeltaShortPeriode);
    #endif

    Clavier.Compute();
    LastShortPeriodeRunMillis = StartLoopMillis;
  }

  long DeltaMedianPeriode = StartLoopMillis - LastMedianPeriodeRunMillis;
  if( DeltaMedianPeriode >= MedianPeriode)
  {
    #if (SCHED_DEBUG_PRINTF == 1)
    Serial.print("Run Median Task after ");
    Serial.println(DeltaMedianPeriode);
    #endif
    
    Navigation.Run();
    LastMedianPeriodeRunMillis = StartLoopMillis;
  }

  long DeltaLongPeriode = StartLoopMillis - LastLongPeriodeRunMillis;
  if( DeltaLongPeriode >= LongPeriode)
  {
    #if (SCHED_DEBUG_PRINTF == 1)
    Serial.print("Run Long Task after ");
    Serial.println(DeltaLongPeriode);
    #endif

    Regul.run();
    LastLongPeriodeRunMillis = StartLoopMillis;
  }
}
