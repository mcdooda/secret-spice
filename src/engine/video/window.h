#ifndef ENGINE_VIDEO_WINDOW_H
#define ENGINE_VIDEO_WINDOW_H

#include <string>
#include <SDL/SDL.h>
#include "view.h"

namespace engine
{
namespace video
{

class Window
{
	public:
		Window();
		~Window();
		
		void open(geometry::Vector2d size, std::string name, bool fullScreen);

		void toggleFullScreen();
		
		inline bool isFullScreen() const { return m_fullScreen; }

		inline const geometry::Vector2d& getSize() { return m_size; }
		inline void setSize(const geometry::Vector2d& size) { m_size = size; }

		geometry::Vector2d getDesktopSize();

		void setView(View view);
		inline const View& getView() const { return m_view; }
		void setInterfaceView();

		void resize();
	
	private:
		geometry::Vector2d m_size;
		geometry::Vector2d m_oldSize;
		bool m_fullScreen;
		SDL_Surface* m_screen;
		View m_view;
};

} // video
} // engine

#endif // ENGINE_VIDEO_WINDOW_H


