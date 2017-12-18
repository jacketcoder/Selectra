#pragma once
#include<iostream>
#include<random>
#include<algorithm>
#include<ctime>
#include"GL\glew.h"
#include"Window.h"
#include"Bengine.h"
#include"Camera2D.h"
#include"GLSL.h"
#include"Level.h"
#include"InputManager.h";
#include"SpriteFont.h"
#include"SpriteBatch.h"
#include"AudioEngine.h"
#include"Timing.h"
#include"Selectra.h"
#include"Balls.h"
#include "gameObject.h"
#include"_GUI.h"
#include"AI.h"

const float CAMERA_SPEED = 0.0f;

enum GAMESTATE{PLAY,PAUSE,EXIT};
 enum BALLCOLOR{RED,YELLOW,PINK,PUPRLE,WHITE};
class MainGame
{
public:
	MainGame();
	~MainGame();
	void gameStart();
	
	
private:
	//functions
	void position(){ cout << _randomPosition.x << "x and y" << _randomPosition.y << std::endl; }
	void drawScore();
	void initializeGame();
	void gameLoop();
	void initShaders();
	void drawGame();
	void processInput();
	void initLevel();
	void updateObjects(float deltaTime);
	int randomFunction(int min, int max);
	//void updateBalls(float deltaTime);
	void scoreAI();
	void creatingBall();
	void checkingBallPosition();
	//data
	GAMESTATE _gameState;
	int _windowWidth, _windowHeight;
	//engine datas
	Bengine::Window _window;
	Bengine::Camera2D _camera;
	Bengine::GLSL _shader;
	Bengine::AudioEngine _audioEngine;
	//Bengine::GUI _gui;
	//storing level in vectors
	std::vector<Level*> _levels;
	int _level1;
	Bengine::SpriteFont* _spriteFont;
	Bengine::SpriteBatch _scoreSpriteBatch;
	Bengine::InputManager _inputManager;
	//spritebatch of selectra
	Bengine::SpriteBatch _selectraSpriteBatch;
	Selectra* _selectra;
	Balls* _ball;
	std::vector<Balls*> _balls;
	Bengine::SpriteBatch _ballSpriteBatch;
	GUI _gui;
	GUI _backGround;
	gameObject *_gameObject[5];
	Bengine::Color _randColor;

	std::vector<Bengine::Color> _color;
	Bengine::SpriteBatch _GUI;
	Bengine::SpriteBatch _backGroundSprite;
	int randX;
	float speedY;
	 int _score;
	 std::mt19937 randomEngine;
	 int _speed;
	 glm::vec2 _randomPosition;
	 int _randomColorNo;
	 bool _update;
	 glm::vec2 _speedLimit;
	 float m_fps;
	 glm::vec2 _dirn;
	 int BALL;
	
	 bool _createBall;
	 bool _state ;
	 int x, y;
	 AI _AI;
	 int _life;
	 int gui = 0;
};

