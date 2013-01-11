#include "stdafx.h"
#include "PublicMap.h"


PublicMap* PublicMap::instance_ = 0;

PublicMap* PublicMap::Instance()
{
	if(instance_ == 0)
		instance_ = new PublicMap;

	return instance_;
}

PublicMap::PublicMap(void)
{
	pubMap.Load("Maps/map1.tm");
}

MapObject::ObjectType PublicMap::GetType(int row, int col)
{
	return pubMap.GetType(row, col);
}

const sf::Vector2f& PublicMap::GetLocation(int row, int col)
{
	return pubMap.GetLocation(row, col);
}