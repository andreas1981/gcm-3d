#include "StepPulseForm.h"

StepPulseForm::StepPulseForm(float _startTime, float _duration) : PulseForm(_startTime, _duration) { };

float StepPulseForm::calcMagnitude( float amplitude, float time, float coords[], Area* area )
{
	return amplitude;
};


