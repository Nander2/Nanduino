int outPin = A5;                 // digital pin 8
int inputPin = A0;
int firstGatePin = 2;
int secondGatePin = 3;
int inputVoltage = 0;
unsigned long firstGateTime;

#define CHARGE  400

#define CYCLE   50

void setup()
{
  Serial.begin(250000);
  
  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  pinMode(outPin, OUTPUT);      // sets the digital pin as output
  pinMode(inputPin, INPUT);      // sets the digital pin as output
  pinMode(firstGatePin, INPUT);      // sets the digital pin as output
  pinMode(secondGatePin, INPUT);      // sets the digital pin as output
  attachInterrupt(digitalPinToInterrupt(firstGatePin), First, RISING );
  attachInterrupt(digitalPinToInterrupt(secondGatePin), Second, RISING );
  analogReference(DEFAULT);
}

void First()
{
  firstGateTime = micros();
}

void Second()
{
  unsigned long deltaT = micros() - firstGateTime; 
  double Speed = 0.0613 / ((double)(deltaT)/ 1000000.);
  Serial.print("Speed is ");
  Serial.print(Speed);
  Serial.println("m.s-1");
}
 
void loop()
{
  int inputRead = 0;
  double inputSum  = 0;
  inputVoltage = 0;
  
  for(int i = 0; i <= 10; i++)
  {
    inputRead =  analogRead(inputPin);
    inputSum += inputRead;
  }
  
  inputVoltage = ((450./1003.) * (inputSum / 10.)) * 0.82;

  if(inputVoltage < CHARGE)
  {
    int loop = 0;
    while(inputVoltage < CHARGE && loop < CYCLE)
    {
      digitalWrite(outPin, HIGH);   // sets the pin on
      delayMicroseconds(165);        // pauses for 50 microseconds      
      digitalWrite(outPin, LOW);    // sets the pin off
      delayMicroseconds(155);        // pauses for 50 microseconds
      ++loop;
    }
  }      
}
