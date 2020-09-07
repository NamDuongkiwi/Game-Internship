#pragma once
#include "Sprite2D.h"

enum MonsterStatus
{
	SMALL,
	MEDIUM,
	BIG,
	DIE
};

class Monster : public Sprite2D {


public:
	Monster();
	Monster(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	void SetBlood(int blood);
	int GetBlood();
	void SetMonsterStatus(MonsterStatus m_status);
	MonsterStatus GetMonsterStatus();
	void ChangeStatus();
	void Update(GLfloat deltaTime) override;



private:
	int m_blood;
	MonsterStatus m_status;
};