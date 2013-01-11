#include "stdafx.h"
#include "Monster.h"
#include "PublicMap.h"
//every 5 levels the speed increases, other stuff is guesswork for now
Monster::Monster(int level) : attackable(false), isShowing(false), HP(100+5*level*level), speed(level/5), armor((level>5) ? level-5 : 0), lastPos(0,0), monsterShape(10)
{
	monsterShape.setFillColor(sf::Color::Red);
	monsterShape.setOutlineColor(sf::Color::White);
	monsterShape.setOutlineThickness(armor);
}

//does not check if it's a valid spawn, left to Playing class!
void Monster::Spawn(int row, int col)
{
	monsterShape.setPosition(PublicMap::Instance()->GetLocation(row, col));
	isShowing=true;
	attackable=true;
}


void Monster::Update()
{

}

void Monster::Show(bool b)
{
	isShowing=b;
}

bool Monster::Kill(int dmg)
{
	HP-= (dmg-armor);
	
	if(HP<=0)
	{
		Die();
		return true;
	}
	return false;
}

void Monster::Die()
{
	isShowing=false;
	attackable=false;
}

void Monster::Draw()
{
	if(isShowing)
	Game::Instance()->mainWindow_.draw(monsterShape);
}

