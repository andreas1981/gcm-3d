#include "PulseForm.h"

#include <iostream>
using namespace std;

PulseForm::PulseForm(float _startTime, float _duration)
{
	startTime = _startTime;
	duration = _duration;
std::cout << "DEBUG: PulseForm constructor called!\n";
};

PulseForm::~PulseForm() { };

bool PulseForm::isActive(float time)
{
	if( duration < 0 )
		return true;
	if( time < startTime || time > startTime + duration)
		return false;
	return true;
};
