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
#include <soloud.h>
#include <soloud_wav.h>
#include <Application.h>

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
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
void GSPlay::Init()
{
	m_ispause = false;

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("play_background");
	
	//BackGround + under
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth + 20, screenHeight + 20);
	m_BackGround1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround1->Set2DPosition(screenWidth / 2, screenHeight / 2 - screenHeight);
	m_BackGround1->SetSize(screenWidth + 20, screenHeight + 20);

	//score
	texture = ResourceManagers::GetInstance()->GetTexture("GameOver2");
	m_BackgroundGameover = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackgroundGameover->Set2DPosition((GLfloat)screenWidth / 2, (GLfloat)screenHeight / 2);
	m_BackgroundGameover->SetSize(screenWidth, screenHeight);

	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("times");
	m_score = std::make_shared< Text>(shader, font, getScore(score), TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));


	int buffer[1];
	std::fstream file("..\\Data\\highscore.txt", std::ios::in | std::ios::binary);
	if (file.is_open())
	{
		LOGI("Load File:highscore.txt\t\t");
		file.read(reinterpret_cast<char*>(buffer), sizeof(GLint));
	}
	else LOGE("ERROR Highscore.bin \n");
	file.close();
	buffer[0] < 0 ? m_highscore = 0 : m_highscore = buffer[0];


	font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_TextSttGame = std::make_shared< Text>(shader, font, "GAME OVER", TEXT_COLOR::RED, 1.5);
	m_TextSttGame->Set2DPosition(Vector2((GLfloat)screenWidth / 2 - 110, 100));

	//player
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("duck");
	m_player = std::make_shared<MainCharacter>(model, shader, texture, 3, 0.05f);


	//boom
	texture = ResourceManagers::GetInstance()->GetTexture("boom");
	m_boom = std::make_shared<Boom>(model, shader, texture, 5, 0.02f);
	m_boom->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_boom->SetSize(0, 0);

	//SoLoud::Soloud soloud;
	
	Application::GetInstance()->m_soloud.setLooping(Application::GetInstance()->m_soloud.play(Application::GetInstance()->sound_gameplay), 1);

	model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	texture = ResourceManagers::GetInstance()->GetTexture("endboss");
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_boss = std::make_shared<Boss>(model, shader, texture, 5, 0.1f);
	m_boss->Set2DPosition(screenWidth / 2, -100);
	m_boss->SetSize(200, 200);

}

void GSPlay::parallelBackground(float deltaTime) {
	m_BackGround->Set2DPosition(m_BackGround->Get2DPosition().x, m_BackGround->Get2DPosition().y + 50 * deltaTime);
	if (m_BackGround->Get2DPosition().y > screenHeight + screenHeight / 2) {
		m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	}
	m_BackGround1->Set2DPosition(m_BackGround1->Get2DPosition().x, m_BackGround1->Get2DPosition().y + 50 * deltaTime);
	if (m_BackGround1->Get2DPosition().y > screenHeight / 2) {
		m_BackGround1->Set2DPosition(screenWidth / 2, screenHeight / 2 - screenHeight);
	}
}




std::shared_ptr<Boom> GSPlay::CreatBoom(float x, float y) {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("boom");
	std::shared_ptr<Boom> boom = std::make_shared<Boom>(model, shader, texture, 5, 0.02f);
	boom->Set2DPosition(x, y);
	return boom;
}

float item_time = 0;


void GSPlay::creatItem(float deltaTime) {
	item_time += deltaTime;
	if (item_time > 4) {
		int random = rand() % 4 + 1;
		int random1 = rand() % 7 + 1;
		//random = 1;
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("chili");
		std::shared_ptr<Item> item;
		if (m_player->getShoot() == false) {
			if (random == 2 || random == 3)
				random = 4;
		}
		if (random == 1) {
			item = std::make_shared<Item>(model, shader, texture, BROOM);
			item->SetSize(200, 200);
		}
		else if (random == 2) {
			item = std::make_shared<Item>(model, shader, texture, TRUNGRAN);
			item->SetSize(50, 50);
		}
		else if (random == 3) {
			item = std::make_shared<Item>(model, shader, texture, CHILI);
			item->SetSize(100, 100);
		}
		else if (random == 4) {
			item = std::make_shared<Item>(model, shader, texture, NEPTUNE);
			item->SetSize(100, 100);
		}
		item->Set2DPosition(screenWidth *random1/ 7, -40);
		m_list_item.push_back(item);

		item_time = 0;
	}
}
void GSPlay::eatItem() {
	for (int i = 0; i < m_list_item.size(); i++) {
		if (m_list_item.at(i)->checkCollision1(m_player) == true) {
			if (m_list_item.at(i)->getItemType() == BROOM && m_player->getShoot() == true) {
				m_player->setShoot(false);
				Application::GetInstance()->m_soloud.play(Application::GetInstance()->sound_choidam);
			}
			else if (m_list_item.at(i)->getItemType() == NEPTUNE && m_player->getShoot() == false) {
				m_player->setShoot(true);
				m_player->setStatus(NORMAL);
				Application::GetInstance()->m_soloud.setVolume(Application::GetInstance()->m_soloud.play(Application::GetInstance()->sound_bonus), 1.5);
			}
			else if (m_list_item.at(i)->getItemType() == CHILI && m_player->getStatus() == NORMAL) {
				m_player->setStatus(FIRE);
				Application::GetInstance()->m_soloud.setVolume(Application::GetInstance()->m_soloud.play(Application::GetInstance()->sound_bonus), 1.5);
			}
			else if (m_list_item.at(i)->getItemType() == NEPTUNE && m_player->getStatus() == FIRE ) {
				Application::GetInstance()->m_soloud.setVolume(Application::GetInstance()->m_soloud.play(Application::GetInstance()->sound_bonus), 1.5);
				m_player->setStatus(PAN);
			}
			m_list_item.erase(m_list_item.begin() + i);
		}
	}


	// qua range
	for (int i = 0; i < m_list_item.size(); i++) {
		std::shared_ptr<Item> item = m_list_item.at(i);
		if (item->Get2DPosition().y > screenHeight) {
			m_list_item.erase(m_list_item.begin());
			item = NULL;
		}
	}
}
float m_time = 0;
float m_shoottime = 0;
void GSPlay::creatMonster(float deltaTime) {
	m_time += deltaTime;
	if (m_time > 1.2) {
		int random;
		random = rand() % 7 + 1;
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Enemy");
		std::shared_ptr<Monster> monster = std::make_shared<Monster>(model, shader, texture);
		monster->Set2DPosition(screenWidth * random / 8, -40);
		monster->SetSize(200, 200);
		m_list_monster.push_back(monster);
		m_time = 0;
	}
}
void GSPlay::deleteMonster() {
	for (int i = 0; i < m_list_monster.size(); i++) {
		if (m_list_monster.at(i)->GetMonsterStatus() == DIE) {
			Application::GetInstance()->m_soloud.play(Application::GetInstance()->sound_balloon);
			score += 1;
			m_score->setText(getScore(score));
			m_boom = NULL;
			m_boom = CreatBoom(m_list_monster.at(i)->Get2DPosition().x, m_list_monster.at(i)->Get2DPosition().y);
			m_boom->SetSize(m_list_monster.at(i)->getwidth(), m_list_monster.at(i)->getheight());
			m_list_monster.erase(m_list_monster.begin() + i);
		}
	}
	for (int i = 0; i < m_list_monster.size(); i++) {
		std::shared_ptr<Monster> monster = m_list_monster.at(i);
		if (monster->Get2DPosition().y > screenHeight + 40) {
			m_list_monster.erase(m_list_monster.begin());
			std::cout << m_list_monster.size() << std::endl;
			monster = NULL;
		}
	}

}
void GSPlay::Exit()
{
}

void GSPlay::GameOver()
{
	m_SttGamePlay = GAME_OVER;
	m_ispause = true;
	m_TextSttGame->setText("GAME OVER");
	if (score > m_highscore)
	{
		std::ofstream writeFile("..\\Data\\highscore.txt", std::ios::binary);
		if (!writeFile.is_open())
		{
			LOGE("ERROR highscore.txt \n");
			return;
		}
		else
		{
			LOGI("Load File:highscore.txt\t\t");
			writeFile << (GLint)score;
			writeFile.close();
		}
	}
}
void GSPlay::Pause()
{
	m_SttGamePlay = GAME_PAUSE;
	m_ispause = true;
}

void GSPlay::Resume()
{
	m_SttGamePlay = GAME_RUNNING;
	m_ispause = false;
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	m_player->HandleKeyEvents(key, bIsPressed);
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}


void GSPlay::setbroom() {
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("broom");
	broom = std::make_shared<Sprite2D>(model, shader, texture);
	broom->Set2DPosition(m_player->Get2DPosition().x, m_player->Get2DPosition().y);
	if (!m_player->getShoot()) {
		broom->SetSize(200, 200);
	}
	else broom->SetSize(0, 0);
}

void GSPlay::creatBoss() {
}

float bosstime = 0;
void GSPlay::Update(float deltaTime)
{
	
	if(m_ispause == false && deltaTime > 0){
		parallelBackground(deltaTime);
		m_player->Update(deltaTime);
		m_boom->Update(deltaTime);
		setbroom();
		broom->Set2DPosition(m_player->Get2DPosition().x + 5, m_player->Get2DPosition().y - 70);
		broom->Update(deltaTime);
		creatItem(deltaTime);
		for (auto obj : m_list_item) {
			obj->Update(deltaTime);
		}
		eatItem();
		
		for (auto obj : m_list_monster) {
			obj->Update(deltaTime);
			m_player->HitMonster(obj);
			if (m_player->checkCollision(obj) == true) {
				m_boom = CreatBoom(m_boss->Get2DPosition().x, m_boss->Get2DPosition().y);
				m_boom->SetSize(200, 200);
				GameOver();
				Application::GetInstance()->m_soloud.play(Application::GetInstance()->sound_balloon);
				Application::GetInstance()->m_soloud.play(Application::GetInstance()->sound_bokeu);
			}
		}
		deleteMonster();
		bosstime += deltaTime;
		if (bosstime < 30) 	{
			creatMonster(deltaTime);	
		}
		else if (bosstime > 30 && m_list_monster.size() == 0) {
			m_boss->Update(deltaTime);
			m_player->HitBoss(m_boss);
			if (m_boss->GetBlood() < 0) {
				m_boom = CreatBoom(m_boss->Get2DPosition().x, m_boss->Get2DPosition().y);
				m_boom->SetSize(200,200);
				Application::GetInstance()->m_soloud.play(Application::GetInstance()->sound_balloon);
				m_boss->Set2DPosition(screenWidth / 2, -100);
				bosstime = 0;
			}	
		}
	}

}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_BackGround1->Draw();
	broom->Draw();
	m_player->Draw();
	m_boss->Draw();
	for (auto obj : m_list_monster) {
		obj->Draw();
	}
	for (auto obj : m_list_item) {
		obj->Draw();
	}
	m_boom->Draw();
	m_score->Draw();	
	if (m_SttGamePlay == GAME_PAUSE || m_SttGamePlay == GAME_OVER)
	{
		m_BackgroundGameover->Draw();
		m_TextSttGame->Draw();
	}
}

void GSPlay::SetNewPostionForBullet()
{
}