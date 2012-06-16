#include "ExternalVelocityCalculator.h"

ExternalVelocityCalculator::ExternalVelocityCalculator()
{
	U_gsl = gsl_matrix_alloc (9, 9);
	om_gsl = gsl_vector_alloc (9);
	x_gsl = gsl_vector_alloc (9);
	p_gsl = gsl_permutation_alloc (9);
};

ExternalVelocityCalculator::~ExternalVelocityCalculator()
{
	gsl_matrix_free(U_gsl);
	gsl_vector_free(om_gsl);
	gsl_vector_free(x_gsl);
	gsl_permutation_free(p_gsl);
};

ExternalVelocityCalculator* ExternalVelocityCalculator::getInstance()
{
	static ExternalVelocityCalculator fbc;
	return &fbc;
};

void ExternalVelocityCalculator::do_calc(ElasticNode* new_node, ElasticMatrix3D* matrix, float* values[], bool inner[], float outer_normal[])
{

	float local_n[3][3];
	local_n[0][0] = outer_normal[0];
	local_n[0][1] = outer_normal[1];
	local_n[0][2] = outer_normal[2];

	qm.create_local_basis(local_n[0], local_n[1], local_n[2]);

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
			// omega (as right-hand part of OLE) is zero - it is not-moving border
			gsl_vector_set(om_gsl, i, 0);
			// corresponding string in matrix is zero ...
			for(int j = 0; j < 9; j++)
				gsl_matrix_set(U_gsl, i, j, 0);
			// ... except velocity
			if ( outer_count == 3 ) {
				// Velocity normal
				gsl_matrix_set(U_gsl, i, 0, local_n[0][0]);
				gsl_matrix_set(U_gsl, i, 1, local_n[0][1]);
				gsl_matrix_set(U_gsl, i, 2, local_n[0][2]);
				outer_count--;
			} else if ( outer_count == 2 ) {
				// Velocity tangential
				gsl_matrix_set(U_gsl, i, 0, local_n[1][0]);
				gsl_matrix_set(U_gsl, i, 1, local_n[1][1]);
				gsl_matrix_set(U_gsl, i, 2, local_n[1][2]);
				outer_count--;
			} else if ( outer_count == 1 ) {
				// Velocity tangential
				gsl_matrix_set(U_gsl, i, 0, local_n[2][0]);
				gsl_matrix_set(U_gsl, i, 1, local_n[2][1]);
				gsl_matrix_set(U_gsl, i, 2, local_n[2][2]);
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
