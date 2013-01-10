#pragma once
#include "Game.h"
#include "IVisibleObject.h"
#include <memory>

class GameState
{
public:
	virtual void HandleEvents();
	virtual void Update();
	virtual void Draw();

protected:
	GameState();
	void ChangeState(GameState* newState);
	std::vector<std::shared_ptr<IVisibleObject> > objects;
};

