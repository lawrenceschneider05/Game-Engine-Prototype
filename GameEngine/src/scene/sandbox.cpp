#include "sandbox.h"
#include "physics/physicsbody.h"
#include <log/logger.h>
#include "rendering/renderer.h"
#include "input/input.h"

namespace GameEngine
{
	Sandbox::Sandbox(Camera* _camera) : player(0,128,16,32, this), IWorld(_camera)
	{
		chunkManager = new ChunkManager();
		pm.addDynamicObject(&player.getPhysicsBody());
		pm.resetStaticColliders(getCM()->getColliders());
		/*for (const Tile& t : tm.getChunk().getTiles())
		{
			pm.addBody(new PhysicsBody({ t.x, t.y, t.w, t.h }, false, true));
		}*/
		/*pm.addBody(new PhysicsBody({ -CHUNK_HEIGHT_PIXELS / 2, -CHUNK_HEIGHT_PIXELS / 2,
			CHUNK_WIDTH_PIXELS, CHUNK_HEIGHT_PIXELS }, false, true));*/
	
	}
	Sandbox::~Sandbox()
	{
		delete chunkManager;
	}

	void Sandbox::update(f32 dt)
	{
		/*if (cm.areChunksUpdated())
		{
			pm.resetStaticColliders(cm.getColliders());
		}*/
		pm.resetStaticColliders(getCM()->getColliders());
		player.update();
		pm.applyPhysics(dt);
	}

	void Sandbox::render()
	{
		getCM()->render();
		player.render();
	}	
}

