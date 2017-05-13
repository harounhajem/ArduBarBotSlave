// SDCardHandler.h

#ifndef _SDCARDHANDLER_h
#define _SDCARDHANDLER_h

#include "Ingridients.h"
#include "SD.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SDCardHandlerClass
{
public:

	void BeginSD();

	bool Save(Container oldBottles[6]);

	void Load(Container *containers);

private:

	File myFile;

	size_t readField(File* file, char* str, size_t size, char* delim);
};

extern SDCardHandlerClass SDCardHandler;

#endif

