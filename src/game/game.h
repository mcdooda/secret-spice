#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "../engine/game.h"

#include "level.h"
#include "audioanalyzer.h"

namespace game
{

class Game : public engine::Game
{
	public:
		Game(const std::vector<std::string>& args);
		virtual ~Game();
		
		virtual void checkArgs();
		
	public:
		// music
		audio::Music* music;
		AudioAnalyzer audioAnalyzer;
		std::list<essentia::Real> ticks;
		Spectrum* currentSpectrum;
		
		// video program
		video::View view;
		video::View interfaceView;
		
		// attributes & uniforms
		video::Program levelProgram;
		video::Attribute levelPositionAttribute;
		video::Attribute levelUvAttribute;
		video::Uniform levelVpMatrixUniform;
		video::Uniform levelColorUniform;
		
		// game objects
		Level level;
		
		float beginTime;
		float lastTick;
		float rotateDirection;
};

} // game

#endif // GAME_GAME_H


