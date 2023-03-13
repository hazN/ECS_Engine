#include "iPlaneShape.h"

iPlaneShape::iPlaneShape(const Vec3& norm, float dotProd)
	: iShape(shapeType::Plane)
	, m_Normal(norm)
	, m_DotProd(dotProd)
{
}

iPlaneShape::~iPlaneShape()
{
}

// Method : getNormal
// Summary: return Normal vector of plane
// Accepts: none
const Vec3& iPlaneShape::getNormal() const
{
	return m_Normal;
}

// Method : getDotProd
// Summary: return dot product of the plane
// Accepts: none
float iPlaneShape::getDotProd() const
{
	return m_DotProd;
}

// Method : cast
// Summary: casting from shape to plane shape
// Accepts: iShape* shape
iPlaneShape* iPlaneShape::cast(iShape* shape)
{
	return dynamic_cast<iPlaneShape*>(shape);
}
