#include "Engine.hpp"


void Engine::run()
{
	//m_window.create(sf::VideoMode(1920, 1080, 32), "framework", sf::Style::Titlebar | sf::Style::Close);
	m_window.create(sf::VideoMode(1920, 1080, 32), "framework", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);
	m_window.setFramerateLimit(100);

	m_state = std::make_unique<State>(m_window);

	sf::Clock clock;
	float lastTime = 0;
	while (m_state->isRunning())
	{
		sf::Time elapsed = clock.restart();
		float fps = 1.f / elapsed.asSeconds() - lastTime;
		m_state->update(elapsed.asSeconds());
		lastTime = elapsed.asSeconds();
		m_state->draw();
		if(m_state->restart())
			m_state = std::make_unique<State>(m_window);
	}
}