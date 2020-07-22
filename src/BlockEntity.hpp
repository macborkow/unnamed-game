#pragma once

#include "Entity.hpp"



class BlockEntity : public Entity
{
public:
	BlockEntity(float x, float y, CollisionType collisionType, std::vector < std::shared_ptr<Entity>>& entities)
		: Entity(x, y)
		, m_entities{ entities }
	{m_collisionType = collisionType;
	m_isDec = false; }
	
	void update(float delta)
	{
		if (m_isDec == true)
		{
			bool hasCollided = false;

			for (auto &e : m_entities)
			{
				if(m_animation.getBounds() != e->getAnimation().getBounds() && !e->isDead())
				if (e->getCollisionBox().intersects(this->getCollisionBox()))
				{
					hasCollided = true;
				}
			}

			if (!hasCollided && m_animation.getCurrentID() == "col")
			{
				m_animation.setAnimation("stand");
				m_animation.resetCurrent();
			}
			else if (hasCollided && m_animation.getCurrentID() != "col")
			{
				m_animation.setAnimation("col");
				m_animation.resetCurrent();
			}

		}
		Entity::update(delta);
	}


	sf::FloatRect getCollisionBox() {
		if (m_isDec)
		{
			sf::FloatRect temp = m_animation.getBounds();
			temp.top += temp.height*0.8;
			temp.height = temp.height*0.2;
			temp.left += temp.width *0.1;
			temp.width -= temp.width *0.2;
			return temp;
		}
		
		return m_animation.getBounds();
	}
	void makeDec() { m_isDec = true; }
private:
	std::vector < std::shared_ptr<Entity>>& m_entities;
	bool m_isDec;
};