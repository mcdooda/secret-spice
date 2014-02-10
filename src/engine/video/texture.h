#ifndef ENGINE_VIDEO_TEXTURE_H
#define ENGINE_VIDEO_TEXTURE_H

#include <GL/glew.h>
#include "../geometry/vector2.h"

namespace engine
{
namespace video
{

class Texture
{
	public:
		Texture();

		inline GLuint getTextureId() const { return m_textureId; }
		inline const geometry::Vector2& getSize() const { return m_size; }

	protected:
		GLuint m_textureId;
		geometry::Vector2 m_size;
};

} // video
} // engine

#endif // ENGINE_VIDEO_TEXTURE_H


