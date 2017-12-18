#include "AI.h"



AI::AI()
{


}
int AI::randomFunction(int min, int max){
	std::uniform_int_distribution<int>randX(min, max);
	int value = randX(randomEngine);
	return value;

}
int AI::aiBall(glm::vec2 dirn){
	if (dirn == glm::vec2(0, 0))
		return(BALLCOLOR::RED);
	else if (dirn == glm::vec2(1, 1))
		return(BALLCOLOR::YELLOW);
	else if (dirn == glm::vec2(2, 2))
		return(BALLCOLOR::PINK);
	else if (dirn == glm::vec2(3, 3))
		return(BALLCOLOR::PUPRLE);
	else
		return(BALLCOLOR::WHITE);


}
glm::vec2 AI::createDirVector(int randomColorNo){
	switch (randomColorNo){
	case 0:
		return(glm::vec2(0, 0));
		break;
	case 1:
		return(glm::vec2(1, 1));
		break;
	case 2:
		return(glm::vec2(2, 2));
		break;
	case 3:
		return(glm::vec2(3, 3));
		break;
	case 4:
		return(glm::vec2(4, 4));
		break;
	}
}
void AI::positionBall(Balls*&_balls,int _wide)
{//finding in which basket the ball is in
	if (_balls->_information && (_balls->passCollisionBW() || _balls->passCollisionBB())){
		_balls->_information = false;
		if (_balls->getPosition().x > _wide / 2){
			//if ball is in right basket
			_balls->_idLeftBasket = false;
		}
		else{
			_balls->_idRightBasket = false;
		}

	}
}

void AI::scoreAI(std::vector<Balls*>&_balls,int &_score,int _wide){
	//std::cout << "ai";
//	Bengine::SoundEffect _soundeffect = _audioEngine.loadSoundEffect("collide.wav");
	for (int i = 0; i < _balls.size(); i++){
		positionBall(_balls[i], _wide);
		for (int j = i + 1; j < _balls.size(); j++){
			
			if (!_balls[i]->_ballAI&&!_balls[j]->_ballAI){
				//ball in right side
				if (_balls[i]->_idRightBasket&&_balls[j]->_idRightBasket){
					if (BALLCOLOR::RED == aiBall(_balls[i]->_dirn) && BALLCOLOR::RED == aiBall(_balls[j]->_dirn)){
						_score += 2;
						//_soundeffect.play();
						_balls[i] = _balls.back();
						_balls.pop_back();
						_balls[j] = _balls.back();
						_balls.pop_back();
					}
					else if (BALLCOLOR::YELLOW == aiBall(_balls[i]->_dirn) && BALLCOLOR::YELLOW == aiBall(_balls[j]->_dirn)){
						_score += 2;
						//_soundeffect.play();
						_balls[i] = _balls.back();
						_balls.pop_back();
						_balls[j] = _balls.back();
						_balls.pop_back();

					}
					else if (BALLCOLOR::PUPRLE == aiBall(_balls[i]->_dirn) && BALLCOLOR::PUPRLE == aiBall(_balls[j]->_dirn)){
						_score += 2;
						//_soundeffect.play();
						_balls[i] = _balls.back();
						_balls.pop_back();
						_balls[j] = _balls.back();
						_balls.pop_back();

					}
					else if (BALLCOLOR::PINK == aiBall(_balls[i]->_dirn) && BALLCOLOR::PINK == aiBall(_balls[j]->_dirn)){
						_score += 2;
					//	_soundeffect.play();
						_balls[i] = _balls.back();
						_balls.pop_back();
						_balls[j] = _balls.back();
						_balls.pop_back();

					}
					else if (BALLCOLOR::WHITE == aiBall(_balls[i]->_dirn) && BALLCOLOR::WHITE == aiBall(_balls[j]->_dirn)){
						_score += 2;
					//	_soundeffect.play();
						_balls[i] = _balls.back();
						_balls.pop_back();
						_balls[j] = _balls.back();
						_balls.pop_back();

					}
					else{
						continue;
					}


				}





				else if (_balls[i]->_idLeftBasket&&_balls[j]->_idLeftBasket){

					if (BALLCOLOR::RED == aiBall(_balls[i]->_dirn) && BALLCOLOR::RED == aiBall(_balls[j]->_dirn)){
						_score += 2;
						//_soundeffect.play();
						_balls[i] = _balls.back();
						_balls.pop_back();
						_balls[j] = _balls.back();
						_balls.pop_back();

					}
					else if (BALLCOLOR::YELLOW == aiBall(_balls[i]->_dirn) && BALLCOLOR::YELLOW == aiBall(_balls[j]->_dirn)){
						_score += 2;
					//	_soundeffect.play();
						_balls[i] = _balls.back();
						_balls.pop_back();
						_balls[j] = _balls.back();
						_balls.pop_back();

					}
					else if (BALLCOLOR::PUPRLE == aiBall(_balls[i]->_dirn) && BALLCOLOR::PUPRLE == aiBall(_balls[j]->_dirn)){
						_score += 2;
						//_soundeffect.play();
						_balls[i] = _balls.back();
						_balls.pop_back();
						_balls[j] = _balls.back();
						_balls.pop_back();

					}
					else if (BALLCOLOR::PINK == aiBall(_balls[i]->_dirn) && BALLCOLOR::PINK == aiBall(_balls[j]->_dirn)){
						_score += 2;
					//	_soundeffect.play();
						_balls[i] = _balls.back();
						_balls.pop_back();
						_balls[j] = _balls.back();
						_balls.pop_back();

					}
					else if (BALLCOLOR::WHITE == aiBall(_balls[i]->_dirn) && BALLCOLOR::WHITE == aiBall(_balls[j]->_dirn)){
						_score += 2;
					//	_soundeffect.play();
						_balls[i] = _balls.back();
						_balls.pop_back();
						_balls[j] = _balls.back();
						_balls.pop_back();

					}
					else{
						continue;
					}
				}



				else{
				}

			}
		}
	}
}

AI::~AI()
{
}
