#include "stdafx.h"
#include "Playing.h"
#include "Editing.h"

Playing* Playing::instance_ = 0;

Playing* Playing::Instance()
{
	if(instance_ == 0)
		instance_ = new Playing;

	return instance_;
}


Playing::Playing() : level(0), running(false), NUM_MONSTERS(10), spawnIndex(0), spawnPoint(PublicMap::Instance()->GetSpawn())
{
	PublicMap::Instance()->Load("Maps/map1.tm");
	monsters.resize(NUM_MONSTERS, level);
	buttons.emplace_back("Edit", [this]{this->ChangeState(Editing::Instance());}, 800, 600);
	buttons.emplace_back("Next Wave", [this]{
		this->running=true;
	}, 800 , 550);
}

void Playing::Update()
{
	//spawn until you've gone through every monster
	if(running)
	{
		if (spawnTimer.getElapsedTime().asSeconds() > 2.0f && spawnIndex!=monsters.size())
		{
			monsters[spawnIndex].Spawn(spawnPoint.y, spawnPoint.x);
			++spawnIndex;
			spawnTimer.restart();
		}

		for (auto& monster : monsters)
			monster.Update();
	}

	for(auto& button : buttons)
		button.Update();

	if (monstersEscaped+monstersKilled==NUM_MONSTERS)
	{
		++level;
		running=false;
		
	}
}

void Playing::HandleEvents()
{
	sf::Event someEvent;
	Game::Instance()->mainWindow_.pollEvent(someEvent);
	for (auto& button : buttons)
		button.HandleEvents(someEvent);

}

void Playing::Draw()
{
	PublicMap::Instance()->Draw();
	for (auto& monster : monsters)
		monster.Draw();
	for (auto& button : buttons)
		button.Draw();
}

void Playing::Reset()
{
	PublicMap::Instance()->Load("Maps/map1.tm");
	for(auto& monster : monsters)
		monster.UnSpawn();
	spawnTimer.restart();
	spawnPoint=PublicMap::Instance()->GetSpawn();


	monstersEscaped=monstersKilled=level=spawnIndex=0;
	running=false;
}