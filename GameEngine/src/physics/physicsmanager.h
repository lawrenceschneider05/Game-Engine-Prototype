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
		~PhysicsManager();
		void applyPhysics(f32 dt);


		inline void addDynamicObject(PhysicsBody* pb)
		{
			dynamicObjects.push_back(pb);
		}

		

		inline void resetStaticColliders(const vector<AABB>& colliders)
		{
			staticObjects.clear();
			addStaticColliders(colliders);
		}
	private:
		inline void addStaticColliders(const vector<AABB>& colliders)
		{
			//staticObjects.insert(staticObjects.end(), colliders.begin(), colliders.end());

			for (const auto& collider : colliders)
			{
				staticObjects.push_back(collider);
			}
		}
	private:
		vector<AABB> staticObjects{};
		vector<PhysicsBody*> dynamicObjects{};
		vector<Collision> collisions{};

		void applyGravity(f64 dt);
		void integrate(f64 dt);

		void detectCollisions(f32 dt);
		void resolveCollisions(f32 dt);

		void resetGroundState();

		void resolveStaticDynamicCollision(const AABB& staticObject, PhysicsBody& dynamicObject);
	};
}