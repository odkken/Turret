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
	void Load(const std::string& fileName);
	void Save();

	MapObject::ObjectType GetType(int row, int col);
	const sf::Vector2f& GetLocation(int row, int col);
	const sf::Vector2i GetIndex(const sf::Vector2f& location);

	void Click(MapObject& obj);
	
	void Reset();
	bool InsertObject(MapObject& obj);
	const sf::Vector2f& ClosestNode(const sf::Vector2f& pos);

private:

	//this is accessed as mapgrid[row][col], which means mapgrid[y][x] is typical
	std::vector<std::vector<std::pair< sf::Vector2f, MapObject > > > mapGrid;
	int FindIndex(const sf::Vector2f& location);
};

