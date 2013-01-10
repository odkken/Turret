#pragma once
#include "MapObject.h"
#include <memory>
class WorldMap : public IVisibleObject
{
public: 

	const sf::Vector2i MAP_SIZE;

	WorldMap();
	void Update();
	bool HandleEvents(const sf::Event& someEvent);
	void Draw();
	void Show(bool b);

	void Save();

	void Click(MapObject& obj);
	
	void Reset();
	bool InsertObject(MapObject& obj);
	const sf::Vector2f& ClosestNode(const sf::Vector2f& pos);

private:
	std::vector<std::pair< sf::Vector2f, MapObject > > mapGrid;
	int FindIndex(const sf::Vector2f& location);
};

