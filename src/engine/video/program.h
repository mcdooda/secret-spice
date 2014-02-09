#ifndef ENGINE_VIDEO_PROGRAM_H
#define ENGINE_VIDEO_PROGRAM_H

#include <map>
#include <string>
#include <vector>
#include "attribute.h"
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
		
		Attribute getAttribute(std::string attributeName);
		Uniform getUniform(std::string uniformName);
		
	private:
		int compileProgram(unsigned int fragmentShaderId, unsigned int vertexShaderId);
		int compileShader(std::string shader, unsigned int shaderType);
		
		void checkProgram(unsigned int programId);
		void checkShader(std::string shaderFile, unsigned int shaderId);
		
		const char* readCode(std::string shader);
		
		void loadAttributes();
		void loadUniforms();
		
	protected:
		unsigned int m_programId;
		bool m_valid;
		
		std::map<std::string, Attribute> m_attributes;
		std::map<std::string, Uniform> m_uniforms;
};

} // video
} // engine

#endif // ENGINE_VIDEO_PROGRAM_H


