#include "Level.h"
Level::Level() :_pos(0), _width(0), _height(0)
{


	
}

void Level::filePath(const std::string& levelPath){

	//taking input from level file
	std::ifstream load;
	load.open(levelPath);
	if (load.fail()){
		Bengine::fatalError("cannnot load" + levelPath + "in system");
	}
	std::string test;
	load >> test >> _numBalls;
	std::cout << _numBalls << std::endl;
	//reading the level into _data vectors for futher use
	while (std::getline(load, test)){
		_data.push_back(test);
	}

	int column = _data.size();
	int row = _data[column - 1].size();

//	std::cout << column << "vector data" << row << std::endl;

	//print the level
	/*for (int i = 0; i < _data.size(); i++){
		if (i>12)
		std::cout << _data[i] << std::endl;
	}*/

}


void Level::drawingSprite(){
			Bengine::Color test;
			//making color white so that ahy color becomes as it was in image
				glm::vec4 UV(0.0f, 0.0f, 1.0f, 1.0f);
				test.r = 225;
				test.g = 225;
				test.b = 225;
				test.a = 225;
			_spriteBatch.init();
			_spriteBatch.begin();
			//rendering the textures
			for (int y = 0; y < _data.size(); y++){
				for (int x = 0; x < _data[y].size(); x++){
					//graping the required data from level
					char levelData = _data[y][x];
					//getting requirement of texture

					glm::vec4 destRect(x *  WALL_LENGTH, y* WALL_LENGTH, WALL_LENGTH, WALL_LENGTH);
				

					//switching it for various costant datas
					switch (levelData)  {
					case '8':{
						std::cout << y *  WALL_LENGTH << " end data" << x*  WALL_LENGTH << std::endl;
						

					}break;
					case '*':{
						//std::cout << y *  WALL_LENGTH << "asdafs" << x*  WALL_LENGTH << std::endl;
						_spriteBatch.draw(destRect, UV, Bengine::ResourceManager::getTexture("light_Brick.png").id, 0.0f, test);

					}break;
					case '-':{
						std::cout << y *  WALL_LENGTH << "asdafs" << x*  WALL_LENGTH << std::endl;
						_spriteBatch.draw(destRect, UV, Bengine::ResourceManager::getTexture("light_Brick.png").id, 0.0f, test);
					}break;
					case '2':{
						_selectraPos.x = x* WALL_LENGTH;
						_selectraPos.y = y* WALL_LENGTH;

					}break;
					case '+':{
						_initialBallPos.x = x *  WALL_LENGTH;
						_initialBallPos.y = y *  WALL_LENGTH;
						}break;
					case ' 1':{

					}break;
					default:;//std::cout << "undefined data in switch condition";

		}
		}
	}

_spriteBatch.end();


}

void Level::render(){
	_spriteBatch.renderBatch();
}
Level::~Level()
{
}
