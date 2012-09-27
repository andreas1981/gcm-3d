#include "CylinderArea.h"

CylinderArea::CylinderArea( float _radius, float _bX, float _bY, float _bZ, float _eX, float _eY, float _eZ )
{
	radius = _radius;
	begin[0] = _bX;
	begin[1] = _bY;
	begin[2] = _bZ;

	end[0] = _eX;
	end[1] = _eY;
	end[2] = _eZ;
};

CylinderArea::~CylinderArea() { };

bool CylinderArea::isInArea( ElasticNode* cur_node )
{
	throw GCMException( GCMException::CONFIG_EXCEPTION, "CylinderArea.isInArea is not implemented yet!");
};
