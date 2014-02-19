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
		
		void draw(video::Attribute vertexAttribute, const video::Uniform& colorUniform);
		
		void addPlatform(Platform platform);
		void removeOldPlatforms(float maxTime);
		
	private:
		std::list<Platform> m_platforms;
};

} // game

#endif // GAME_LEVEL_G

