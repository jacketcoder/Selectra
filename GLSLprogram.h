#pragma once
#include<GL/glew.h>
#include<string>
class GLSLprogram
{
public:
	GLSLprogram();
	~GLSLprogram();
	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath );
	void linkShaders();
	void addAttribute(const std::string& attributeName);
	void use();
	void unuse();
	GLuint getUniformLocation(const std::string uniformName);
private:
	int _numAttributes; 
	void compileShader(const std::string& filePath,GLuint id );
	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};

