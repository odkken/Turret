#pragma once
#include "ivisibleobject.h"
class Monster :
	public IVisibleObject
{
public:
	Monster(int level);
	bool HandleEvents(sf::Event someEvent);
	void Update();
	void Draw();
	void Show(bool b);
	void Spawn(int row, int col);

	//returns true if monster died from attack
	bool Kill(int dmg);

private:
	bool attackable, isShowing;
	void move();
	void Die();
	int HP, speed, armor;
	sf::Vector2f lastPos;
	sf::CircleShape monsterShape;
};

