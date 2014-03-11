#include "level.h"

namespace game
{

Level::Level()
{
	
}

Level::~Level()
{
	
}

void Level::draw(video::Attribute vertexAttribute, const video::Uniform& colorUniform)
{
	for (std::list<Platform>::iterator it = m_platforms.begin(); it != m_platforms.end(); it++)
	{
		it->draw(vertexAttribute, colorUniform);
	}
}

void Level::addPlatform(Platform platform)
{
	m_platforms.push_back(platform);
}

void Level::removeOldPlatforms(float maxTime)
{
	while (m_platforms.begin() != m_platforms.end() && m_platforms.begin()->getTime() < maxTime)
		m_platforms.pop_front();
}

void Level::fadeOldPlatforms(float maxTime)
{
	for (std::list<Platform>::iterator it = m_platforms.begin(); it != m_platforms.end() && it->getTime() < maxTime; it++)
		it->setColor(video::Color(0.5f));
}

} // game


