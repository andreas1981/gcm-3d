#include "StepPulseForm.h"

StepPulseForm::StepPulseForm(float _startTime, float _duration) : PulseForm(_startTime, _duration) { };

float StepPulseForm::calcMagnitudeNorm( float time, float coords[], Area* area )
{
	return 1.0;
};


