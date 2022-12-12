#pragma once
#include "Paddle.h"

namespace gm 
{
	class PlayerController
	{
	public:
		PlayerController();

		void handleInput(const sf::Event& event, Paddle& paddle, int height, int player = 0);
		void update(Paddle& paddle, int height);

		~PlayerController();
	};
}