#include "game.h"
#include "input/input.h"

namespace GameEngine
{
	Game::Game(Camera& _camera) : camera(_camera), sandbox(&_camera)
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