#pragma once
#include "GameState.h"
#include "PublicMap.h"
#include "Monster.h"
#include "ClickableText.h"
class Playing :
	public GameState
{
public:
	static Playing* Instance();
	
	int monstersKilled;
	int monstersEscaped;
	int level;


	void HandleEvents();
	void Update();
	void Draw();

	void Reset();


private:
	static Playing* instance_;
	Playing();

	bool running;

	const int NUM_MONSTERS;
	int spawnIndex;
	std::vector<ClickableText> buttons;
	sf::Vector2i spawnPoint;
	sf::Clock spawnTimer;
	std::vector<Monster> monsters;
	//std::vector<Turret> turrets;
};

