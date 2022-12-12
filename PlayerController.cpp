#include "PlayerController.h"

using namespace sf;
using namespace gm;

PlayerController::PlayerController() {}



void PlayerController::update(Paddle& paddle, int height) 
{

	if (paddle.getPosition().y < 0) 
	{
		paddle.setPosition(Vector2f(paddle.getPosition().x, 0));
		paddle.setMovementDirection(MovementDirection::None);
	}
	else if (paddle.getPosition().y > (height - paddle.getSize().y)) 
	{
		paddle.setPosition(Vector2f(paddle.getPosition().x, height - paddle.getSize().y));
		paddle.setMovementDirection(MovementDirection::None);
	}
}

void PlayerController::handleInput(const sf::Event& event, Paddle& paddle, int height, int player) 
{
	
	if (player == 0 ) 
	{
		if (event.type == Event::KeyPressed) 
		{
			if (event.key.code == Keyboard::Up  && paddle.getPosition().y > 0) 
			{
				paddle.setMovementDirection(MovementDirection::Up);
			}
			else if (event.key.code == Keyboard::Down && paddle.getPosition().y < (height - paddle.getSize().y/2)) 
			{
				paddle.setMovementDirection(MovementDirection::Down);
			}
		}

		if (event.type == Event::KeyReleased) 
		{
			if (event.key.code == Keyboard::Up && paddle.getMovementDirection() == MovementDirection::Up) 
			{
				paddle.setMovementDirection(MovementDirection::None);
			}
			if (event.key.code == Keyboard::Down && paddle.getMovementDirection() == MovementDirection::Down) 
			{
				paddle.setMovementDirection(MovementDirection::None);
			}
		}
	}
}


PlayerController::~PlayerController() {}