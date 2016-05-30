#ifndef CONFIGURATION_h
#define CONFIGURATION_h

#define BlkPwmPin  9
#define CoolFanPwmPin	2
#define HeatFanPwmPin	3

typedef struct 
{
	int TempConsigne;
    byte BlkPwmValue;
	byte DeltatTemp;
	byte PwmCoolFan;
	byte pwmHeatFan;
	byte HeatMax;
	byte CoolMax;
	byte spare1;
	byte Spare2;
} config_t;

#endif