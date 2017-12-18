#include "MainGame.h"
#include<iostream>
#include<Bengine/Error.h>
#include<Bengine/ResourceManager.h>

MainGame::MainGame() :
_screenWidth(150), 
_screenHeight(768),
_time(0.0f),
_gameState(GameState::PLAY),
_maxFPS(60.0f)
{
	_camera.init(_screenWidth, _screenHeight);
}


MainGame::~MainGame()
{
}
void MainGame::run(){
	initSystems();//just calling it,initialize the systems
	gameLoop();//then call the game loop
}
void MainGame::initSystems(){
	Bengine::init();
	_window.create("GameEngine", _screenWidth, _screenHeight, 0);
	initShaders();
	_spriteBatch.init();
	_fpsLimiter.init(_maxFPS);
}
void MainGame::initShaders(){
	_glsl.compileLinkShaders("colorShadingV.txt", "colorShadingF.txt");
	_glsl.addAttribute("vertexPosition");
	_glsl.addAttribute("vertexColor");
	_glsl.addAttribute("vertexUV");

}
void MainGame::gameLoop(){//need to be called
	while (_gameState != GameState::EXIT){
		//used for frame time measuring
		_fpsLimiter.begin();
		processInput();
		_time += 0.009;
		_camera.update();
		for (int i = 0; i < _bullet.size();){
			if (_bullet[i].update() == true){
				_bullet[i] = _bullet.back();
				_bullet.pop_back();
			}
			else
				i++;
	}
				
		drawGame();
		_fps = _fpsLimiter.end();
		//float startTicks = SDL_GetTicks();
		//print only on every 10 frame;
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 1000){
			std::cout << _fps << std::endl;
			frameCounter = 0;
		}


	}
}
void MainGame::processInput(){
	SDL_Event evnt;
	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = .1f;
	while (SDL_PollEvent(&evnt)){//askes the event need to be processed,user moving mouse,typing
		//loking its type
		switch (evnt.type){
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x,evnt.motion.y);
			break;
		}
	}

			if (_inputManager.isKeyDown(SDLK_w)) {
				_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
			}
		if (_inputManager.isKeyDown(SDLK_s)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
		}
		if (_inputManager.isKeyDown(SDLK_a)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
		}
		if (_inputManager.isKeyDown(SDLK_d)) {
			_camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
		}
		if (_inputManager.isKeyDown(SDLK_q)) {
			_camera.setScale(_camera.getScale() + SCALE_SPEED);
		}
		if (_inputManager.isKeyDown(SDLK_e)) {
			_camera.setScale(_camera.getScale() - SCALE_SPEED);
		}

		if (_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
			glm::vec2 mouseCoords = _inputManager.getMouseCoords();
			mouseCoords = _camera.convertScreenToWorld(mouseCoords);

			glm::vec2 playerPosition(0.0f);
			glm::vec2 direction = mouseCoords - playerPosition;
			direction = glm::normalize(direction);
			std::cout << mouseCoords.x << " " << mouseCoords.y << std::endl;
			_bullet.emplace_back(playerPosition, direction, 5.00f, 1000);
		}
}
;
void MainGame::drawGame(){

	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_glsl.use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = _glsl.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	//GLint timeLocation = _glsl.getUniformLocation("time");
	//glUniform1f(timeLocation, _time);
	//set the camera
	GLint pLocation = _glsl.getUniformLocation("P");
	glm::mat4 cameraMatrix = _camera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &cameraMatrix[0][0]);




	_spriteBatch.begin();
	glm::vec4 pos(0, 0, 50, 50);
	glm::vec4 uv(0, 0, 1, 1);

	static Bengine::GLTexture texture = Bengine::ResourceManager::getTexture("Texture/png/my.png");
	Bengine::Color color;
	color.r = 225;
	color.g = 225;
	color.b = 0;
	color.a = 225;
	//std::cout << std::endl;
	_spriteBatch.draw(pos, uv, texture.id, 0, color);
	//_spriteBatch.draw(pos + glm::vec4(50, 0, 0, 0), uv, texture.id, 0, color);
	for (int i = 0; i < _bullet.size(); i++)
		_bullet[i].draw(_spriteBatch);
	_spriteBatch.end();
	_spriteBatch.renderBatch();
	glBindTexture(GL_TEXTURE_2D, 0);
	_glsl.unuse();
	_window.swapBuffer();
}
