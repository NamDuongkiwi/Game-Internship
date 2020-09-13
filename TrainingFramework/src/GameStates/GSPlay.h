#pragma once
#include "gamestatebase.h"
#include "MainCharacter.h"
#include "Monster.h"
#include "Boom.h"
#include "Boss.h"
#include "Item.h"
#include <soloud.h>
#include <soloud_wav.h>

class Sprite2D;
class Sprite3D;
class Text;
class MainCharacter;
class Monster;
class Bullet;
class Boom;
class Boss;
class Item;



enum StateGamePlay
{
	GAME_PAUSE,
	GAME_OVER,
	GAME_RUNNING,
};

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();
	void GameOver();


	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
	
	
	//make some noise
	void parallelBackground(float deltaTime);


	void SetNewPostionForBullet();
	void creatMonster(float deltaTime);
	void deleteMonster();
	void creatItem(float deltaTime);
	void eatItem();
	void creatBoss();
	std::shared_ptr<Boom> CreatBoom(float x, float y);
	std::string getScore(int score);
	void setbroom();
	//void boomaudio();

private:
	float m_time;
	float m_current;
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Sprite2D> m_BackGround1;
	std::shared_ptr<Sprite2D> m_BackgroundGameover;
	std::shared_ptr<Text>  m_score;
	int  m_highscore;
	std::shared_ptr<Text> m_TextSttGame;

	StateGamePlay m_SttGamePlay;
	bool m_ispause;
	
	//game
	std::shared_ptr<MainCharacter> m_player;
	std::vector<std::shared_ptr<Monster>> m_list_monster;
	std::shared_ptr<Boom> m_boom;
	std::shared_ptr<Boss> m_boss;
	std::vector<std::shared_ptr<Item>> m_list_item;
	std::shared_ptr<Sprite2D> broom;
	
	
	//
	
	
};

