#include "Bullet.h"
#include<Bengine\ResourceManager.h>

Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime) {
	_lifeTime = lifeTime;
		_position = pos;
		_direction = dir;
		_speed = speed;
}
void Bullet::draw(Bengine::SpriteBatch& spriteBatch){
	glm::vec4 uv(0, 0, 1, 1);
	static Bengine::GLTexture texture = Bengine::ResourceManager::getTexture("Texture/png/my.png");
	Bengine::Color color;
	color.r = 225;
	color.g = 225;
	color.b = 0;
	color.a = 225;
	//std::cout << std::endl;
	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, 30, 30);
	spriteBatch.draw(posAndSize, uv, texture.id, 0, color);
}
bool Bullet::update(){
	_position += _direction*_speed;
	_lifeTime--;
	if (_lifeTime == 0)
		return true;
	return false;
}
Bullet::~Bullet()
{
}
