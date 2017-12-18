#pragma once
#include"GLTexture.h"
#include<string>
namespace Bengine{
	class imageLoader
	{
	public:
		static GLTexture loadPNG(std::string filepath);
		imageLoader();
		~imageLoader();
	};
}
