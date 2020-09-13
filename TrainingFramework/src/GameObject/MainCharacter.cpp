#include "MainCharacter.h"
#include "Monster.h"


#include "Shaders.h"
#include "Models.h"
#include "Texture.h"
#include "ResourceManagers.h"
#include "Application.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine


MainCharacter::MainCharacter() {

}

MainCharacter::MainCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime) : Sprite2D(model, shader, texture), m_numFrames(numFrames), m_frameTime(frameTime), m_currentFrame(0), m_currentTime(0.0) {
	this->can_shoot = true;
	this->Set2DPosition(screenWidth / 2, screenHeight / 2 + 200);
	this->SetSize(200, 200);
	latency = 0;
	keyPressed = 0;
	this->m_status = NORMAL;
	texture = ResourceManagers::GetInstance()->GetTexture("broom");
	cantshoot = std::make_shared<Sprite2D>(model, shader, texture);
	cantshoot->SetSize(200,200);
}

void MainCharacter::setStatus(Status status) {
	this->m_status = status;
}

Status MainCharacter::getStatus() {
	return this->m_status;
}

void MainCharacter::setShoot(bool cs) {
	this->can_shoot = cs;
}
bool MainCharacter::getShoot() {
	return this->can_shoot;
}


void MainCharacter::Init() {
Sprite2D:Init();
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("broom");
}



#define MRIGHT 1
#define MLEFT 2
#define MUP 4
#define MDOWN 8
#define SHOOT 16


void MainCharacter::HandleKeyEvents(int key, bool bIsPressed) {
	if (bIsPressed) {
		switch (key) {
		case VK_UP:
			//m_Direction = UP;
			keyPressed |= MUP;
			break;
		case VK_DOWN:
			keyPressed |= MDOWN;
			break;
		case VK_LEFT:
			keyPressed |= MLEFT;
			break;
		case VK_RIGHT:
			keyPressed |= MRIGHT;
			break;
		case 'C':
			keyPressed |= SHOOT;
		default:
			break;
		}
	}
	else {
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
			keyPressed &= ~MRIGHT;
			break;
		default:
			break;
		}
	}
}


void MainCharacter::HitMonster(std::shared_ptr<Monster> monster) {
	for (int i = 0; i < m_list_bullet.size(); i++) {
		if (m_list_bullet.at(i)->checkCollision(monster) == true) {
			monster->SetBlood(monster->GetBlood() - m_list_bullet.at(i)->getDame());
			//printf("ban trung + %d + %d \n", m_list_bullet.at(i)->getDame(), monster->GetBlood());
			m_list_bullet.erase(m_list_bullet.begin() + i);
		}
	}
}

void MainCharacter::HitBoss(std::shared_ptr<Boss> monster) {
	for (int i = 0; i < m_list_bullet.size(); i++) {
		if (m_list_bullet.at(i)->checkCollision(monster) == true) {
			monster->SetBlood(monster->GetBlood() - m_list_bullet.at(i)->getDame());
			//printf("ban trung + %d + %d \n", m_list_bullet.at(i)->getDame(), monster->GetBlood());
			m_list_bullet.erase(m_list_bullet.begin() + i);
		}
	}
}

bool MainCharacter::checkCollision(std::shared_ptr<Monster> obj) {
	
	//           |__________|
	//
	//          |======|
	//
	

	float u_lr = obj->Get2DPosition().x - obj->getwidth() / 2 + 55;
	float u_rr = obj->Get2DPosition().x + obj->getwidth() / 2 - 55;
	float u_br = obj->Get2DPosition().y + obj->getheight() / 2 - 50;
	float u_ar = obj->Get2DPosition().y - obj->getheight() / 2 + 40;

	float d_lr = this->Get2DPosition().x - this->getwidth() / 2 + 65;
	float d_rr = this->Get2DPosition().x + this->getwidth() / 2 - 65;
	float d_br = this->Get2DPosition().y + this->getheight() / 2 - 40;
	float d_ar = this->Get2DPosition().y - this->getheight() / 2 + 50;
	

	if (u_br > d_ar && u_ar < d_br) {
		if (d_lr > u_rr || d_rr < u_lr) {
			return false;
		}
		else if (d_lr < u_rr && d_rr > u_lr) {
			return true;
		}
		//else if ( )
		else return false;
	}
	else return false;

	
}




float m_shoot = 0;
float change_time;
void MainCharacter::Shoot(float deltaTime) {
		
	m_shoot += deltaTime;
	if (can_shoot == true && m_shoot > 0.1) {
		GLfloat x = this->Get2DPosition().x;
		GLfloat y = this->Get2DPosition().y;
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("egg");
		std::shared_ptr<Bullet> bullet;
		if (this->getStatus() == NORMAL) {
			bullet = std::make_shared<Bullet>(model, shader, texture, EGG);
			bullet->SetSize(40, 40);
		}
		else if (this->getStatus() == FIRE) {
			bullet = std::make_shared<Bullet>(model, shader, texture, FIRE_EGG);
			bullet->SetSize(40, 40);
		}
		else if (this->getStatus() == PAN) {
			bullet = std::make_shared<Bullet>(model, shader, texture, PAN_EGG);
			bullet->SetSize(90, 90);
		}
		bullet->Set2DPosition(x, y - 60);
			//bullet->SetSize(40, 40);
		m_list_bullet.push_back(bullet);			
		Application::GetInstance()->m_soloud.setVolume(Application::GetInstance()->m_soloud.play(Application::GetInstance()->sound_shoot), 0.2);
		m_shoot = 0;
	}
}

void MainCharacter::changeStatus(float deltaTime) {
	if (this->getStatus() == FIRE || this->getStatus() == PAN) {
		change_time += deltaTime;
	}
	if (change_time > 10) {
		this->setStatus(NORMAL);
		change_time = 0;
	}
}
void MainCharacter::Update(float deltaTime) {
	changeStatus(deltaTime);
	Shoot(deltaTime);
	cantshoot->Set2DPosition(this->Get2DPosition().x, this->Get2DPosition().y);
	for (int i = 0; i < m_list_bullet.size(); i++) {
		std::shared_ptr<Bullet> bullet = m_list_bullet.at(i);
		m_list_bullet.at(i)->Update(deltaTime);
		if (bullet->Get2DPosition().y < 0) {
			m_list_bullet.erase(m_list_bullet.begin());
			bullet = NULL;
		}
	}
	//keypress and move 
	if (keyPressed & MRIGHT)
	{
		if (this->Get2DPosition().x < screenWidth - 40) {
			this->Set2DPosition(this->Get2DPosition().x + deltaTime * 350, this->Get2DPosition().y);
		}
		else {
			//make some noise
		}
	}
	if (keyPressed & MLEFT)
	{
		if (this->Get2DPosition().x > 40) {
			Set2DPosition(this->Get2DPosition().x - deltaTime * 350, this->Get2DPosition().y);
		}
		else {
			//make some noise
		}
	}
	if (keyPressed & MUP)
	{
		if (this->Get2DPosition().y > 50) {
			Set2DPosition(this->Get2DPosition().x, this->Get2DPosition().y - deltaTime * 350);
		}
		else {
			//make some noise
		}
	}
	if (keyPressed & MDOWN)
	{
		if (this->Get2DPosition().y < screenHeight - 50) {
			Set2DPosition(this->Get2DPosition().x, this->Get2DPosition().y + deltaTime * 350);
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
}






void MainCharacter::Draw() {
	//shoot
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
