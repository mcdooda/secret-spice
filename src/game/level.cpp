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
		it->draw(vertexAttribute, colorUniform);
}

void Level::getCurrentPlatforms(float time, Platform** previousPlatform, Platform** nextPlatform)
{
	*previousPlatform = NULL;
	*nextPlatform = NULL;
	for (std::list<Platform>::iterator it = m_platforms.begin(); it != m_platforms.end(); it++)
	{
		if (it->getTime() > time)
		{
			*nextPlatform = &(*it);
			it--;
			*previousPlatform = &(*it);
			break;
		}
	}
	if (*previousPlatform == NULL)
	{
		std::list<Platform>::iterator it = m_platforms.end();
		it--;
		*previousPlatform = &(*it);
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
		it->setColor(video::Color(0.0f, 0.0f, 1.0f, 1.0f));
}

} // game


