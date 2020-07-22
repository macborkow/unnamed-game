#include "World.hpp"

void World::updateAI()
{

	for (auto &a : m_enemies)
	{
		if (!m_character->isDead())
		{
			int distance = 70;
			//a->setInput(none);

			bool isGround = false;
			bool isObstacle = false;
			bool toLeft = false;
			bool toRight = false;
			float leftDist = 0;
			float rightDist = 0;
			bool isSafe = false;
			bool isSafeSide = false;
			sf::FloatRect temp;
			sf::FloatRect temp2;
			for (auto &b : m_blocks)
			{

				if (a->getAnimation().getFlip() == false)
				{

					temp.top = a->getCollisionBox().top + a->getCollisionBox().height + 5;
					temp.left = a->getCollisionBox().left + a->getCollisionBox().width;
					temp.height = 5;
					temp.width = 5;
					if (temp.intersects(b->getCollisionBox()))
					{
						isGround = true;
					}
					temp.height = 500;
					if (temp.intersects(b->getCollisionBox()))
					{
						isSafe = true;
					}
					temp.left += (a->getCollisionBox().width + 15);
					temp.height = 5;
					temp.width = 1;
					if (temp.intersects(b->getCollisionBox()))
						isSafeSide = true;
				}
				else
				{
					temp.top = a->getCollisionBox().top + a->getCollisionBox().height + 5;
					temp.left = a->getCollisionBox().left;
					temp.height = 5;
					temp.width = -5;
					if (temp.intersects(b->getCollisionBox()))
					{
						isGround = true;
					}
					temp.height = 500;
					if (temp.intersects(b->getCollisionBox()))
					{
						isSafe = true;
					}
					temp.left -= (a->getCollisionBox().width + 15);
					temp.height = 5;
					temp.width = -1;
					if (temp.intersects(b->getCollisionBox()))
						isSafeSide = true;
				}

				temp.top = a->getCollisionBox().top;
				temp.left = a->getCollisionBox().left - 110;
				temp.height = 5;
				temp.width = 5;
				if (temp.intersects(b->getCollisionBox()))
				{
					isObstacle = true;
					toLeft = true;
					leftDist = a->getCollisionBox().left - b->getCollisionBox().left + b->getCollisionBox().width;
				}
				temp.top = a->getCollisionBox().top;
				temp.left = a->getCollisionBox().left + a->getCollisionBox().width + 110;
				temp.height = 5;
				temp.width = -5;
				if (temp.intersects(b->getCollisionBox()))
				{
					isObstacle = true;
					toRight = true;
					rightDist = b->getCollisionBox().left - a->getCollisionBox().left + a->getCollisionBox().width;
				}
			}

			if (!isGround)
			{
				if (!isSafe || !a->canAttack())
				{
					if (std::abs(a->getVelocity().x) > 140)
						a->setInput(jump);
					else
					{
						if (a->getVelocity().x >= 0)
						{
							a->setInput(right);
						}
						else if (a->getVelocity().x < 0)
							a->setInput(left);
					}
				}
				else
				{
					if(std::abs(a->getVelocity().x) > 60)
						a->setInput(none);
					else
						if (a->getVelocity().x >= 0)
						{
							a->setInput(right);
						}
						else if (a->getVelocity().x < 0)
							a->setInput(left);
				}

			}
			else if (isObstacle &&
				std::abs(m_character->getCollisionBox().left + m_character->getCollisionBox().width / 2 - a->getCollisionBox().left + a->getCollisionBox().width / 2) < 500)
			{

				if (!a->canAttack())
				{
					if (toLeft)
					{
						if (a->getVelocity().x < -140)
							a->setInput(jump);
						else
							a->setInput(right);
					}
					if (toRight)
					{
						if (a->getVelocity().x > 140 )
							a->setInput(jump);
						else
							a->setInput(left);
					}
					if (toRight && toLeft)
					{
						if (a->getVelocity().x < -110 && m_character->getCollisionBox().left + m_character->getCollisionBox().width / 2 - a->getCollisionBox().left + a->getCollisionBox().width / 2 < 0)
							a->setInput(jump);
						else if (a->getVelocity().x > 110 && m_character->getCollisionBox().left + m_character->getCollisionBox().width / 2 - a->getCollisionBox().left + a->getCollisionBox().width / 2 > 0)
							a->setInput(jump);
						else if (a->getVelocity().x > 0)
						{
							a->setInput(right);
						}
						else if (a->getVelocity().x < -0)
							a->setInput(left);
						else
						{
							//if (a->getAnimation().getFlip() == true)
							//	a->setInput(right);
							//else
							//	a->setInput(left);
							if (std::rand() % 2 == 0)
								a->setInput(right);
							else
								a->setInput(left);
						}
					}
				}
				else
				{
					if (toLeft)
					{
						if (a->getVelocity().x < -110)
							a->setInput(jump);
						else
							a->setInput(right);
					}
					if (toRight)
					{
						if (a->getVelocity().x > 110)
							a->setInput(jump);
						else
							a->setInput(left);
					}
					if (toRight && toLeft)
					{

						if (a->getVelocity().x < -110 && m_character->getCollisionBox().left + m_character->getCollisionBox().width / 2 - a->getCollisionBox().left + a->getCollisionBox().width / 2 < 0)
							a->setInput(jump);
						else if (a->getVelocity().x > 110 && m_character->getCollisionBox().left + m_character->getCollisionBox().width / 2 - a->getCollisionBox().left + a->getCollisionBox().width / 2 > 0)
							a->setInput(jump);
						else if (a->getVelocity().x > 0)
						{
							a->setInput(right);
						}
						else if (a->getVelocity().x < -0)
							a->setInput(left);
						else
						{
							//if (a->getAnimation().getFlip() == true)
							//	a->setInput(right);
							//else
							//	a->setInput(left);
							if (std::rand() % 2 == 0)
								a->setInput(right);
							else
								a->setInput(left);
						}
					}

					distance = 30;
					sf::FloatRect templeft = a->getCollisionBox();
					templeft.left = templeft.left - distance + 10;
					templeft.width = distance - 10;
					sf::FloatRect tempright = a->getCollisionBox();
					tempright.left = tempright.left + tempright.width;;
					tempright.width = tempright.width + distance - 10;
					for (auto p : m_players)
						if (!p->isDead())
							if ((p->getCollisionBox().intersects(templeft) && a->getAnimation().getFlip() == true) || (p->getCollisionBox().intersects(tempright) && a->getAnimation().getFlip() == false))
							{
								if (a->getAnimation().getFlip() == true)
									a->setInput(attack);
								else if (a->getAnimation().getFlip() == false)
									a->setInput(attack);
							}
					for (auto p : m_enemies)
						if (!p->isDead())
							if ((p->getCollisionBox().intersects(templeft) && a->getAnimation().getFlip() == true) || (p->getCollisionBox().intersects(tempright) && a->getAnimation().getFlip() == false))
							{
								if (a->getAnimation().getFlip() == true)
									a->setInput(attack);
								else if (a->getAnimation().getFlip() == false)
									a->setInput(attack);
							}
				}
			}

			if (!isObstacle && isGround
				&& std::abs(m_character->getCollisionBox().left + m_character->getCollisionBox().width / 2 - a->getCollisionBox().left + a->getCollisionBox().width / 2) < 650)
			{
				if (!a->canAttack())
				{
					sf::FloatRect tempL;
					sf::FloatRect tempR;
					tempR.top = a->getCollisionBox().top;
					tempR.left = a->getCollisionBox().left + a->getCollisionBox().width + 40;
					tempR.height = 5;
					tempR.width = 5;
					tempL.top = a->getCollisionBox().top;
					tempL.left = a->getCollisionBox().left - 40;
					tempL.height = 5;
					tempL.width = 5;
					bool colLeft = false;
					bool colRight = false;
					for (auto &e : m_enemies)
					{
						if (!e->isDead())
						{
							if (tempL.intersects(e->getCollisionBox()))
								colLeft = true;
							if (tempR.intersects(e->getCollisionBox()))
								colRight = true;
						}
					}

					if (colLeft)
					{
						for (auto p : m_players)
							if (!p->isDead())
								if (p->getCollisionBox().left + p->getCollisionBox().width / 2 >
									a->getCollisionBox().left + a->getCollisionBox().width / 2)
								{
									if (a->getCollisionBox().left + a->getCollisionBox().width / 2 < p->getCollisionBox().left)
									{
										a->setInput(right);
									}
									else if (a->getCollisionBox().left > p->getCollisionBox().left + p->getCollisionBox().width / 2)
										a->setInput(left);

									if (a->getCollisionBox().left - distance < p->getCollisionBox().left + p->getCollisionBox().width
										&&	a->getCollisionBox().left - -a->getCollisionBox().width / 2 > p->getCollisionBox().left + p->getCollisionBox().width)
										a->setInput(right);

									if (a->getCollisionBox().left + a->getCollisionBox().width + -a->getCollisionBox().width / 2 < p->getCollisionBox().left
										&&	a->getCollisionBox().left + a->getCollisionBox().width + distance > p->getCollisionBox().left)
										a->setInput(left);

									if (a->getCollisionBox().left - (distance + 10) < p->getCollisionBox().left + p->getCollisionBox().width
										&&	a->getCollisionBox().left - distance > p->getCollisionBox().left + p->getCollisionBox().width)
									{
										if (a->getVelocity().x < -70)
											a->setInput(jump);
										else
											a->setInput(left);
									}

									if (a->getCollisionBox().left + a->getCollisionBox().width + distance < p->getCollisionBox().left
										&&	a->getCollisionBox().left + a->getCollisionBox().width + (distance + 10) > p->getCollisionBox().left)
									{
										if (a->getVelocity().x > 70)
											a->setInput(jump);
										else
											a->setInput(right);
									}
								}
								else
									a->setInput(right);
					}
					else if (colRight)
					{
						for (auto p : m_players)
							if (!p->isDead())
								if (p->getCollisionBox().left + p->getCollisionBox().width / 2 <
									a->getCollisionBox().left + a->getCollisionBox().width / 2)
								{
									if (a->getCollisionBox().left + a->getCollisionBox().width / 2 < p->getCollisionBox().left)
									{
										a->setInput(right);
									}
									else if (a->getCollisionBox().left > p->getCollisionBox().left + p->getCollisionBox().width / 2)
										a->setInput(left);

									if (a->getCollisionBox().left - distance < p->getCollisionBox().left + p->getCollisionBox().width
										&&	a->getCollisionBox().left - -a->getCollisionBox().width / 2 > p->getCollisionBox().left + p->getCollisionBox().width)
										a->setInput(right);

									if (a->getCollisionBox().left + a->getCollisionBox().width + -a->getCollisionBox().width / 2 < p->getCollisionBox().left
										&&	a->getCollisionBox().left + a->getCollisionBox().width + distance > p->getCollisionBox().left)
										a->setInput(left);

									if (a->getCollisionBox().left - (distance + 10) < p->getCollisionBox().left + p->getCollisionBox().width
										&&	a->getCollisionBox().left - distance > p->getCollisionBox().left + p->getCollisionBox().width)
									{
										if (a->getVelocity().x < -70)
											a->setInput(jump);
										else
											a->setInput(left);
									}

									if (a->getCollisionBox().left + a->getCollisionBox().width + distance < p->getCollisionBox().left
										&&	a->getCollisionBox().left + a->getCollisionBox().width + (distance + 10) > p->getCollisionBox().left)
									{
										if (a->getVelocity().x > 70)
											a->setInput(jump);
										else
											a->setInput(right);
									}
								}
								else
									a->setInput(left);
					}
					else if (colRight&&colLeft)
					{
						for (auto p : m_players)
							if (!p->isDead())
								if (p->getCollisionBox().left + p->getCollisionBox().width / 2 >
									a->getCollisionBox().left + a->getCollisionBox().width / 2)
									a->setInput(left);
								else if (p->getCollisionBox().left + p->getCollisionBox().width / 2 <
									a->getCollisionBox().left + a->getCollisionBox().width / 2)
									a->setInput(right);
					}
					else
					{
						distance = 70;
						float dist_play = 10000;
						for (auto p : m_players)
						{
							float temp = std::abs((p->getCollisionBox().left + p->getCollisionBox().width / 2) - (a->getCollisionBox().left + a->getCollisionBox().width / 2));
							if (temp < dist_play && !p->isDead())
							{
								dist_play = temp;
								if (a->getCollisionBox().left + a->getCollisionBox().width / 2 < p->getCollisionBox().left)
								{
									a->setInput(right);
								}
								else if (a->getCollisionBox().left > p->getCollisionBox().left + p->getCollisionBox().width / 2)
									a->setInput(left);

								if (a->getCollisionBox().left - distance < p->getCollisionBox().left + p->getCollisionBox().width
									&&	a->getCollisionBox().left - -a->getCollisionBox().width / 2 > p->getCollisionBox().left + p->getCollisionBox().width)
									a->setInput(right);

								if (a->getCollisionBox().left + a->getCollisionBox().width + -a->getCollisionBox().width / 2 < p->getCollisionBox().left
									&&	a->getCollisionBox().left + a->getCollisionBox().width + distance > p->getCollisionBox().left)
									a->setInput(left);

								if (a->getCollisionBox().left - (distance + 10) < p->getCollisionBox().left + p->getCollisionBox().width
									&&	a->getCollisionBox().left - distance > p->getCollisionBox().left + p->getCollisionBox().width)
								{
									if (a->getVelocity().x < -70)
										a->setInput(jump);
									else
										a->setInput(left);
								}

								if (a->getCollisionBox().left + a->getCollisionBox().width + distance < p->getCollisionBox().left
									&&	a->getCollisionBox().left + a->getCollisionBox().width + (distance + 10) > p->getCollisionBox().left)
								{
									if (a->getVelocity().x > 70)
										a->setInput(jump);
									else
										a->setInput(right);
								}
							}
						}
					}
				}
				else
				{
					sf::FloatRect tempL;
					sf::FloatRect tempR;
					tempR.top = a->getCollisionBox().top;
					tempR.left = a->getCollisionBox().left + a->getCollisionBox().width + 20;
					tempR.height = 5;
					tempR.width = 5;
					tempL.top = a->getCollisionBox().top;
					tempL.left = a->getCollisionBox().left - 20;
					tempL.height = 5;
					tempL.width = 5;
					bool colLeft = false;
					bool colRight = false;
					for (auto &e : m_enemies)
					{
						if (!e->isDead())
						{
							if (tempL.intersects(e->getCollisionBox()))
								colLeft = true;
							if (tempR.intersects(e->getCollisionBox()))
								colRight = true;
						}
					}

					if (colLeft)
					{
						if (a->getAnimation().getFlip() == true)
							a->setInput(attack);
						else
							a->setInput(right);
					}
					else if (colRight)
					{
						if (a->getAnimation().getFlip() == false)
							a->setInput(attack);
						else
							a->setInput(left);
					}
					else if (colLeft&&colRight)
					{
						a->setInput(attack);
					}
					else
					{
						distance = 30;
						float dist_play = 10000;
						for (auto p : m_players)
						{
							float temp = std::abs((p->getCollisionBox().left + p->getCollisionBox().width / 2) - (a->getCollisionBox().left + a->getCollisionBox().width / 2));
							if (temp < dist_play && !p->isDead())
							{
								dist_play = temp;
								if (a->getCollisionBox().left + a->getCollisionBox().width / 2 < p->getCollisionBox().left)
								{
									a->setInput(right);
								}
								else if (a->getCollisionBox().left > p->getCollisionBox().left + p->getCollisionBox().width / 2)
									a->setInput(left);

								sf::FloatRect templeft = a->getCollisionBox();
								templeft.left = templeft.left - distance + 10;
								templeft.width = distance - 10;

								sf::FloatRect tempright = a->getCollisionBox();
								tempright.left = tempright.left + tempright.width;;
								tempright.width = distance - 10;
								if (templeft.intersects(p->getCollisionBox()) && !tempright.intersects(p->getCollisionBox()) && a->getAnimation().getFlip() == true)
								{
									a->setInput(attack);
								}
								if (tempright.intersects(p->getCollisionBox()) && !templeft.intersects(p->getCollisionBox()) && a->getAnimation().getFlip() == false)
									a->setInput(attack);
							}
						}
					}
				}

			}


		}
		else
		a->setInput(none);
	}
}