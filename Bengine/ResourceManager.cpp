#include "ResourceManager.h"

namespace Bengine{
	ResourceManager::ResourceManager()
	{
	}


	ResourceManager::~ResourceManager()
	{
	}

	TextureCache ResourceManager::_textureCache;
	GLTexture ResourceManager::getTexture(std::string texturePath){
		return _textureCache.getTexture(texturePath);
	}
}