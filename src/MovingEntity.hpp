#pragma once

#include "LivingEntity.hpp"
#include <iostream>

enum Input
{
	left,
	right,
	jump,
	none,
	attack,
	block
};

class MovingEntity : public LivingEntity
{
public:
	MovingEntity(float x, float y, int hp, bool canAttack, std::vector < std::shared_ptr<Entity>>& entities)
		: LivingEntity(x, y)
		, m_max_velocity{150}
		, m_acceleration{500}
		, m_entities{ entities }
		, m_deadCounter{ 3 }
	{
		m_input = none; 
		m_isJumping = false;
		m_jumpTimer = 0;
		m_x_velocity = 0;
		m_y_velocity = 0;
		m_isOnGround = false;
		m_isAttacking = false;
		m_attackTimer = 0;
		m_hp = hp;
		m_isDamaged = false;
		m_damageCounter = 0;
		m_canAttack = canAttack;
	}

	void update(float delta);
	
	void setInput(Input input)
	{
		m_input = input;
	}

	bool timeToErase()
	{
		if (m_deadCounter < 0)
			return true;
		else
			return false;
	}

	sf::FloatRect getCollisionBox() {

		sf::FloatRect temp;
		temp.height = m_animation.getBounds().height * 0.95;
		temp.top = m_animation.getBounds().top + 0.05*m_animation.getBounds().height;
		temp.left = m_animation.getBounds().left + 0.3*m_animation.getBounds().width;
		temp.width = m_animation.getBounds().width*0.4;
		return temp;
	}

	sf::Vector2f getVelocity() {
		return sf::Vector2f(m_x_velocity, m_y_velocity);
	}

	sf::Vector2f getPos() {
		return sf::Vector2f(m_x, m_y);
	}

	void setPos(float x, float y)
	{
		m_x = x;
		m_y = y;
	}

	void damage()
	{
		if (m_damageCounter <= 0)
		{
			
			m_hp--;
			m_isDamaged = true;
			if (m_hp <= 0)
				kill();
			else
				playSound("jump");
		}
	}
	
	void knockback(int dir)
	{
		if (m_damageCounter <= 0)
		{
			if (dir == -1)
			{
				m_isJumping = true;
				m_jumpTimer = 0.295;
				m_x_velocity = -m_max_velocity;
			}
			else if (dir == 1)
			{
				m_isJumping = true;
				m_jumpTimer = 0.295;
				m_x_velocity = m_max_velocity;
			}
		}
	}

	bool canAttack() { return m_canAttack; }

	int getHp() { return m_hp; }

	float getDamageCounter() { return m_damageCounter;  }

protected:
	float m_x_velocity, m_y_velocity;
	float m_max_velocity, m_acceleration;
	Input m_input;
	float m_jumpTimer;
	float m_attackTimer;
	bool m_isAttacking;
	bool m_isJumping;
	bool m_isOnGround;
	float m_deadCounter;
	int m_hp;
	bool m_isDamaged;
	float m_damageCounter;
	bool m_canAttack;


	std::vector < std::shared_ptr<Entity>>& m_entities;

};