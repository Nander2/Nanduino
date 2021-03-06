/*************************************************** 
  This is a library for the AM2315 Humidity Pressure & Temp Sensor

  Designed specifically to work with the AM2315 sensor from Adafruit
  ----> https://www.adafruit.com/products/1293

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"

#define AM2315_I2CADDR       0x5C
#define AM2315_READREG       0x03

class Adafruit_AM2315 {
 public:
  Adafruit_AM2315();
  boolean begin(void);
  double readTemperature(void);
  double readHumidity(void);
  bool readTemperatureAndHumidity(double&, double&);
  
 private:
  boolean readData(void);
  void IncrementErrorCounter(void);
  double humidity, temp;
  long LastReadMillis;
  int ReadErrorCounter;
};

