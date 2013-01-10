#pragma once
#include "IVisibleObject.h"
class MapObject :
	public IVisibleObject
{
public:
	static const sf::Vector2i OBJECT_SIZE;
	enum ObjectType{wall, path, empty, spawn, exit};
	MapObject(ObjectType object);
	void Draw();
	bool HandleEvents(const sf::Event& someEvent);
	void Update();
	//const sf::FloatRect& GetBounds();
	void ChangeType(ObjectType newType);
	ObjectType GetType() {return thisObject;};
	void SetPosition(const sf::Vector2f& pos);
	const sf::Vector2f& GetPos();
	void Show(bool b);

private:
	sf::RectangleShape shape;
	ObjectType thisObject;
	bool isShowing;

	void UpdateImage();
};

