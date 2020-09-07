#pragma once
#include "Sprite2D.h"

//class Boom : public Sprite2D {
//public:
//	Boom();
//	Boom(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
//	void Draw() override;
//	void Update(float deltaTime);
//private:
//	int m_numFrames;
//	GLfloat m_frameTime;
//	int m_currentFrame;
//	GLfloat m_currentTime;
//};
class Boom :public Sprite2D {
public:
	Boom();
	Boom(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	void Draw() override;
	void Update(GLfloat deltaTime) override;
private:
		int m_numFrames;
		GLfloat m_frameTime;
		int m_currentFrame;
		GLfloat m_currentTime;
};