#pragma once
#include<Bengine/Bengine.h>
#include<Bengine/sprite.h>
#include<SDL/SDL.h>
#include<GL/glew.h>
#include<Bengine/GLSL.h>
#include<Bengine/GLTexture.h>
#include<Bengine/Window.h>
#include<Bengine/Camera2D.h>
#include<Bengine/SpriteBatch.h>
#include<Bengine/InputManager.h>
#include<Bengine/Timing.h>
#include<vector>
#include"Bullet.h"
enum class GameState{PLAY,EXIT};
class MainGame
{
public:
	MainGame();
	~MainGame();
	void run();//starting the game
	private:

	void initSystems();//set up the window initialize SDL,openGL
	void initShaders();
	void gameLoop();
	void drawGame();
	//void calculateFPS();
	void processInput();
	Bengine::Window _window;//need a window,pointer to window for resize the window,set screen height,width.handle to window
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;
	//std::vector<Bengine::Sprite*> _sprites;
	float _time;
	float _fps;
	float _maxFPS; 
	
	Bengine::GLSL _glsl;
	Bengine::GLTexture _playerTexture;
	Bengine::Camera2D _camera;
	Bengine::SpriteBatch _spriteBatch;;
	Bengine::InputManager _inputManager;
	Bengine::FpsLimiter  _fpsLimiter;
	std::vector<Bullet>_bullet;
};

