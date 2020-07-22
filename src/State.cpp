#include "State.hpp"

#include <iostream>

State::State(sf::RenderWindow& window)
	: m_window(window)
	, m_running(true)
	, m_world(m_window)
	, m_player2{false}
{
}

void State::update(float delta)
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_running=false;
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				m_running = false;
				break;
			case sf::Keyboard::F5:
				m_world.restart();
				break;
			case sf::Keyboard::F1:
				m_world.spawnPlayer2();
				m_player2 = true;
				break;
			default:
				break;
			}
			break;
		default: 
			break;
		}
	}

	m_world.playerInput(none);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_world.playerInput(left);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_world.playerInput(right);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_world.playerInput(none);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_world.playerInput(jump);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
		m_world.playerInput(attack);

	

	if (m_player2)
	{
		m_world.player2Input(none);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			m_world.player2Input(left);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			m_world.player2Input(right);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			m_world.player2Input(none);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			m_world.player2Input(jump);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
			m_world.player2Input(attack);
	}

	m_world.update(delta);
	
}

void State::draw()
{
	m_window.clear(sf::Color::Black);
	m_world.draw();
	m_window.display();
}