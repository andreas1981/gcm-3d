#include "SphereArea.h"

SphereArea::SphereArea( float _radius, float x, float y, float z )
{
	radius = _radius;
	center[0] = x;
	center[1] = y;
	center[2] = z;
};

SphereArea::~SphereArea() { };

bool SphereArea::isInArea( ElasticNode* cur_node )
{
	if( ( cur_node->coords[0] - center[0] ) * ( cur_node->coords[0] - center[0] ) +
		( cur_node->coords[1] - center[1] ) * ( cur_node->coords[1] - center[1] ) + 
		( cur_node->coords[2] - center[2] ) * ( cur_node->coords[2] - center[2] ) < 
		radius * radius ) 
	{
		return true;
	} 
	return false;
};
