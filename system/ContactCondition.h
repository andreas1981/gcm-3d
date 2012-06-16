#ifndef _GCM_CONTACT_CONDITION_H
#define _GCM_CONTACT_CONDITION_H 1

#include "./areas/Area.h"
#include "./forms/PulseForm.h"
#include "../methods/ContactCalculator.h"

class ContactCondition
{
public:
	Area* area;
	PulseForm* form;
	ContactCalculator* calc;
};

#endif
