#include "MainGame.h"

MainGame::MainGame() :
_windowWidth(680) //x axis
, _windowHeight(960)//y axis
, _gameState(PLAY)
, _selectra(nullptr)
, _score(0)
, _randomColorNo(0)
, _speedLimit(4, 5)
, _state(false)
, _life(3)
	
{
	randomEngine.seed(time(nullptr));
	//red color
	_randColor.setColor(225, 0, 0, 225);//0    0,0   red
	_color.push_back(_randColor);
	//yellow
	_randColor.setColor(225, 225, 0, 225);//1   1,1  yellow
	_color.push_back(_randColor);
	//blue
	_randColor.setColor(13, 3, 194, 225);//2    2,2    pink
	_color.push_back(_randColor);
	//purple
	_randColor.setColor(189, 9, 189, 225);//3   3,3   purple 
	_color.push_back(_randColor); 
	//white
	_randColor.setColor(0,0,0,225);//4    4,4   white
	_color.push_back(_randColor);

}

void MainGame::initializeGame(){

	//initialize the SDL
	Bengine::init();
	//only adding after sdl init
	_audioEngine.init();
	//creates SDL window
	_window.create("SELECTRA", _windowHeight, _windowWidth, Bengine::FULLSCREEN);

	initShaders();
	initLevel();
	_camera.init(_windowHeight, _windowWidth);
	
}
void MainGame::initLevel(){
	//loading UI
	_gui.init(_GUI, _windowWidth, _windowHeight, &_inputManager);
	_gui.drawObject();
	//loading background
	_backGround.init(_backGroundSprite, _windowWidth, _windowHeight, &_inputManager);
	_backGround._uiTexture = Bengine::ResourceManager::getTexture("background.png").id;
	_backGround.drawObject();
	//loading the level
	_levels.push_back(new Level);
	_level1 = 0;
	_levels[_level1]->filePath("testingLevel.txt");

	//drawing the scenes of level
	_levels[_level1]->drawingSprite();

	//creating selectra
	_selectra = new Selectra();
	_selectra->init( 5,_levels[_level1]->selectraReturnPos(), &_inputManager,_windowWidth);
	_selectraSpriteBatch.init();
	//creating initial ball
	//make it generalize
	//creatingBall();
	_ballSpriteBatch.init();
	//for score
	_scoreSpriteBatch.init();
	_spriteFont = new Bengine::SpriteFont("font1.ttf",32);

}
int MainGame::randomFunction(int min, int max){
	std::uniform_int_distribution<int>randX(min,  max);
	int value = randX(randomEngine);
	return value ;

}
void MainGame::creatingBall(){
	int pos; 
	pos = randomFunction(20, _windowWidth);
	_randomPosition = glm::vec2(pos, _windowHeight-20);
	_speed = randomFunction(_speedLimit.x, _speedLimit.y);
	_randomColorNo = randomFunction(0,_color.size()-1);
	_dirn = _AI.createDirVector(_randomColorNo);
		_balls.push_back(new Balls);
		//cout << _randomPosition.x << "x and y" << _randomPosition.y << endl;
		_balls.back()->init(_randomPosition, _speed, _levels[_level1]->data(), _color[_randomColorNo], _dirn);
}

void MainGame::initShaders(){
	//initializes shader
	//complies and links shader files
	_shader.compileLinkShaders("colorShadingV.txt", "colorShadingF.txt");
	_shader.addAttribute("vertexPosition");
	_shader.addAttribute("vertexColor");
	_shader.addAttribute("vertexUV");

}
void MainGame::updateObjects(float deltaTime){
	for(int i = 0; i < _balls.size(); i++){
	_gameObject[0] = _selectra;
	//updating selectra and collision with ball via virtual function
	_gameObject[1] = _balls[i];
		_gameObject[0]->update(deltaTime, _balls[i],_windowWidth);
		//updating ball and collision with ball via virtual function
		_gameObject[1]->update(deltaTime, _balls[i], _windowWidth);

		//checking ball ball collision
		for (int j = i + 1; j < _balls.size(); j++)
		{
			_balls[j]->collisionBall(_balls[i]);


		}

		//generating balls if it has touched the selectra and  fall in basket touching wall or ball
		if ((_gameObject[1]->passCollisionBW() || _gameObject[1]->passCollisionBB()) && _balls[i]->_idW&&!_balls[i]->_idSelectra&&_balls[i]->_idB){
			//cout << "ball in basket";
			_balls[i]->_ballAI = false;
			_balls[i]->_idW = false;
			_balls[i]->_idB = false;
			creatingBall();

		}
		//in case ball doesnot touches selectra and fall in the basket touching wall or ball
		if ((_gameObject[1]->passCollisionBW() || _gameObject[1]->passCollisionBB()) && _balls[i]->_idSelectra ){
			_balls[i]->_ballAI = false;
			_balls[i]->_idB = false;
			_balls[i]->_idSelectra = false;
			if (_balls[i]->getPosition().x > _windowWidth / 2){
				//in right basket
				_balls[i]->_idLeftBasket = false;
				//cout << "in right basket";
			}
			else{
				//in left basket
				_balls[i]->_idRightBasket = false;
			//	cout << "in left basket";
			}
			creatingBall();
		}

		//delete the ball first and decrease the score
		if (_balls[i]->getPosition().y < 0&&_balls[i]->_idSelectra){
			_balls[i] = _balls.back();
			_balls.pop_back();
			//cout << "ball deleted"<<endl;
			--_life;
			
			creatingBall();
		}

	}
	int preScore = _score;
	Bengine::SoundEffect _soundeffect = _audioEngine.loadSoundEffect("collide.wav");
	_AI.scoreAI(_balls,  _score,_windowWidth);
	if (preScore!=_score)
		_soundeffect.play();
}

void MainGame::gameLoop(){
	const float DESIRED_FPS = 60;
	const int MAX_PHYSICS_STEPS = 6;
	const float MS_PER_SECOND = 1000;
	const float DESIRED_FRAME_TIME = MS_PER_SECOND / DESIRED_FPS;
	const float MAX_DELTA_TIME = 1.0f; // Maximum size of deltaTime
	// Used to cap the FPS
	Bengine::FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(60000.0f);
	// Start our previousTicks variable
	float previousTicks = SDL_GetTicks();
	bool check = true;
	while (_gameState == PLAY&&_life>0){
		if (_state&&check){
			creatingBall();
			check = false;
		}
		fpsLimiter.begin();
		float newTicks = SDL_GetTicks();
		float frameTime = newTicks - previousTicks;
		previousTicks = newTicks;
		// Get the total delta time
		float totalDeltaTime = frameTime / DESIRED_FRAME_TIME;
		_inputManager.update();
		processInput();
		int i = 0;
		while (totalDeltaTime > 0 && i < MAX_PHYSICS_STEPS){
			float deltaTime = std::min(totalDeltaTime, MAX_DELTA_TIME);
			updateObjects(deltaTime);
			totalDeltaTime -= deltaTime;
			++i;
		}
		_camera.update();
		drawGame();
		m_fps = fpsLimiter.end();
		//std::cout << m_fps << std::endl;
		
	}
	

	
}
void MainGame::processInput(){
	SDL_Event evnt;

	const float SCALE_SPEED = .01f;
	while (SDL_PollEvent(&evnt)){//askes the event need to be processed,user moving mouse,typing
		//loking its type
		switch (evnt.type){
		case SDL_QUIT:
			_gameState = EXIT;
			break;
			case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		case SDL_MOUSEMOTION:{
			x = evnt.motion.x;
			y = evnt.motion.y;
			}
			break;
		}
	}
	

	
}

void MainGame::drawGame(){
	//checking primary condition to enter in loop

		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		_shader.use();
		
		//making texture active
		glActiveTexture(GL_TEXTURE0);

		//set the camera
		GLint pLocation = _shader.getUniformLocation("P");
		glm::mat4 cameraMatrix = _camera.getCameraMatrix();
		glUniformMatrix4fv(pLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

		//makes sure shader uses texture
		GLint textureUniform = _shader.getUniformLocation("mySampler");
		glUniform1i(textureUniform, 0);
		//draws UI
		
				if (!_state){
			_gui.renderUI();
			if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
			{
				SDL_GetMouseState(&x, &y);
				gui = _gui.getCursorPos(x,y);
				if (gui == 1){
					_state = true;
				}
				else if (gui == 2){
					//cout << "exit";
					_gameState = GAMESTATE::EXIT;
				}
				else {
				//	cout << "again";
					_state = false;
				}
			}

		}
				if(_state){
					//disapprearing the mouse cursor
					SDL_ShowCursor(SDL_DISABLE);
					glClearColor(225, 225, 225, 225);
					//draws background
					_backGround.renderUI();
					//draws level
					_levels[_level1]->render();
					//drawing selectra and ball
					_selectraSpriteBatch.begin();
					_ballSpriteBatch.begin();
					//using inherited feature for drawing
					_selectra->drawObject(_selectraSpriteBatch);
					for (int i = 0; i < _balls.size(); i++){
						_balls[i]->drawObject(_ballSpriteBatch);
						_ballSpriteBatch.end();
						_ballSpriteBatch.renderBatch();
					}
					_selectraSpriteBatch.end();
					_selectraSpriteBatch.renderBatch();
					drawScore();

					//game over
					if (_life <= 0){
						_backGround._uiTexture = Bengine::ResourceManager::getTexture("end.png").id;
						//_backGround.init(_backGroundSprite, _windowWidth, _windowHeight, &_inputManager);
						_backGround.drawObject();
						_backGround.renderUI();
						SDL_Delay(2000);
					}
				}
		glBindTexture(GL_TEXTURE_2D, 0);
		_shader.unuse();
		_window.swapBuffer();
}
void MainGame::drawScore(){
	Bengine::Color scoreColor;
	scoreColor.setColor(225, 0, 0, 225);
	char score[100];
	char life[100];
	_scoreSpriteBatch.begin();
	sprintf_s(score, "TOTAL SCORE %d", _score);
	sprintf_s(life, "      LIFE   %d ", _life);
	_spriteFont->draw(_scoreSpriteBatch, score, glm::vec2(0, _windowHeight-150), glm::vec2(1), 0.0f, scoreColor);
	Bengine::Color scoreColorL;
	scoreColorL.setColor(225, 225, 0, 225);
	_scoreSpriteBatch.end();
	_scoreSpriteBatch.renderBatch();
	_spriteFont->draw(_scoreSpriteBatch, life, glm::vec2(50, _windowHeight - 100), glm::vec2(1), 0.0f, scoreColorL);
	_scoreSpriteBatch.end();
	_scoreSpriteBatch.renderBatch();

}
void MainGame::gameStart(){

	initializeGame();
	
	Bengine::Music music = _audioEngine.loadMusic("background.mp3");
	//looping for ever
	music.play(-1);
	gameLoop();
}
MainGame::~MainGame()
{
	for (int i = 0; i < _levels.size(); i++)
		delete _levels[i];
	delete _selectra;
	delete _spriteFont;
	for (int i = 0; i < _balls.size(); i++)
		delete _balls[i];

}
