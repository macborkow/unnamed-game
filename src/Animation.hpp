#pragma once

#include <SFML/Graphics.hpp>


class Animation 
{
public:
	Animation() = default;
	void update(float delta);

	sf::Sprite& getSprite() { return m_sprite; }
	void setAnimation(const std::string& id);
	void makeAnimation(const std::string& id, int framesCount, bool isRepeating, int width, int height, float frameTime, int row);
	void setTexture(sf::Texture& texture) { m_sprite.setTexture(texture); }
	void setScale(float scale) { m_scale = scale; }
	sf::FloatRect getBounds();

	void setFlip(bool flip) { m_flip = flip; }
	bool getFlip() { return m_flip;  }
	void resetCurrent() { m_currentAnim->currentFrame=0; }
	std::string getCurrentID() { return m_id; }
private:
	struct AnimationSet
	{
		int framesCount;
		bool isRepeating;
		int width;
		int height;
		float frameTime;
		int row;
		int currentFrame;
	};

	sf::Sprite m_sprite;
	float m_scale;
	std::shared_ptr<AnimationSet> m_currentAnim;
	std::map<std::string, std::shared_ptr<AnimationSet>> m_animations;
	float m_timer;
	bool m_flip;
	std::string m_id;
};