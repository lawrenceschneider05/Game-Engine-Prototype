#pragma once
#include "ecs/entities/ecsmanager.h"
#include <memory>

using std::unique_ptr;

namespace GameEngine
{
	class EntityFactory
	{
	public:
		EntityFactory();
		unique_ptr<ECSManager> init(TileManager& tm);
	private:
		void initPlayer(unique_ptr<ECSManager>& ecs);
	};
}

