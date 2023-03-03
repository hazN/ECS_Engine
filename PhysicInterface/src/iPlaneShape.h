#pragma once
#include "iShape.h"

class iPlaneShape : public iShape
{
public:
	iPlaneShape(const Vec3& norm, float dotProd);//todo
	virtual ~iPlaneShape();

	const Vec3& getNormal() const;
	float getDotProd() const;

	static iPlaneShape* cast(iShape* shape);

protected:
	iPlaneShape(shapeType type) : iShape(type) {}

private:
	Vec3 m_Normal;
	float m_DotProd;

	iPlaneShape(const iPlaneShape&) : iShape(shapeType::Plane) {}

	iPlaneShape& operator=(const iPlaneShape&)
	{
		return *this;
	}
};