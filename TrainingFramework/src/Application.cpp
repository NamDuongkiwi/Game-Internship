#include "Application.h"
#include "GameStates/GameStateMachine.h"
#include "GameStates/GameStatebase.h"
extern GLint screenWidth;
extern GLint screenHeight;


Application::Application()
{
	//m_soloud
}


Application::~Application()
{
}


void Application::Init()
{
	m_soloud.init();
	sound_balloon.load("src/balloon.wav");
	sound_shoot.load("src/shot.wav");
	sound_gameplay.load("src/Ant.wav");
	sound_bonus.load("src/bonus.wav");
	sound_choidam.load("src/choidam.wav");
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	GameStateMachine::GetInstance()->PushState(StateTypes::STATE_Intro);
}

void Application::Update(GLfloat deltaTime)
{
	GameStateMachine::GetInstance()->PerformStateChange();

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->Update(deltaTime);
}

void Application::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->Draw();
}

void Application::HandleKeyEvent(unsigned char key, bool bIsPresseded)
{
	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->HandleKeyEvents(key, bIsPresseded);

}

void Application::HandleTouchEvent(GLint x, GLint y, bool bIsPresseded)
{

	if (GameStateMachine::GetInstance()->HasState())
		GameStateMachine::GetInstance()->CurrentState()->HandleTouchEvents(x, y, bIsPresseded);
}

void Application::Exit()
{
	exit(0);
}
