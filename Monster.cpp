#include "stdafx.h"
#include "Monster.h"
#include "PublicMap.h"
#include "Playing.h"
#include <thread>
#include <mutex>


Monster::Monster(int level) : isSpawned(false), HP(100+5*level*level), speed(100*(1+level)), armor(level/5), lastPos(-1,-1), currentPos(-1,-1), monsterShape(10)
{
	monsterShape.setFillColor(sf::Color::Red);
	monsterShape.setOutlineColor(sf::Color::Blue);
	monsterShape.setOutlineThickness(-armor);
	monsterShape.setOrigin(monsterShape.getGlobalBounds().width/2,monsterShape.getGlobalBounds().height/2);
}

//does not check if it's a valid spawn, left to Playing class!
void Monster::Spawn(int row, int col)
{
	monsterShape.setPosition(PublicMap::Instance()->GetLocation(row, col));
	currentPos.x=col;
	currentPos.y=row;
	isSpawned=true;
	isMoving=false;
	moveTimer.restart();
}

void Monster::UnSpawn()
{
	isSpawned=false;
}

//returns true if you've finished moving
bool Monster::Move(const sf::Vector2i& dir)
{
	sf::Vector2f destination(PublicMap::Instance()->GetLocation(currentPos.y+dir.y,currentPos.x+dir.x));
	//if you're within a pixel of where you're moving to, set the position there and finish moving.
	if(abs(monsterShape.getPosition().x - destination.x) < 1.0f && abs(monsterShape.getPosition().y - destination.y) < 1.0f)
	{
		monsterShape.setPosition(destination);
		lastPos=currentPos;
		currentPos+=dir;
		moveTimer.restart();
		return true;
	}
	else
	{
		monsterShape.move(sf::Vector2f(dir)*(10*speed*moveTimer.restart().asSeconds()/MapObject::OBJECT_SIZE.x));
		return false;
	}
}
void Monster::Update()
{
	if(isSpawned)
	{
		if(moveTimer.getElapsedTime().asSeconds()*speed > 60.0f && !isMoving)
		{
			moveTimer.restart();
			isMoving=true;
		}
		if(isMoving && Move(FigureDirection()))
			isMoving=false;
	}

	if(PublicMap::Instance()->GetType(currentPos.y, currentPos.x)==MapObject::ObjectType::exit)
	{
		UnSpawn();
		++Playing::Instance()->monstersEscaped;
	}
}

void Monster::Show(bool b)
{
}


void Monster::Attack(int dmg)
{
	//fix this if things get too slow (unlikely)
	attackQueue.push_back(dmg);
}

bool Monster::Kill()
{
	//again, slow but probably not a big deal.  alternative to this is to have preallocated queue, limiting number of attacks per update (probably not an issue either)
	while(attackQueue.size())
	{
		HP-= (attackQueue.back()-armor);
		attackQueue.pop_back();
		if(HP<=0)
		{
			Die();
			return true;
		}
	}
	return false;
}

void Monster::Die()
{
	//gives more points for higher levels, temporary until balance testing
	Playing::Instance()->monstersKilled+=level;
	isSpawned=false;
}

bool Monster::HandleEvents(const sf::Event& someEvent)
{
	return false;
}


void Monster::Draw()
{
	if(isSpawned)
		Game::Instance()->mainWindow_.draw(monsterShape);
}

const sf::Vector2i Monster::FigureDirection()
{
	if(((PublicMap::Instance()->GetType(currentPos.y+1,currentPos.x) == MapObject::ObjectType::path)
		|| (PublicMap::Instance()->GetType(currentPos.y+1,currentPos.x) == MapObject::ObjectType::exit)) && sf::Vector2i(currentPos.x,currentPos.y+1)!=lastPos)
		return sf::Vector2i(0,1);

	if(((PublicMap::Instance()->GetType(currentPos.y-1,currentPos.x) == MapObject::ObjectType::path)
		|| (PublicMap::Instance()->GetType(currentPos.y-1,currentPos.x) == MapObject::ObjectType::exit)) && sf::Vector2i(currentPos.x,currentPos.y-1)!=lastPos)
		return sf::Vector2i(0,-1);

	if(((PublicMap::Instance()->GetType(currentPos.y,currentPos.x-1) == MapObject::ObjectType::path)
		|| (PublicMap::Instance()->GetType(currentPos.y,currentPos.x-1) == MapObject::ObjectType::exit)) && sf::Vector2i(currentPos.x-1,currentPos.y)!=lastPos)
		return sf::Vector2i(-1,0);

	if(((PublicMap::Instance()->GetType(currentPos.y,currentPos.x+1) == MapObject::ObjectType::path)
		|| (PublicMap::Instance()->GetType(currentPos.y,currentPos.x+1) == MapObject::ObjectType::exit)) && sf::Vector2i(currentPos.x+1,currentPos.y)!=lastPos)
		return sf::Vector2i(1,0);

	return sf::Vector2i(0,0);
}