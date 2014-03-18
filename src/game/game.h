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
		virtual void checkArgs();
		
		void initWindow();
		void initAudioAnalyzer();
		void initPasses();
		void initView();
		void initLevel();
		void initAudio();
		
		void closeAudioAnalyzer();
		
		virtual void begin();
		virtual bool update();
		virtual void draw();
		virtual void end();
		
	private:
		// music
		audio::Music* music;
		AudioAnalyzer audioAnalyzer;
		std::list<essentia::Real> ticks;
		Spectrum* currentSpectrum;
		
		// video program
		video::View view;
		
		// attributes & uniforms
		video::Program levelProgram;
		video::Attribute levelVertexAttribute;
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


