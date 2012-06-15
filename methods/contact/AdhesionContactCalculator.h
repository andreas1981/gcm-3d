#ifndef _GCM_CONTACT_ADHESION_CALCULATOR_H
#define _GCM_CONTACT_ADHESION_CALCULATOR_H  1

#include <gsl/gsl_linalg.h>
#include <vector>
using std::vector;

#include "../../datatypes/ElasticNode.h"
#include "../../datatypes/ElasticMatrix3D.h"
#include "../../datatypes/Basis.h"

class AdhesionContactCalculator
{
public:
	AdhesionContactCalculator();
	~AdhesionContactCalculator();
	void do_calc(ElasticNode* new_node, basis* basis, ElasticMatrix3D* matrix, float* values[], bool inner[], ElasticMatrix3D* virt_matrix, float* virt_values[], bool virt_inner[], int stage, float outer_normal[]);
private:
	// Used for border calculation
	gsl_matrix *U_gsl;
	gsl_vector *om_gsl;
	gsl_vector *x_gsl;
	gsl_permutation *p_gsl;
};

#endif
