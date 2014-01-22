#ifndef ENGINE_VIDEO_TEXTURE_H
#define ENGINE_VIDEO_TEXTURE_H

#include <string>
#include <SDL2/SDL.h>
#include "../geometry/vector2.h"
#include "color.h"

namespace engine
{
namespace video
{

class Texture
{
	public:
		Texture(std::string filename);

		inline unsigned int getId() const { return m_id; }
		inline unsigned int getWidth() const { return m_surface->w; }
		inline unsigned int getHeight() const { return m_surface->h; }
		inline geometry::Vector2 getDimensions() const { return geometry::Vector2(m_surface->w, m_surface->h); }

		inline const std::string& getPath() const { return m_path; }
		
		Color getPixel(int x, int y);

	protected:
		Texture() {}

		void load();
		void free();
		
		SDL_Surface* m_surface;
		
		unsigned int m_id;

		std::string m_path;
};

} // video
} // engine

#endif // ENGINE_VIDEO_TEXTURE_H


