#include "Ball.h"


Ball::Ball() :_pos(0)
{
}
void Ball::init(float speed, glm::vec2 position, Bengine::InputManager* inputManager){
	_speed = speed;
	_pos = position;
	_inputManager = inputManager;
	_color.r = 233;
	_color.g = 0;
	_color.b = 0;
	_color.a = 225;
}
void Ball::draw(Bengine::SpriteBatch& _spriteBatch){
	int textureID=Bengine::ResourceManager::getTexture("Ball1.png").id;
	const glm::vec4 UV(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect(_pos.x, _pos.y, RADIUS1, RADIUS1);

	_spriteBatch.draw(destRect, UV, textureID, 0.0f, _color);
}
void Ball::collide(const std::vector<std::string>& leveldata){
	std::vector<glm::vec2>tilePosition;
	//first corner
	checkingCollision(leveldata, tilePosition, _pos.x, _pos.y);
	//std::cout << _pos.x << "first corner"<<_pos.y << std::endl;(13,4)
	//second corner
	checkingCollision(leveldata, tilePosition, _pos.x+RADIUS1, _pos.y);
	//std::cout << _pos.x + RADIUS1 << "second corner" << _pos.y << std::endl;//(63,4)
	//third corner
	checkingCollision(leveldata, tilePosition, _pos.x, _pos.y+RADIUS1);//(13,54)
	//forth corner
	checkingCollision(leveldata, tilePosition, _pos.x+RADIUS1, _pos.y+RADIUS1);//(63,54)

	//do collision
	for (int i = 0; i < tilePosition.size();i++)
	AABBcollision(tilePosition[i]);
}
void Ball::update(const std::vector<std::string>& levelData){
	if(_inputManager->isKeyDown(SDLK_a))
		_pos.x += _speed;
	else if (_inputManager->isKeyDown(SDLK_d))
		_pos.x -= _speed;
	else if (_inputManager->isKeyDown(SDLK_w))
		_pos.y += _speed;
	else if  (_inputManager->isKeyDown(SDLK_s))
		_pos.y -= _speed;
	else {
		_pos.x = _pos.x;
		_pos.y = _pos.y;
	}
	collide(levelData);

}
void Ball::checkingCollision(const std::vector<std::string>& levelData,
							std::vector<glm::vec2>& tilePosition
							, float x, float y){

	glm::vec2 cornerPos = glm::vec2(floor(x / (float)RADIUS1), floor(y / (float)RADIUS1));
	if (cornerPos.x > 0 && cornerPos.y > 0){
		if (levelData[cornerPos.y][cornerPos.x] != '.'&&levelData[cornerPos.y][cornerPos.x] != 'g'){
			tilePosition.push_back(cornerPos*(float)RADIUS1 + glm::vec2((float)RADIUS1 / (float)2));
		}

	}
}
void Ball::AABBcollision(glm::vec2 tilePosition){
	const float MIN_DISTANCE = WALL_RADIUS/2+RADIUS1/2;
	glm::vec2 centerPos = _pos + RADIUS1;
	glm::vec2 distance = centerPos - tilePosition;
	float xDepth = MIN_DISTANCE - abs(distance.x);
	float yDepth = MIN_DISTANCE - abs(distance.y);

	if (xDepth > 0 || yDepth > 0){
		if (std::max(xDepth,0.0f) < std::max(yDepth, 0.0f)){
			if (distance.x < 0)
				_pos.x -= xDepth;
			
			else
				_pos.x += xDepth;
			if (distance.y < 0)
				_pos.y-= yDepth;

			else
				_pos.y += yDepth;

		}
	}

}
Ball::~Ball()
{
}
