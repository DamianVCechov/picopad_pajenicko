// ****************************************************************************
//
//                              PicoPad Battery
//
// ****************************************************************************
// Interface and part of the code taken from Picopad SDK
// https://github.com/pajenicko/picopad

#ifndef _PICOPAD_BAT_H
#define _PICOPAD_BAT_H

#ifdef __cplusplus
extern "C" {
#endif

// battery input pin

// Using divider 1:1
//#define BAT_PIN		28		// input from battery
//#define BAT_ADC		ADC_MUX_GPIO28	// ADC input
//#define BAT_MUL		2		// voltage multiplier

// Using Pico internal divider 1:2
#define BAT_PIN				29		// input from battery
#define BAT_ADC				ADC_MUX_GPIO29	// ADC input
#define BAT_MUL				3		// voltage multiplier
#define BAT_DIODE_FV_INT 	311		// voltage drop in mV on diode
#define BAT_DIODE_FV 		0.311f		// voltage drop in mV on diode

// init battery measurement
void BatInit();

// get battery voltage in V
float GetBat();

// get battery voltage, integer in mV
int GetBatInt();

// terminate battery measurement
void BatTerm();

#ifdef __cplusplus
}
#endif

#endif // _PICOPAD_BAT_H
