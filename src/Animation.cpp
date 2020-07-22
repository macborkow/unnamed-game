#include "Animation.hpp"

void Animation::update(float delta)
{
	m_timer += delta;
	if (m_timer >= m_currentAnim->frameTime)
	{
		m_timer = 0;
		m_currentAnim->currentFrame++;
		if (m_currentAnim->currentFrame > m_currentAnim->framesCount - 1 && m_currentAnim->isRepeating)
		{
			m_currentAnim->currentFrame = 0;
		}
		if (m_currentAnim->currentFrame >= m_currentAnim->framesCount - 1 && !m_currentAnim->isRepeating)
			m_currentAnim->currentFrame = m_currentAnim->framesCount-1;
	}


	if (m_flip)
		m_sprite.setTextureRect(sf::IntRect(
			m_currentAnim->width*m_currentAnim->currentFrame + m_currentAnim->width,
			m_currentAnim->height*m_currentAnim->row,
			-m_currentAnim->width,
			m_currentAnim->height));
	else
		m_sprite.setTextureRect(sf::IntRect(
			m_currentAnim->width*m_currentAnim->currentFrame,
			m_currentAnim->height*m_currentAnim->row,
			m_currentAnim->width,
			m_currentAnim->height));

	m_sprite.setScale(m_scale,m_scale);
}

void Animation::setAnimation(const std::string & id)
{
	auto it = m_animations.find(id);
	if (m_currentAnim != it->second)
	{
		m_currentAnim = it->second;
	//	m_timer = 0;
		m_id = id;
	}
}

void Animation::makeAnimation(const std::string & id, int framesCount, bool isRepeating, int width, int height, float frameTime, int row)
{
	std::shared_ptr<AnimationSet> anim = std::make_unique<AnimationSet>();
	anim->framesCount = framesCount;
	anim->isRepeating = isRepeating;
	anim->width = width;
	anim->height = height;
	anim->frameTime = frameTime;
	anim->row = row;
	anim->currentFrame = 0;
	m_animations.emplace(id, std::move(anim));
}

sf::FloatRect Animation::getBounds()
{
	return sf::FloatRect(
		m_sprite.getPosition().x,
		m_sprite.getPosition().y,
		m_currentAnim->width*m_scale,
		m_currentAnim->height*m_scale);
}
