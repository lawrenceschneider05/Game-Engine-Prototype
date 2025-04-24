#include "physics.h"
#include <iostream>

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

	cout << obj.x << " " << obj.vx << " " << obj.y << " " << obj.vy << "\n";
}

void GameEngine::Physics::processCollisions(PhysicsObject& obj, vector<PhysicsObject> objects, f64 dt)
{
}

void GameEngine::Physics::resolveCollision(PhysicsObject& one, PhysicsObject& two, f64 dt)
{
}
