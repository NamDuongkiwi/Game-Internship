
#include "Enemy.h"
#include "Player.h"
#include "Shaders.h"
#include "Models.h"
#include "Texture.h"
#include "Sprite2D.h"
#include "Enemy.h"

Enemy::Enemy() {
}
Enemy::Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime) :Sprite2D(model, shader, texture), m_numFrames(numFrames), m_frameTime(frameTime), m_currentFrame(0), m_currentTime(0.0)
{
	m_blood = 500;
	m_status = small;
}

void Enemy::ChangeStatus() {
	if (m_blood >=400 ) {
		m_status = small;
		auto texture = ResourceManagers::GetInstance()->GetTexture("Enemy");
		this->m_pTexture = texture;
	}
	else if (m_blood >= 200 && m_blood < 400) {
		m_status = medium;
		auto texture = ResourceManagers::GetInstance()->GetTexture("Enemy2");
		this->m_pTexture = texture;
	}
	else if (m_blood >50 && m_blood <= 200) {
		m_status = big;
		auto texture = ResourceManagers::GetInstance()->GetTexture("Enemy3");
		this->m_pTexture = texture;
	}
	else {
		m_status = die;
		auto texture = ResourceManagers::GetInstance()->GetTexture("boom");
		auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
		this->m_pTexture = texture;
		this->m_pShader = shader;
		this->m_numFrames = 5;
		this->m_frameTime = 0.3f;
	}
}

EnemyStatus Enemy::getStatus() {
	return this->m_status;
}

void Enemy:: Update(GLfloat deltaTime) {
	m_currentTime += deltaTime;
	if (m_currentTime > m_frameTime) {
		m_currentFrame++;
		if (m_currentFrame == m_numFrames) {
//			m_currentFrame = 0;
		}
		m_currentTime -= m_frameTime;
	}

	this->SetBlood(this->GetBlood());
	ChangeStatus();
	Set2DPosition(this->Get2DPosition().x, this->Get2DPosition().y + 50 * deltaTime);
}
void Enemy::SetBlood(GLint blood) {
	this->m_blood = blood;
}
GLint Enemy::GetBlood() {
	return this->m_blood;
}



bool Enemy::checkHit(std::shared_ptr<Bullet> bullet) {
	GLfloat x_bullet = bullet->Get2DPosition().x;
	GLfloat y_bullet = bullet->Get2DPosition().y;
	GLfloat x_enemy = this->Get2DPosition().x;
	GLfloat y_enemy = this->Get2DPosition().y;
	if (y_bullet < y_enemy)
	{
		return true;
	}
	else return false;
}



void Enemy:: Draw() {

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