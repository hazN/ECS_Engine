#include "iBoxShape.h"

iBoxShape::iBoxShape(const Vec3& halfExtent)
    : iShape(shapeType::Box)
    , m_halfExtent(halfExtent)
{
}

iBoxShape::~iBoxShape()
{
}

const Vec3& iBoxShape::getHalfExtents() const
{
    return m_halfExtent;
}

iBoxShape* iBoxShape::cast(iShape* shape)
{
    return dynamic_cast<iBoxShape*>(shape);
}
