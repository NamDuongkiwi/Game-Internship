#pragma once
#include "gamestatebase.h"
#include "MainCharacter.h"
#include "Monster.h"
#include "Boom.h"

class Sprite2D;
class Sprite3D;
class Text;
class MainCharacter;
class Monster;
class Bullet;
class Boom;


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

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();


	void SetNewPostionForBullet();
	void creatMonster();
	std::shared_ptr<Boom> CreatBoom(float x, float y);
	std::string getScore(int score);

private:
	float m_time;
	float m_current;
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_score;
	std::shared_ptr<MainCharacter> m_player;
	std::vector<std::shared_ptr<Monster>> m_list_monster;
	std::shared_ptr<Boom> m_boom;
};

