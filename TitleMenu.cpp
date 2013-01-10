#include "stdafx.h"
#include "TitleMenu.h"
#include "MyAlgorithms.h"
#include "ShowingDoors.h"
#include <utility>

GameState* TitleMenu::instance_ = 0;
GameState* TitleMenu::Instance(Game* game)
{
	if(instance_ == 0)
		instance_ = new TitleMenu(game);

	return instance_;
}

TitleMenu::TitleMenu(Game* game) : BUTTON_SPACING(50)
{
	titleMenuFont.loadFromFile("fonts/segoesc.ttf");

	//create buttons and put them into the list
	buttons.emplace_back(sf::Text("Play", titleMenuFont, 30), [this, game]{this->ChangeState(game,ShowingDoors::Instance(game));});
	buttons.emplace_back(sf::Text("Exit", titleMenuFont, 30), [game]{game->mainWindow_.close();});
	for (unsigned int i=0; i<buttons.size(); ++i)
	{
		MyAlgorithms::CenterOrigin(buttons[i].first);
		buttons[i].first.setPosition(game->mainWindow_.getSize().x/2, game->mainWindow_.getSize().y/2 + i*(BUTTON_SPACING + buttons[i].first.getGlobalBounds().height));
	}

}

void TitleMenu::HandleEvents(Game* game)
{
	sf::Event someEvent;
	if(game->mainWindow_.waitEvent(someEvent) && someEvent.type==sf::Event::MouseButtonPressed)
	{
		for (auto button : buttons)
			if (MyAlgorithms::IsWithin(sf::Mouse::getPosition(game->mainWindow_), button.first))//if the click was on the button
				button.second();//execute the button's function
	}
	if (someEvent.type==sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		game->mainWindow_.close();
}

void TitleMenu::Update(Game* game)
{
	for (auto& button : buttons)
	{
		button.first.setColor(sf::Color::White);
		if (MyAlgorithms::IsWithin(sf::Mouse::getPosition(game->mainWindow_), button.first))
			button.first.setColor(sf::Color::Red);
	}
}

void TitleMenu::Draw(Game* game)
{
	game->mainWindow_.clear();

	for (auto button : buttons)
		game->mainWindow_.draw(button.first);

	game->mainWindow_.display();
}