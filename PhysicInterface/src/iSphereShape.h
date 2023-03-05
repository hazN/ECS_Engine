#pragma once
#include "iShape.h"

class iSphereShape : public iShape
{
public:
	iSphereShape(float rad);
	virtual ~iSphereShape();

	float getRad() const;

	static iSphereShape* cast(iShape* shape);

protected:
	iSphereShape(shapeType type) : iShape(type) {}

private:
	float m_Rad;

	iSphereShape(const iSphereShape&) : iShape(shapeType::Sphere) {}

	iSphereShape& operator=(const iSphereShape&)
	{
		return *this;
	}
};