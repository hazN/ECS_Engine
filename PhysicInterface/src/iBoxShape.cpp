#include "iBoxShape.h"

iBoxShape::iBoxShape(const Vec3& halfExtent)
    : iShape(shapeType::Box)
    , m_halfExtent(halfExtent)
{
}

iBoxShape::~iBoxShape()
{
}

// Method : getHalfExtents
// Summary: return half extents of the box
// Accepts: none
const Vec3& iBoxShape::getHalfExtents() const
{
    return m_halfExtent;
}

// Method : cast
// Summary: casting from shape to box shape
// Accepts: iShape* shape
iBoxShape* iBoxShape::cast(iShape* shape)
{
    return dynamic_cast<iBoxShape*>(shape);
}
