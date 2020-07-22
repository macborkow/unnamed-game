#pragma once

#include <vector>
#include <memory>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "AssetManager.hpp"
#include "MovingEntity.hpp"
#include "BlockEntity.hpp"

class World
{
public:
	World(sf::RenderWindow&);
	~World() {};
	void playerInput(Input input) { m_character->setInput(input); }
	void player2Input(Input input) { m_character2->setInput(input); }
	void update(float delta);
	void draw();
	bool getRestart() { return m_restart; }
	void restart() { m_restart = true; }
	void spawnPlayer2();
private:
	void spawnBlock(int x, int y, const std::string& id, CollisionType coltype);
	void spawnDecoration(int x, int y, const std::string& id, CollisionType coltype);
	void spawnEnemy(int x, int y);
	void spawnDK(int x, int y);
	void updateAI();
	void updateMap();
	void updateEntities(float delta);
	void init();
	void updateCosmetics(float delta);
	sf::RenderWindow& m_window;
	AssetManager<sf::Texture> m_textures;
	AssetManager<sf::SoundBuffer> m_sounds;
	std::shared_ptr<MovingEntity> m_character;
	std::shared_ptr<MovingEntity> m_character2;
	std::vector <std::shared_ptr<Entity>> m_entities;
	std::vector <std::shared_ptr<MovingEntity>> m_players;
	std::vector <std::shared_ptr<MovingEntity>> m_enemies;
	std::vector <std::shared_ptr<BlockEntity>> m_blocks;
	std::vector <std::shared_ptr<BlockEntity>> m_decorations;
	sf::Sprite m_bg;
	sf::Text m_end;
	Animation m_hp;
	Animation m_head;
	sf::View m_view;
	sf::Font m_font;
	sf::Text m_text;
	sf::Music m_music;
	int m_distance;
	bool m_previousHole;
	int m_worldLevel;
	bool m_quit;
	bool m_restart;
	bool m_boss;
	bool m_shake;
	float m_shakeTimer;
	bool m_player2;
	sf::Color m_funnyColor;
};