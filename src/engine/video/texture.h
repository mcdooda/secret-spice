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
		Texture();

		inline unsigned int getTextureId() const { return m_textureId; }
		inline const geometry::Vector2& getSize() const { return m_size; }

	protected:
		unsigned int m_textureId;
		geometry::Vector2 m_size;
};

} // video
} // engine

#endif // ENGINE_VIDEO_TEXTURE_H


