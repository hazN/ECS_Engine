#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

typedef glm::vec3 Vec3;
typedef glm::quat Quat;

//class : shapeType
//Summary : enum class contain the shape type
enum class shapeType
{
	Box,
	Cylinder,
	Plane,
	Sphere,
};

// class : iShape
// Summary : interface class for shape
class iShape
{
public:
	virtual ~iShape() {}
	shapeType getShapeType()
	{
		return m_shapeType;
	}

private:
	shapeType m_shapeType;
	iShape(const iShape&);
	iShape& operator=(const iShape&) {}

protected:
	iShape(shapeType type) 
	{
		m_shapeType = type;
	}
};
