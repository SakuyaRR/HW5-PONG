#pragma once

#include "Paddle.h"
#include "SquareBall.h"
#include <iostream>

namespace gm 
{
	class AIController
	{
	public:
		AIController();

		void sense(Paddle& paddle, const SquareBall& sqball);
		void update(Paddle& paddle, int height);

		~AIController();
	};
}

