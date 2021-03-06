#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <list>

#include "platform.h"

namespace game
{

class Level
{
	public:
		Level();
		~Level();
		
		void draw(float maxTime, video::Attribute positionAttribute, video::Attribute uvAttribute, const video::Uniform& colorUniform);
		
		void getCurrentPlatforms(float time, Platform** previousPlatform, Platform** nextPlatform);
		
		void addPlatform(Platform platform);
		void removeOldPlatforms(float maxTime);
		void fadeOldPlatforms(float maxTime);
		
	private:
		std::list<Platform> m_platforms;
};

} // game

#endif // GAME_LEVEL_G


