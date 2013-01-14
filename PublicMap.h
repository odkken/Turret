#pragma once
#include "WorldMap.h"


//static worldmap interface for monsters and playing classes
//also contains turret grid
class PublicMap
{
public:
	static PublicMap* Instance();

	MapObject::ObjectType GetType(int row, int col);
	const sf::Vector2f& GetLocation(int row, int col);
	void Load(const std::string& file);
	const sf::Vector2i& GetSpawn();

	void Draw();

private:
	PublicMap();
	static PublicMap* instance_;
	WorldMap pubMap;
};

