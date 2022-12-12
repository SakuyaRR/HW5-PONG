#include "Paddle.h"

using namespace sf;
using namespace gm;

Paddle::Paddle(const Vector2f& position, const Vector2f& size) : GameObject(position, size), direction(MovementDirection::None) 
{
	body.setPosition(position);
	body.setSize(size);
}

void Paddle::update(sf::RenderWindow& window, float deltaTime) 
{
	move(Vector2f(0, PlayerMovementSpeedPerSecond * direction * deltaTime));
}

void Paddle::render(sf::RenderWindow& window, float deltaTime) 
{
	window.draw(body);
}

void Paddle::move(const Vector2f& velocity) 
{
	GameObject::move(velocity);
	body.setPosition(position);
}

void Paddle::setMovementDirection(MovementDirection direction) 
{
	this->direction = direction;
}

MovementDirection Paddle::getMovementDirection() const 
{
	return direction;
}

void Paddle::setPosition(const Vector2f& position) 
{
	GameObject::setPosition(position);
	body.setPosition(position);
}

const Vector2f Paddle::getSize() const {
	return body.getSize();
}

void Paddle::setSize(const Vector2f& size) {
	body.setSize(size);
}
const Color& Paddle::getFillColor() const {
	return body.getFillColor();
}

void Paddle::setFillColor(const Color& color) {
	body.setFillColor(color);
}

