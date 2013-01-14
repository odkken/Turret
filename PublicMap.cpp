#include "stdafx.h"
#include "PublicMap.h"


PublicMap* PublicMap::instance_ = 0;

PublicMap* PublicMap::Instance()
{
	if(instance_ == 0)
		instance_ = new PublicMap;

	return instance_;
}

void PublicMap::Draw()
{
	pubMap.Draw();
}

PublicMap::PublicMap(void)
{
	pubMap.Load("Maps/map1.tm");
}

void PublicMap::Load(const std::string& file)
{
	pubMap.Load(file);
}

//row,column
MapObject::ObjectType PublicMap::GetType(int row, int col)
{
	return pubMap.GetType(row, col);
}

//row, column
const sf::Vector2f& PublicMap::GetLocation(int row, int col)
{
	return pubMap.GetLocation(row, col);
}

const sf::Vector2i& PublicMap::GetSpawn()
{
	return pubMap.GetSpawn();
}