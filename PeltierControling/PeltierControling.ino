
//pins
#define PeltierPwmPin  3
#define PeltierDirPin  12
#define PeltierCurPin  A0

#define FanPwmPin  11
#define FanDirPin  13
#define FanCurPin  A1

//vars
int peltierInputPercentage = 0;
int PeltierPwm = map(peltierInputPercentage, 0, 100, 0, 255);
float peltierInputCurrent = 0;

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
 return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() 
{
  Serial.begin(9600);
  analogReference(EXTERNAL);
  analogWrite(FanPwmPin, 255);
}

void loop() 
{
  char option;

  if(Serial.available() > 0)
  {
    option = Serial.read();
    if(option == 'a') 
      peltierInputPercentage += 5;
    else if(option == 'z')
      peltierInputPercentage -= 5;

    if(peltierInputPercentage > 99) 
      peltierInputPercentage = 99;
    else if(peltierInputPercentage < 0) 
      peltierInputPercentage = 0;

    PeltierPwm = map(peltierInputPercentage, 0, 99, 0, 255);
    analogWrite(PeltierPwmPin, PeltierPwm);
  }

  peltierInputCurrent = mapfloat(float(analogRead(PeltierCurPin)), 0.0, 1023.0, 0.0, 2.0);
  
  Serial.print("Percentage : ");
  Serial.print(peltierInputPercentage);
  Serial.print(" Current=");
  Serial.println(peltierInputCurrent);
  
  delay(20);
}
