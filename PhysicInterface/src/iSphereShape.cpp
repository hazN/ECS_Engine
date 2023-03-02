#include "iSphereShape.h"

iSphereShape::iSphereShape(float rad)
	: iShape(shapeType::Sphere)
	, m_Rad(rad)
{

}

iSphereShape::~iSphereShape()
{
}

float iSphereShape::getRad() const
{
	return m_Rad;
}

iSphereShape* iSphereShape::cast(iShape* shape)
{
	return dynamic_cast<iSphereShape*>(shape);
}
