#pragma once
#include"Balls.h"
#include<vector>
#include<random>
#include<ctime>
class AI
{

public:
	AI();
	int randomFunction(int min, int max);
	int ballColor();
	enum BALLCOLOR{ RED, YELLOW, PINK, PUPRLE, WHITE };
	int aiBall(glm::vec2 dirn);
	glm::vec2 createDirVector(int randomColorNo);
	void scoreAI(std::vector<Balls*>&_balls, int& _score, int _wide);
	~AI();
	std::mt19937 randomEngine;
	void positionBall(Balls*&_balls, int _wide);
	Bengine::Color returnBall();
	int rightBall;
	int leftBall;
};

