#pragma once
#include"gameObject.h"
#include"Balls.h"
const int SELECTRA_LENGTH = 50;
const int SELECTRA_HEIGHT = 25;
class Balls;
class Selectra :public gameObject
{
public:
	Selectra();
	void init(float speed, glm::vec2 pos, Bengine::InputManager* inputManager,int width);
	void update(float deltaTime, Balls* gameObject1,int);
	void inclineSelectra(float angle){ _angle = angle; }
	bool collisionSelectra(Balls *gameObject);
	void afterCollision(Balls *gameObject, int wide);
	~Selectra();
private:
	void moveSelectra(float deltaTime);
	int _width;
	std::vector <Balls>* ball;
};

