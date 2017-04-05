// DrinkMixer.h

#ifndef _DRINKMIXER_h
#define _DRINKMIXER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class DrinkMixerClass
{
 protected:


 public:
	void init();
};

extern DrinkMixerClass DrinkMixer;

#endif

