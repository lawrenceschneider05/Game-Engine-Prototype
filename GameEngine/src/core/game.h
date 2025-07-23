#include "types.h"
#include "scene/sandbox.h"
#include <memory>
#include <entities/player.h>
#include <scene/sandbox.h>

using std::unique_ptr;

namespace GameEngine
{
	class Game
	{
	public:
		Game();
		~Game();

		void update(f64 dt);
		void render(f64 dt);
	private:
		
		Sandbox sandbox;
	};
}