#pragma once
#include "types.h"
#include "componentmanager.h"
#include <vector>

using std::vector;

namespace GameEngine
{
	class ISystem
	{
	public:
		ISystem(ComponentManager& _cm) : cm(_cm) {}
		virtual ~ISystem() = default;
		virtual void init() = 0;
		virtual void update(f64 dt) = 0;
		virtual void onComponentChanged() = 0;
	protected:
		ComponentManager& cm;
		vector<Entity> entities;
		Signature signature;
	};
}