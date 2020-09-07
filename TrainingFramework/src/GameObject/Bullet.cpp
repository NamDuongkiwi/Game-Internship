#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture) :Sprite2D(model,shader,texture) {

}

Bullet::Bullet() : Sprite2D() {
}
void Bullet::Update(GLfloat deltaTime) {
	//TODO:
	Set2DPosition(this->Get2DPosition().x , this->Get2DPosition().y - deltaTime * 300);
}
void Bullet::Draw() {
Sprite2D::Draw();
}
