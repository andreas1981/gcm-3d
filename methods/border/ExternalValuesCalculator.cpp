#include "ExternalValuesCalculator.h"

#define VAR1 0
#define VAL1 0
#define VAR2 1
#define VAL2 0
#define VAR3 2
#define VAL3 0

ExternalValuesCalculator::ExternalValuesCalculator()
{
	U_gsl = gsl_matrix_alloc (9, 9);
	om_gsl = gsl_vector_alloc (9);
	x_gsl = gsl_vector_alloc (9);
	p_gsl = gsl_permutation_alloc (9);
};

ExternalValuesCalculator::~ExternalValuesCalculator()
{
	gsl_matrix_free(U_gsl);
	gsl_vector_free(om_gsl);
	gsl_vector_free(x_gsl);
	gsl_permutation_free(p_gsl);
};

void ExternalValuesCalculator::do_calc(ElasticNode* new_node, ElasticMatrix3D* matrix, float* values[], bool inner[], float outer_normal[], float scale)
{

	// Tmp value for GSL solver
	int s;

	int outer_count = 3;

	// Here we will store (omega = Matrix_OMEGA * u)
	float omega[9];

	for(int i = 0; i < 9; i++)
	{
		// If omega is 'inner' one
		if(inner[i])
		{
			// Calculate omega value
			omega[i] = 0;
			for(int j = 0; j < 9; j++)
			{
				omega[i] += matrix->U(i,j) * values[i][j];
			}
			// Load appropriate values into GSL containers
			gsl_vector_set(om_gsl, i, omega[i]);
			for(int j = 0; j < 9; j++)
				gsl_matrix_set(U_gsl, i, j, matrix->U(i,j));
		}
		// If omega is 'outer' one
		else
		{
			// omega (as right-hand part of OLE) is zero - it is free border, no external stress
			gsl_vector_set(om_gsl, i, 0);
			// corresponding string in matrix is zero ...
			for(int j = 0; j < 9; j++)
				gsl_matrix_set(U_gsl, i, j, 0);

			// ... except normal and tangential stress
			// We use outer normal to find total stress vector (sigma * n) - sum of normal and shear - and tell it is zero
			// TODO - never-ending questions - is everything ok with (x-y-z) and (ksi-eta-dzeta) basises?

			if ( outer_count == 3 ) {
				gsl_matrix_set(U_gsl, i, VAR1, 1);
				gsl_vector_set(om_gsl, i, VAL1);
				outer_count--;
			} else if ( outer_count == 2 ) {
				gsl_matrix_set(U_gsl, i, VAR2, 1);
				gsl_vector_set(om_gsl, i, VAL2);
				outer_count--;
			} else if ( outer_count == 1 ) {
				gsl_matrix_set(U_gsl, i, VAR3, 1);
				gsl_vector_set(om_gsl, i, VAL3);
				outer_count--;
			}
		}
	}

	// Solve linear equations using GSL tools
	gsl_linalg_LU_decomp (U_gsl, p_gsl, &s);
	gsl_linalg_LU_solve (U_gsl, p_gsl, om_gsl, x_gsl);

	for(int j = 0; j < 9; j++)
		new_node->values[j] = gsl_vector_get(x_gsl, j);

};
