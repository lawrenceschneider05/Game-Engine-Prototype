#include "physicsmanager.h"
#include <log/logger.h>
#include "glm/glm.hpp"

namespace GameEngine
{
	void PhysicsManager::detectCollisions(f32 dt)
	{
		i16 numCollisions = 0;
		for (int i = 0; i < bodies.size() - 1; i++)
		{
			for (int j = i + 1; j < bodies.size(); j++)
			{
				if (AABBIsCollision(bodies[i]->aabb, bodies[j]->aabb))
				{
					numCollisions++;
					Collision c = { *bodies[i], *bodies[j] };
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
		for (PhysicsBody* pb : bodies)
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
		for (PhysicsBody* pb : bodies)
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
				resolveStaticDynamicCollision(c.pb2, c.pb1);
			}
			else if (c.pb1.isStatic && !c.pb2.isStatic)
			{
				resolveStaticDynamicCollision(c.pb1, c.pb2);
			}
		}
		collisions.clear();
	}
	

	void PhysicsManager::resetGroundState()
	{
		for (PhysicsBody* pb : bodies)
		{
			if (!pb->isStatic)
			{
				pb->grounded = false;
			}
		}
	}

	void PhysicsManager::resolveStaticDynamicCollision(const PhysicsBody& staticBody, PhysicsBody& dynamicBody)
	{
		const AABB& a = staticBody.aabb;
		AABB& b = dynamicBody.aabb;

		f32 overlapX = std::max(0.0f, std::min(a.x + a.w, b.x + b.w) - std::max(a.x, b.x));
		f32 overlapY = std::max(0.0f, std::min(a.y + a.h, b.y + b.h) - std::max(a.y, b.y));

		if (overlapX > 0 && overlapY > 0)
		{
			if (overlapY < overlapX)
			{
				// Y-axis resolution
				if (b.y + b.h / 2 > a.y + a.h / 2)
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
				if (b.x + b.w / 2 < a.x + a.w / 2)
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