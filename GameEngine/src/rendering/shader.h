#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>

using std::string;
using namespace glm;

namespace GameEngine
{
	class Shader
	{
	public:
		Shader() {}
		~Shader()
		{
			glDeleteShader(program);
		}
		Shader(string vertPath, string fragPath);
		void bind();
		void setMat4(string, mat4);
	private:
		string readFile(const string& path);
		void compileShaders();
		string vertPath, fragPath;
		u32 program;
	};
}