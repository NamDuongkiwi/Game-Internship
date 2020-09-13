#include "Shaders.h"
#include "Models.h"
#include "Texture.h"
#include "ResourceManagers.h"
#include "Boss.h"
#include "Application.h"

Boss::Boss(){}

Boss::Boss(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime) : Sprite2D(model, shader, texture), m_numFrames(numFrames), m_frameTime(frameTime), m_currentFrame(0), m_currentTime(0.0) {
	m_shoottime = 0;
	m_blood = 5000;
}

//float m_shoottime = 0;
void Boss::Shoot(float deltaTime) {
	m_shoottime += deltaTime;
	if ( m_shoottime > 3) {
		GLfloat x = this->Get2DPosition().x;
		GLfloat y = this->Get2DPosition().y;
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("shit");
		std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(model, shader, texture, SHIT);
		bullet->SetSize(70, 70);
		bullet->Set2DPosition(x, y + 60);
		//bullet->SetSize(40, 40);
		m_list_bullet.push_back(bullet);
		Application::GetInstance()->m_soloud.setVolume(Application::GetInstance()->m_soloud.play(Application::GetInstance()->sound_shoot), 0.2);
		m_shoottime = 0;
	}
}
void Boss::SetBlood(int blood) {
	this->m_blood = blood;
}
int Boss::GetBlood() {
	return this->m_blood;
}



void Boss::Die() {

}

void Boss::Draw() {
	for (auto obj : m_list_bullet) {
		obj->Draw();
	}


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
void Boss::Update(float deltaTime) {
	if(this->Get2DPosition().y < 200)
		this->Set2DPosition(this->Get2DPosition().x, this->Get2DPosition().y + 50 * deltaTime);
	Shoot(deltaTime);
	for (auto obj : m_list_bullet) {
		obj->Update(deltaTime);
	}
	m_currentTime += deltaTime;
	if (m_currentTime > m_frameTime) {
		m_currentFrame++;
		if (m_currentFrame == m_numFrames) {
			m_currentFrame = 0;
		}
		m_currentTime -= m_frameTime;
	}
}

