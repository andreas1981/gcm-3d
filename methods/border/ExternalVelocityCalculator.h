#ifndef _GCM_EXTERNAL_VELOCITY_CALCULATOR_H
#define _GCM_EXTERNAL_VELOCITY_CALCULATOR_H  1

#include "../BorderCalculator.h"
#include <gsl/gsl_linalg.h>
#include "../../system/quick_math.h"

class ExternalVelocityCalculator : public BorderCalculator
{
public:
	ExternalVelocityCalculator();
	~ExternalVelocityCalculator();
	void do_calc(ElasticNode* new_node, ElasticMatrix3D* matrix, float* values[], bool inner[], float outer_normal[], float scale);

protected:

private:
	// Used for border calculation
	gsl_matrix *U_gsl;
	gsl_vector *om_gsl;
	gsl_vector *x_gsl;
	gsl_permutation *p_gsl;

	quick_math qm;
};

#endif
