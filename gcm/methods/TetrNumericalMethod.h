#ifndef _GCM_TETR_NUMERICAL_METHOD_H
#define _GCM_TETR_NUMERICAL_METHOD_H  1

class TetrMesh;

#include "NumericalMethod.h"
#include "../datatypes/ElasticNode.h"

class TetrNumericalMethod : public NumericalMethod
{
public:
	TetrNumericalMethod();
	~TetrNumericalMethod();
	virtual void do_next_part_step(ElasticNode* cur_node, ElasticNode* new_node, float time_step, int stage, TetrMesh* mesh) = 0;
	virtual float get_max_lambda(ElasticNode* node, TetrMesh* mesh) = 0;
};

#endif
