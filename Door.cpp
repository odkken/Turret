#include "stdafx.h"
#include "Door.h"

bool Door::firstConstructed=true;
sf::SoundBuffer Door::soundBuffer;
sf::Sound Door::mouseOverSound;

Door::Door(const float& x, const float& y, int level, bool boss) : monster(level, boss)
{
	doorFont.loadFromFile("fonts/arial.ttf");
	doorText.setFont(doorFont);
	doorText.setString("soup");
	//load sounds the first time a door is made
	if(firstConstructed)
	{
		soundBuffer.loadFromFile("sounds/click.wav");
		mouseOverSound.setBuffer(soundBuffer);
		firstConstructed=false;
	}

	doorShape.setSize(sf::Vector2f(240,500));
	doorShape.setOutlineThickness(-5);
	doorShape.setFillColor(sf::Color(120,60,0,255));
	MyAlgorithms::CenterOrigin(doorShape);
	doorShape.setPosition(x,y);
	monster.SetPosition(x,y);
}

void Door::SetPosition(const float& x, const float& y)
{
	doorShape.setPosition(x, y);
}

void Door::MouseOver(bool b)
{
	//if you weren't previously moused over and now you are
	if (!isMousedOver && b)
		mouseOverSound.play();

	isMousedOver=b;

	if(isMousedOver)
		doorShape.setOutlineColor(sf::Color::White);
	else
		doorShape.setOutlineColor(doorShape.getFillColor());
}

const Door::DoorState& Door::GetState()
{
	return state;
}

const sf::RectangleShape& Door::GetShape()
{
	return doorShape;
}


void Door::openAnimation()
{
}

void Door::Select(bool b)
{
	isSelected=b;
}

void Door::Open()
{
	sf::Color currentCol = doorShape.getFillColor();
	currentCol.a=0;
	doorShape.setFillColor(currentCol);
	doorShape.setOutlineColor(currentCol);
}

Monster& Door::GetMonster()
{
	return monster;
}