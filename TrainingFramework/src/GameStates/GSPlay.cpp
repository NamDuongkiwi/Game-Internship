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
<<<<<<< HEAD
void GSPlay::Init()
=======
void GSPlay ::Init()
>>>>>>> 8eb5612be7992648d90237e85683e8ac5385e1d7
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
<<<<<<< HEAD
	//	auto color = ResourceManagers::GetInstance()->("times");
=======
//	auto color = ResourceManagers::GetInstance()->("times");
>>>>>>> 8eb5612be7992648d90237e85683e8ac5385e1d7
	m_score->Set2DPosition(Vector2(5, 25));


	//player
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("duck");
	m_player = std::make_shared<MainCharacter>(model, shader, texture, 3, 0.1f);


	//boom
	texture = ResourceManagers::GetInstance()->GetTexture("boom");
	m_boom = std::make_shared<Boom>(model, shader, texture, 5, 0.02f);
	m_boom->Set2DPosition(screenWidth / 2, screenHeight / 2);
<<<<<<< HEAD
	m_boom->SetSize(0, 0);
=======
	m_boom->SetSize(0,0);
>>>>>>> 8eb5612be7992648d90237e85683e8ac5385e1d7
	//m_boom = NULL;
}

std::shared_ptr<Boom> GSPlay::CreatBoom(float x, float y) {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("boom");
	std::shared_ptr<Boom> boom = std::make_shared<Boom>(model, shader, texture, 5, 0.02f);
	boom->Set2DPosition(x, y);
	return boom;
<<<<<<< HEAD
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

=======
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

>>>>>>> 8eb5612be7992648d90237e85683e8ac5385e1d7


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
<<<<<<< HEAD
float m_time = 0;
void GSPlay::Update(float deltaTime)
{

=======
float m_time =0;
void GSPlay::Update(float deltaTime)
{
	
>>>>>>> 8eb5612be7992648d90237e85683e8ac5385e1d7
	m_time += deltaTime;
	if (m_time > 1.2) {
		creatMonster();
		m_time = 0;
	}
	m_player->Update(deltaTime);
	m_boom->Update(deltaTime);
<<<<<<< HEAD

=======
	
>>>>>>> 8eb5612be7992648d90237e85683e8ac5385e1d7
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
<<<<<<< HEAD

=======
	
>>>>>>> 8eb5612be7992648d90237e85683e8ac5385e1d7


	std::cout << getScore(score) << std::endl;
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
<<<<<<< HEAD
	//	m_bullet->Draw();
	//	anim_die->Draw();
=======
//	m_bullet->Draw();
//	anim_die->Draw();
>>>>>>> 8eb5612be7992648d90237e85683e8ac5385e1d7
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