#pragma once
#include "entity.h"
#include "systemmanager.h"
#include "componentmanager.h"
#include "types.h"
#include "signatures.h"

namespace GameEngine
{
	class ECSManager
	{
	public:
		ECSManager();
		void init();
		Entity addEntity();
		
		template <typename T>
		void addComponent(Entity e, const T& c)
		{
			cm.addComponent<T>(e, c);
			sm.onComponentChange();
		}

		template <typename T>
		void removeComponent(Entity e)
		{
			cm.removeComponent<T>(e);
			sm.onComponentChange();
		}

		template <typename T>
		const T& getComponent(Entity e)
		{
			return *cm.getComponent<T>(e);
		}

		void update(f64 dt);

		vector<Entity> getFilteredEntities(Signature bitmask)
		{
			vector<Entity> entities{};
			for (Entity e = 0; e < size; e++)
			{
				if ((bitmask & cm.getEntityBitmask(e)) == bitmask)
				{
					entities.push_back(e);
				}
			}
			return entities;
		}
	private:
		ComponentManager cm;
		SystemManager sm;
		Entity size;

		
	};
}