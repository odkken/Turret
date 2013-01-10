#pragma once
#include "Game.h"
#include "stdafx.h"
class IVisibleObject
{
public:
	virtual bool HandleEvents(const sf::Event& someEvent) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Show(bool b) = 0;
};