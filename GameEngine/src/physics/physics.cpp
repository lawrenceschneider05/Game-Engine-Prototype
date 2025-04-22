#include "physics.h"

void GameEngine::Physics::applyGravity(PhysicsObject& obj, f64 dt)
{
	obj.ay -= GRAVITY * dt;
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
}

void GameEngine::Physics::resolveCollision(PhysicsObject& one, PhysicsObject& two, f64 dt)
{
}
