#pragma once
#include "GameState.h"
#include "WorldMap.h"
#include "MapObject.h"
#include "ClickableText.h"
class Editing :
	public GameState
{
public:
	static Editing* Instance();
	void HandleEvents();
	WorldMap& GetMap();
	void Draw();

private:
	Editing();
	static Editing* instance_;
	WorldMap map;
	MapObject mouseObject;
	ClickableText resetButton, saveButton;
};

