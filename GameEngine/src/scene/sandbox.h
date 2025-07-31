#pragma once
#include "iscene.h"
#include "entities/player.h"
#include "chunks/chunkmanager.h"
#include "physics/physicsmanager.h"

namespace GameEngine
{
	class Sandbox : public IWorld
	{
	public:
		Sandbox(Camera*);
		~Sandbox();
		void update(f32 dt) override;
		void render() override;

		inline ChunkManager* getCM()
		{
			return (ChunkManager*)chunkManager;
		}
	private:
		Player player;
		PhysicsManager pm;
	};
}