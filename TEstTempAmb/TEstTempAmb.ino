#define LM35PIN A0

void setup() 
{
  analogReference(INTERNAL1V1);
  Serial.begin(9600);
  pinMode(LM35PIN, INPUT);
}

void loop() 
{
  int AnalogValue = analogRead(LM35PIN);
  Serial.print("Raw Value : ");
  Serial.print(AnalogValue);
  double TempC = (4.9 * (double)(AnalogValue) * 100.0)/1024.0;
  Serial.print(" Converted Value : ");
  Serial.println(TempC);
  delay(1000);

}
