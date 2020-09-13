#include "Bullet.h"
#include "Monster.h"
#include "ResourceManagers.h"
Bullet::Bullet() {
}

Bullet::Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, BulletType type) : Sprite2D(model, shader, texture)
{
	this->setType(type);
	this->setDame();
	this->SetSize(40, 40);
}
void Bullet::setDame() {
	if (this->getBulletType() == EGG) {
		this->b_dame = 100;
		auto texture = ResourceManagers::GetInstance()->GetTexture("egg");
		this->SetTexture(texture);
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		texture = ResourceManagers::GetInstance()->GetTexture("egg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		bonus = std::make_shared<Sprite2D>(model, shader, texture);
		bonus->SetSize(0, 0);
	}
	else if (this->getBulletType() == FIRE_EGG) {
		this->b_dame = 150;
		auto texture = ResourceManagers::GetInstance()->GetTexture("Fire");
		this->SetTexture(texture);
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		texture = ResourceManagers::GetInstance()->GetTexture("egg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");	
		bonus = std::make_shared<Sprite2D>(model, shader, texture);
		bonus->SetSize(40, 40);
		//bonus->Draw();
	}
	else if (this->getBulletType() == PAN_EGG) {
		this->b_dame = 180;
		auto texture = ResourceManagers::GetInstance()->GetTexture("chaoshoot");
		this->SetTexture(texture);
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		texture = ResourceManagers::GetInstance()->GetTexture("trungran");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		bonus = std::make_shared<Sprite2D>(model, shader, texture);
		
		bonus->SetSize(50, 50);
		//bonus->Draw();
	}
	else if (this->getBulletType() == SHIT) {
		this->b_dame = 180;
		auto texture = ResourceManagers::GetInstance()->GetTexture("shit");
		this->SetTexture(texture);
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		texture = ResourceManagers::GetInstance()->GetTexture("trungran");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		bonus = std::make_shared<Sprite2D>(model, shader, texture);

		bonus->SetSize(0, 0);
		//bonus->Draw();
	}
}
int Bullet::getDame() {
	return this->b_dame;
}
void Bullet::setType(BulletType type) {
	this->b_type = type;
}
BulletType Bullet::getBulletType() {
	return this->b_type;
}
void Bullet::Update(GLfloat deltaTime) {
	if (this->getBulletType() != SHIT) {
		this->Set2DPosition(this->Get2DPosition().x, this->Get2DPosition().y - deltaTime * 500);
		bonus->Set2DPosition(this->Get2DPosition().x, this->Get2DPosition().y - 20);
	}
	else {
		this->Set2DPosition(this->Get2DPosition().x, this->Get2DPosition().y + deltaTime * 100);
	}
}

bool Bullet::checkCollision(std::shared_ptr<Sprite2D> monster) {
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
	if (m_br > b_ar && m_br - monster->getheight() < b_ar) {
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

bool Bullet::checkCollision(std::shared_ptr<Boss> monster) {
	float m_lr = monster->Get2DPosition().x - (monster->getheight() / 2) + 40;
	float m_rr = monster->Get2DPosition().x + (monster->getwidth() / 2) - 50;
	float b_lr = this->Get2DPosition().x - (this->getwidth() / 2) + 10;
	float b_rr = this->Get2DPosition().x + (this->getwidth() / 2) - 10;
	float m_br = monster->Get2DPosition().y + (monster->getheight() / 2) - 50;
	float b_ar = this->Get2DPosition().y - (this->getheight() / 2);
	if (m_br > b_ar && m_br - monster->getheight() < b_ar) {
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

void Bullet::Draw() {
Sprite2D::Draw();
bonus->Draw();
}