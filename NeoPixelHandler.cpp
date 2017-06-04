// 
// 
// 

#include "NeoPixelHandler.h"



void NeoPixelHandlerClass::NeoPixelRainBow(uint8_t wait)
{
	if (millis() - timerLed > wait)
	{
		for (i = 0; i < _strip.numPixels(); i++) {
			_strip.setPixelColor(i, Wheel((i + j) & 255));
		}
		_strip.show();
		timerLed = millis();
		j++;
		if (j > 255)
			j = 0;
	}
}

void NeoPixelHandlerClass::SetColor_DrinkProduce()
{
	for (int i = 0; i < _strip.numPixels(); i++) {

		// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
		_strip.setBrightness(255);

		_strip.setPixelColor(i, _strip.Color(128, 0, 128)); // Moderately bright green color.
		_strip.show(); // This sends the updated pixel color to the hardware.
		delay(90);

	}

	colorFade = true;
	brightness = 255;
}

void NeoPixelHandlerClass::SetColor_Off()
{
	if (colorFade)
	{
		if (millis() - timerFade > 38UL)
		{
			brightness--;

			for (int i = 0; i < _strip.numPixels(); i++) {


				_strip.setBrightness(brightness);
				_strip.show(); // This sends the updated pixel color to the hardware.

				if (brightness < 1)
				{
					brightness = 255;
					colorFade = false;
					Serial.println("\n---------------\nLed Fade Fininsh\n---------------");
				}

			}

			timerFade = millis();
		}
	}
}

uint32_t NeoPixelHandlerClass::Wheel(byte WheelPos)
{
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return _strip.Color(255 - WheelPos * 3, 0, WheelPos * 3, 0);
	}
	if (WheelPos < 170) {
		WheelPos -= 85;
		return _strip.Color(0, WheelPos * 3, 255 - WheelPos * 3, 0);
	}
	WheelPos -= 170;
	return _strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0, 0);
}



NeoPixelHandlerClass::NeoPixelHandlerClass(Adafruit_NeoPixel &stripy)
{
	_strip = stripy;
}
