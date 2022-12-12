#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include "SquareBall.h"
#include "Paddle.h"
#include "PlayerController.h"
#include "AIController.h"
#include "UI.h"


namespace gm 
{
	const int width = 640;
	const int height = 640;

	enum GameState 
	{
		Menu = 0,
		Gamestart = 1,
		Gameend = 2
	};


	class Game 
	{
	private:
		sf::RenderWindow window;

		sf::Clock clock;
		float deltaTime;
	
		GameState gameState;

		sf::Font font;
	
		sf::Text gametitle, gametext, play, endwords, playagain;
	
		SquareBall sqball;
		Paddle paddlea;
		Paddle paddleb;
		UI uiscore;
		sf::Clock newclock;
		bool goal = false;
		PlayerController playerController;
		AIController aiController;
		
	public:

		Game();

		void run();
		void handleInput();
		void update();
		void render();
		void GameStateChange(GameState state);

		~Game();
	};

	int Rand(int min, int max);
	float Randf(float min, float max);
}
