#pragma once
#include"glm/glm.hpp"
#include"SpriteBatch.h"
#include"ResourceManager.h"
#include"InputManager.h"
#include"SDL\SDL.h"
#include<iostream>
#include"Level.h"
#include<algorithm>
const float RADIUS1 = 50;
const float WALL_RADIUS = 50;
class Ball
{
public:
	Ball();
	~Ball(); 
	void init(float speed, glm::vec2 position, Bengine::InputManager* _inputManager);
	void update(const std::vector<std::string>& levelData);
	void draw(Bengine::SpriteBatch& _spriteBatch);
	glm::vec2 getPosition(){ return _pos; }
	
	
private:
	void checkingCollision(const std::vector<std::string>& levelData,
							 std::vector<glm::vec2>& tilePosition
							,float x,float y);
	void collide(const std::vector<std::string>& levelData);
	void AABBcollision(glm::vec2 tilePosition);

	float _speed;
	glm::vec2 _pos;
	Bengine::Color _color;
	Bengine::InputManager* _inputManager;

};

