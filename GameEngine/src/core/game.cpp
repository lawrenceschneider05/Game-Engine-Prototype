#include "game.h"

namespace GameEngine
{
	Game::Game()
	{
		EntityFactory factory = EntityFactory();
		ecs = factory.init();
	}
	void Game::update(f64 dt)
	{
		ecs->update(dt);
	}
	void Game::render()
	{
		tm.render();
		ecs->render();
	}
}