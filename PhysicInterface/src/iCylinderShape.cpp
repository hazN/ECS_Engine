#include "iCylinderShape.h"

iCylinderShape::iCylinderShape(const Vec3& halfExtent)
    : iShape(shapeType::Cylinder)
    , m_halfExtent(halfExtent)
{
}

iCylinderShape::~iCylinderShape()
{
}

// Method : getHalfExtents
// Summary: return half extents of the cylinder
// Accepts: none
const Vec3& iCylinderShape::getHalfExtents() const
{
    return m_halfExtent;
}

// Method : cast
// Summary: casting from shape to cylinder shape
// Accepts: iShape* shape
iCylinderShape* iCylinderShape::cast(iShape* shape)
{
	return dynamic_cast<iCylinderShape*>(shape);
}
