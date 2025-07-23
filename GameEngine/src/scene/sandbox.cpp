#include "sandbox.h"
#include "physics/physicsbody.h"
#include <log/logger.h>
#include "rendering/renderer.h"

namespace GameEngine
{
	Sandbox::Sandbox() : player(0,200,16,32)
	{
		pm.addBody(&player.getPhysicsBody());

		/*for (const Tile& t : tm.getChunk().getTiles())
		{
			pm.addBody(new PhysicsBody({ t.x, t.y, t.w, t.h }, false, true));
		}*/
		/*pm.addBody(new PhysicsBody({ -CHUNK_HEIGHT_PIXELS / 2, -CHUNK_HEIGHT_PIXELS / 2,
			CHUNK_WIDTH_PIXELS, CHUNK_HEIGHT_PIXELS }, false, true));*/
	}

	void Sandbox::update(f32 dt)
	{
		player.update();
		pm.applyPhysics(dt);
	}

	void Sandbox::render()
	{
		tm.render();
		player.render();
	}	
}

