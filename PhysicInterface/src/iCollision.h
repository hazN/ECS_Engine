#pragma once
#include "iBodyType.h"

class iCollision
{
public:
	virtual ~iCollision() {}
	BodyType getBodyType() const
	{
		return m_bodyType;
	}

private:
	BodyType m_bodyType;
	iCollision(const iCollision&) {}
	iCollision& operator=(const iCollision&)
	{
		return *this;
	}

protected:
	iCollision(BodyType type)
	{
		m_bodyType = type;
	}
};

