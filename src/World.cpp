#include "World.hpp"


World::World(sf::RenderWindow& window)
	: m_window(window)
	, m_quit{false}
	, m_boss{false}
	, m_shake{false}
	, m_shakeTimer{0}
	, m_restart{false}
	, m_player2{false}
{
	init();
}

void World::update(float delta)
{
	updateAI();
	updateMap();
	m_bg.setColor(sf::Color(delta, 255, 255));
	updateEntities(delta);
	updateCosmetics(delta);
}

void World::draw()
{
	m_window.setView(m_view);

	m_window.draw(m_bg);

	for (auto a : m_blocks)			
		m_window.draw(a->getAnimation().getSprite());
	for (auto a : m_enemies)
		m_window.draw(a->getAnimation().getSprite());

	for (auto a : m_players)
		m_window.draw(a->getAnimation().getSprite());

	for (auto a : m_decorations)
		m_window.draw(a->getAnimation().getSprite());

	
	m_window.draw(m_hp.getSprite());
	m_window.draw(m_head.getSprite());
	m_window.draw(m_text);

	if (m_quit)
		m_window.draw(m_end);
}
