
//pins
#define PeltierPwmPin  3
#define PeltierDirPin  12
#define PeltierCurPin  A0

#define FanPwmPin  11
#define FanDirPin  13
#define FanCurPin  A1

//vars
int peltierInputPercentage = 100;
int PeltierPwm = map(peltierInputPercentage, 0, 100, 0, 255);
float peltierInputCurrent = 0;

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() 
{
  analogReference(EXTERNAL);
  analogWrite(FanPwmPin, 255);
  analogWrite(PeltierPwmPin, 255);
}

void loop() 
{
  delay(20);
}
