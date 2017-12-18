#pragma once
#include<string>
#include<iostream>
#include<vector>
#include"SpriteBatch.h"
#include"glm\glm.hpp"
#include"ResourceManager.h"
#include"Ball.h"
#include<fstream>
#include"Error.h"
const int  WALL_LENGTH = 20;
class Level
{
public:
	//loads the level
	Level();
	~Level();
	void filePath(const std::string& levelPath);
	
	void drawingSprite();
	void render();
	
	 const std::vector<std::string>&data()const{ return _data; }
	glm::vec2 returnPos()const{  return _pos; }
	glm::vec2 sreturnPos()const{ return _spos; }
	glm::vec2 selectraReturnPos()const{ return _selectraPos; }
	std::vector<glm::vec2> ballsReturnPos()const{ return  _ballsPosL; }
	glm::vec2 ballPosition()const{ return _initialBallPos; }
	int numBalls()const{ return _numBalls; }
	int widthLevel()const{ return _data[31].size(); }
	int heightLevel()const{ return _data.size(); }
private:
	//functions
	

	//datas
	int _ball;
	std::vector<std::string>_data;
	Bengine::SpriteBatch _spriteBatch;
	int _width, _height;
	//position of baskets


	//starting position of balls
	//ivec2 means vector of 2 dim integers
	//created vector as there as no of balls

	//test
	int _numBalls;
	std::vector<glm::vec2> _ballsPosL;
	glm::vec2 _initialBallPos;
	glm::vec2 _pos;
	glm::vec2 _spos;
	glm::vec2 _selectraPos;

};

