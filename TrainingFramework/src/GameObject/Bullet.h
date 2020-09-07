#pragma once
#include "Sprite2D.h"


class Monster;

class Bullet : public Sprite2D {

	enum BulletType {
		Egg,
		Fire_Egg,
		Pan
	};
public:
	Bullet();
	Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	//	void Move();]
	int getDame();
	void Update(GLfloat deltaTime) override;
	bool checkCollision(std::shared_ptr<Monster> monster);



private:
	int dame;
	BulletType b_type;
};