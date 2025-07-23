#include "physicsmanager.h"
#include <log/logger.h>
#include "glm/glm.hpp"

namespace GameEngine
{
	void PhysicsManager::detectCollisions(f32 dt)
	{
		i16 numCollisions = 0;
		for (int i = 0; i < dynamicObjects.size(); i++)
		{
			for (int j = 0; j < staticObjects.size(); j++)
			{
				if (AABBIsCollision(dynamicObjects[i]->aabb, staticObjects[j]))
				{
					numCollisions++;
					PhysicsBody s = PhysicsBody(staticObjects[j], false, true);
					Collision c = { *dynamicObjects[i], s };
					collisions.push_back(c);
				}
			}
		}
	}

	void PhysicsManager::applyPhysics(f32 dt)
	{
		applyGravity(dt);
		integrate(dt);
		detectCollisions(dt);
		resetGroundState();
		resolveCollisions(dt);
	}



	void PhysicsManager::integrate(f64 dt)
	{
		for (PhysicsBody* pb : dynamicObjects)
		{
			if (pb->isStatic) { continue; }
			pb->motion.vx += pb->motion.ax * dt;
			pb->motion.vy += pb->motion.ay * dt;
			pb->aabb.x += pb->motion.vx * dt;
			pb->aabb.y += pb->motion.vy * dt;
		}
	}
	void PhysicsManager::applyGravity(f64 dt)
	{
		for (PhysicsBody* pb : dynamicObjects)
		{

			if (!pb->gravity && pb->grounded) { continue; }
			if (pb->motion.ay - (GRAVITY * dt) >= -TERMINAL_VELOCITY)
			{
				pb->motion.ay -= (GRAVITY * dt);
			}
			else {
				pb->motion.ay = -TERMINAL_VELOCITY;
			}
		}
	}	

	void PhysicsManager::resolveCollisions(f32 dt)
	{
		for (Collision c : collisions)
		{
			if (c.pb1.isStatic && c.pb2.isStatic)
			{
				continue;
			}
			else if (!c.pb1.isStatic && c.pb2.isStatic)
			{
				resolveStaticDynamicCollision(c.pb2.aabb, c.pb1);
			}
			else if (c.pb1.isStatic && !c.pb2.isStatic)
			{
				resolveStaticDynamicCollision(c.pb1.aabb, c.pb2);
			}
		}
		collisions.clear();
	}
	

	void PhysicsManager::resetGroundState()
	{
		for (PhysicsBody* pb : dynamicObjects)
		{
			if (!pb->isStatic)
			{
				pb->grounded = false;
			}
		}
	}

	void PhysicsManager::resolveStaticDynamicCollision(const AABB& staticCollider, PhysicsBody& dynamicBody)
	{
		AABB& b = dynamicBody.aabb;

		f32 overlapX = std::max(0.0f, std::min(staticCollider.x + staticCollider.w, b.x + b.w) - std::max(staticCollider.x, b.x));
		f32 overlapY = std::max(0.0f, std::min(staticCollider.y + staticCollider.h, b.y + b.h) - std::max(staticCollider.y, b.y));

		if (overlapX > 0 && overlapY > 0)
		{
			if (overlapY < overlapX)
			{
				// Y-axis resolution
				if (b.y + b.h / 2 > staticCollider.y + staticCollider.h / 2)
				{
					// Coming from above
					b.y += overlapY;
					dynamicBody.grounded = true;
				}
				else
				{
					// Coming from below
					b.y -= overlapY;
				}

				dynamicBody.motion.vy = 0;
				dynamicBody.motion.ay = 0;
			}
			else
			{
				// X-axis resolution
				if (b.x + b.w / 2 < staticCollider.x + staticCollider.w / 2)
				{
					b.x -= overlapX;
				}
				else
				{
					b.x += overlapX;
				}

				dynamicBody.motion.vx = 0;
				dynamicBody.motion.ax = 0;
			}
		}
	}

}