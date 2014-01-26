#ifndef ENGINE_VIDEO_RENDERTEXTURE_H
#define ENGINE_VIDEO_RENDERTEXTURE_H

#include "../geometry/vector2.h"

namespace engine
{
namespace video
{

class RenderTexture
{
	public:
		RenderTexture();
		~RenderTexture();
		
		void init(std::string name, unsigned int fragDataLocation, unsigned int textureId, const geometry::Vector2& size);
		
		inline const std::string& getName() const { return m_name; }
		inline unsigned int getFragDataLocation() const { return m_fragDataLocation; }
		inline unsigned int getTextureId() const { return m_textureId; }
		inline const geometry::Vector2& getSize() const { return m_size; }
		
	private:
		std::string m_name;
		unsigned int m_fragDataLocation;
		unsigned int m_textureId;
		geometry::Vector2 m_size;
};

} // video
} // engine

#endif // ENGINE_VIDEO_RENDERTEXTURE_H


