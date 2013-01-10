#include "stdafx.h"
#include "ShowingDoors.h"
#include "MyAlgorithms.h"
#include "Debugger.h"

GameState* ShowingDoors::instance_ = 0;

ShowingDoors::ShowingDoors(Game* game) : chosenDoor(-1), revealDoor(-1), selectionState(unselected), uid(0,2)
{
	font.loadFromFile("fonts/segoesc.ttf");
	bottomText.setFont(font);
	topText.setFont(font);
	bgImg.loadFromFile("images/The+Doors.png");
	background.setTexture(bgImg);
	bossDoor=uid(randEng);
	//create doors, using random number to place boss
	for (int i=0; i<3; i++)
	{
		doors.emplace_back((i+1)*game->mainWindow_.getSize().x/4, game->mainWindow_.getSize().y/2, game->Level(), (i==bossDoor));
	}
}

void ShowingDoors::HandleEvents(Game* game)
{
	eventClock.restart();
	sf::Event someEvent;
	if(game->mainWindow_.pollEvent(someEvent) && someEvent.type==sf::Event::MouseButtonPressed)
	{
		//handle clicking on a door
		int i=0;
		for (auto& door : doors)
		{
			if (MyAlgorithms::IsWithin(sf::Mouse::getPosition(game->mainWindow_), door.GetShape()) && selectionState==unselected)//if the click was on the door and you haven't selected one yet
			{
				door.Select(true);
				chosenDoor=i;
				RevealDoor();
				selectionState=selected_first;
				++i;
			}
		}

		//handle other stuff
	}

	if((someEvent.type==sf::Event::Closed) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		game->mainWindow_.close();
	Debugger::Instance()->AddLine("EventClock: " + std::to_string(eventClock.getElapsedTime().asMicroseconds()));
}
void ShowingDoors::Update(Game* game)
{
	updateClock.restart();
	switch(selectionState)
	{
	case unselected:

		bottomText.setString("Choose wisely...");
		bottomText.setPosition(game->mainWindow_.getSize().x/2 - bottomText.getGlobalBounds().width/2, game->mainWindow_.getSize().y - 50);

		//update doors (highlight)
		for (auto& door : doors)
		{
			if (MyAlgorithms::IsWithin(sf::Mouse::getPosition(game->mainWindow_), door.GetShape()))
				door.MouseOver(true);
			else
				door.MouseOver(false);
		}
		break;


	case selected_first:
		bottomText.setString("Keep it?");
		bottomText.setPosition(game->mainWindow_.getSize().x/2 - bottomText.getGlobalBounds().width/2, game->mainWindow_.getSize().y - 100);

		break;
	}
	topText.setString("Level " + std::to_string(game->Level()));



	//eventually needs to enter battle (change state to inbattle), battlestate returns here, then reset all the shit.

	Debugger::Instance()->AddLine("UpdateClock: " + std::to_string(updateClock.getElapsedTime().asMicroseconds()));
}
void ShowingDoors::Draw(Game* game)
{
	
	game->mainWindow_.clear();
	drawClock.restart();
	//game->mainWindow_.draw(background);
	for (auto& door : doors)
	{
		
		//game->mainWindow_.draw(door.GetMonster().GetImage());
		game->mainWindow_.draw(door.GetShape());
		game->mainWindow_.draw(door.doorText);
	}
	game->mainWindow_.draw(topText);
	game->mainWindow_.draw(bottomText);
	Debugger::Instance()->AddLine("DrawClock: " + std::to_string(drawClock.getElapsedTime().asMicroseconds()));
	Debugger::Instance()->Draw(game->mainWindow_);
	game->mainWindow_.display();
	
}


//seems like a lot of fuss but if you just iterate through and open the first suitable door you'll introduce an exploit
void ShowingDoors::RevealDoor()
{
	//create a list of possible doors to reveal, the requirements being they aren't the chosen door and they don't have a boss behind them
	std::vector<int> chooseFrom;
	for(int i=0; i<3; ++i)
		if (i!=chosenDoor && i!=bossDoor)
			chooseFrom.push_back(i);

	std::uniform_int_distribution<int>::param_type pt(0,chooseFrom.size()-1);
	uid.param(pt);//resize our distribution to only be the # of possible doors to open (1 or 2)
	
	//open a random door (or the only door)
	revealDoor=chooseFrom[uid(randEng)];
	doors[revealDoor].Open();
}


GameState* ShowingDoors::Instance(Game* game)
{
	if(instance_ == 0)
		instance_ = new ShowingDoors(game);
	return instance_;
}