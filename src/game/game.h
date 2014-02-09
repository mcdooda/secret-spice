#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "../engine/game.h"

namespace game
{

class Game : public engine::Game
{
	public:
		Game(std::vector<std::string> args);
		virtual ~Game();
		
		void initPasses();
		void initObjects();
		void initView();
		void initLogic();
		
		virtual void begin();
		virtual bool update();
		virtual void draw();
		virtual void end();
		
	private:
		// drawable objects
		geometry::Circle circle1;
		geometry::Circle circle2;
		
		geometry::Rectangle unitSquare;
		
		geometry::LineSegment x;
		geometry::LineSegment y;
		
		// camera
		video::View view;
		
		// mouse
		geometry::Vector2 viewMouse;
		
		// zoom or unzoom?
		bool zoom;
		
		// program
		video::Program program;
		
		// attributes & uniforms
		video::Attribute vertexAttribute;
		video::Uniform vpMatrixUniform;
		video::Uniform colorUniform;
};

} // game

#endif // GAME_GAME_H


