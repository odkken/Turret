#include "stdafx.h"
#include "ClickableText.h"
#include "Resources.h"
#include "MyAlgorithms.h"

ClickableText::ClickableText(const std::string& message, std::function<void()> func, int x, int y, const sf::Color& color) : text(message, Resources::Instance()->FontBank("Arial"), 30), OnClick(func)
{
	text.setColor(color);
	SetPosition(x,y);
}

bool ClickableText::HandleEvents(const sf::Event& someEvent)
{
	if(isShowing)
	{
		if(someEvent.type==sf::Event::MouseButtonPressed && MyAlgorithms::IsWithin(sf::Mouse::getPosition(Game::Instance()->mainWindow_), text))
		{
			OnClick();
			return true;
		}
		if(someEvent.type==sf::Event::MouseMoved && MyAlgorithms::IsWithin(sf::Mouse::getPosition(Game::Instance()->mainWindow_), text))
		{
			MouseOver(true);
			return true;
		}
		else
			MouseOver(false);

		return false;

	}
}

void ClickableText::Update()
{
	if (MyAlgorithms::IsWithin(sf::Mouse::getPosition(Game::Instance()->mainWindow_), text))
	{
		MouseOver(true);
	}

	else MouseOver(false);
}

void ClickableText::Draw()
{
	if(isShowing)
		Game::Instance()->mainWindow_.draw(text);
}


//centers to position
void ClickableText::SetPosition(float x, float y)
{
	text.setPosition(x-text.getGlobalBounds().width/2,y);
}

void ClickableText::MouseOver(bool b)
{
	if (b)
		text.setColor(sf::Color::Red);
	else
		text.setColor(sf::Color::White);
}


void ClickableText::Show(bool b)
{
	isShowing=b;
}