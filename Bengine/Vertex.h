#pragma once
#include<GL/glew.h>
namespace Bengine{
	struct Position{
		float x;
		float y;
	};
	struct Color{
		GLubyte r;
		GLubyte	g;
		GLubyte	b;
		GLubyte a;
	
		void setColor(int x, int y, int z ,int s){
			r = GLubyte(x);
			g = GLubyte(y);
			b = GLubyte(z);
			a = GLubyte(s);
		}
	};
	struct UV{
		float u, v;
	};
	struct Vertex{

		Position position;
		Color color;
		UV uv;
		void setPosition(float x, float y){
			position.x = x;
			position.y = y;
		}
		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a){
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}
		void setUV(float u, float v){
			uv.u = u;
			uv.v = v;
		}

	};
}