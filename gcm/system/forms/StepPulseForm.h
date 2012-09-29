#ifndef _GCM_PULSE_FORM_STEP_H
#define _GCM_PULSE_FORM_STEP_H 1

#include "./PulseForm.h"

class StepPulseForm : public PulseForm
{
public:
	StepPulseForm(float _startTime, float _duration);
	float calcMagnitudeNorm( float time, float coords[], Area* area );
};

#endif
