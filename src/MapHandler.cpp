#include "World.hpp"
#include "EntityHandler.cpp"

void World::init()
{
	srand(time(NULL));

	m_previousHole = false;

	m_font.loadFromFile("assets/LCD_Solid.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(48);
	m_text.setFillColor(sf::Color::White);
	m_text.setPosition(640 - 48, 0);
	m_text.setString("0");
	m_end.setFont(m_font);
	m_end.setCharacterSize(96);
	m_end.setFillColor(sf::Color::White);
	m_end.setString("PRESS F5 TO RESTART");

	m_textures.setAsset("character", "assets/character4.png");
	m_textures.setAsset("character_alt", "assets/character_alt2.png");
	m_textures.setAsset("enemy", "assets/enemy5.png");
	m_textures.setAsset("block", "assets/block.png");
	m_textures.setAsset("bg3", "assets/bg.png");
	m_textures.setAsset("block0", "assets/block0.png");
	m_textures.setAsset("end", "assets/end.png");
	m_textures.setAsset("dk", "assets/deadknight.png");
	m_textures.setAsset("grass", "assets/grass2.png");
	m_textures.setAsset("hp", "assets/hp.png");
	m_textures.setAsset("head", "assets/head.png");

	m_sounds.setAsset("death", "assets/death.wav");
	m_sounds.setAsset("skeledeath", "assets/skeledeath.wav");
	m_sounds.setAsset("hit", "assets/hit.wav");
	m_sounds.setAsset("miss", "assets/miss.wav");
	m_sounds.setAsset("jump", "assets/jump.wav");
	m_sounds.setAsset("thud", "assets/thud.wav");

	m_hp.setTexture(*m_textures.getAsset("hp"));
	m_hp.makeAnimation("3", 1, false, 32, 8, 0, 0);
	m_hp.makeAnimation("2", 1, false, 32, 8, 0, 1);
	m_hp.makeAnimation("1", 1, false, 32, 8, 0, 2);
	m_hp.makeAnimation("0", 1, false, 32, 8, 0, 3);
	m_hp.setAnimation("3");
	m_hp.setScale(4);
	m_hp.getSprite().setPosition(10, 10);
	m_head.setTexture(*m_textures.getAsset("head"));
	m_head.makeAnimation("living", 1, false, 16, 16, 0, 0);
	m_head.makeAnimation("dead", 1, false, 16, 16, 0, 1);
	m_head.setAnimation("living");
	m_head.makeAnimation("alt", 1, false, 16, 16, 0, 2);
	m_head.setScale(4);

	m_bg.setTexture(*m_textures.getAsset("bg3"));
	m_bg.setScale(4, 4);

	m_character = std::make_unique<MovingEntity>(128, -128, 3,true, m_entities);
	m_character->getAnimation().setTexture(*m_textures.getAsset("character"));
	m_character->getAnimation().makeAnimation("walk", 8, true, 32, 32, 0.1f, 0);
	m_character->getAnimation().makeAnimation("stand", 1, false, 32, 32, 0.1f, 1);
	m_character->getAnimation().makeAnimation("fall", 3, true, 32, 32, 0.1f, 2);
	m_character->getAnimation().makeAnimation("dead", 9, false, 32, 32, 0.075f, 4);
	m_character->getAnimation().makeAnimation("attack", 8, false, 32, 32, 0.05f, 3);
	m_character->getAnimation().setAnimation("stand");
	m_character->getAnimation().setScale(4);
	m_character->addSound("death", *m_sounds.getAsset("death"));
	m_character->addSound("hit", *m_sounds.getAsset("hit"));
	m_character->addSound("miss", *m_sounds.getAsset("miss"));
	m_character->addSound("jump", *m_sounds.getAsset("jump"));
	m_character->setCollisionType(living);

	m_entities.push_back(m_character);

	m_players.push_back(m_character);



	for (int i = 1; i < 4; ++i)
	{
		spawnDecoration(128 * i, 480 - 256, "grass", nocol);
		spawnBlock(128 * i, 480 - 128, "block", top);
		spawnBlock(128 * i, 480, "block0", nocol);
		//	spawnBlock(0, 480 +128- 128*i, "block0", all);
	}

	m_distance = 3;

	m_view.setSize(1280, 960);

	m_music.openFromFile("assets/sounds.ogg");
	m_music.play();
	m_music.setLoop(true);
}

void World::updateMap()
{
	if (m_character->getAnimation().getBounds().left + m_character->getAnimation().getBounds().width > m_distance * 128 - 128 * 4)
	{
		m_distance++;
		int offsetted = m_distance - 6;
		int levelCap = 1000;
		int temp;
		if (offsetted * 2 > 60)
			temp = 60;
		else
			temp = offsetted*2;

		if (!m_boss && offsetted <= levelCap - 1)
		{
			if (/*rand() % 4 != 0*/rand() % 100 > temp)
			{
				spawnDecoration(128 * m_distance, 480 - 256, "grass", nocol);
				spawnBlock(128 * m_distance, 480 - 128, "block", all);
				spawnBlock(128 * m_distance, 480, "block0", nocol);
				m_previousHole = false;
				if (rand() % 200 < m_distance * 2)
				{
					if (rand() % 4 == 0 && offsetted > 30)
						spawnDK(128 * m_distance, 480 - 256.01);
					else
						spawnEnemy(128 * m_distance, 480 - 256.01);
				}
			}
			else
			{
				int choice = rand() % 3;
				if (m_previousHole == true)
					choice = rand() % 2;
				switch (choice)
				{
				case 0:
					if (m_previousHole)
					{
						spawnDecoration(128 * m_distance, 480 - 256, "grass", nocol);
						spawnBlock(128 * m_distance, 480 - 128 - 128, "block", top);
						spawnBlock(128 * m_distance, 480 - 128, "block", all);
					}
					else
					{
						spawnDecoration(128 * m_distance, 480 - 256 - 128, "grass", nocol);
						spawnBlock(128 * m_distance, 480 - 128 - 128, "block", all);
						spawnBlock(128 * m_distance, 480 - 128, "block0", all);
					}
					spawnBlock(128 * m_distance, 480, "block0", nocol);
					m_previousHole = false;
					if (rand() % 200 < m_distance * 3)
						if (rand() % 4 == 0 && offsetted > 30)
							spawnDK(128 * m_distance, 480 - 256.01 - 128);
						else
							spawnEnemy(128 * m_distance, 480 - 256.01 - 128);
					break;
				case 1:
					spawnDecoration(128 * m_distance, 480 - 128, "grass", nocol);
					spawnBlock(128 * m_distance, 480, "block", all);
					//spawnBlock(128 * m_distance, 480, "block0", nocol);
					m_previousHole = true;
					if (rand() % 200 < m_distance * 3)
						if (rand() % 4 == 0 && offsetted > 30)
							spawnDK(128 * m_distance, 480 - 256.01 + 128);
						else
							spawnEnemy(128 * m_distance, 480 - 256.01 + 128);
					break;
				case 2:  m_previousHole = true;
					break;
				default: break;
				}
			}



			m_text.setString(std::to_string(offsetted));
		}
		else if (!m_boss)
			m_text.setString(std::to_string(offsetted));


		//if (offsetted >= levelCap && m_boss == false)
		//{
		//	m_boss = true;
		//	m_text.setString("35!");
		//
		//	m_distance = offsetted+6;
		//
		//	for (int i = 0; i < 7; i++)
		//	{
		//		if(i<5)
		//		spawnBlock(128 * (m_distance + i), 480 - 128, "block", top);
		//		else
		//		{
		//			spawnBlock(128 * (m_distance + i), 480 - 256, "block", all);
		//			spawnBlock(128 * (m_distance + i), 480-128, "block0", nocol);
		//		}
		//		spawnBlock(128 * (m_distance + i), 480, "block0", nocol);
		//
		//		for (int j = 0; j < 5; ++j)
		//		{
		//			if(j<4)
		//				spawnBlock(128 * (m_distance + 7+i), 480 - 128 * j , "block0", all);
		//			else
		//				spawnBlock(128 * (m_distance + 7+i), 480 - 128 * j , "block", all);
		//		}
		//	}
		//
		//
		//	spawnDK(128 * (m_distance + 6), 480 - 256 - 128-128);
		//	int i = m_dks.size()-1;
		//		m_dks[i]->getAnimation().setFlip(true);
		//}




	}
}

void World::updateCosmetics(float delta)
{
	if (m_character->isDead())
	{
		if (m_character2 != nullptr)
			if (!m_character2->isDead())
			{
				m_character = m_character2;
				m_head.setAnimation("alt");
				if (m_character->getHp() == 3)
				{
					m_hp.setAnimation("3");
				}
				else if (m_character->getHp() == 1)
				{
					m_hp.setAnimation("1");
				}
				else if (m_character->getHp() == 2)
				{
					m_hp.setAnimation("2");
				}
				return;
			}
		m_quit = true;//ewuw
		//m_text.setString("END");
		m_end.setPosition(m_view.getCenter().x - m_end.getGlobalBounds().width / 2, m_view.getCenter().y - m_end.getGlobalBounds().height / 2);
	}

	if (m_shakeTimer == 0)
		m_view.setCenter(m_character->getAnimation().getBounds().left + m_character->getAnimation().getBounds().width / 2,
			120);///m_character->getAnimation().getBounds().top + m_character->getAnimation().getBounds().height / 2-188);
	else
	{
		m_view.setCenter(m_character->getAnimation().getBounds().left + m_character->getAnimation().getBounds().width / 2 + rand() % 15 - 7.5,
			120 + rand() % 15 - 7.5);
		m_shakeTimer -= delta;
		if (m_shakeTimer < 0)
		{
			m_shakeTimer = 0;
		}
	}


	m_bg.setPosition(m_view.getCenter().x - m_view.getSize().x / 2, m_view.getCenter().y - m_view.getSize().y / 2);
	m_text.setPosition(m_view.getCenter().x + m_view.getSize().x / 2 - 160 + 25, m_view.getCenter().y - m_view.getSize().y / 2 + 48);
	m_hp.update(delta);
	m_head.update(delta);
	if (!m_character->isDead())
	{
		if (m_character->getHp() == 2 && m_hp.getCurrentID() != "2")
		{
			m_hp.setAnimation("2");
			m_shakeTimer = 0.25;
		}
		else if (m_character->getHp() == 1 && m_hp.getCurrentID() != "1")
		{
			m_hp.setAnimation("1");
			m_shakeTimer = 0.25;
		}
	}
	else if (m_hp.getCurrentID() != "0")
	{
		m_hp.setAnimation("0");
		m_head.setAnimation("dead");
		m_shakeTimer = 0.25;
	}

	m_hp.getSprite().setPosition(m_view.getCenter().x + m_view.getSize().x / 2 - 140, m_view.getCenter().y - m_view.getSize().y / 2 + 20);
	m_head.getSprite().setPosition(m_view.getCenter().x + m_view.getSize().x / 2 - 140 - 64, m_view.getCenter().y - m_view.getSize().y / 2 + 20);
}