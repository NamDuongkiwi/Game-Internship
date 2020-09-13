#pragma once
#include "Sprite2D.h"
#include "Boss.h"

class Monster;
class Boss;


enum BulletType {
	EGG,
	FIRE_EGG,
	PAN_EGG,
	SHIT
};
class Bullet : public Sprite2D {

	
public:
	
	Bullet();
	Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, BulletType type);
	//	void Move();]
	void setDame();
	void setType(BulletType type);
	BulletType getBulletType();
	int getDame();
	void Update(GLfloat deltaTime) override;
	bool checkCollision(std::shared_ptr<Sprite2D> monster);
	bool checkCollision(std::shared_ptr<Boss> monster);
	void Draw() override;

private:
	int b_dame;
	BulletType b_type;
	std::shared_ptr<Sprite2D> bonus;
};