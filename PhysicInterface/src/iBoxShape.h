#pragma once
#include "iShape.h"


class iBoxShape : public iShape
{
public:
	iBoxShape(const Vec3& halfExtent  );
	virtual ~iBoxShape();

	const Vec3& getHalfExtents() const;

	static iBoxShape* cast(iShape* shape);

protected:
	iBoxShape(shapeType type) : iShape(type) {}

private:
	Vec3 m_halfExtent;

	iBoxShape(const iBoxShape&) : iShape(shapeType::Box) {}
	
	iBoxShape& operator=(const iBoxShape&)
	{
		return *this;
	}
};

