#pragma once
#include "isystem.h"

namespace GameEngine
{
	class PhysicsSystem : public ISystem
	{
	public:
		PhysicsSystem(ComponentManager& _cm) : ISystem(_cm) {}
		~PhysicsSystem();
		void init() override;
		void update(f64 dt) override;
		void onComponentChanged() override;
	private:
	};
}