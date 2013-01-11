#pragma once
#include "GameState.h"
#include "PublicMap.h"
class Playing :
	public GameState
{
public:
	static Playing* Instance();

private:
	static Playing* instance_;

	sf::Clock spawnTimer;
};

