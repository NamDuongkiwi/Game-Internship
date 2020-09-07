#include "Bullet.h"
#include "Monster.h"
Bullet::Bullet() {
}

Bullet::Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture) : Sprite2D(model, shader, texture)
{
	this->b_type = Egg;
	this->dame = 100;
	this->SetSize(40, 40);
}

int Bullet::getDame() {
	return this->dame;
}

void Bullet::Update(GLfloat deltaTime) {
	this->Set2DPosition(this->Get2DPosition().x, this->Get2DPosition().y - deltaTime * 700);
}

bool Bullet::checkCollision(std::shared_ptr<Monster> monster) {
	//----------------------------
	//		lr/ rr/ ar/ dr: left range/ right range/ above range/ below range
	//		m: monster
	//		b: bullet
	//-----------------------------
	//
	float m_lr = monster->Get2DPosition().x - (monster->getheight() / 2) + 40;
	float m_rr = monster->Get2DPosition().x + (monster->getwidth() / 2) - 50;
	float b_lr = this->Get2DPosition().x - (this->getwidth() / 2) + 10;
	float b_rr = this->Get2DPosition().x + (this->getwidth() / 2) - 10;
	float m_br = monster->Get2DPosition().y + (monster->getheight() / 2) - 50;
	float b_ar = this->Get2DPosition().y - (this->getheight() / 2);
	if (m_br > b_ar) {
		if (m_lr < b_rr && m_lr > b_lr) {
			return true;
		}
		else if (m_rr > b_lr && m_rr < b_rr) {
			return true;
		}
		else if (m_lr < b_lr && m_rr > b_rr) {
			return true;
		}
		else return false;
	}
	else return false;


}
