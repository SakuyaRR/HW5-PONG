#include "Game.h"


using namespace gm;
using namespace sf;
using namespace std;

Vector2f centerPosition = Vector2f(width / 2, height / 2);
Vector2f paddleaPosition = Vector2f(30, height / 2);
Vector2f paddlebPosition = Vector2f(width - 30, height / 2);


Game::Game() : window(VideoMode(width, height), "Game"), 
               clock(), deltaTime(0), sqball(centerPosition, Vector2f(10, 10)), 
	           paddlea(paddleaPosition, Vector2f(10, 120)), paddleb(paddlebPosition, Vector2f(10, 120)), 
	           gameState(GameState::Menu)
{
	window.setFramerateLimit(60);
	if (!font.loadFromFile("Asset/PressStart2P-vaV7.ttf"))
	{
		cout<< "Error: Failed to load font!" << endl;
		
	}

	gametitle.setFont(font);
	gametext.setFont(font);
	play.setFont(font);
	endwords.setFont(font);
	playagain.setFont(font);

	gametitle.setString("pong");
	gametext.setString("player vs AI");
	play.setString("Press space to play");
	endwords.setString("who wins");
	playagain.setString("Space to replay");

	gametitle.setCharacterSize(80);
	gametext.setCharacterSize(24);
	play.setCharacterSize(18);
	endwords.setCharacterSize(36);
	playagain.setCharacterSize(22);

	gametitle.setFillColor(sf::Color::White);
	gametext.setFillColor(sf::Color::White);
	play.setFillColor(sf::Color::White);
	endwords.setFillColor(sf::Color::White);
	playagain.setFillColor(sf::Color::White);

	gametitle.setStyle(sf::Text::Bold );
	gametext.setStyle(sf::Text::Regular);
	play.setStyle(sf::Text::Bold);
	endwords.setStyle(sf::Text::Bold);
	playagain.setStyle(sf::Text::Bold);

	gametitle.setPosition(Vector2f(170, 80));
	gametext.setPosition(Vector2f(190, 240));
	play.setPosition(Vector2f(150, 500));
	endwords.setPosition(Vector2f(190, 80));
	playagain.setPosition(Vector2f(35, 350));


}

void Game::run() 
{
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		handleInput();
		update();
		render();
	}
}

void Game::handleInput() 
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
		if (gameState == GameState::Menu)
		{
			if (event.type == Event::KeyPressed)
			{
				
				if (event.key.code == Keyboard::Space) 
				{
					GameStateChange(GameState::Gamestart);
					
				}
			}
		}
		if (gameState == GameState::Gamestart)
		{
				playerController.handleInput(event, paddlea, height, 0);
		}
		if (gameState == GameState::Gameend) 
		{
			if (event.type == Event::KeyPressed) 
			{
				if (event.key.code == Keyboard::Space) 
				{
					GameStateChange(GameState::Gamestart);
				}
				if (event.key.code == Keyboard::B) 
				{
					GameStateChange(GameState::Menu);
				}
			}
		}
	}
	if (gameState == GameState::Gamestart)
	{
			aiController.sense(paddleb, sqball);
	}
}
void Game::update()
{
	if (gameState == GameState::Gamestart)
	{
		playerController.update(paddlea, height);
		aiController.update(paddleb, height);

		sqball.update(window, deltaTime);
		paddlea.update(window, deltaTime);
		paddleb.update(window, deltaTime);

		if (sqball.collide(paddlea.getCollider()))
		{
			sqball.Bounce(paddlea, -1);
		}
		else if (sqball.collide(paddleb.getCollider()))
		{
			sqball.Bounce(paddleb, 1);
		} 
		else if (sqball.getPosition().y <= 0 || sqball.getPosition().y >= (height - sqball.getSize().y))
		{
			sqball.Bounce(sqball.getPosition().y <= 0, height);
		} 
		else if (!goal && (sqball.getPosition().x <= 0 || sqball.getPosition().x >= (height- sqball.getSize().x)))
		{
			goal = true;
			newclock.restart();
			if (sqball.getPosition().x <= 0)
			{
				uiscore.SetScore(Vector2i(uiscore.GetScore().x, uiscore.GetScore().y + 1));
			}
			else
			{
				uiscore.SetScore(Vector2i(uiscore.GetScore().x + 1, uiscore.GetScore().y));
			}

			sqball.setPosition(centerPosition - Vector2f(sqball.getSize().x / 2, sqball.getSize().y / 2) + Vector2f(-1000, 0));
			sqball.setVelocity(Vector2f(0, 0));
		}

		uiscore.update(window);

		if (goal == true)
		{
			if (uiscore.GetScore().x == 6)
			{
				endwords.setString("Player wins");
				goal = false;
				GameStateChange(GameState::Gameend);
			}

			else if (uiscore.GetScore().y == 6)
			{
				endwords.setString("AI wins");
				goal = false;
			}

			GameStateChange(GameState::Gameend);
		}
		else
		{ 
			if (newclock.getElapsedTime().asSeconds() >= 2)
			{
				sqball.setPosition(centerPosition - Vector2f(sqball.getSize().x / 2, sqball.getSize().y / 2));
				sqball.setVelocity(Vector2f(float(pow(-1, Rand(1, 4))) * 120.f, Randf(-20, 20)));
				goal = false;
			}
		}
	}

}

void Game::render() 
{
	window.clear();
	if (gameState == GameState::Menu) 
	{
		window.draw(gametitle);
		window.draw(gametext);

		window.draw(play);
	}
	if (gameState == GameState::Gamestart) 
	{
		sqball.render(window, deltaTime);
		paddlea.render(window, deltaTime);
		paddleb.render(window, deltaTime);
		uiscore.render(window);
	}
	if (gameState == GameState::Gameend) 
	{
		window.draw(endwords);
		window.draw(playagain);
	}
	window.display();
}

Game::~Game() {}

void Game::GameStateChange(GameState state) 
{

	if (state == GameState::Menu) 
	{
		gameState = GameState::Menu;
		
	}
	else if (state == GameState::Gamestart) 
	{
		gameState = GameState::Gamestart;

		sqball.setPosition(centerPosition - Vector2f(sqball.getSize().x / 2, sqball.getSize().y / 2));
		paddlea.setPosition(paddleaPosition - Vector2f(paddlea.getSize().x / 2, paddlea.getSize().y / 2));
		paddleb.setPosition(paddlebPosition - Vector2f(paddleb.getSize().x / 2, paddleb.getSize().y / 2));
		uiscore.SetScore(Vector2i(0, 0));

		sqball.setVelocity(Vector2f(120, Randf(-30, 30)));
	}
	else if (state == GameState::Gameend) 
	{
		gameState = GameState::Gameend;
	
		sqball.setPosition(centerPosition - Vector2f(sqball.getSize().x / 2, sqball.getSize().y / 2) + Vector2f(-999, 0));
		sqball.setVelocity(Vector2f(0, 0));
		paddlea.setPosition(paddleaPosition - Vector2f(paddlea.getSize().x / 2, paddlea.getSize().y / 2));
		paddleb.setPosition(paddlebPosition - Vector2f(paddleb.getSize().x / 2, paddleb.getSize().y / 2));
		paddlea.setMovementDirection(MovementDirection::None);
		paddleb.setMovementDirection(MovementDirection::None);
	}
}





int gm::Rand(int min, int max) 
{
	static bool setup = true;
	if (setup)
	{
		srand(unsigned int(time(NULL))); 
		setup = false;
	}
	int tmp = min + rand() % ((max + 1) - min);
	return (tmp == 0) ? 1 : tmp;
}

float gm::Randf(float min, float max) 
{
	static bool setup = true;
	if (setup)
	{
		srand(unsigned int(time(NULL))); 
		setup = false;
	}
	return (min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))));
}


	



