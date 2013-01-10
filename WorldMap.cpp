#include "stdafx.h"
#include "WorldMap.h"
#include <fstream>

WorldMap::WorldMap() : MAP_SIZE(20,20)
{
	int nodes = MAP_SIZE.x * MAP_SIZE.y;
	for (int i=0; i<nodes; ++i)
	{
		mapGrid.emplace_back(
			sf::Vector2f(MapObject::OBJECT_SIZE.x/2 + MapObject::OBJECT_SIZE.x*(i % MAP_SIZE.x), MapObject::OBJECT_SIZE.y/2 + MapObject::OBJECT_SIZE.y*((i/MAP_SIZE.x) % (MAP_SIZE.y)) ),
			MapObject(MapObject::ObjectType::wall));
		mapGrid[i].second.SetPosition(mapGrid[i].first);
	}
}

void WorldMap::Click(MapObject& obj)
{
	for(auto& node : mapGrid)
		if(obj.GetPos() == node.first)
			node.second.ChangeType(obj.GetType());
}

bool WorldMap::HandleEvents(const sf::Event& someEvent)
{
	return false;
}

void WorldMap::Draw()
{
	for (auto& node : mapGrid)
		node.second.Draw();
}

void WorldMap::Save()
{
	static int i=0;
	i++;
	std::ofstream saveFile;
	saveFile.open("Maps/map" + std::to_string(i) + ".tm");
	for (auto& node : mapGrid)
		saveFile << node.second.GetType()<<std::endl;
}

void WorldMap::Update()
{
}

void WorldMap::Show(bool b)
{
}

const sf::Vector2f& WorldMap::ClosestNode(const sf::Vector2f& pos)
{
	for (auto& node : mapGrid)
		if (abs((node.first-pos).x) <= MapObject::OBJECT_SIZE.x/2 && abs((node.first-pos).y) <= MapObject::OBJECT_SIZE.y/2)
			return node.first;
	return pos;
}

void WorldMap::Reset()
{
	for (auto& node : mapGrid)
		node.second.ChangeType(MapObject::ObjectType::wall);
}