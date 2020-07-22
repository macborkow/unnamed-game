#include "MovingEntity.hpp"

void MovingEntity::update(float delta)
{

	if (this->isDead())
	{
		m_animation.setAnimation("dead");
		
		if (m_deadCounter == 3)
			playSound("death");

		if (m_deadCounter >= 0)
			m_deadCounter -= delta;
		
		m_input = none;
		m_x_velocity = 0;
		m_hp = 2;
		
	}


	
	m_isBlocked = false;
	
	if (m_input == attack && !m_canAttack)
		m_input = none;

	switch (m_input)
	{
	case left:
		if (m_y_velocity == 0)
			m_x_velocity -= m_acceleration * delta;

		if (m_x_velocity < -m_max_velocity)
			m_x_velocity = -m_max_velocity;
		break;
	case right:
		if (m_y_velocity == 0)
			m_x_velocity += m_acceleration * delta;

		if (m_x_velocity > m_max_velocity)
			m_x_velocity = m_max_velocity;
		break;
	case jump:
		if (m_isOnGround && !m_isAttacking)
		{
			m_isJumping = true;
			playSound("jump");
		}
		break;
	case none:
		if (m_x_velocity > 0 && m_y_velocity == 0)
			m_x_velocity -= m_acceleration / 2 * delta;
		if (m_x_velocity < 0 && m_y_velocity == 0)
			m_x_velocity += m_acceleration / 2 * delta;
		break;
	case attack:
		if (m_isOnGround && !m_isDamaged && m_damageCounter <= 0.5 && !m_isJumping )
		{
			m_isAttacking = true;
		}
			break;
	default: break;
	}

	if (m_x_velocity < m_acceleration / 100 && m_x_velocity > -m_acceleration / 100)
		m_x_velocity = 0;

	if (m_isDamaged && m_damageCounter <= 0)
	{
		m_isDamaged = false;
		m_damageCounter = 1;
	}

	if (m_damageCounter > 0)
	{
		if (m_attackTimer < 0.2 && m_isAttacking)
		{
			m_isAttacking = false;
			m_attackTimer = 0;
			this->getAnimation().resetCurrent();
		}
		m_damageCounter -= delta;
		
		if(m_damageCounter <= 0.01)
			this->getAnimation().getSprite().setColor(sf::Color::White);
		else if (m_damageCounter <= 0.9)
			if(!this->isDead())
				this->getAnimation().getSprite().setColor(sf::Color(255,255,255,m_damageCounter*255*4));
			else
				this->getAnimation().getSprite().setColor(sf::Color::White);
		else
			this->getAnimation().getSprite().setColor(sf::Color::Red);
	}

	if (m_isAttacking)
	{
		m_attackTimer += delta;
		if (m_attackTimer < 0.25)
		{
			if (m_animation.getFlip() == false)
			{
				m_x_velocity = m_max_velocity / 4;
			}
			else if (m_animation.getFlip() == true)
			{
				m_x_velocity = -m_max_velocity / 4;
			}
		}
		else if (m_attackTimer < 0.3)
		{
			if (m_animation.getFlip() == false)
			{
				m_x_velocity = m_max_velocity / 4;
			}
			else if (m_animation.getFlip() == true)
			{
				m_x_velocity = -m_max_velocity / 4;
			}
			m_y_velocity = -100;
		}
		else
			m_x_velocity = 0;
	}

	if (m_isJumping)
	{
		m_jumpTimer += delta;
		m_y_velocity = -2.4*m_max_velocity;
	}
	else
	{
		int factor;
		if (m_isDead)
			factor = 4;
		else
			factor = 2;
		m_y_velocity += m_acceleration * factor * delta;
	}

	m_isOnGround = false;
	bool hit_something = false;

	for (auto &a : m_entities)
	{
		if (m_animation.getBounds() != a->getAnimation().getBounds())
		{
			sf::FloatRect tem;
			tem.left = m_animation.getBounds().left + m_animation.getBounds().width * 0.3;
			tem.top = m_animation.getBounds().top + m_animation.getBounds().height;
			tem.height = std::abs(m_y_velocity * delta);
			tem.width = m_animation.getBounds().width - m_animation.getBounds().width * 0.6;


			sf::FloatRect tem2;
			tem2.left = m_animation.getBounds().left + m_animation.getBounds().width * 0.3;
			tem2.top = m_animation.getBounds().top + m_animation.getBounds().height*0.05;
			tem2.height = m_animation.getBounds().height - m_animation.getBounds().height*0.05;
			tem2.width = m_animation.getBounds().width - m_animation.getBounds().width * 0.6;

			sf::FloatRect temp;
			if (a->getCollisionType() == top || a->getCollisionType() == all)
			{

				temp.left = a->getAnimation().getBounds().left + a->getAnimation().getBounds().width / 10;
				temp.top = a->getAnimation().getBounds().top;
				temp.height = 0.1;
				temp.width = a->getAnimation().getBounds().width - a->getAnimation().getBounds().width / 5;

				if (tem.intersects(temp) && m_y_velocity > 0)
				{
					m_isOnGround = true;
					m_y = temp.top - m_animation.getBounds().height;
				}

				if (tem2.intersects(a->getAnimation().getBounds()) && a->getCollisionType() == all)
				{
					//m_x_velocity = -m_x_velocity;
					//m_x_velocity = 0;
					if (getCollisionBox().left < a->getAnimation().getBounds().left + a->getAnimation().getBounds().width
						&& getCollisionBox().left + getCollisionBox().width > a->getAnimation().getBounds().left + a->getAnimation().getBounds().width
						&& m_x_velocity < 0 && m_isBlocked == false)
					{
						m_x_velocity = 0;
						m_isBlocked = true;
					}

					if (getCollisionBox().left + getCollisionBox().width > a->getAnimation().getBounds().left
						&& getCollisionBox().left < a->getAnimation().getBounds().left
						&& m_x_velocity > 0 && m_isBlocked == false)
					{
						m_x_velocity = 0;
						m_isBlocked = true;
					}
					//if (m_x < a->getAnimation().getBounds().left && m_x_velocity < 0)
						//m_x_velocity = 0;
					//	m_x = a->getAnimation().getBounds().left + a->getAnimation().getBounds().width - m_animation.getBounds().width * 0.3;
					//else
					//	m_x = a->getAnimation().getBounds().left - m_animation.getBounds().width + m_animation.getBounds().width * 0.3;
				}
			}

			if (a->getCollisionType() == living && !a->isDead() && !this->isDead() && this->m_damageCounter<= 0 && std::dynamic_pointer_cast<MovingEntity>(a)->getDamageCounter() <= 0)
			{
				temp.left = a->getAnimation().getBounds().left + a->getAnimation().getBounds().width * 0.35 ;
				temp.top = a->getAnimation().getBounds().top + a->getAnimation().getBounds().height*0.05;//05;
				temp.height = a->getAnimation().getBounds().height*0.05;
				temp.width = a->getAnimation().getBounds().width - a->getAnimation().getBounds().width * 0.7;

				sf::FloatRect temp2;
				temp2.top = a->getAnimation().getBounds().top + a->getAnimation().getBounds().height*0.05;
				temp2.height = a->getAnimation().getBounds().height - a->getAnimation().getBounds().height*0.1;
				temp2.width = a->getAnimation().getBounds().width - a->getAnimation().getBounds().width * 0.60;
				temp2.left = a->getAnimation().getBounds().left + a->getAnimation().getBounds().width * 0.30;

				tem2.top = m_animation.getBounds().top + m_animation.getBounds().height*0.05;
				tem2.height = m_animation.getBounds().height - m_animation.getBounds().height*0.1 ;
				//tem2.left = getCollisionBox().left - 10;
				//tem2.width = getCollisionBox().left + getCollisionBox().width + 10;


				if (temp.intersects(tem) && !this->m_isJumping)
				{
					if (m_y_velocity > 150)
					{
						std::dynamic_pointer_cast<MovingEntity>(a)->damage();
						m_isJumping = true;
						m_jumpTimer = 0.295;
						m_y = m_y = temp.top - m_animation.getBounds().height;
						m_isOnGround = true;
						m_isBlocked = true;
					}

					//m_y_velocity = 0;

					//m_y_velocity = 0;

				}

				else if (temp2.intersects(tem2))
				{
					if (getCollisionBox().left < a->getCollisionBox().left + a->getCollisionBox().width
						&& getCollisionBox().left + getCollisionBox().width > a->getCollisionBox().left + a->getCollisionBox().width
						&& m_x_velocity < 0 && m_isBlocked == false)
					{
						m_isBlocked = true;
						m_x_velocity = +m_max_velocity/8;
						//m_x = a->getCollisionBox().left + a->getCollisionBox().width  - this->getAnimation().getBounds().width*0.3;
					}

					if (getCollisionBox().left + getCollisionBox().width > a->getCollisionBox().left
						&& getCollisionBox().left < a->getCollisionBox().left
						&& m_x_velocity > 0 && m_isBlocked == false)
					{
						m_isBlocked = true;
						m_x_velocity = -m_max_velocity/8;
						//m_x = a->getCollisionBox().left  - this->getAnimation().getBounds().width*0.7;
					}

					//a->kill();
					//this->kill();
				}
				
				if (this->m_isAttacking&&m_attackTimer>0.15&&m_attackTimer<0.3)
				{
					
					sf::FloatRect sword;
					sword = this->getCollisionBox();
					sword.top = sword.top + sword.height*0.4;
					sword.height = sword.height*0.2;

					if (this->getAnimation().getFlip() == true)
					{
						sword.left -= this->getCollisionBox().width*0.5; //-
					}
					else
						sword.left += this->getCollisionBox().width*0.5;

					if (sword.intersects(a->getCollisionBox()))
					{
						std::dynamic_pointer_cast<MovingEntity>(a)->damage();
						if(!a->isDead())
							playSound("hit");
						hit_something = true;
						if (getCollisionBox().left + getCollisionBox().width/2 < a->getCollisionBox().left + a->getCollisionBox().width/2)
							std::dynamic_pointer_cast<MovingEntity>(a)->knockback(1);
						else
							std::dynamic_pointer_cast<MovingEntity>(a)->knockback(-1);
					}
				}
				

			}

		}
	}

	if (hit_something == false && this->m_attackTimer < 0.1 && this->m_isAttacking)
		playSound("miss");


	if (m_isOnGround && m_isJumping == false)
		m_y_velocity = 0;

	if (m_jumpTimer > 0.3)
	{
		m_isJumping = false;
		m_jumpTimer = 0;
	}

	if (m_attackTimer > 0.7)
	{
		m_isAttacking = false;
		m_attackTimer = 0;
		if(!m_isDead)
			m_animation.resetCurrent();
	}


	m_x += m_x_velocity * delta;
	m_y += m_y_velocity * delta;


//animation
	if (!this->isDead() && !this->m_isAttacking && m_isBlocked == false)
	{
		if (m_x_velocity > m_acceleration/15 )
		{
			if(m_damageCounter <= 0.5)
			m_animation.setFlip(false);
			m_animation.setAnimation("walk");
		}
		else if (m_x_velocity < -m_acceleration/15)
		{
			if (m_damageCounter <= 0.5)
			m_animation.setFlip(true);
			m_animation.setAnimation("walk");
		}
		else
			m_animation.setAnimation("stand");

		if (m_y_velocity != 0 && !m_isOnGround)
			m_animation.setAnimation("fall");
	}

	if (m_isAttacking && !m_isDead)
		m_animation.setAnimation("attack");

	Entity::update(delta);
}