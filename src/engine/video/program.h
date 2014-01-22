#ifndef ENGINE_VIDEO_PROGRAM_H
#define ENGINE_VIDEO_PROGRAM_H

#include <string>
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
		
		int getAttribLocation(std::string attribName);
		Uniform getUniform(std::string uniformName);
		
	private:
		int compileProgram(int fragmentShaderId, int vertexShaderId);
		int compileShader(std::string shader, int shaderType);
		
		void checkProgram(int programId);
		void checkShader(std::string shaderFile, int shaderId);
		
		const char* readCode(std::string shader);
		
	private:
		int m_programId;
		bool m_valid;
};

} // video
} // engine

#endif // ENGINE_VIDEO_PROGRAM_H


