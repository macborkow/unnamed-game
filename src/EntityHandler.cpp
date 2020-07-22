#include "World.hpp"

void World::spawnPlayer2()
{
	if (!m_player2)
	{
		m_player2 = true;
		m_character2 = std::make_unique<MovingEntity>(m_character->getCollisionBox().left + 64, -128, 3, true, m_entities);
		m_character2->getAnimation().setTexture(*m_textures.getAsset("character_alt"));
		m_character2->getAnimation().makeAnimation("walk", 8, true, 32, 32, 0.1f, 0);
		m_character2->getAnimation().makeAnimation("stand", 1, false, 32, 32, 0.1f, 1);
		m_character2->getAnimation().makeAnimation("fall", 3, true, 32, 32, 0.1f, 2);
		m_character2->getAnimation().makeAnimation("dead", 9, false, 32, 32, 0.075f, 4);
		m_character2->getAnimation().makeAnimation("attack", 8, false, 32, 32, 0.05f, 3);
		m_character2->getAnimation().setAnimation("stand");
		m_character2->getAnimation().setScale(4);
		m_character2->addSound("death", *m_sounds.getAsset("death"));
		m_character2->addSound("hit", *m_sounds.getAsset("hit"));
		m_character2->addSound("miss", *m_sounds.getAsset("miss"));
		m_character2->addSound("jump", *m_sounds.getAsset("jump"));

		m_character2->setCollisionType(living);

		m_entities.push_back(m_character2);
		m_players.push_back(m_character2);
	}
}

void World::spawnBlock(int x, int y, const std::string& id, CollisionType coltype)
{
	std::shared_ptr<BlockEntity> temp = std::make_unique<BlockEntity>(x, y, coltype, m_entities);
	temp->getAnimation().setTexture(*m_textures.getAsset(id));
	temp->getAnimation().makeAnimation("stand", 1, false, 32, 32, 0.1f, 0);
	temp->getAnimation().setAnimation("stand");
	temp->getAnimation().setScale(4);
	if (rand() % 2 == 0)
		temp->getAnimation().setFlip(true);
	m_entities.push_back(temp);
	m_blocks.push_back(temp);

}

void World::spawnDecoration(int x, int y, const std::string& id, CollisionType coltype)
{
	std::shared_ptr<BlockEntity> temp = std::make_unique<BlockEntity>(x, y, coltype, m_entities);
	temp->getAnimation().setTexture(*m_textures.getAsset(id));
	temp->getAnimation().makeAnimation("col", 3, false, 8, 32, 0.15, 0);
	temp->getAnimation().makeAnimation("stand", 3, false, 8, 32, 0.2f, 4);
	temp->getAnimation().makeAnimation("static", 1, false, 8, 32, -1, 0);
	temp->getAnimation().setAnimation("static");
	temp->getAnimation().setScale(4);
	temp->makeDec();
	m_entities.push_back(temp);
	m_decorations.push_back(temp);
	std::shared_ptr<BlockEntity> temp2 = std::make_unique<BlockEntity>(x + 32, y, coltype, m_entities);
	temp2->getAnimation().setTexture(*m_textures.getAsset(id));
	temp2->getAnimation().makeAnimation("col", 3, false, 8, 32, 0.15, 1);
	temp2->getAnimation().makeAnimation("stand", 3, false, 8, 32, 0.2f, 5);
	temp2->getAnimation().makeAnimation("static", 1, false, 8, 32, -1, 1);
	temp2->getAnimation().setAnimation("static");
	temp2->getAnimation().setScale(4);
	temp2->makeDec();
	m_entities.push_back(temp2);
	m_decorations.push_back(temp2);
	std::shared_ptr<BlockEntity> temp3 = std::make_unique<BlockEntity>(x + 64, y, coltype, m_entities);
	temp3->getAnimation().setTexture(*m_textures.getAsset(id));
	temp3->getAnimation().makeAnimation("col", 3, false, 8, 32, 0.15, 2);
	temp3->getAnimation().makeAnimation("stand", 3, false, 8, 32, 0.2f, 6);
	temp3->getAnimation().makeAnimation("static", 1, false, 8, 32, -1, 2);
	temp3->getAnimation().setAnimation("static");
	temp3->getAnimation().setScale(4);
	temp3->makeDec();
	m_entities.push_back(temp3);
	m_decorations.push_back(temp3);
	std::shared_ptr<BlockEntity> temp4 = std::make_unique<BlockEntity>(x + 96, y, coltype, m_entities);
	temp4->getAnimation().setTexture(*m_textures.getAsset(id));
	temp4->getAnimation().makeAnimation("col", 3, false, 8, 32, 0.15, 3);
	temp4->getAnimation().makeAnimation("stand", 3, false, 8, 32, 0.2f, 7);
	temp4->getAnimation().makeAnimation("static", 1, false, 8, 32, -1, 3);
	temp4->getAnimation().setAnimation("static");
	temp4->getAnimation().setScale(4);
	temp4->makeDec();
	m_entities.push_back(temp4);
	m_decorations.push_back(temp4);
}

void World::spawnEnemy(int x, int y)
{
	std::shared_ptr<MovingEntity> temp = std::make_unique<MovingEntity>(x, y, 1, false, m_entities);
	temp->getAnimation().setTexture(*m_textures.getAsset("enemy"));
	temp->getAnimation().makeAnimation("walk", 8, true, 32, 32, 0.09f, 0);
	temp->getAnimation().makeAnimation("stand", 1, false, 32, 32, 0.1f, 1);
	temp->getAnimation().makeAnimation("fall", 1, false, 32, 32, 0.1f, 2);
	temp->getAnimation().makeAnimation("dead", 9, false, 32, 32, 0.075f, 3);
	temp->getAnimation().setAnimation("stand");
	temp->addSound("death", *m_sounds.getAsset("skeledeath"));
	temp->addSound("jump", *m_sounds.getAsset("thud"));
	temp->setCollisionType(living);
	temp->getAnimation().setScale(4);
	if (rand() % 2 == 0)
		temp->getAnimation().setFlip(true);
	m_entities.push_back(temp);
	m_enemies.push_back(temp);
}

void World::spawnDK(int x, int y)
{
	std::shared_ptr<MovingEntity> temp = std::make_unique<MovingEntity>(x, y, 3, true, m_entities);
	temp->getAnimation().setTexture(*m_textures.getAsset("dk"));
	temp->getAnimation().makeAnimation("walk", 8, true, 32, 32, 0.1f, 0);
	temp->getAnimation().makeAnimation("stand", 1, false, 32, 32, 0.1f, 1);
	temp->getAnimation().makeAnimation("fall", 1, false, 32, 32, 0.1f, 2);
	temp->getAnimation().makeAnimation("attack", 8, false, 32, 32, 0.05f, 3);
	temp->getAnimation().makeAnimation("dead", 9, false, 32, 32, 0.075f, 4);
	temp->getAnimation().setAnimation("stand");
	temp->addSound("death", *m_sounds.getAsset("skeledeath"));
	temp->addSound("hit", *m_sounds.getAsset("hit"));
	temp->addSound("miss", *m_sounds.getAsset("miss"));
	temp->addSound("jump", *m_sounds.getAsset("thud"));
	temp->setCollisionType(living);
	temp->getAnimation().setScale(4);
	if (rand() % 2 == 0)
		temp->getAnimation().setFlip(true);
	m_entities.push_back(temp);
	m_enemies.push_back(temp);
}

void World::updateEntities(float delta)
{
	sf::FloatRect killView;
	killView.left = -2000 + m_view.getCenter().x;
	killView.top = -1000 + m_view.getCenter().y;
	killView.height = 2000 + m_view.getCenter().y;
	killView.width = 4000 + m_view.getCenter().x;


	for (int i = 0; i < m_entities.size(); ++i)
	{
		m_entities[i]->update(delta);

		if (!m_entities[i]->getAnimation().getBounds().intersects(killView))
		{
			m_entities[i]->kill();
			m_entities.erase(m_entities.begin() + i);
			--i;
		}

	}

	for (int i = 0; i < m_enemies.size(); ++i)
	{
		if (m_enemies[i]->timeToErase())
		{
			m_enemies.erase(m_enemies.begin() + i);
			--i;
		}
	}


	for (int i = 0; i < m_blocks.size(); ++i)
	{
		if (m_blocks[i]->isDead())
		{
			m_blocks.erase(m_blocks.begin() + i);
			--i;
		}
	}

	for (int i = 0; i < m_decorations.size(); ++i)
	{
		if (m_decorations[i]->isDead())
		{
			m_decorations.erase(m_decorations.begin() + i);
			--i;
		}
	}


}
