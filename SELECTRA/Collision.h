#pragma once
#include<vector>
#include<string>
#include<glm\glm.hpp>
#include<iostream>
#include"InputManager.h"
#include"SpriteBatch.h"
#include"SDL\SDL.h"
#include"GL\glew.h"
#include"ResourceManager.h"
#include<algorithm>
const int BALL_RADIUS = 25;
const int SBALL_RADIUS = 100;
class Collision
{
public:
	Collision();
	~Collision();
	void init(float speed, glm::vec2,glm::vec2 spos, Bengine::InputManager* inputManager);
	std::vector<std::string> dataLevel(std::vector<std::string>data){ return data; }
	glm::vec2 positionPlayer(){ return _pos; }
	void update(std::vector<std::string>, Bengine::SpriteBatch& _spriteBatch);
	void drawPlayer(Bengine::SpriteBatch& _spriteBatch);
private:
	void dropBall();
	void ckeckCollision(std::vector<std::string> data, float x, float y, std::vector<glm::vec2>& position);
	void collide(std::vector<std::string> data);
	void AABBCollision(glm::vec2 position);
	glm::vec2 _pos;
	glm::vec2 _spos;
	float _speed;
	glm::vec2 m_Dir = glm::vec2(1, 0);
	float dir;
	GLuint m_TextureID;
	Bengine::InputManager* _inputManager;
	
	
};

