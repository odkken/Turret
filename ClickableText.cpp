#include "stdafx.h"
#include "ClickableText.h"
#include "Resources.h"
#include "MyAlgorithms.h"
#include "Debugger.h"

ClickableText::ClickableText(const std::string& message, std::function<void()> func, int x, int y) : text(message, Resources::Instance()->FontBank("Arial"), 30), OnClick(func), isShowing(true), isMousedOver(false)
{
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
		if(MyAlgorithms::IsWithin(sf::Mouse::getPosition(Game::Instance()->mainWindow_), text)) //if your mouse is over the button
		{
			if(!isMousedOver) //and you weren't already moused over
			{
				text.setColor(sf::Color::Red);
				isMousedOver=true;
			}
		}
		else if(isMousedOver) //if you were moused over
		{
			text.setColor(sf::Color::White);
			isMousedOver=false;
		}
		return false;

	}
}

void ClickableText::Update()
{
	//isMousedOver ? text.setColor(sf::Color::Red) : text.setColor(sf::Color::White);
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
	isMousedOver=b;
}


void ClickableText::Show(bool b)
{
	isShowing=b;
}

sf::Text& ClickableText::GetText()
{
	return text;
}