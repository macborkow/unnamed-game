#pragma once

#include "AssetManager.hpp"
#include "MovingEntity.hpp"
#include "World.hpp"

class State
{
public:
	State(sf::RenderWindow&);
	void update(float delta);
	void draw();
	bool isRunning() { return m_running;  }
	bool restart() { return m_world.getRestart(); }
private:
	sf::RenderWindow& m_window;
	bool m_running;
	World m_world;
	bool m_player2;
};