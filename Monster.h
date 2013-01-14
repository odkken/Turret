#pragma once
#include "ivisibleobject.h"
class Monster :
	public IVisibleObject
{
public:
	Monster(int level);
	bool HandleEvents(const sf::Event & someEvent);
	void Update();
	void Draw();
	void Show(bool b);
	void Spawn(int row, int col);
	void UnSpawn();
	void Attack(int dmg);

private:
	std::vector<int> attackQueue;
	//returns true if monster died from attack
	bool Kill();
	bool isSpawned, isMoving;
	const sf::Vector2i FigureDirection();

	//THREADED
	bool Move(const sf::Vector2i& direction);
	void Die();
	int HP, speed, armor;

	int level;

	sf::Vector2i currentPos;
	sf::Vector2i lastPos;

	sf::CircleShape monsterShape;

	sf::Clock moveTimer;
};

