#pragma once
#include "iscene.h"
#include "entities/player.h"
#include "chunks/chunkmanager.h"
#include "physics/physicsmanager.h"

namespace GameEngine
{
	class Sandbox : public IScene
	{
	public:
		Sandbox();
		void update(f32 dt) override;
		void render() override;
	private:
		Player player;
		ChunkManager tm;
		PhysicsManager pm;
	};
}