#pragma once

//singleton which accepts and draws messages to the upper right hand corner of the screen
class Debugger
{
public:
	static Debugger* Instance();
	void Draw(sf::RenderWindow& window);
	void AddLine(const sf::String& message);

protected:
	Debugger();

private:
	static Debugger* instance_;
	sf::Font debugFont;
	sf::Text debugText;
	sf::String debugString;
};

