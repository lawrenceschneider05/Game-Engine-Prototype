#include "types.h"
#include "tiles/tilemanager.h"
#include "ecs/entities/ecsmanager.h"
#include "entityfactory.h"
#include <memory>

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
		unique_ptr<ECSManager> ecs;
		TileManager tm;

	};
}