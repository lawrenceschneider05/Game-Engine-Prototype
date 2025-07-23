#pragma once
#include <vector>
#include "physicsbody.h"
#include "collision.h"

using std::vector;

namespace GameEngine
{
	constexpr f32 METER = 128;
	constexpr f32 GRAVITY = METER * 30;
	constexpr f32 TERMINAL_VELOCITY = METER * 100;
	class PhysicsManager
	{
	public:
		
		void applyPhysics(f32 dt);

		inline void addBody(PhysicsBody* pb)
		{
			bodies.push_back(pb);
		}
	private:
		vector<PhysicsBody*> bodies{};
		vector<Collision> collisions{};

		void applyGravity(f64 dt);
		void integrate(f64 dt);

		void detectCollisions(f32 dt);
		void resolveCollisions(f32 dt);

		void resetGroundState();

		void resolveStaticDynamicCollision(const PhysicsBody& staticBody, PhysicsBody& dynamicBody);
	};
}