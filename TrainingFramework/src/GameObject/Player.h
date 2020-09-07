#pragma once
#include "Sprite2D.h"
#include "Bullet.h"
#include "GameStates/GameStateBase.h"
#include "Enemy.h"
enum MoveDirection
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN,
};
class Enemy;
class Player : public Sprite2D {
public:
	
	Player();
	Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);

	void		Init() override;
	void		Draw() override;
	void		Update(GLfloat deltatime) override;
	void		HandleKeyEvents(int key, bool bIsPressed);
	void		Shoot();
	void		checkHitEnemy(std::shared_ptr<Enemy> enemy);
	std::vector<std::shared_ptr<Bullet>>		getListBullet();
protected:
	//animation
	int m_numFrames;
	GLfloat m_frameTime;
	int m_currentFrame;
	GLfloat m_currentTime;

	//moving
	bool m_IsMoving;
	MoveDirection m_Direction;
	//Bullet
	
	//
	//std::shared_ptr<Bullet> m_bullet;
	std::vector<std::shared_ptr<Bullet>> m_list_bullet;
};