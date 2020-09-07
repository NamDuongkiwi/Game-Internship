#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"


extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay ()
{
	m_time = 0;
	m_current = 0;
}


GSPlay::~GSPlay()
{

}


void GSPlay ::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("play_background");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);


	//player
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
//	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	texture = ResourceManagers::GetInstance()->GetTexture("boom");
	std::shared_ptr<Player> player = std::make_shared<Player>(model, shader, texture, 5, 0.5f);
	m_player=(player);

	//
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Enemy");
	std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(model, shader, texture,1,1);
	enemy->Set2DPosition(200, 0);
	enemy->SetSize(150, 150);
	m_enemy.push_back(enemy);


	//anim die
	/*model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("boom");
	anim_die = std::make_shared<Enemy>(model, shader, texture, 5, 0.5f);
	anim_die->SetSize(200, 200);
	anim_die->Set2DPosition(200, 200);*/
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}

void GSPlay ::HandleKeyEvents(int key, bool bIsPressed)
{
	m_player->HandleKeyEvents(key, bIsPressed);
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPlay::Update(float deltaTime)
{
	m_time += deltaTime;
	if (m_time > 1.3)
	{	
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Enemy");
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(model, shader, texture, 1, 1);
		enemy->Set2DPosition(200, 0);
		enemy->SetSize(150, 150);
		m_enemy.push_back(enemy);
		m_time = 0;
	}
	
	for (auto obj : m_enemy) {
		obj->Update(deltaTime);
	}
	for (int i = 0; i < m_enemy.size(); i++) {
		m_player->checkHitEnemy(m_enemy.at(i));
		if (m_enemy.at(i)->getStatus() == die) {
			m_enemy.erase(m_enemy.begin() + i);
		}
	}

	m_player->Update(deltaTime);
//	anim_die->Update(deltaTime);
	//m_enemy->ChangeStatus();
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
//	anim_die->Draw();
	m_player->Draw();
	for (auto obj : m_enemy) {
		obj->Draw();
	}
}

void GSPlay::SetNewPostionForBullet()
{
}