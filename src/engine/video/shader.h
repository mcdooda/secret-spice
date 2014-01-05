#ifndef ENGINE_VIDEO_SHADER_H
#define ENGINE_VIDEO_SHADER_H

#include <string>

namespace engine
{
namespace video
{

class Shader
{
	public:
		Shader();
		~Shader();
		
		void load(std::string fragmentShader, std::string vertexShader);
		
		void use();
		
		int getAttribLocation(std::string attribName);
		int getUniformLocation(std::string uniformName);
		
	private:
		int compileProgram(int fragmentShaderId, int vertexShaderId);
		int compileShader(std::string shader, int shaderType);
		
		void checkProgram(int programId);
		void checkShader(int shaderId);
		
		std::string readCode(std::string shader);
		
	private:
		int m_programId;
};

} // video
} // engine

#endif // ENGINE_VIDEO_SHADER_H


