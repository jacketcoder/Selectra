#include "GLSLprogram.h"
#include"Error.h"
#include<fstream>
#include<iostream>
#include<vector>
GLSLprogram::GLSLprogram() : _numAttributes(0),_programID(0), _vertexShaderID(0), _fragmentShaderID(0)
{

}
void GLSLprogram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath){
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0)
		fatalError("vertex shader failed to be created");
	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0)
		fatalError("fragment shader failed to be created");
	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);



}
void GLSLprogram::linkShaders(){
	GLuint _programID = glCreateProgram();
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);
	glLinkProgram(_programID); 
	
	GLint isLinked = 0;
	
	glGetProgramiv(_programID, GL_LINK_STATUS, (int*)&isLinked);
	
	if (isLinked == GL_FALSE){
		GLint maxLength = 0;
		
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);
		glDeleteProgram(_programID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
		std::printf("%s\n", &(errorLog[0]));
		fatalError(" shader  failed to link");
		//return;

	}
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
	 

}
GLSLprogram::~GLSLprogram(){}
void GLSLprogram ::compileShader(const std::string& filePath,GLuint id)  

{
	
	std::ifstream vertexFile(filePath);
	if (vertexFile.fail()){
		perror(filePath.c_str());
		fatalError("failed to open" + filePath);
	}
	//reading entire file 
	std::string fileContents = "";
	std::string line;
	while (std::getline(vertexFile, line)){
		//getline doesnot grab the new line
		fileContents += line + "\n";

	}
	vertexFile.close();
	const char*contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);
	glCompileShader(id);
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE){
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
		glDeleteShader(id);
		std::printf("%s\n", &(errorLog[0]));
		fatalError(" shader"+filePath +" failed to compile");
		return;
	}

}
void GLSLprogram::addAttribute(const std::string& attributeName){
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}
GLuint GLSLprogram::getUniformLocation(const std::string uniformName){
	//std::cout << _programID;
	GLuint location= glGetUniformLocation(_programID, uniformName.c_str());
	std::cout << _programID;
	//std::cout << location;
	if (location == GL_INVALID_INDEX){
		fatalError("Uniform" + uniformName + "not found in shader");
	}
	return location;
}
void GLSLprogram::use(){
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++)
		glEnableVertexAttribArray(i);

}
void GLSLprogram::unuse(){
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++)
		glDisableVertexAttribArray(i);

}