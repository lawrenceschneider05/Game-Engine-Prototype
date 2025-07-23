#pragma once
#include "iactor.h"

namespace GameEngine
{
	class Player : public IActor
	{
	public:
		Player(f32 x, f32 y, f32 w, f32 h);
		void update() override;
		void render() override;
	private:
		void moveLeft();
		void moveRight();
		void jump();

		bool shouldMoveLeft = false;
		bool shouldMoveRight = false;
		bool isMovingLeft = false;
		bool isMovingRight = false;
		bool shouldJump = false;
		bool isJumping = false;

		const f32 MAX_HORIZONTAL_VELOCITY = 192;
		const f32 MOVEMENT_ACCELERATION = 64;
		const f32 MOVEMENT_DEACCELERATION = 64;
		const f32 JUMP_INITIAL_VELOCITY = 256;
		const f32 HORIZONTAL_INITIAL_VELOCITY = 32;
	};
}