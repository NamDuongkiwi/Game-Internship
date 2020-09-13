#include "Item.h"
#include "MainCharacter.h"
#include "ResourceManagers.h"



Item::Item() {

}

//BROOM,
//CHILI,
//TRUNGRAN
Item::Item(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, ItemType type):Sprite2D(model, shader, texture) {
	
	this->m_type = type;
	if (this->getItemType() == BROOM) {
		auto texture = ResourceManagers::GetInstance()->GetTexture("broom");
		this->SetTexture(texture);
		this->m_width = 5;
	}
	else if (this->getItemType() == NEPTUNE) {
		auto texture = ResourceManagers::GetInstance()->GetTexture("neptune");
		this->SetTexture(texture);
		this->m_width = 30;
	}
	else if (this->getItemType() == CHILI) {
		auto texture = ResourceManagers::GetInstance()->GetTexture("chili");
		this->SetTexture(texture);
		this->m_width = 30;
	}
	else if (this->getItemType() == TRUNGRAN) {
		auto texture = ResourceManagers::GetInstance()->GetTexture("trungran2");
		this->SetTexture(texture);
		this->m_width = 30;
	}
}
ItemType Item::getItemType() {
	return this->m_type;
}
void Item::Update(float deltaTime) {
	if (this->getItemType() == BROOM) {
		Set2DPosition(this->Get2DPosition().x, this->Get2DPosition().y + 700 * deltaTime);
	}
	else 
		Set2DPosition(this->Get2DPosition().x, this->Get2DPosition().y + 100 * deltaTime);
}
bool Item::checkCollision1(std::shared_ptr<MainCharacter> player) {
	//------------------------
	//u = up
	//d = down
	//lr = left range , rr = right range
	//ar = above range, br = below range
	//------------------------
	float u_lr = this->Get2DPosition().x - this->m_width / 2;
	float u_rr = this->Get2DPosition().x + this->m_width / 2;
	float u_br = this->Get2DPosition().y + this->getheight() / 2 -20;
	float u_ar = this->Get2DPosition().y - this->getheight() / 2;

	float d_lr = player->Get2DPosition().x - player->getwidth() / 2 + 35;
	float d_rr = player->Get2DPosition().x + player->getwidth() / 2  - 35;
	float d_br = player->Get2DPosition().y + player->getheight() / 2;
	float d_ar = player->Get2DPosition().y - player->getheight() / 2;

	if (u_br > d_ar && u_ar  < d_ar) {
		if (u_lr < d_rr && u_lr > d_lr) {
			return true;
		}
		else if (u_rr > d_lr && u_rr < d_rr) {
			return true;
		}
		else if (u_lr > d_lr && u_rr < d_rr) {
			return true;
		}
		else return false;
	}
	else return false;
//	if(u_br > d)
	//       |  u  |  ______  
	//       |_____|
	//
	//     |---------------|
	//     |      d        |
		//
	//
	//
	//


}
void Item::Draw() {
Sprite2D::Draw();
}