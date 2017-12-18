#pragma once
#include<iostream>
#include<GL/glew.h>
#include<string>
#include<fstream>
using std::string;
using std::cout;
using std::endl;
namespace Bengine{
	class GLSL
	{
	public:
		GLSL();
		~GLSL();
		void compileLinkShaders(const std::string& vertexFilePath, const std::string& shaderFilePath);
		void uniformData();
		void addAttribute(const std::string& attributeName);
		GLuint getUniformLocation(const std::string& uniformName);
		void use();
		void unuse();
	private:
		string readShaderCode(const char* fileName);
		bool checkProgramStatus(GLuint programID);
		bool checkShaderStatus(GLuint shaderID);
		int _numAttributes;
		GLuint _programID;
	};

}