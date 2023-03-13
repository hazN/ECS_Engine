#include "iSphereShape.h"

iSphereShape::iSphereShape(float rad)
	: iShape(shapeType::Sphere)
	, m_Rad(rad)
{

}

iSphereShape::~iSphereShape()
{
}

// Method : getRad
// Summary: return dot radius of the sphere
// Accepts: none
float iSphereShape::getRad() const
{
	return m_Rad;
}

// Method : cast
// Summary: casting from shape to sphere shape
// Accepts: iShape* shape
iSphereShape* iSphereShape::cast(iShape* shape)
{
	return dynamic_cast<iSphereShape*>(shape);
}
