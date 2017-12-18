#include"error.h"
#include<cstdlib>
#include<iostream>
#include<SDL/SDL.h>
namespace Bengine{
	void fatalError(std::string errorString){
		std::cout << errorString.c_str() << std::endl;
		std::cout << " to quit...";
		int error;
		std::cin >> error;
		SDL_Quit();
		exit(69);

	}
}