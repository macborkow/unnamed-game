#pragma once

#include "Animation.hpp"
#include <SFML/Audio.hpp>

enum CollisionType
{
	nocol,
	top,
	all,
	living,
	prop
};

class Entity
{
public:
	Entity(float x, float y) 
		: m_x{x}
		, m_y{y}
		, m_isDead{false}
	{}
	virtual void update(float delta)
	{
		m_animation.update(delta);
		m_animation.getSprite().setPosition(m_x, m_y);
	}
	Animation& getAnimation()
	{
		return m_animation;
	}
	bool isDead() { return m_isDead; }
	void kill() { m_isDead = true;  }
	virtual sf::FloatRect getCollisionBox() = 0;
	CollisionType getCollisionType() { return m_collisionType; }
	void setCollisionType(CollisionType setter) { m_collisionType = setter; }
protected:
	float m_x, m_y;
	Animation m_animation;
	bool m_isDead;
	sf::FloatRect m_collisionBox;
	CollisionType m_collisionType;
};