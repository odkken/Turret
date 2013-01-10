#include "stdafx.h"
#include "Editing.h"

Editing* Editing::instance_ = 0;

Editing* Editing::Instance()
{
	if(instance_ == 0)
		instance_ = new Editing;
	return instance_;
}

Editing::Editing() :
	mouseObject(MapObject::ObjectType::wall),
	resetButton("Reset", []{Editing::Instance()->GetMap().Reset();}, 800, 600),
	saveButton("Save", []{Editing::Instance()->GetMap().Save();}, 800, 650)
{
}

WorldMap& Editing::GetMap()
{
	return map;
}

void Editing::Draw()
{
	map.Draw();
	resetButton.Draw();
	saveButton.Draw();
	mouseObject.Draw();
}

void Editing::HandleEvents()
{
	sf::Event someEvent;
	if(Game::Instance()->mainWindow_.waitEvent(someEvent) && someEvent.type==sf::Event::MouseMoved)
	{
		mouseObject.SetPosition(map.ClosestNode(sf::Vector2f(someEvent.mouseMove.x,someEvent.mouseMove.y)));
	}

	if(someEvent.type==sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		Game::Instance()->mainWindow_.close();
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		map.Click(mouseObject);

	if(someEvent.type==sf::Event::KeyPressed)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			mouseObject.ChangeType(MapObject::ObjectType::empty);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			mouseObject.ChangeType(MapObject::ObjectType::path);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			mouseObject.ChangeType(MapObject::ObjectType::wall);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			mouseObject.ChangeType(MapObject::ObjectType::spawn);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
			mouseObject.ChangeType(MapObject::ObjectType::exit);

	}

	if(someEvent.type==sf::Event::KeyPressed && someEvent.key.code==sf::Keyboard::D)
		Game::Instance()->debug=!Game::Instance()->debug;

	if(resetButton.HandleEvents(someEvent) || saveButton.HandleEvents(someEvent))
		mouseObject.Show(false);
	else
		mouseObject.Show(true);
}