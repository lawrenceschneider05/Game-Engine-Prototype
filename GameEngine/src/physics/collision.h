#pragma once
#include "physicsbody.h"

namespace GameEngine
{
	struct Collision
	{
		PhysicsBody& pb1, pb2;

		Collision(PhysicsBody& _pb1, PhysicsBody& _pb2) : 
			pb1(_pb1), pb2(_pb2) {}
	};
}
