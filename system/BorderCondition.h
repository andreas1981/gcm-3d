#ifndef _GCM_BORDER_CONDITION_H
#define _GCM_BORDER_CONDITION_H 1

#include "./areas/Area.h"
#include "./forms/PulseForm.h"
#include "../methods/BorderCalculator.h"

class BorderCondition
{
public:
	Area* area;
	PulseForm* form;
	BorderCalculator* calc;
};

#endif
