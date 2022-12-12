#include "UI.h"
#include <iostream>
using namespace sf;
using namespace gm;
using namespace std;

UI::UI() : score(Vector2i(0, 0))
{
	
	if (!font.loadFromFile("Asset/PressStart2P-vaV7.ttf"))
	{
		cout << "Error: Failed to load font!" << endl;
	}

	scorep.setFont(font);
	scoreai.setFont(font);
	
	scorep.setString("0");
	scoreai.setString("0");
	

	scorep.setCharacterSize(60);
	scoreai.setCharacterSize(60);
	
	
	scorep.setFillColor(sf::Color::Red);
	scoreai.setFillColor(sf::Color::Red);
	
	
	scorep.setStyle(sf::Text::Bold);
	scoreai.setStyle(sf::Text::Bold);
	
	
	scorep.setPosition(Vector2f(170, 40));
	scoreai.setPosition(Vector2f(420, 40));
	
}
const Vector2i& UI::GetScore() const 
{
	return score;
}
void UI::SetScore(const sf::Vector2i score) 
{
	this->score = score;
}
void UI::update(sf::RenderWindow& window) 
{
	scorep.setString(std::to_string(score.x));
	scoreai.setString(std::to_string(score.y));
	
}
void UI::render(sf::RenderWindow& window) 
{
	window.draw(scorep);
	window.draw(scoreai);
	
}

UI::~UI() {}