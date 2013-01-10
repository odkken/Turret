#include "stdafx.h"
#include "Monster.h"
#include "MyAlgorithms.h"

Monster::Monster(int level, bool boss)
{
	font.loadFromFile("fonts/segoesc.ttf");
	text.setFont(font);
	text.setString("Level " + std::to_string(level) + (boss ? "Boss" : "Scrub"));
	MyAlgorithms::CenterOrigin(text);
}

void Monster::SetPosition(const float& x, const float& y)
{
	text.setPosition(x,y);
}

sf::Text& Monster::GetImage()
{
	return text;
}