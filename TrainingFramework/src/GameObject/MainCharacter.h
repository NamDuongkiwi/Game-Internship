#pragma once
#include "Sprite2D.h"
#include "Bullet.h"


//class Bullet;
class Monster;

class MainCharacter : public Sprite2D {
public:
	MainCharacter();
	MainCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	void		Init();
	void		Draw() override;
	void		Update(GLfloat deltaTime) override;
	void		HandleKeyEvents(int key, bool bIsPressed);
	void		Shoot();
	void		HitMonster(std::shared_ptr<Monster> monster);
	bool		checkCollision(std::shared_ptr<Sprite2D> obj);
private:
	//animetion
	int m_numFrames;
	GLfloat m_frameTime;
	int m_currentFrame;
	GLfloat m_currentTime;

	//quanlity
	bool can_shoot;
	int keyPressed;

	//
	float  latency;
	std::vector<std::shared_ptr<Bullet>> m_list_bullet;

};
