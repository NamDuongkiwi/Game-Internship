#pragma once
#include "Sprite2D.h"
//#include "GameStates/gamestatebase.h"


class Bullet : public Sprite2D {

	enum BulletType {
		Egg,
		Fire_Egg,
		Pan_egg
	};
public:
	Bullet();
	Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
//	void Move();
	void Update(GLfloat deltaTime) override;
	void Draw() override;
private:
	/*bool m_isMoving;
	BulletType m_BulletType;*/
};