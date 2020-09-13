#pragma once
#include "Sprite2D.h"


class MainCharacter;
enum ItemType {
	NEPTUNE,
	BROOM,
	CHILI,
	TRUNGRAN
};
class Item :public Sprite2D {
public:
	Item();
	Item(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, ItemType type);
	ItemType getItemType();
	void Update(float deltaTime);
	void Draw();
	void setImage(ItemType type);
	bool checkCollision1(std::shared_ptr<MainCharacter> player);
private:
	ItemType m_type;
	float m_width;
};