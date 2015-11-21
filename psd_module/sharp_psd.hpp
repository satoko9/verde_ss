#ifndef SHARP_PSD_HPP
#define SHARP_PSD_HPP

#include "analog.hpp"
#include "math.h"

class Sharp_psd{
private:
	Analog *pin;
public:
	Sharp_psd(Analog &analog_pin);
	int setup();			//analog���͐ݒ�
	float voltage();		//���͂��ꂽ�d��[v]��Ԃ�
	float distance();		//���̂܂ł̋���[cm]��Ԃ�
};

#endif//SHARP_PSD_HPP
