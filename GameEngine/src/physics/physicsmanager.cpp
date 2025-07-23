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
		//applyGravity(dt);
		integrate(dt);
		detectCollisions(dt);
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
			else if (c.pb1.isStatic && !c.pb2.isStatic)
			{
				if (c.pb2.motion.vy != 0)
				{
					// find overlap
					f32 overlap = std::max(0.0f, std::min(c.pb1.aabb.y + c.pb1.aabb.h, c.pb2.aabb.y + c.pb2.aabb.h) - std::max(c.pb1.aabb.y, c.pb2.aabb.y));

					if (c.pb2.motion.vy > 0)
					{
						c.pb2.aabb.y -= overlap;
					}
					else
					{
						c.pb2.aabb.y += overlap;
					}
					c.pb2.motion.vy = 0;
					c.pb2.motion.ay = 0;
					c.pb2.grounded = true;
				}
				// case two moving right
				// cost three moving up
				// cost four moving down
			}
			else if (!c.pb1.isStatic && c.pb2.isStatic)
			{
				if (c.pb1.motion.vy != 0)
				{
					// find overlap
					f32 overlap = std::max(0.0f, std::min(c.pb1.aabb.y + c.pb1.aabb.h, c.pb2.aabb.y + c.pb2.aabb.h) - std::max(c.pb1.aabb.y, c.pb2.aabb.y));
					//f32 overlap = std::abs((c.pb1.aabb.y - (c.pb1.aabb.h / 2)) - (c.pb2.aabb.y - (c.pb2.aabb.h / 2)));

					if (c.pb1.motion.vy > 0)
					{
						c.pb1.aabb.y -= overlap;
					}
					else
					{
						c.pb1.aabb.y += overlap;
					}
					c.pb1.motion.vy = 0;
					c.pb1.motion.ay = 0;
					c.pb1.grounded = true;

				}
			}
			// implement later
			else if (!c.pb1.isStatic && !c.pb2.isStatic)
			{
				// find direction
				f32 relativeVelocity = c.pb1.motion.vx - c.pb2.motion.vx;
			}
		}
		collisions.clear();
	}
}