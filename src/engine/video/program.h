#ifndef ENGINE_VIDEO_PROGRAM_H
#define ENGINE_VIDEO_PROGRAM_H

#include <map>
#include <string>
#include <vector>
#include "attribute.h"
#include "uniform.h"
#include "window.h"

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
		
		void use(Window* window);
		
		void pass();
		void render();
		
		Attribute getAttribute(std::string attributeName);
		Uniform getUniform(std::string uniformName);
		
	private:
		GLuint compileProgram(GLuint fragmentShaderId, GLuint vertexShaderId);
		GLuint compileShader(std::string shader, GLuint shaderType);
		
		void checkProgram(GLuint programId);
		void checkShader(std::string shaderFile, GLuint shaderId);
		
		const GLchar* readCode(std::string shader);
		
		void loadAttributes();
		void loadUniforms();
		
	protected:
		GLuint m_programId;
		bool m_valid;
		
		std::map<std::string, Attribute> m_attributes;
		std::map<std::string, Uniform> m_uniforms;
};

} // video
} // engine

#endif // ENGINE_VIDEO_PROGRAM_H


