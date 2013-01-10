#pragma once
class GameState;
class Game
{
public:
	static Game* Instance();
	static const int SCREEN_WIDTH=1024;
	static const int SCREEN_HEIGHT=768;
	sf::RenderWindow mainWindow_;
	bool debug;
	void Loop();
	
private:
	Game();
	static Game* instance_;
	
	sf::Clock gameClock;
	friend class GameState;
	void ChangeState(GameState*);
	int level_;
	GameState* state_;
	void HandleEvents();
	void Update();
	void Draw();
};