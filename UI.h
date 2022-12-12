#pragma once
#include "GameObject.h"
namespace gm 
{
	class UI
	{
	protected:

		sf::Vector2i score;
		sf::Font font;
		sf::Text scorep, scoreai;

	public:
		UI();

		const sf::Vector2i& GetScore() const;
		void SetScore(const sf::Vector2i score);

		void update(sf::RenderWindow& window);

		void render(sf::RenderWindow& window);

		~UI();
	};
}