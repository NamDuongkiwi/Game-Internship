#pragma once
#include "Sprite2D.h"
#include "Sprite2D.h"
#include "Bullet.h"
#include "GameStates/GameStateBase.h"
#include "Enemy.h"
#include "Player.h"

enum EnemyStatus {
	small,
	medium,
	big,
	boom,
	die
};
class Enemy : public Sprite2D {
public:
	Enemy();
	Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	void ChangeStatus();
	void Update(GLfloat deltaTime) override;
	void Draw() override;
	bool checkHit(std::shared_ptr<Bullet> bullet);
	void SetBlood(GLint blood);
	GLint GetBlood();
	EnemyStatus getStatus();
private:
	GLint m_blood;
	EnemyStatus m_status;

	float m_time;

	//anim
	int m_numFrames;
	GLfloat m_frameTime;
	int m_currentFrame;
	GLfloat m_currentTime;

};