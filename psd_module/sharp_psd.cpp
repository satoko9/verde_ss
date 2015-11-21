#include "sharp_psd.hpp"

Sharp_psd::Sharp_psd(Analog &pin){
	this->pin=&pin;
}

int Sharp_psd::setup(){
	pin->setupAnalogIn();
}

float Sharp_psd::voltage(){
	return pin->analogRead();
}

float Sharp_psd::distance(){
	return 8.3764 * pow(pin->analogRead(), -1.197);
}
