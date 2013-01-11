#include "stdafx.h"
#include "WorldMap.h"
#include <fstream>
#include "MyAlgorithms.h"

WorldMap::WorldMap() : MAP_SIZE(20,20)
{
	for (int row=0; row<MAP_SIZE.y; ++row)
	{
		std::vector<std::pair<sf::Vector2f, MapObject> > rowVec;
		for (int col=0; col<MAP_SIZE.x; ++col)
		{
			rowVec.emplace_back(sf::Vector2f(MapObject::OBJECT_SIZE.x*(col + .5f), MapObject::OBJECT_SIZE.y*(row + .5f)), MapObject(MapObject::ObjectType::wall));
			rowVec[col].second.SetPosition(rowVec[col].first);
		}
		mapGrid.push_back(rowVec);
	}
}

void WorldMap::Click(MapObject& obj)
{
	sf::Vector2i node = GetIndex(obj.GetPos());
	mapGrid[node.y][node.x].second.ChangeType(obj.GetType());
}

bool WorldMap::HandleEvents(const sf::Event& someEvent)
{
	return false;
}

void WorldMap::Draw()
{
	for (auto& row : mapGrid)
		for (auto& col : row)
			col.second.Draw();
}

void WorldMap::Save()
{
	static int i=0;
	i++;
	std::ofstream saveFile;
	saveFile.open("Maps/map" + std::to_string(i) + ".tm");

	//this stores rows as continous numbers, but isn't an issue as long as there aren't more than 10 different mapobject types
	for (auto& row : mapGrid)
	{
		for (auto& col : row)
		{
			saveFile << col.second.GetType();
		}
		saveFile << std::endl;
	}

	saveFile.close();
}

void WorldMap::Update()
{
}

void WorldMap::Show(bool b)
{
}

const sf::Vector2f& WorldMap::ClosestNode(const sf::Vector2f& pos)
{
	sf::Vector2i node = GetIndex(pos);
	return mapGrid[node.y][node.x].first;
}

MapObject::ObjectType WorldMap::GetType(int row, int col)
{
	return mapGrid[row][col].second.GetType();
}

const sf::Vector2f& WorldMap::GetLocation(int row, int col)
{
	return mapGrid[row][col].first;
}

const sf::Vector2i WorldMap::GetIndex(const sf::Vector2f& location)
{
	int x = location.x/MapObject::OBJECT_SIZE.x - 1/2;
	int y = location.y/MapObject::OBJECT_SIZE.y - 1/2;
	return sf::Vector2i((x > MAP_SIZE.x - 1) ? MAP_SIZE.x - 1 : x ,(y > MAP_SIZE.y - 1) ? MAP_SIZE.y - 1 : y);
}

void WorldMap::Reset()
{
	for (auto& row : mapGrid)
		for (auto& col : row)
			col.second.ChangeType(MapObject::ObjectType::wall);
}

void WorldMap::Load(const std::string& fileName)
{
	std::ifstream mapFile(fileName);
	std::string row;
	if (mapFile.is_open())
	{
		int i=0;
		int j=0;
		//read in a whole line
		while(mapFile >> row)
		{
			//iterate through individual numbers in the line, reading them as a type and storing them to the corresponding node
			for(int type : row)
			{
				mapGrid[i][j].second.ChangeType(static_cast<MapObject::ObjectType>(type));
				++j;
			}
			++i;
		}
	}
	else std::cout<<"Couldn't open map."<<std::endl;

}