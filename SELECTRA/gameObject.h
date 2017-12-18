#pragma once
#include<random>
#include<algorithm>
#include<ctime>
#include<vector>
#include<string>
#include<glm\glm.hpp>
#include<iostream>
#include"InputManager.h"
#include"SpriteBatch.h"
#include"SDL\SDL.h"
#include"GL\glew.h"
#include"ResourceManager.h"
#include"AudioEngine.h"
#include<algorithm>
class Selectra;
class Balls;

class gameObject
{
public:
	gameObject();
	//basic stuff
	void drawObject(Bengine::SpriteBatch& _spriteBatch);
	virtual ~gameObject();
	void collisionLevelData(std::vector<std::string> data);
	virtual void update(float deltaTime, Balls *gameObject,int) = 0;
	bool passCollisionBW(){ return _collisionWall; }
	bool passCollisionBS(){ return _collisionSelectra; }
	bool passCollisionBB(){ return _collisionBall; }
	void setPosition(int x, int y);
	void setCondition(bool value){_collisionWall = value;}
	glm::vec2 getPosition(){ return _position;  }
	int checkSpeed(){ return _speed; }
	void AABBCollision(glm::vec2 position);
	int randomFunction(int min, int max);
protected:
	bool _collisionWall;
	bool _collisionSelectra;
	bool _collisionBall;;
	//std::vector<std::string> _levelData;
	Bengine::SpriteBatch* _objectBatch;
	float _speed;
	glm::vec2 _position;
	const int POINT = 20;
	int LENGHT = 20;
	const int HEIGHT = 20;
	Bengine::Color _color;
	float _angle;
	const glm::vec4 UV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	GLuint m_TextureID;
	Bengine::InputManager* _inputManager;
	void dropBall();
	void ckeckCollision(std::vector<std::string> data, float x, float y, std::vector<glm::vec2>& position);
	void collide(std::vector<std::string> data);
	std::mt19937 randomEngine;

};