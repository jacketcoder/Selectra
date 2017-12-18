#pragma once
#include<GL/glew.h>
#include"GLTexture.h"
#include<string>
namespace Bengine{
	class Sprite
	{
	public:
		Sprite();//2 d image ,usually squares
		~Sprite();
		void init(float x, float y, float width, float height, std::string texturePath);

		void draw();
	private:
		//assuming square
		float _x, _y, _width, _height;
		GLuint _vboID;//32 bit
		GLTexture _texture;
	};
}
