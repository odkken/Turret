#include "stdafx.h"
#include "GameState.h"

GameState::GameState()
{
}


//default event handling
void GameState::HandleEvents()
{
	sf::Event gameEvent;
	if((Game::Instance()->mainWindow_.pollEvent(gameEvent) && gameEvent.type==sf::Event::Closed) || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		Game::Instance()->mainWindow_.close();

	for(auto& object : objects)
	{
		object->HandleEvents(gameEvent);
	}
}
void GameState::Update(){}
void GameState::Draw()
{
	for(auto& object : objects)
	{
		object->Draw();
	}

	Game::Instance()->mainWindow_.display();
}

void GameState::ChangeState (GameState* newState)
{
	Game::Instance()->ChangeState(newState);
}