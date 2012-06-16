#ifndef _GCM_FREE_BORDER_CALCULATOR_H
#define _GCM_FREE_BORDER_CALCULATOR_H  1

#include "../BorderCalculator.h"
#include <gsl/gsl_linalg.h>

class FreeBorderCalculator : public BorderCalculator
{
public:
	FreeBorderCalculator();
	~FreeBorderCalculator();
	void do_calc(ElasticNode* new_node, ElasticMatrix3D* matrix, float* values[], bool inner[], float outer_normal[]);

protected:

private:
	// Used for border calculation
	gsl_matrix *U_gsl;
	gsl_vector *om_gsl;
	gsl_vector *x_gsl;
	gsl_permutation *p_gsl;
};

#endif
