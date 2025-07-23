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

		bool shouldMoveLeft = false;
		bool shouldMoveRight = false;
		bool isMovingLeft = false;
		bool isMovingRight = false;
		const f32 MAX_HORIZONTAL_VELOCITY = 256;
		const f32 MOVEMENT_ACCELERATION = 128;
		const f32 MOVEMENT_DEACCELERATION = 64;
	};
}