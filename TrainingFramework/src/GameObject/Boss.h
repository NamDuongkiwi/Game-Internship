
#pragma once
#include "Sprite2D.h"
#include "Bullet.h"
class Bullet;
class Boss:public Sprite2D {
public:
	Boss();
	Boss(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	void		Draw() override;
	void		Update(GLfloat deltaTime) override;
	void		Shoot(float deltaTime);
	void		SetBlood(int blood);
	int			GetBlood();

private:
	//animation
	int m_numFrames;
	GLfloat m_frameTime;
	int m_currentFrame;
	GLfloat m_currentTime;
	void Die();

	std::vector<std::shared_ptr<Bullet>> m_list_bullet;
	float m_shoottime = 0;
	int m_blood;
};