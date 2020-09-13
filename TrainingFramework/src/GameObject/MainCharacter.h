#pragma once
#include "Sprite2D.h"
#include "Bullet.h"
#include <soloud.h>
#include <soloud_wav.h>



//class Bullet;
class Monster;
enum Status {
	NORMAL,
	FIRE,
	PAN
};

class MainCharacter : public Sprite2D {
public:
	MainCharacter();
	MainCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	void setStatus(Status status);
	Status getStatus();
	void setShoot(bool cs);
	bool getShoot();

	void		Init();
	void		Draw() override;
	void		Update(float deltaTime) override;
	void		HandleKeyEvents(int key, bool bIsPressed);
	void		Shoot(float deltaTime);
	void		HitMonster(std::shared_ptr<Monster> monster);
	void		HitBoss(std::shared_ptr<Boss> monster);
	bool		checkCollision(std::shared_ptr<Monster> obj);
	void		changeStatus(float deltaTime);

private:
	//animetion
	int m_numFrames;
	GLfloat m_frameTime;
	int m_currentFrame;
	GLfloat m_currentTime;

	std::shared_ptr<Sprite2D> cantshoot;

	//quanlity
	bool can_shoot;
	Status m_status;




	int keyPressed;

	//
	float latency;
	std::vector<std::shared_ptr<Bullet>> m_list_bullet;
	std::shared_ptr<Sprite2D> bonus;



	
};
