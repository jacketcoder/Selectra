#include "GLSL.h"
#include"Error.h"
#include<glm/glm.hpp>
namespace Bengine{
	GLSL::GLSL() : _numAttributes(0), _programID(0)
	{
	}
	string GLSL::readShaderCode(const char* fileName){
		std::ifstream meInput(fileName);
		if (!meInput.good()){
			cout << "file failed to load,," << fileName;
		}
		return std::string(std::istreambuf_iterator<char>(meInput), std::istreambuf_iterator<char>());

	}
	bool GLSL::checkShaderStatus(GLuint shaderID){
		GLint compileStatus;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
		if (compileStatus != GL_TRUE){
			GLint infoLoglength;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLoglength);
			GLchar* buffer = new GLchar[infoLoglength];
			GLsizei bufferSize;
			glGetShaderInfoLog(shaderID, infoLoglength, &bufferSize, buffer);
			cout << buffer << endl;
			delete[]buffer;
			return false;
		}

		return true;

	}
	bool GLSL::checkProgramStatus(GLuint programID){
		GLint linkStatus;
		glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE){
			GLint infoLoglength;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLoglength);
			GLchar* buffer = new GLchar[infoLoglength];
			GLsizei bufferSize;
			glGetProgramInfoLog(programID, infoLoglength, &bufferSize, buffer);
			cout << buffer << endl;
			delete[]buffer;
			return false;
		}

		return true;

	}

	void GLSL::compileLinkShaders(const std::string& vertexFilePath, const std::string& shaderFilePath){
		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (vertexShaderID == 0)
			fatalError("vertex shader failed to create");
		if (fragmentShaderID == 0)
			fatalError("fragment shader failed to create");


		//reading from file


		const char* adapter[1];
		//string temp = readShaderCode("VertexShaderCode.glsl");
		string temp = readShaderCode(vertexFilePath.c_str());
		adapter[0] = temp.c_str();


		glShaderSource(vertexShaderID, 1, adapter, 0);
		//temp = readShaderCode("FragmentShaderCode.glsl");
		temp = readShaderCode(shaderFilePath.c_str());
		adapter[0] = temp.c_str();
		glShaderSource(fragmentShaderID, 1, adapter, 0);

		glCompileShader(vertexShaderID);
		glCompileShader(fragmentShaderID);

		//checking errors
		if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
			fatalError("failed to complie");



		_programID = glCreateProgram();
		glAttachShader(_programID, vertexShaderID);
		glAttachShader(_programID, fragmentShaderID);
		glLinkProgram(_programID);
		//checking errors

		if (!checkProgramStatus(_programID))
			fatalError("failed to link");

		//deleting after being used
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

		//using ID
		glUseProgram(_programID);
	}

	void GLSL::uniformData(){
		glm::vec3 dominatingColor(1.0f, 1.0f, .0f);
		GLint dominatingColorUniformLocation = glGetUniformLocation(_programID, "dominatingColor");
		if (dominatingColorUniformLocation == GL_INVALID_INDEX)
			cout << "uniform variable cant be created";
		glUniform3fv(dominatingColorUniformLocation, 1, &dominatingColor[0]);


	}
	GLuint GLSL::getUniformLocation(const std::string& uniformName){
		GLuint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
			fatalError("uniform" + uniformName + "cannot be created");
		return location;
	}
	void GLSL::addAttribute(const std::string& attributeName){
		glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());

	}
	void GLSL::use(){
		glUseProgram(_programID);
		for (int i = 0; i < _numAttributes; i++)
			glEnableVertexAttribArray(i);
	}
	void GLSL::unuse(){
		glUseProgram(0);
		for (int i = 0; i < _numAttributes; i++)
			glDisableVertexAttribArray(i);
	}
	GLSL::~GLSL()
	{
	}
}