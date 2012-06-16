#ifndef _GCM_PULSE_FORM_H
#define _GCM_PULSE_FORM_H 1

#include "../../datatypes/ElasticNode.h"
#include "../GCMException.h"
#include "../areas/Area.h"

class PulseForm
{
public:
	PulseForm(float _startTime, float _duration);
	~PulseForm();
	virtual float calcMagnitude( float amplitude, float time, float coords[], Area* area ) = 0;
	bool isActive(float time);
private:
	float startTime;
	float duration;
};

#endif
