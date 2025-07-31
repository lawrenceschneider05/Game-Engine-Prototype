#pragma once
#include "types.h"
#include "physicsbody.h"

namespace GameEngine
{
	class Physics
	{
	public:
		static void applyGravity(PhysicsBody* pb, f64 dt);
		static void integrate(PhysicsBody* pb, f64 dt);
	};
}