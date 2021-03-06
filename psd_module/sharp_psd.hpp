#ifndef SHARP_PSD_HPP
#define SHARP_PSD_HPP

#include "analog.hpp"
#include "math.h"

class Sharp_psd{
private:
	Analog *pin;
public:
	Sharp_psd(Analog &analog_pin);
	int setup();			//analog入力設定
	float voltage();		//入力された電圧[v]を返す
	float distance();		//物体までの距離[cm]を返す
};

#endif//SHARP_PSD_HPP
