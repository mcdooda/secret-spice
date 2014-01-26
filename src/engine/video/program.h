#ifndef ENGINE_VIDEO_PROGRAM_H
#define ENGINE_VIDEO_PROGRAM_H

#include <string>
#include <vector>
#include "attrib.h"
#include "uniform.h"

namespace engine
{
namespace video
{

class Program
{
	public:
		Program();
		~Program();
		
		void load(std::string fragmentShader, std::string vertexShader);
		
		inline bool isValid() const { return m_valid; }
		
		void use();
		
		void pass();
		void render();
		
		Attrib getAttrib(std::string attribName);
		Uniform getUniform(std::string uniformName);
		
		inline const Uniform& getVpMatrixUniform() const { return m_vpMatrixUniform; }
		inline const Attrib& getPositionAttrib() const { return m_positionAttrib; }
		
		void addInputTexture(RenderTexture texture);
		
	private:
		int compileProgram(unsigned int fragmentShaderId, unsigned int vertexShaderId);
		int compileShader(std::string shader, unsigned int shaderType);
		
		void checkProgram(unsigned int programId);
		void checkShader(std::string shaderFile, unsigned int shaderId);
		
		const char* readCode(std::string shader);
		
		void loadCommonAttribsUniforms();
		
	protected:
		unsigned int m_programId;
		bool m_valid;
		
		Uniform m_vpMatrixUniform;
		Attrib m_positionAttrib;
		
		std::vector<RenderTexture> m_inputTextures;
		std::vector<Uniform> m_inputTexturesUniforms;
};

} // video
} // engine

#endif // ENGINE_VIDEO_PROGRAM_H


