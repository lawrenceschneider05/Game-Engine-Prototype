#include "player.h"
#include "rendering/renderer.h"
#include "input/input.h"

namespace GameEngine
{
	Player::Player(f32 x, f32 y, f32 w, f32 h) : IActor(true, x, y, w, h)
	{
	}

	void Player::update()
	{

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
		moveLeft();
		moveRight();
		Logger::log(LOG_DEBUG, vx());
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
}