#pragma once
#include"GL\glew.h"
#include"SDL\SDL.h"

#include<string>
namespace Bengine{
	enum  windowFlags{ INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4,NORMAL=0x00 };
	class Window
	{
	public:
		Window();
		~Window();
		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
		int getScreenHeight(){ return _screenHeight; }
		int getScreenWidth(){ return _screenWidth; }
		void swapBuffer();
	private:
		SDL_Window* _sdlWindow;
		int _screenWidth, _screenHeight;

	};
}
