#ifndef SHARP_PSD_HPP
#define SHARP_PSD_HPP

#include "analog.hpp"
#include "math.h"

class Sharp_psd{
private:
	Analog *pin;
public:
	Sharp_psd(Analog &analog_pin);
	int setup();			//analog“ü—Íİ’è
	float voltage();		//“ü—Í‚³‚ê‚½“dˆ³[v]‚ğ•Ô‚·
	float distance();		//•¨‘Ì‚Ü‚Å‚Ì‹——£[cm]‚ğ•Ô‚·
};

#endif//SHARP_PSD_HPP
