#pragma once

#include "Entity.hpp"
#include <SFML/Audio.hpp>



class LivingEntity : public Entity
{
public:
	LivingEntity(float x, float y) : Entity(x, y)
	{}
	virtual void update(float delta)
	{
		m_animation.update(delta);
		m_animation.getSprite().setPosition(m_x, m_y);
		m_isBlocked = false;
	}
	Animation& getAnimation()
	{
		return m_animation;
	}
	void addSound(std::string str, sf::SoundBuffer& s)
	{
		sf::Sound temp;
		temp.setBuffer(s);
		m_soundMap.insert(std::make_pair(str, temp));

	}

protected:
	void playSound(std::string str)
	{
		if (m_soundMap.find(str) != m_soundMap.end())
			if (m_soundMap.at(str).getStatus() != sf::Sound::Playing)
				m_soundMap.at(str).play();
	}
	bool m_isBlocked;
	std::map<std::string, sf::Sound> m_soundMap;
};