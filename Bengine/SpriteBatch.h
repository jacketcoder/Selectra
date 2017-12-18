#pragma once
#include"GL\glew.h"
#include"glm\glm.hpp"
#include"Vertex.h"
#include<vector>
namespace Bengine{
	enum class GlyphSortType{
	NONE,
	BACK_TO_FRONT,
	FRONT_TO_BACK,
	TEXTURE

	};


	class Glyph{
	private:
		glm::vec2 rotatePoint(glm::vec2 pos, float angle);
	public:
		Glyph();
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color &Color);
		Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color &Color,float angle);
		Vertex topLeft;
		Vertex topRight;
		Vertex bottomLeft;
		Vertex bottomRight;
		GLuint texture;
		float depth;
	};
	class RenderBatch{
	public:
		RenderBatch(GLuint offset,GLuint numVertices,GLuint texture):
			offset(offset), numVertices(numVertices),texture(texture){}

		GLuint offset, numVertices, texture;

	};
	class SpriteBatch
	{
		
	public:
	 	SpriteBatch();
		~SpriteBatch();
		void init();
		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();
		void draw(const glm::vec4& destRect,const glm::vec4& uvRect,GLuint texture,float depth,const Color &color);
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color &color,float angle);
		void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color &color, const glm::vec2 dir);
		void renderBatch();
private:
	
	static bool compareFrontToBack(Glyph*a,Glyph*b);//it is of classes not of functions
	static bool compareBackToFront(Glyph*a, Glyph*b);
	static bool compareTexture(Glyph*a, Glyph*b);
	void createRenderBatches();
		void createVertexArray();
		void sortGlyphs();
		GlyphSortType _sortType;
		GLuint _vbo;
		GLuint _vao;
		std::vector<Glyph*>_glyphPointer;
		std::vector<Glyph>_glyphs;
		std::vector<RenderBatch>_renderBatches;
	};
}

