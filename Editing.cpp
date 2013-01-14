#include "stdafx.h"
#include "Editing.h"
#include "Playing.h"

Editing* Editing::instance_ = 0;

Editing* Editing::Instance()
{
	if(instance_ == 0)
		instance_ = new Editing;
	return instance_;
}

Editing::Editing() : mouseObject(MapObject::ObjectType::wall)
{
	buttons.emplace_back("Reset", []{Editing::Instance()->GetMap().Reset();}, 800, 550);
	buttons.emplace_back("Save", []{Editing::Instance()->GetMap().Save();}, 800, 600);
	buttons.emplace_back("Load", []
	{
		std::string x; 
		std::cout<<"Enter a map file (Maps/map#.tm)"<<std::endl;
		std::cin>>x;
		Editing::Instance()->GetMap().Load(x);
	}, 800, 650);
	buttons.emplace_back("Play", [this]{
		this->ChangeState(Playing::Instance());
		Playing::Instance()->Reset();
	}, 800, 700);
}

WorldMap& Editing::GetMap()
{
	return map;
}

void Editing::Draw()
{
	map.Draw();
	for(auto& button : buttons)
		button.Draw();
	mouseObject.Draw();
}

void Editing::Update()
{
	for (auto& button : buttons)
		button.Update();
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

	//only paint if the click was within the grid
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && sf::Mouse::getPosition(Game::Instance()->mainWindow_).x<map.MAP_DIMS.x && sf::Mouse::getPosition(Game::Instance()->mainWindow_).y < map.MAP_DIMS.y)
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

	for	(auto& button : buttons)
		button.HandleEvents(someEvent);

}