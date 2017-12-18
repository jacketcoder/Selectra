#include "TextureCache.h"
#include"imageLoader.h"
#include<iostream>
namespace Bengine{
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}
	GLTexture TextureCache::getTexture(std::string texturePath){
		//look up texture if it is in the map
		auto mit = _textureMap.find(texturePath);
		//check if it is in the map
		if (mit == _textureMap.end()){
			//loading the texture
			GLTexture newTexture = imageLoader::loadPNG(texturePath);
			//inserting to map
			//		std::pair<std::string, GLTexture>newPair(texturePath, newTexture);
			_textureMap.insert(make_pair(texturePath, newTexture));

			//std::cout << "used texture";
			return newTexture;
		}
		//std::cout << "used cached texture";
		return mit->second;


	}
}