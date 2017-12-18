#include "gameObject.h"


gameObject::gameObject() :_collisionWall(false), _collisionSelectra(false), _collisionBall(false)
{
	randomEngine.seed(time(nullptr));
}
void gameObject::setPosition(int x, int y){
	_position.x = x;
	_position.y = y;
}

void gameObject::drawObject(Bengine::SpriteBatch& _spriteBatch){
	glm::vec4 _destRect;
	_objectBatch = &_spriteBatch;
	_destRect.x = _position.x;
	_destRect.y = _position.y;
	_destRect.z = LENGHT;
	_destRect.w = HEIGHT;
	//std::cout << _destRect.x << _destRect.y << std::endl;
	if (_angle==0)
		_objectBatch->draw(_destRect, UV, m_TextureID, 0.0f, _color);
	else
		_objectBatch->draw(_destRect, UV, m_TextureID, 0.0f, _color, _angle);

}
void gameObject::collisionLevelData(std::vector<std::string> data){
	
	collide(data);


}
int gameObject::randomFunction(int min, int max){
	std::uniform_int_distribution<int>randX(min, max);
	int value = randX(randomEngine);
	return value;

}

void gameObject::collide(std::vector<std::string> leveldata){
	std::vector<glm::vec2> position;
	ckeckCollision(leveldata, _position.x, _position.y, position);//(150,100)
	//std::cout << _position.x << " " << _position.y << std::endl;
	ckeckCollision(leveldata, _position.x + LENGHT, _position.y, position);// (200,100)
	ckeckCollision(leveldata, _position.x, _position.y + HEIGHT, position);//(150,150)
	ckeckCollision(leveldata, _position.x + LENGHT, _position.y + HEIGHT, position);//(200,150)
	//std::cout << cornerPos.x << "right" << cornerPos.y << std::endl;
	//std::cout << leveldata[cornerPos.y][cornerPos.x];
	for (int x = 0; x < position.size(); x++)
	{
		//std::cout << "collision loop"; 
		AABBCollision(position[x]);
	}
}
void gameObject::ckeckCollision(std::vector<std::string> leveldata, float x, float y, std::vector<glm::vec2>& position){
	//conversion into point form of level to check the position
	int x1 = x / POINT;
	int y1 = y / POINT;
	int column = leveldata.size();
	int row = leveldata[column - 1].size();
	//changes if level data is changed
	if (y1 <12 && x1 < row&&y1>0 && x1>0){
		glm::ivec2 cornerPos = glm::ivec2(x1, y1);
		if (leveldata[cornerPos.y][cornerPos.x] == '*'&&leveldata[cornerPos.y][cornerPos.x] != '1'){
			//conversion to same position
			cornerPos *= POINT;
			//finding mid points
			cornerPos.x +=float(POINT/ 2);
			cornerPos.y +=float( POINT / 2);
			position.push_back(cornerPos);

		}

	}
}


void gameObject::AABBCollision(glm::vec2 position){
	glm::vec2 centerPlayer = glm::vec2(_position.x + LENGHT / 2, _position.y + HEIGHT / 2);
	//surface collision only
	const float minDis = POINT / 2 + LENGHT / 2;
	glm::vec2 distance = centerPlayer - position;
	float xDepth = minDis - abs(distance.x);
	float yDepth = minDis - abs(distance.y);
		if (xDepth > 0 || yDepth > 0){
			_collisionWall = true;
			if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)){
				if (distance.x < 0){
					_position.x -= xDepth;
				}
				else{
					_position.x += xDepth;
				}
			}
			else{
				if (distance.y < 0)
					_position.y -= yDepth;

				else
					_position.y += yDepth;


			}
		}

}



gameObject::~gameObject()
{
}
