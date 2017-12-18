#include "Sprite.h"
#include"Vertex.h"
#include"ResourceManager.h"
#include<cstddef>
namespace Bengine{
	Sprite::Sprite()
	{
		_vboID = 0;
	}
	void Sprite::init(float x, float y, float width, float height, std::string texturePath){
		_x = x;
		_y = y;
		_width = width;
		_height = height;
		_texture = ResourceManager::getTexture(texturePath);
		//immediate mode can be used but it is very slow.
		//generate buffer only if it hasnot been genereted.
		if (_vboID == 0){
			glGenBuffers(1, &_vboID);
		}

		/* GLfloat vertexData[] = {
			0.0f, 1.0f,
			1.0f,0.0f,0.0f,

			-1.0f, -1.0f,
			0.0f,1.0f,0.0f,

			1.0f, -1.0f,
			0.0f,0.0f,1.0f
			};
			*/
		Vertex vertexData[6];
		vertexData[0].setPosition(x + width, y + height);
		vertexData[1].setPosition(x, y + height);
		vertexData[2].setPosition(x, y);
		vertexData[3].setPosition(x, y);
		vertexData[4].setPosition(x + width, y);
		vertexData[5].setPosition(x + width, y + height);


		vertexData[0].setUV(x + width, y + height);
		vertexData[1].setUV(x, y + height);
		vertexData[2].setUV(x, y);
		vertexData[3].setUV(x, y);
		vertexData[4].setUV(x + width, y);
		vertexData[5].setUV(x + width, y + height);

		//vertex color
		for (int i = 0; i < 6; i++){
			vertexData[i].setColor(225, 0, 225, 225);
		}
		vertexData[1].setColor(0, 0, 225, 225);
		vertexData[4].setColor(0, 225, 0, 225);

		//uploading the data
		//blind buffer
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		//WHERE ARE DATA
		//position attribute pointer
		//for position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, 0);
		//for color
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (char*)(sizeof(GLfloat)*2));
		
		//position attribute pointer
		//for position
		//	glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, 0);
		//for color
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (char*)(sizeof(GLfloat) * 2));



	}
	void Sprite::draw(){
		glBindTexture(GL_TEXTURE_2D, _texture.id);
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		//what are we giving
				glDrawArrays(GL_TRIANGLES, 0, 6);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	Sprite::~Sprite()
	{
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		if (_vboID != 0)
			glDeleteBuffers(1, &_vboID);
	}
}