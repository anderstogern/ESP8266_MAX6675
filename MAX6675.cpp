/*
 * MAX6675.cpp
 *
 *  Created on: 27 Sep 2017
 *      Author: ast
 */

#include "MAX6675.h"
#include <SPI.h>

MAX6675::MAX6675(uint8_t cs) {
	_cs = 15;

	pinMode(_cs, OUTPUT);
	digitalWrite(_cs, HIGH);

	SPI.begin();
}

double MAX6675::getTemperatureCelcius() {
	uint16_t v;

	pinMode(_cs, OUTPUT);
	digitalWrite(_cs, HIGH);

	SPI.begin();

	digitalWrite(_cs, LOW);
	delay(1);

	SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));

	v = SPI.transfer(0);
	v <<= 8;
	v |= SPI.transfer(0);

	SPI.endTransaction();

	digitalWrite(_cs, HIGH);

	if (v & 0x4) {
		// uh oh, a serious problem!
		return NAN;
	}

	if (v & 0x8000) {
		// Negative value, drop the lower 18 bits and explicitly extend sign bits.
		v = 0xFFC00000 | ((v >> 10) & 0x003FF);
	} else {
		// Positive value, just drop the lower 18 bits.
		v >>= 3;
	}

	double centigrade = v;

	// LSB = 0.25 degrees C
	centigrade *= 0.25;
	return centigrade;
}

double MAX6675::getTemperatureCelcius(uint8_t samples) {
	//double temps[samples];
	double avgTemp = 0.0;

	for (int sample = 0; sample < samples; sample++) {
		/*double temp = getTemperatureCelcius();
		if (sample == 0) {
			for (int i = 0; i < samples; i++) {
				temps[i] = temp;
			}
		} else {
			for (int i = 0; i < samples - 1; i++) {
				temps[i] = temps[i + 1];
			}
			temps[5] = temp;
		}*/
		avgTemp += getTemperatureCelcius();

		delay(10);
	}

	/*for (int sample = 0; sample < samples; sample++) {
		avgTemp += temps[sample];
	}*/
	return avgTemp / (float) samples;
}
