#include "Window.h"
#include"Error.h"
#include<iostream>
namespace Bengine{
	Window::Window()
	{
	}
	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags){
		Uint32 flags = SDL_WINDOW_OPENGL;
		if (currentFlags&FULLSCREEN)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		if (currentFlags&INVISIBLE)
			flags |= SDL_WINDOW_HIDDEN;
		if (currentFlags&BORDERLESS)
			flags |= SDL_WINDOW_BORDERLESS;

		_sdlWindow = SDL_CreateWindow(windowName.c_str(), 200, 30, screenWidth, screenHeight, flags);
		if (_sdlWindow == nullptr){
			fatalError("SDL Window could not be created");//SDL_WINDOWPOS_CENTERED
		}
		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (glContext == nullptr)
			fatalError("SDL_GL context could not be created");
		GLenum error = glewInit();
		if (error != GLEW_OK)
			fatalError("could not initialize glew");
		std::cout << "openGL version" << glGetString(GL_VERSION)<< std::endl;
		//yellow color
		glClearColor(0.0f, 0.0f, .0f, 0.0f);
		//set VSYNC

		SDL_GL_SetSwapInterval(0);
		//enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		return 0;

	}
	void Window::swapBuffer(){
		SDL_GL_SwapWindow(_sdlWindow);
	}
	Window::~Window()
	{
	}
}