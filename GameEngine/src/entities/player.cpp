#include "player.h"
#include "rendering/renderer.h"
#include "input/input.h"

namespace GameEngine
{
	Player::Player(f32 x, f32 y, f32 w, f32 h, IWorld* _world) : IActor(true, x, y, w, h), world(_world)
	
	{

	}

	void Player::update()
	{
		if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			Coordinate c = world->camera->ScreenToWorld(Input::getMousePosition());
			world->chunkManager->removeBlock(c);
		}
		if (Input::isKeyPressed(GLFW_KEY_A))
		{
			shouldMoveLeft = true;
			isMovingRight = false;
		}
		else
		{
			shouldMoveLeft = false;
		}
		if (Input::isKeyPressed(GLFW_KEY_D))
		{
			shouldMoveRight = true;
			isMovingLeft = false;
		}
		else
		{
			shouldMoveRight = false;
		}
		if (Input::isKeyPressed(GLFW_KEY_W))
		{
			shouldJump = true;
		}
		else
		{
			shouldJump = false;
		}
		moveLeft();
		moveRight();
		jump();
	}

	void Player::render()
	{
		Renderer::drawQuad({ x(), y() }, { w(), h() }, { 0,0,0,1 });
	}

	void Player::moveLeft()
	{
		if (shouldMoveLeft)
		{
			applyHorizontalAcceleration(-MOVEMENT_ACCELERATION);
			if (!isMovingLeft)
			{
				applyHorizontalVelocity(-HORIZONTAL_INITIAL_VELOCITY);
			}
			isMovingLeft = true;

			if (vx() < -MAX_HORIZONTAL_VELOCITY)
			{
				setHorizontalAcceleration(0);
				setHorizontalVelocity(-MAX_HORIZONTAL_VELOCITY);
			}
		}
		
		else
		{
			if (isMovingLeft && vx() < -MAX_HORIZONTAL_VELOCITY)
			{
				setHorizontalAcceleration(0);
				setHorizontalVelocity(-MAX_HORIZONTAL_VELOCITY);
			}
			if (isMovingLeft && vx() < 0 && !isMovingRight)
			{
				applyHorizontalAcceleration(MOVEMENT_DEACCELERATION);
			}
			if (isMovingLeft && vx() > 0 && !isMovingRight)
			{
				setHorizontalVelocity(0);
				setHorizontalAcceleration(0);
				isMovingLeft = false;
			}
		}
	}

	void Player::moveRight()
	{
		if (shouldMoveRight)
		{
			applyHorizontalAcceleration(MOVEMENT_ACCELERATION);
			if (!isMovingRight)
			{
				applyHorizontalVelocity(HORIZONTAL_INITIAL_VELOCITY);
			}
			isMovingRight = true;

			if (vx() > MAX_HORIZONTAL_VELOCITY)
			{
				setHorizontalAcceleration(0);
				setHorizontalVelocity(MAX_HORIZONTAL_VELOCITY);
			}
		}
		else
		{
			if (isMovingRight && vx() > MAX_HORIZONTAL_VELOCITY)
			{
				setHorizontalAcceleration(0);
				setHorizontalVelocity(MAX_HORIZONTAL_VELOCITY);
			}
			if (isMovingRight && vx() > 0 && !isMovingLeft)
			{
				applyHorizontalAcceleration(-MOVEMENT_DEACCELERATION);
			}
			if (isMovingRight && vx() < 0 && !isMovingLeft)
			{
				setHorizontalVelocity(0);
				setHorizontalAcceleration(0);
				isMovingRight = false;
			}
		}
	}

	void Player::jump()
	{
		if (shouldJump && grounded())
		{
			applyVerticalVelocity(JUMP_INITIAL_VELOCITY);
			isJumping = true;
		}
		if (grounded())
		{
			isJumping = false;
		}
	}
}