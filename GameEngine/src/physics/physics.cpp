#include "physics.h"
#include <iostream>
#include <log/logger.h>
#include "rendering/renderer.h"

using std::cout;

void GameEngine::Physics::applyGravity(PhysicsObject& obj, f64 dt)
{
	if (obj.vy >= -TERMINAL_VELOCITY * dt)
	{
		obj.ay -= GRAVITY * dt;
	}
	else {
		obj.ay = 0;
	}
}

void GameEngine::Physics::processMovement(PhysicsObject& obj, f64 dt)
{
	obj.vx += obj.ax * dt;
	obj.x += obj.vx * dt;

	obj.vy += obj.ay * dt;
	obj.y += obj.vy * dt;
}

void GameEngine::Physics::processCollisions(PhysicsObject& obj, vector<PhysicsObject> objects, f64 dt)
{
	for (PhysicsObject p : objects)
	{
		if (isCollision(obj, p, dt))
		{
			resolveCollision(obj, p, dt);
		}
	}
}

void GameEngine::Physics::resolveCollision(PhysicsObject& one, PhysicsObject& two, f64 dt)
{
    // Compute centers
    f64 oneCenterX = one.x + one.w / 2.0;
    f64 oneCenterY = one.y + one.h / 2.0;
    f64 twoCenterX = two.x + two.w / 2.0;
    f64 twoCenterY = two.y + two.h / 2.0;

    // Calculate difference and penetration on both axes
    f64 dx = oneCenterX - twoCenterX;
    f64 dy = oneCenterY - twoCenterY;

    f64 px = (one.w + two.h) / 2.0 - std::abs(dx);
    f64 py = (one.w + two.h) / 2.0 - std::abs(dy);

    if (px <= 0 || py <= 0) {
        return; // No collision to resolve
    }

    // Resolve along the axis of least penetration
    if (px < py) {
        // Horizontal collision
        if (dx > 0) {
            one.x += px;  // Move one to the right
        }
        else {
            one.x -= px;  // Move one to the left
        }
        one.vx = 0;
        one.ax = 0;
    }
    else {
        // Vertical collision
        if (dy > 0) {
            one.y += py;  // Move one down
        }
        else {
            one.y -= py;  // Move one up
        }
        one.vy = 0;
        one.ay = 0;
    }
}



bool GameEngine::Physics::isCollision(PhysicsObject one, PhysicsObject two, f64 dt)
{
	f32 oneNextX = one.x + one.vx * dt + 0.5f * one.ax * dt;
	f32 oneNextY = one.y + one.vy * dt + 0.5f * one.ay * dt;
	f32 twoNextX = two.x + two.vx * dt + 0.5f * two.ax * dt;
	f32 twoNextY = two.y + two.vy * dt + 0.5f * two.ay * dt;

	return (oneNextX < twoNextX + two.w) &&
		(oneNextX + one.w > twoNextX) &&
		(oneNextY < twoNextY + two.h) &&
		(oneNextY + one.h > twoNextY);
}