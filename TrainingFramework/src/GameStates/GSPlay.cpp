#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "time.h"
#include <string>
#include<iostream>


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

int score = 0;
std::string GSPlay::getScore(int score) {
	return std::to_string(score);
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

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("times");
	m_score = std::make_shared< Text>(shader, font, getScore(score), TEXT_COLOR::RED, 1.0);
//	auto color = ResourceManagers::GetInstance()->("times");
	m_score->Set2DPosition(Vector2(5, 25));


	//player
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("duck");
	m_player = std::make_shared<MainCharacter>(model, shader, texture, 3, 0.1f);


	//boom
	texture = ResourceManagers::GetInstance()->GetTexture("boom");
	m_boom = std::make_shared<Boom>(model, shader, texture, 5, 0.02f);
	m_boom->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_boom->SetSize(0,0);
	//m_boom = NULL;
}

std::shared_ptr<Boom> GSPlay::CreatBoom(float x, float y) {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("boom");
	std::shared_ptr<Boom> boom = std::make_shared<Boom>(model, shader, texture, 5, 0.02f);
	boom->Set2DPosition(x, y);
	return boom;
}

void GSPlay::creatMonster() {
	int random;
	srand(time(NULL));
	random = rand() % 7 + 2;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Enemy");
	std::shared_ptr<Monster> monster = std::make_shared<Monster>(model, shader, texture);
	monster->Set2DPosition(screenWidth / random, -40);
	monster->SetSize(200, 200);
	m_list_monster.push_back(monster);
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
float m_time =0;
void GSPlay::Update(float deltaTime)
{
	
	m_time += deltaTime;
	if (m_time > 1.2) {
		creatMonster();
		m_time = 0;
	}
	m_player->Update(deltaTime);
	m_boom->Update(deltaTime);
	
	for (auto obj : m_list_monster) {
		obj->Update(deltaTime);
		m_player->HitMonster(obj);
	}
	for (int i = 0; i < m_list_monster.size(); i++) {
		if (m_list_monster.at(i)->GetMonsterStatus() == DIE) {
			score += 1;
			m_score->setText(getScore(score));
			//std::cout << getScore() << std::endl;
			//m_boom->Set2DPosition(m_list_monster.at(i)->Get2DPosition().x, m_list_monster.at(i)->Get2DPosition().y);
			m_boom = NULL;
			m_boom = CreatBoom(m_list_monster.at(i)->Get2DPosition().x, m_list_monster.at(i)->Get2DPosition().y);
			m_boom->SetSize(m_list_monster.at(i)->getwidth(), m_list_monster.at(i)->getheight());
			m_list_monster.erase(m_list_monster.begin() + i);
			//m_boom = NULL;
		}
	}
	


	std::cout << getScore(score) << std::endl;
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
//	m_bullet->Draw();
//	anim_die->Draw();
	m_player->Draw();
	for (auto obj : m_list_monster) {
		obj->Draw();
	}
	m_boom->Draw();
	m_score->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}