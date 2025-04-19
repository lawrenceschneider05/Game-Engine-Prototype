#pragma once
#include <string>
#include <glm/glm.hpp>

using std::string;
using namespace glm;

namespace GameEngine
{
	class Shader
	{
	public:
		Shader() {}
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