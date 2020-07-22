#pragma once

#include "State.hpp"

class Engine
{
public:
	Engine() = default;
	void run();
private:
	sf::RenderWindow m_window;
	std::unique_ptr<State> m_state;
};