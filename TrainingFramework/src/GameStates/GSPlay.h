#pragma once
#include "gamestatebase.h"
#include "Enemy.h"
#include "Player.h"
class Sprite2D;
class Sprite3D;
class Text;
class Player;
class Enemy;



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

private:
	float m_time;
	float m_current;
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_score;
	std::shared_ptr<Player> m_player;
	std::vector<std::shared_ptr<Enemy>> m_enemy;
	std::shared_ptr<Enemy> anim_die;
};

