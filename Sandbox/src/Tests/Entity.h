#pragma once

class Entity
{
public:
	Entity(float xPos, float yPos)
		: m_XPos(xPos), m_YPos(yPos){}
	virtual ~Entity() {}


	virtual bool Move(float speed, float xDir, float yDir) = 0;

	virtual inline float getX() { return m_XPos; }
	virtual inline float getY() { return m_YPos; }

protected:
	virtual inline void setX(float xPos) { m_XPos = xPos; }
	virtual inline void setY(float yPos) { m_YPos = yPos; }

	float m_XPos, m_YPos;
};