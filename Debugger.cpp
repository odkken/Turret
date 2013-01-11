#include "stdafx.h"
#include "Debugger.h"
#include "Resources.h"

Debugger* Debugger::instance_ = 0;

Debugger* Debugger::Instance()
{
	if(instance_ == 0)
		instance_ = new Debugger;

	return instance_;
}

Debugger::Debugger()
{
	debugText.setFont(Resources::Instance()->FontBank("Arial"));
	debugText.setString(debugString);
}

void Debugger::AddLine(const sf::String& line)
{
	debugString += line + "\n";
}

void Debugger::Draw(sf::RenderWindow& window)
{
	debugText.setString(debugString);
	window.draw(debugText);
	debugString=""; //clears the debugger after each loop to facilitate the addline method
}