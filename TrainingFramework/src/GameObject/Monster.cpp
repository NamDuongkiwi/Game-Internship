
#include "Monster.h"
#include "ResourceManagers.h"



Monster::Monster() {

}
Monster::Monster(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture) :Sprite2D(model, shader, texture) {
	this->SetMonsterStatus(SMALL);
	this->SetBlood(900);
}

int Monster::GetBlood() {
	return this->m_blood;
}
void Monster::SetBlood(int blood) {
	this->m_blood = blood;
}
void Monster::SetMonsterStatus(MonsterStatus status) {
	this->m_status = status;
}

MonsterStatus Monster::GetMonsterStatus() {
	return this->m_status;
}



void Monster::ChangeStatus() {
	if (this->GetBlood() >= 700) {
		this->SetMonsterStatus(SMALL);
		auto texture = ResourceManagers::GetInstance()->GetTexture("Enemy");
		this->SetTexture(texture);
	}
	else if (this->GetBlood() < 700 && this->GetBlood() >= 400) {
		this->SetMonsterStatus(MEDIUM);
		auto texture = ResourceManagers::GetInstance()->GetTexture("Enemy2");
		this->SetTexture(texture);
	}
	else if (this->GetBlood() < 400 && this->GetBlood() >= 0) {
		this->SetMonsterStatus(BIG);
		auto texture = ResourceManagers::GetInstance()->GetTexture("Enemy3");
		this->SetTexture(texture);
	}
	else {
		this->SetMonsterStatus(DIE);
	}
}

void Monster::Update(GLfloat deltaTime) {
	Set2DPosition(this->Get2DPosition().x, this->Get2DPosition().y + 100 * deltaTime);
	this->ChangeStatus();
}