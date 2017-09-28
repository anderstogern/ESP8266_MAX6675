/*
 * MAX6675.h
 *
 *  Created on: 27 Sep 2017
 *      Author: ast
 */

#ifndef _ESP8266_MAX6675_H_
#define _ESP8266_MAX6675_H_

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class MAX6675 {
	public:
		MAX6675(uint8_t cs);
		double getTemperatureCelcius();
		double getTemperatureCelcius(uint8_t samples);
	private:
		uint8_t _cs;
};

#endif /* _ESP8266_MAX6675_H_ */
