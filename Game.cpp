#include "stdafx.h"
#include "Game.h"
#include "Editing.h"
#include "Debugger.h"
#include "Playing.h"
Game::Game() : mainWindow_(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "RPG"), level_(0), debug(false)
{
	state_ = Playing::Instance();
}

Game* Game::instance_ = 0;

Game* Game::Instance()
{
	if(instance_ == 0)
		instance_ = new Game;

	return instance_;
}

void Game::ChangeState(GameState* s)
{
	state_=s;
}

void Game::HandleEvents()
{
	state_->HandleEvents();
}

void Game::Update()
{
	state_->Update();
}

void Game::Draw()
{
	Game::Instance()->mainWindow_.clear();
	state_->Draw();
	if(debug) Debugger::Instance()->Draw(mainWindow_);
	mainWindow_.display();
}

void Game::Loop()
{

	//add lines to the static debugger every time (since they get overridden each loop)... probably a faster way to implement the debugger but this works for now.
	while(mainWindow_.isOpen())
	{
		Debugger::Instance()->AddLine("Draw: " + std::to_string(gameClock.restart().asMicroseconds()));
		HandleEvents();
		Debugger::Instance()->AddLine("Event: " + std::to_string(gameClock.restart().asMicroseconds()));
		Update();
		Debugger::Instance()->AddLine("Update: " + std::to_string(gameClock.restart().asMicroseconds()));
		Draw();
	}
}