#include "Selectra.h"


Selectra::Selectra()
{
}
void Selectra::init(float speed, glm::vec2 pos, Bengine::InputManager* inputManager,int width){
	_speed = speed;
	_position = pos;
	_position.y = 600;
	_color.r = 225;
	_color.g = 225;
	_color.b = 225;
	_color.a = 225;
	LENGHT = LENGHT+20;
	_width = width;
	m_TextureID = Bengine::ResourceManager::getTexture("_selectra.png").id;
	_angle = 0;
	_inputManager = inputManager;
}
void Selectra::moveSelectra(float deltaTime){
	int x, y;
	SDL_GetMouseState(&x, &y);
	_position.x = x;

	if ( _position.x < 0)
		_position.x = 0;
	if (_position.x > _width-30)
		_position.x = _width - 30;
	
}



void Selectra::update(float deltaTime, Balls* gameObject,int wide) {
	moveSelectra(deltaTime);
	if (collisionSelectra(gameObject))
	afterCollision(gameObject, wide);
}
bool Selectra::collisionSelectra(Balls *gameObject){
	glm::vec2 object1S = _position + glm::vec2(LENGHT / 2, HEIGHT / 2);
	//of ball
	glm::vec2 object2B = gameObject->getPosition() + glm::vec2(gameObject->LENGHT / 2, gameObject->HEIGHT / 2);
	glm::vec2 distance = object1S - object2B;
	glm::vec2 minDisR = glm::vec2(LENGHT / 2 + gameObject->LENGHT / 2, HEIGHT / 2 + gameObject->HEIGHT / 2);
	//for rectangular collision
	float xDepth = minDisR.x - abs(distance.x);
	float yDepth = minDisR.y - abs(distance.y);

	gameObject->_collisionSelectra = false;

	if (xDepth > 0 && yDepth > 0){
		gameObject->_collisionSelectra = true;
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)){
			if (distance.x < 0){

				gameObject->_position.x += xDepth;
			}
			else{
				//_position.x += xDepth;
				gameObject->_position.x -= xDepth;
			}
		}
		else{
			if (distance.y < 0){
				//_position.y -= yDepth;
				gameObject->_position.y += yDepth;
			}
			else{
				//_position.y += yDepth;
				gameObject->_position.y -= yDepth;
			}

			
		}
		return true;
	}
	return false;
}

void Selectra::afterCollision(Balls* gameObject,int wide){
	//if (gameObject->passCollisionBS())
	
		glm::vec2 _randomPosition;
		gameObject->_idSelectra = false;
		if (gameObject->getPosition().x > wide / 2){
			//shifted to left basket
			_randomPosition = glm::vec2(randomFunction(100, 240), 15 * 20);
			gameObject->setPosition(_randomPosition.x, _randomPosition.y);
			gameObject->_idRightBasket = false;
		}
		else{
			//shifted to right basket
			_randomPosition = glm::vec2(randomFunction(400, 560), 11 * 20);
			gameObject->setPosition(_randomPosition.x, _randomPosition.y);
			gameObject->_idLeftBasket = false;
		}
	}
Selectra::~Selectra()
{

}
