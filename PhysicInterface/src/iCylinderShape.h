#pragma once
#include "iShape.h"

class iCylinderShape : public iShape
{
public:
	iCylinderShape(const Vec3& halfExtent);
	virtual ~iCylinderShape();

	const Vec3& getHalfExtents() const;

	static iCylinderShape* cast(iShape* shape);

protected:
	iCylinderShape(shapeType type) : iShape(type) {}

private:
	Vec3 m_halfExtent;

	iCylinderShape(const iCylinderShape&) : iShape(shapeType::Cylinder) {}

	iCylinderShape& operator=(const iCylinderShape&)
	{
		return *this;
	}
};

