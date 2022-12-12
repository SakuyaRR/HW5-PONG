#pragma once
#include "GameObject.h"
#include "Paddle.h"
namespace gm 
{
    class SquareBall :
     public GameObject
    {
    protected:

        sf::RectangleShape body;

        sf::Vector2f velocity;

    public:
        SquareBall(const sf::Vector2f& position, const sf::Vector2f& size);

        virtual void update(sf::RenderWindow& window, float deltaTime) override;
        virtual void render(sf::RenderWindow& window, float deltaTime) override;
        virtual void setPosition(const sf::Vector2f& position) override;
        virtual void move(const sf::Vector2f& velocity) override;

        const sf::Color& getFillColor() const;
        void setFillColor(const sf::Color& color);

        void Bounce(const Paddle& paddle, int direction);
        void Bounce(int direction, int height);

        const sf::Vector2f getSize() const;
        void setSize(const sf::Vector2f& size);

        const sf::Vector2f& getVelocity() const;
        void setVelocity(const sf::Vector2f& velocity);

    };
}

