#ifndef ENGINE_VIDEO_PASS_H
#define ENGINE_VIDEO_PASS_H

#include <vector>
#include "program.h"
#include "rendertexture.h"

namespace engine
{
namespace video
{

class Pass : public Program
{
	public:
		Pass();
		virtual ~Pass();
		
		void init(const geometry::Vector2& size);
		
		void use();
		
		RenderTexture newDepthTexture(std::string name);
		RenderTexture newColorTexture(std::string name);
		RenderTexture newFloatTexture(std::string name);
		
	private:
		RenderTexture newOutputTexture(std::string name, int internalFormat, int format, int attachment);
		
	private:
		geometry::Vector2 m_size;
		unsigned int m_fbo;
		
		std::vector<RenderTexture> m_outputTextures;
		RenderTexture m_outputDepthTexture;
};

} // video
} // engine

#endif // ENGINE_VIDEO_PASS_H


