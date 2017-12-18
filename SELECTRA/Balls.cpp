#include "Balls.h"


Balls::Balls() :_idW(true), _idB(true), _idSelectra(true), _idLeftBasket(true),
_idRightBasket(true), _information(true), _ballAI(true)
{

}
void Balls::init(glm::vec2 pos, float speed, std::vector<std::string> data, Bengine::Color color, glm::vec2 dirn){
	_color.r = color.r;
	_color.g = color.g;
	_color.b = color.b;
	_color.a = color.a;
	_data = data;
	_position.x = pos.x;
	_position.y = pos.y;
	_speed = speed;
	_speed1 = speed;
	_dirn = dirn;
	m_TextureID = Bengine::ResourceManager::getTexture("ball.png").id;
}

void Balls::drop(float deltaTime){
	_position.y -= _speed*deltaTime;
}

void Balls::update(float deltaTime, Balls *ball,int a)
{
	
	//checking ball ball collision
		
		drop(deltaTime);
		collisionLevelData(_data);

	
}
bool ballInBasket(bool selectra){
	if (!selectra)
		return true;
	else
		return false;


}

bool Balls::collisionBall(Balls *gameObject){
	//calling function from new ball
	glm::vec2 object1B = _position + glm::vec2(LENGHT / 2, HEIGHT / 2);
	//of ball
	glm::vec2 object2B = gameObject->getPosition() + glm::vec2(gameObject->LENGHT / 2, gameObject->HEIGHT / 2);
	glm::vec2 distance = object1B - object2B;
	const float minDisC = HEIGHT / 2 + gameObject->HEIGHT / 2;
	//for circular collision
	float circledistance = glm::length(distance);
	float circlecoll = minDisC - circledistance;
	
	if (circlecoll>0){
	
		_collisionBall = true;
		gameObject->_collisionBall = true;
		// Get the direction times the collision depth so we can push them away from each other
		glm::vec2 collisionDepthVec = glm::normalize(distance) * circlecoll;

		// Push them in opposite directions
		_position += collisionDepthVec / 2.0f;
		//gameObject->_position -= collisionDepthVec / 2.0f;

		return true;
	}
	return false;
}

Balls::~Balls()
{
}
