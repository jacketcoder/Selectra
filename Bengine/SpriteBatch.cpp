#include "SpriteBatch.h"
#include<algorithm>
#include<iostream>
namespace Bengine{
	Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color &Color){
		//std::cout << "dfadfsa";
		texture = Texture;
		depth = Depth;
		topLeft.color = Color;
		topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = Color;
		bottomLeft.setPosition(destRect.x, destRect.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.color = Color;
		bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.color = Color;
		topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	}
	Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const Color &Color,float angle){
		glm::vec2 halfDims(destRect.z/ 2, destRect.w/ 2);
		//std::cin >> angle; //<< std::endl;
		glm::vec2 tl(-halfDims.x, halfDims.y);
		glm::vec2 bl(-halfDims.x, -halfDims.y);
		glm::vec2 br(halfDims.x, -halfDims.y);
		glm::vec2 tr(halfDims.x, halfDims.y);
		tl = rotatePoint(tl, angle)+halfDims;
		bl = rotatePoint(bl, angle) + halfDims;
		br = rotatePoint(br, angle) + halfDims;
		tr = rotatePoint(tr, angle) + halfDims;
		texture = Texture;
		depth = Depth;
		topLeft.color = Color;
		topLeft.setPosition(destRect.x+tl.x, destRect.y + tl.y);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = Color;
		bottomLeft.setPosition(destRect.x+bl.x, destRect.y+bl.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		bottomRight.color = Color;
		bottomRight.setPosition(destRect.x+br.x, destRect.y+br.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

		topRight.color = Color;
		topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	}
	glm::vec2 Glyph::rotatePoint(glm::vec2 pos, float angle){
		glm::vec2 newv;
		newv.x = pos.x*cos(angle) -pos.y*sin(angle);
		newv.y = pos.x*sin(angle) - pos.y*cos(angle);
		return newv;
	}
	SpriteBatch::SpriteBatch() :_vao(0), _vbo(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}
	void SpriteBatch::init(){
		createVertexArray();
		}
	void SpriteBatch::begin(GlyphSortType sortType){
		_sortType = sortType;
		_renderBatches.clear();
		
		_glyphs.clear();
	}
	void SpriteBatch::end(){
		_glyphPointer.resize(_glyphs.size());
		for (int i = 0; i < _glyphs.size(); i++)
			_glyphPointer[i] = &_glyphs[i];
		sortGlyphs(); 
		createRenderBatches();
		
	}
	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color &color){

		_glyphs.emplace_back(destRect, uvRect, texture,depth, color);
	}
	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color &color, float angle){
		_glyphs.emplace_back(destRect, uvRect, texture, depth, color,angle);
	}
	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color &color, const glm::vec2 dir){
		const glm::vec2 right(1, 0);
		float angle = acos(glm::dot(right, dir));
		if (dir.y < 0)
			angle = -angle;
		//std::cout << angle << std::endl;
		_glyphs.emplace_back(destRect, uvRect, texture, depth, color,angle);
	}
	void SpriteBatch::renderBatch(){
		glBindVertexArray(_vao);
		for (int i = 0; i < _renderBatches.size(); i++){
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
			glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
		}
		glBindVertexArray(0);
	}
	void SpriteBatch::createRenderBatches(){
		std::vector<Vertex>vertices;
		vertices.resize(_glyphPointer.size() * 6);
		if (_glyphPointer.empty())
			return;
		int offset = 0;
		int cv = 0;
		_renderBatches.emplace_back(offset, 6, _glyphPointer[0]->texture);
		vertices[cv++] = _glyphPointer[0]->topLeft;
		vertices[cv++] = _glyphPointer[0]->bottomLeft;
		vertices[cv++] = _glyphPointer[0]->bottomRight;
		vertices[cv++] = _glyphPointer[0]->bottomRight;
		vertices[cv++] = _glyphPointer[0]->topRight;
		vertices[cv++] = _glyphPointer[0]->topLeft;
		offset += 6;
		//cg  current Glyph
		for (int cg = 1; cg < _glyphPointer.size(); cg++){
			if (_glyphPointer[cg]->texture != _glyphPointer[cg - 1]->texture)
				_renderBatches.emplace_back(offset, 6, _glyphPointer[cg]->texture);
			else
				_renderBatches.back().numVertices += 6;

			vertices[cv++] = _glyphPointer[cg]->topLeft;
			vertices[cv++] = _glyphPointer[cg]->bottomLeft;
			vertices[cv++] = _glyphPointer[cg]->bottomRight;
			vertices[cv++] = _glyphPointer[cg]->bottomRight;
			vertices[cv++] = _glyphPointer[cg]->topRight;
			vertices[cv++] = _glyphPointer[cg]->topLeft;
			offset += 6;
		
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		//orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//upload the data
		glBufferSubData(GL_ARRAY_BUFFER,0, vertices.size()*sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void SpriteBatch::createVertexArray(){
		if (_vao == 0)
			glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);
		if (_vbo == 0)
			glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//we maynot draw all vboid
		//position
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//color
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		//UV 
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);

	}
	void SpriteBatch::sortGlyphs(){
		switch (_sortType){
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphPointer.begin(), _glyphPointer.end(), compareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphPointer.begin(), _glyphPointer.end(), compareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphPointer.begin(), _glyphPointer.end(), compareTexture);
				break;
		}


	}
	 bool SpriteBatch::compareFrontToBack(Glyph*a, Glyph*b){
		 return(a->depth < b->depth);
	}
	 bool SpriteBatch::compareBackToFront(Glyph*a, Glyph*b){
		 return(a->depth > b->depth);
	 }
	 bool SpriteBatch::compareTexture(Glyph*a, Glyph*b){
		 return(a->texture < b->texture);
	 }


}