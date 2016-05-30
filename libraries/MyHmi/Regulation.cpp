#include <Regulation.h>
#include <Adafruit_AM2315.h>
#include <LM35.h>
#include <Configuration.h>

#define SampleTime	10000
#define REGUL_DEBUG_PRINTF  1

extern config_t configuration;
extern Adafruit_AM2315 am2315;
extern LM35 AmbientTemp;

Regulation Regul(configuration.TempConsigne);

void(* resetFunc) (void) = 0; //declare reset function @ address 0

Regulation::Regulation(int &setPoint):
ExtSetPoint(setPoint),
IntSetPoint((double)(ExtSetPoint)/10.),
Kp(10),
Ki(0.5),
Kd(4),
aTuneStep(20), 
aTuneNoise(0.1), 
aTuneStartValue(0),
aTuneLookBack(240),
tuning(false),
Mtc(new SimpleMotorControler()),
myPID(new PID(&Input, &Output, &IntSetPoint, Kp, Ki, Kd, REVERSE)),
aTune(new PID_ATune(&Input, &Output))
{ 
}

void Regulation::begin()
{
	Mtc->begin();
	LastMillis = millis() - SampleTime;
	LastOutput = -1234;
	LastInput = am2315.readTemperature();
	TempIsRising = false;
	TempIsFalling = false;
	Compteur = 0;
	
	//turn the PID on
	myPID->SetMode(AUTOMATIC);
}

void Regulation::run()
{
	if(millis() - LastMillis >= SampleTime)
	{
		IntSetPoint = (double)(ExtSetPoint)/10.;
		Input = am2315.readTemperature();
		
		if(isnan(Input))
		{
			Compteur++;
			if(Compteur >= 2)
				resetFunc();
			return;
		}
		else
			Compteur = 0;

		if(tuning)
		{
			byte val = (aTune->Runtime());
			if (val!=0)
			{
				tuning = false;
				//we're done, set the tuning parameters
				Kp = aTune->GetKp();
				Ki = aTune->GetKi();
				Kd = aTune->GetKd();
				myPID->SetTunings(Kp,Ki,Kd);
				//turn the PID on
				myPID->SetMode(AUTOMATIC);
			}
		}
		else
		{
			if(IntSetPoint - configuration.DeltatTemp/10 >= Input)
			{
				//on regule en monter de temperature
				#if (REGUL_DEBUG_PRINTF == 1)
				Serial.print("SetOutputLimits: ");
				Serial.print(((int)(((double)(-configuration.HeatMax)/100. * 32.))));
				Serial.println(", 0");
				#endif
				myPID->SetOutputLimits( ((int)(((double)(-configuration.HeatMax)/100. * 32.))),0);
				TempIsRising = true;
				TempIsFalling = false;
			}
			else if (IntSetPoint + configuration.DeltatTemp/10 <= Input)
			{
				//on regule en descente de temperature
				#if (REGUL_DEBUG_PRINTF == 1)
				Serial.print("SetOutputLimits: 0, ");
				Serial.println(((int)(((double)(configuration.CoolMax)/100. * 32.))));
				#endif
				myPID->SetOutputLimits(0, ((int)(((double)(configuration.CoolMax)/100. * 32.))));
				TempIsRising = false;
				TempIsFalling = true;
			}
			else
			{
				myPID->SetOutputLimits(((int)(((double)(-configuration.HeatMax)/100. * 32.))) / 2, ((int)(((double)(configuration.CoolMax)/100. * 32.))) / 2);
				TempIsRising = false;
				TempIsFalling = false;
			}
			myPID->Compute();
		}
		
		if(LastOutput != Output || Mtc->IsInError())
		{
			#if (REGUL_DEBUG_PRINTF == 1)
			Serial.print("SetPoint: ");
			Serial.print(IntSetPoint);
			Serial.print(" Input: ");
			Serial.print(Input);
			Serial.print(" OutPut:");
			Serial.println(Output);
			#endif
			Mtc->setMotorSpeed(Output * 100);
			
			LastOutput = Output;
		}
		LastMillis = millis();
	}
}

void Regulation::tune(bool shallTune)
{
	if(!tuning)
	{
		//Set the output to the desired starting frequency.
		Output=aTuneStartValue;
		aTune->SetNoiseBand(aTuneNoise);
		aTune->SetOutputStep(aTuneStep);
		aTune->SetLookbackSec((int)aTuneLookBack);
		tuning = true;
	}
	else
	{ 
		//cancel autotune
		aTune->Cancel();
		tuning = false;
		//turn the PID on
		myPID->SetMode(AUTOMATIC);
	}
}

void Regulation::getTempTendency(bool &Rise, bool &Fall)
{
	Rise = TempIsRising;
	Fall = TempIsFalling;
}

bool Regulation::IsTunning()
{
	return tuning;
}

int Regulation::getOutput()
{
	return Output;
}

unsigned int Regulation::getVariable(unsigned char variableID)
{
	return Mtc->getVariable(variableID);
}

void Regulation::getPidConfig(double &Kpl, double &Kil, double &Kdl)
{
	Kpl = Kp;
	Kil = Ki;
	Kdl = Kd;
}