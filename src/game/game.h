#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "../engine/game.h"

#include "level.h"

namespace game
{

class Game : public engine::Game
{
	public:
		Game(std::vector<std::string> args);
		virtual ~Game();
		
		void initWindow();
		void initAudio();
		void initPasses();
		void initView();
		void initLevel();
		
		virtual void begin();
		virtual bool update();
		virtual void draw();
		virtual void end();
		
	private:
		// music
		audio::Music* music;
		
		// video program
		video::Program program;
		video::View view;
		
		// attributes & uniforms
		video::Attribute vertexAttribute;
		video::Uniform vpMatrixUniform;
		video::Uniform colorUniform;
		
		// level
		Level level;
};

} // game

#endif // GAME_GAME_H


