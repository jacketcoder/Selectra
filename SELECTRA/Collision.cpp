#include "Collision.h"


Collision::Collision() :dir(0)
{
}
void  Collision::init(float speed, glm::vec2 pos, glm::vec2 spos, Bengine::InputManager* inputManager){
	_pos = pos;
	_spos = spos;
	_inputManager = inputManager;
	//_camera = camera;
	_speed = speed;
	std::cout << _pos.x<<"in collision file" << _pos.y;



}
void  Collision::drawPlayer(Bengine::SpriteBatch& _spriteBatch){
	Bengine::Color test;
	test.r = 225;
	test.g = 225;
	test.b = 225;
	test.a = 225;

	
	const glm::vec4 UV(0.0f, 0.0f, 1.0f, 1.0f);
	m_TextureID = Bengine::ResourceManager::getTexture("player.png").id;
	glm::vec4 destRect(_pos.x, _pos.y, BALL_RADIUS, BALL_RADIUS);
	glm::vec4 sdestRect(_spos.x, _spos.y, SBALL_RADIUS, BALL_RADIUS);
	_spriteBatch.draw(destRect, UV, m_TextureID, 0.0f, test,m_Dir);
	//_spriteBatch.draw(sdestRect, UV, Bengine::ResourceManager::getTexture("blackWall.png").id, 0.0f, test,0.5);

	int x, y;
	SDL_GetMouseState(&x, &y);
	std::cout << x << " " << 750 - y << std::endl;
	if (x > 500){
		std::cout << "need to change positon" << std::endl;
		_spriteBatch.draw(sdestRect, UV, Bengine::ResourceManager::getTexture("blackWall.png").id, 0.0f, test, -2.14);
	}
}
void Collision::update(std::vector<std::string> data, Bengine::SpriteBatch& _spriteBatch){
	Bengine::Color test;
	test.r = 225;
	test.g = 225;
	test.b = 225;
	test.a = 225;
	const glm::vec4 UV(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 sdestRect(_spos.x, _spos.y, SBALL_RADIUS, BALL_RADIUS);
		/*case SDL_MOUSEMOTION:
			//_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			//std::cout << evnt.motion.x << " " << _windowWidth - evnt.motion.y << std::endl;
			break;
			/*if (_inputManager.isKeyDown(SDL_BUTTON_LEFT)) {
			//glm::vec2 mouseCoords = _inputManager.getMouseCoords();
			//mouseCoords = _camera.convertScreenToWorld(mouseCoords);
			std::cout << evnt.motion.x << " " << evnt.motion.y<< std::endl;

			}*/
	//if (_inputManager->isKeyDown(SDL_BUTTON_LEFT)){
		
	
		if (_inputManager->isKeyDown(SDLK_RIGHT)){
			_pos.x += _speed;
			//m_Dir.x = _pos.x; 
			m_Dir = glm::vec2(1, 0.6);
			//std::cout << _pos.x << "right" << _pos.y << std::endl;
		}
		if (_inputManager->isKeyDown(SDLK_LEFT)){

			_pos.x -= _speed; 
			m_Dir = glm::vec2(-1, 0);
			//std::cout << _pos.x << "left" << _pos.y << std::endl;
		}
		if (_inputManager->isKeyDown(SDLK_UP)){
			m_Dir = glm::vec2(0, 1);
			_pos.y += _speed;
			//std::cout << _pos.x<<"top" << _pos.y << std::endl;
		}
		 if (_inputManager->isKeyDown(SDLK_DOWN)){
			_pos.y -= _speed; 
			m_Dir = glm::vec2(0,- 1);
			//std::cout << _pos.x<<"down" <<  _pos.y << std::endl;
		 } 
		 dropBall();
		 collide(data);
		 
		  dir += 0.005;
		  if (dir > 3.14){
			 dir = 0;
			//  std::cout << "dir" << dir;
		  }
}
void Collision::collide(std::vector<std::string> leveldata){
	std::vector<glm::vec2> position;
	//for (int y = 0; y < data.size(); y++)
		//std::cout << data[y] << std::endl;
	//std::vector<glm::vec2 >tilePos;
	ckeckCollision(leveldata, _pos.x, _pos.y, position);//(150,100)
	ckeckCollision(leveldata, _pos.x + BALL_RADIUS, _pos.y, position);// (200,100)
	ckeckCollision(leveldata, _pos.x, _pos.y + BALL_RADIUS, position);//(150,150)
	ckeckCollision(leveldata, _pos.x + BALL_RADIUS, _pos.y + BALL_RADIUS, position);//(200,150)
	//std::cout << cornerPos.x << "right" << cornerPos.y << std::endl;
	//std::cout << leveldata[cornerPos.y][cornerPos.x];
	for (int x = 0; x < position.size(); x++)
	{
		//std::cout << "collision loop"; 
		AABBCollision(position[x]);
	}
	
}
void Collision::ckeckCollision(std::vector<std::string> leveldata, float x, float y, std::vector<glm::vec2>& position){
	
	int x1 = x / BALL_RADIUS;
	int y1 = y / BALL_RADIUS;
	
	int column = leveldata.size();
	int row = leveldata[column-1].size();
//	std::cout << std::endl << column << " column vs row " << row;
	if (y1 < (column - 1) && x1 < row&&y1>0&&x1>0){
		glm::ivec2 cornerPos = glm::ivec2(x1, y1);
		if (leveldata[cornerPos.y][cornerPos.x] == '*'&&leveldata[cornerPos.y][cornerPos.x] != '1'||leveldata[cornerPos.y][cornerPos.x] == '2'){
			cornerPos *= BALL_RADIUS;
			cornerPos += BALL_RADIUS/2;
		position.push_back(cornerPos);
		
		}

	}
}

void Collision::AABBCollision(glm::vec2 position){
	glm::vec2 centerPlayer = glm::vec2(_pos.x + BALL_RADIUS / 2, _pos.y + BALL_RADIUS/2);
	//std::cout << std::endl << centerPlayer.x << " center player " << centerPlayer.y;
	const float minDis = 25;
	//std::cout << std::endl << position.x << " center AABB " << position.y;
	glm::vec2 distance = centerPlayer - position;
	
	float xDepth = minDis - abs(distance.x);
	float yDepth = minDis - abs(distance.y);
	
	if (xDepth > 0 && yDepth > 0){
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)){
			if (distance.x < 0){

				_pos.x -= xDepth;
			}
			else{
				_pos.x += xDepth;
			}
		}
		else{
			if (distance.y < 0){
			_pos.y -= yDepth;
		}
			else{
			_pos.y += yDepth;
		}

		}
	}
}
void Collision::dropBall(){
	

	_pos.y -=0.1;

}
Collision::~Collision()
{
}
