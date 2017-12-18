#pragma once
#include"gameObject.h"

class Balls:public gameObject
{
public:
	friend Selectra;
	Balls();
	void init(glm::vec2 pos, float speed, std::vector<std::string> data, Bengine::Color color, glm::vec2 dirn);
	void drop(float deltaTime);
	void update(float deltaTime, Balls *gameObject,int);
	bool ballInBasket(bool,bool);
	bool collisionBall(Balls *gameObject);
	~Balls();
	bool _idW;
	bool _idB;
	bool _idSelectra;
	bool _idLeftBasket;
	bool _idRightBasket;
	bool _ballAI;
	bool _information;
	glm::vec2 _dirn;
private:
	 std::vector<std::string> _data;
	 float _speed1;

};

