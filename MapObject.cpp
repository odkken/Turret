#include "stdafx.h"
#include "MapObject.h"

const sf::Vector2i MapObject::OBJECT_SIZE(32,32);

MapObject::MapObject(MapObject::ObjectType object) : thisObject(object), isShowing(true)
{
	shape.setSize(sf::Vector2f(32,32));
	shape.setOrigin(shape.getGlobalBounds().width/2, shape.getGlobalBounds().height/2);
	UpdateImage();
}

void MapObject::UpdateImage()
{
	switch (thisObject)
	{
	case MapObject::wall:
		shape.setFillColor(sf::Color::Black);
		shape.setOutlineThickness(-1);
		shape.setOutlineColor(sf::Color::White);
		break;
	case MapObject::path:
		shape.setFillColor(sf::Color::Yellow);
		shape.setOutlineThickness(0);
		break;
	case MapObject::empty:
		shape.setFillColor(sf::Color::Red);
		shape.setOutlineThickness(-1);
		shape.setOutlineColor(sf::Color::Black);
		break;
	case MapObject::spawn:
		shape.setFillColor(sf::Color::Green);
		shape.setOutlineThickness(-1);
		shape.setOutlineColor(sf::Color::Magenta);
		break;
	case MapObject::exit:
		shape.setFillColor(sf::Color::Magenta);
		shape.setOutlineThickness(-4);
		shape.setOutlineColor(sf::Color::Blue);
		break;
	default:
		break;
	}
}

void MapObject::Draw()
{
	if(isShowing)
		Game::Instance()->mainWindow_.draw(shape);
}

bool MapObject::HandleEvents(const sf::Event& someEvent)
{
	return false;
}

void MapObject::Update()
{
}

void MapObject::ChangeType(MapObject::ObjectType newType)
{
	thisObject=newType;
	UpdateImage();
}

void MapObject::SetPosition(const sf::Vector2f& pos)
{
	shape.setPosition(sf::Vector2f(pos));
}

const sf::Vector2f& MapObject::GetPos()
{
	return shape.getPosition();
}

void MapObject::Show(bool b)
{
	isShowing=b;
}