#include "AIController.h"
using namespace sf;
using namespace gm;

AIController::AIController() {}

void AIController::sense(Paddle& paddle, const SquareBall& sqball) 
{
	
	if ((sqball.getPosition().y + sqball.getSize().y / 2)  > (paddle.getPosition().y + paddle.getSize().y / 2))
	{
		paddle.setMovementDirection(MovementDirection::Down);
	}
	else if ((sqball.getPosition().y + sqball.getSize().y / 2)  < (paddle.getPosition().y + paddle.getSize().y / 2))//45
	{
		paddle.setMovementDirection(MovementDirection::Up);
	}
	else //?
	{
		paddle.setMovementDirection(MovementDirection::None);
	}
}

void AIController::update(Paddle& paddle, int height) {
	
	if (paddle.getPosition().y < 0) 
	{
		paddle.setPosition(Vector2f(paddle.getPosition().x, 0));
		paddle.setMovementDirection(MovementDirection::None);//?
	}
	else if (paddle.getPosition().y > (height - paddle.getSize().y)) 
	{
		paddle.setPosition(Vector2f(paddle.getPosition().x, height - paddle.getSize().y));
		paddle.setMovementDirection(MovementDirection::None);//?
	}
}

AIController::~AIController() {}
