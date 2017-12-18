#pragma once
#include"SpriteBatch.h"
#include"ResourceManager.h"
#include"InputManager.h"
#include"SDL\SDL.h"
#include<iostream>
class GUI
{
public:
	GUI();
	void init(Bengine::SpriteBatch& gui, int width, int height, Bengine::InputManager* _input);
	int getCursorPos(int x, int y);
	void drawObject();
	void renderUI();
	GLuint _uiTexture;
	~GUI();
	bool _nextWindow = false;
private:
	glm::vec2 buttonPlayX;
	glm::vec2 buttonPlayY;
	glm::vec2 buttonQuitX;
	glm::vec2 buttonQuitY;
	
	glm::vec4 _destRect;
	glm::vec4 UV;
	Bengine::SpriteBatch* _UI;
	Bengine::Color color;
	Bengine::InputManager* _input;
};

