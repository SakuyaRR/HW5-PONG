#include "SquareBall.h"
#include "SquareBall.h"
#include <iostream>

using namespace sf;
using namespace gm;

SquareBall::SquareBall(const Vector2f& position, const Vector2f& size) : GameObject(position, size) 
{
	body.setPosition(position);
	body.setSize(size);
	velocity = Vector2f(0, 0);
}
void SquareBall::update(sf::RenderWindow& window, float deltaTime)
{
	move(Vector2f(velocity.x * deltaTime, velocity.y * deltaTime));
}
void SquareBall::render(sf::RenderWindow& window, float deltaTime) 
{
	window.draw(body);
}
void SquareBall::move(const Vector2f& velocity)
{
	GameObject::move(velocity);
	body.setPosition(position);
}
void SquareBall::setPosition(const Vector2f& position) 
{
	GameObject::setPosition(position);
	body.setPosition(position);
}
const Vector2f& SquareBall::getVelocity() const
{
	return velocity;
}
void SquareBall::setVelocity(const Vector2f& velocity)
{
	this->velocity = velocity;
}
const Vector2f SquareBall::getSize() const
{
	return body.getSize();
}
void SquareBall::setSize(const Vector2f& size)
{
	body.setSize(size);
}
const Color& SquareBall::getFillColor() const 
{
	return body.getFillColor();
}

void SquareBall::setFillColor(const Color& color) 
{
	body.setFillColor(color);
}



void SquareBall::Bounce(const Paddle& paddle, int direction)
{
	if (velocity.y > 0 && (getPosition().y + getSize().y) <= (paddle.getPosition().y + 5) &&
		((direction == -1 && getPosition().x <= paddle.getPosition().x + paddle.getSize().x) ||
			(direction == 1 && getPosition().x + getSize().x >= paddle.getPosition().x)))
	{
		setPosition(Vector2f(getPosition().x, paddle.getPosition().y - getSize().y - 0.1f));
		velocity.y = (-1) * velocity.y;
	}

	else if (velocity.y < 0 && getPosition().y >= (paddle.getPosition().y + paddle.getSize().y - 5) &&
		((direction == -1 && getPosition().x <= paddle.getPosition().x + paddle.getSize().x) ||
			(direction == 1 && getPosition().x + getSize().x >= paddle.getPosition().x))) 
	     {
		    setPosition(Vector2f(getPosition().x, paddle.getPosition().y + paddle.getSize().y + 0.1f));
		    velocity.y = (-1) * velocity.y;
	     }
	else 
	{
		if (direction == -1) 
		{
			setPosition(Vector2f(paddle.getPosition().x + paddle.getSize().x + 0.1f, getPosition().y));
		}
		else 
		{
			setPosition(Vector2f(paddle.getPosition().x - getSize().x - 0.1f, getPosition().y));
		}

		if (paddle.getMovementDirection() == MovementDirection::Up) 
		{
			setVelocity(Vector2f((-1) * (getVelocity().x + direction * 40), getVelocity().y - 70));
		}
		else if (paddle.getMovementDirection() == MovementDirection::Down) 
		{
			setVelocity(Vector2f((-1) * (getVelocity().x + direction * 40), getVelocity().y + 70));
		}
		else 
		{
			setVelocity(Vector2f((-1) * (getVelocity().x + direction * 40), getVelocity().y));
		}
	}
}


void SquareBall::Bounce(int direction, int height) 
{
	velocity.y = (-1) * velocity.y;
	if (direction) 
	{
		setPosition(Vector2f(getPosition().x, 0.1f));
	}
	else 
	{
		setPosition(Vector2f(getPosition().x, height - getSize().y - 0.1f));
	}
}