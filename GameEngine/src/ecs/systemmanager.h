#pragma once
#include <vector>
#include <memory>
#include "isystem.h"
#include "types.h"
#include "componentmanager.h"
#include "physicssystem.h"


using std::vector;

using std::unique_ptr;
using std::move;
using std::make_unique;

namespace GameEngine
{
	class SystemManager
	{
	public:
		SystemManager(ComponentManager& _cm) : cm(_cm)
		{

		}

		void init()
		{
			systemArray.emplace_back((ISystem*)(new PhysicsSystem(cm)));
		}
		inline void update(f64 dt)
		{
			for (auto& s : systemArray)
			{
				s->update(dt);
			}
		}
		void onComponentChange()
		{
			for (auto& s : systemArray)
			{
				s->onComponentChanged();
			}
		}
	private:
		ComponentManager& cm;
		vector<unique_ptr<ISystem>> systemArray{};
	};
}