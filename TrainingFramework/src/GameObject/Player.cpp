#pragma once
#include "Player.h"
#include "Shaders.h"
#include "Models.h"
#include "Texture.h"
#include "Sprite2D.h"
#include "GameObject/Enemy.h"


extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

Player::Player() :Sprite2D(){
}


Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime):Sprite2D(model, shader, texture),m_numFrames(numFrames), m_frameTime(frameTime), m_currentFrame(0), m_currentTime(0.0)
{
	m_IsMoving = false;
	m_Direction = UP;
	this->Set2DPosition(screenWidth / 2, screenHeight / 2 + 200);
	this->SetSize(200, 200);
	
	//m_bullet = std::make_shared<Bullet>(model, shader, texture);
	
}

std::vector<std::shared_ptr<Bullet>> Player::getListBullet() {
	return m_list_bullet;
}


void Player::Shoot(){
	GLfloat x = this->Get2DPosition().x;
	GLfloat y = this->Get2DPosition().y;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("egg");
	std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture);
	bullet->Set2DPosition(x, y - 60);
	bullet->SetSize(40, 40);
	m_list_bullet.push_back(bullet);
}




void Player::Init() {
	Sprite2D::Init();
	
}

int presss = 0;
int keyPressed = 0;

#define MRIGHT 1
#define MLEFT 2
#define MUP 4
#define MDOWN 8
#define SHOOT 16


void Player::HandleKeyEvents(int key, bool bIsPressed)
{
	//std::cout << key << bIsPressed << std::endl;
	if (bIsPressed) {
		switch (key) {
		case VK_UP:
			m_IsMoving = true;
			//m_Direction = UP;
			keyPressed |= MUP;
			break;
		case VK_DOWN:
			m_IsMoving = true;
			m_Direction = DOWN;
			keyPressed |= MDOWN;
			break;
		case VK_LEFT:
			m_IsMoving = true;
			m_Direction = LEFT;
			keyPressed |= MLEFT;
			break;
		case VK_RIGHT:
			m_IsMoving = true;
			m_Direction = RIGHT;
			keyPressed |= MRIGHT;
			break;
		case 'C':
			presss++;
			keyPressed |= SHOOT;
		default:
			break;
		}
	}
	else {
		m_IsMoving = false;
		switch (key) {
		case VK_UP:
			keyPressed &= ~MUP;
			break;
		case VK_DOWN:
			keyPressed &= ~MDOWN;
			break;
		case VK_LEFT:
			keyPressed &= ~MLEFT;
			break;
		case VK_RIGHT:
			keyPressed &= ~RIGHT;
			break;
		case 'C':
			presss++;
			keyPressed &= ~SHOOT;
			Shoot();
		default:
			break;
		}
	}
}






void Player::Update(GLfloat deltaTime) {
	//Shoot();

	if (keyPressed & MRIGHT)
	{
		if (this->Get2DPosition().x < screenWidth-40) {
			this->Set2DPosition(this->Get2DPosition().x + deltaTime * 250, this->Get2DPosition().y);
		}
		else {
			//make some noise
		}
	}
	if (keyPressed & MLEFT)
	{
		if (this->Get2DPosition().x > 40) {
			Set2DPosition(this->Get2DPosition().x - deltaTime * 250, this->Get2DPosition().y);
		}
		else {
			//make some noise
		}
	}
	if (keyPressed & MUP)
	{
		if (this->Get2DPosition().y > 50) {
			Set2DPosition(this->Get2DPosition().x, this->Get2DPosition().y - deltaTime * 250);
		}
		else {
			//make some noise
		}
	}
	if (keyPressed & MDOWN)
	{
		if (this->Get2DPosition().y < screenHeight -50) {
			Set2DPosition(this->Get2DPosition().x, this->Get2DPosition().y + deltaTime * 250);
		}
		else {
			//make some noise
		}
	}
	if (keyPressed & SHOOT)
	{
	//hoot();
	}



	//animation
	m_currentTime += deltaTime;
	if (m_currentTime > m_frameTime) {
		m_currentFrame++;
		if (m_currentFrame == m_numFrames) {
			m_currentFrame = 0;
		}
		m_currentTime -= m_frameTime;
	}
	
	//bullet
	for (int i = 0; i < m_list_bullet.size(); i++) {
		std::shared_ptr<Bullet> bullet = m_list_bullet.at(i);
		m_list_bullet.at(i)->Update(deltaTime);
		if (bullet->Get2DPosition().y < 0) {
			m_list_bullet.erase(m_list_bullet.begin());
			bullet = NULL;
		}

		
	}
}
void Player::checkHitEnemy(std::shared_ptr<Enemy> enemy) {
	for (int i = 0; i < m_list_bullet.size(); i++) {
		if (enemy->checkHit(m_list_bullet.at(i))) {
			enemy->SetBlood(enemy->GetBlood() - 50);
			m_list_bullet.erase(m_list_bullet.begin()+i);
		}
	}
}

void Player::Draw() {
	//bullet
	for (auto obj : m_list_bullet) {
		obj->Draw();
	}

	//animation player
	glUseProgram(m_pShader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());

	GLuint iTempShaderVaribleGLID = -1;
	Matrix matrixWVP;

	matrixWVP = m_WorldMat;//* m_pCamera->GetLookAtCamera();

	if (m_pTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_pTexture->Get2DTextureAdd());
		if (m_pShader->iTextureLoc[0] != -1)
			glUniform1i(m_pShader->iTextureLoc[0], 0);
	}
	else
	{
		iTempShaderVaribleGLID = -1;
		iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_color");
		if (iTempShaderVaribleGLID != -1)
			glUniform4f(iTempShaderVaribleGLID, m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	}


	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_POSITION);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_uv");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_UV);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_alpha");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, 1.0);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_matMVP");
	if (iTempShaderVaribleGLID != -1)
		glUniformMatrix4fv(iTempShaderVaribleGLID, 1, GL_FALSE, matrixWVP.m[0]);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_numFrames");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, m_numFrames);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_currentFrame");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, m_currentFrame);


	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}