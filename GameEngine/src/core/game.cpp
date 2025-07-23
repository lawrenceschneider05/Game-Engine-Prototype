#include "game.h"

namespace GameEngine
{
	Game::Game()
	{
		
	}
	Game::~Game()
	{
		//delete ecs;
	}
	void Game::update(f64 dt)
	{
		sandbox.update(dt);
	}
	void Game::render(f64 dt)
	{
		sandbox.render();
	}
}