#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "../engine/game.h"

namespace game
{

class Game : public engine::Game
{
	public:
		Game();
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
		
		geometry::LineSegment x;
		geometry::LineSegment y;
		
		// camera
		video::View view;
		
		// mouse
		geometry::Vector2 viewMouse;
		
		// zoom or unzoom?
		bool zoom;
		
		// render
		
		// 1st pass
		video::Pass pass1;
		
		video::RenderTexture colorTexture;
		
		video::Attrib vertexAttrib;
		video::Uniform vpMatrixUniform;
		video::Uniform colorUniform;
		
		// 2nd pass
		video::Render finalRender;
};

} // game

#endif // GAME_GAME_H


