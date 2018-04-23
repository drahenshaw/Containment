#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>

#include "State.h"
#include "BaseScreen.h"
#include "TitleScreen.h"
#include "Character.h"
#include "Zombie.h"
#include "Background.h"
#include "Obstacle.h"


//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(800, 600), "PA9");
//	GameState state;
//
//	window.setFramerateLimit(60);
//	state.setCurrentScreen(new TitleScreen());
//	
//	
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//
//			state.getCurrentScreen()->handleEvents(event, window, state);
//		}
//
//		window.clear();
//
//		state.getCurrentScreen()->draw(window, state);
//
//		window.display();
//	}
//
//	return 0;
//}

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	Character player({ 100.0f, 100.0f });

	Zombie *enemy = new Zombie();

	Background *test = new Background(0,0,800,600,"overcast.jpg");//Just a picture I had available

	//Timepoint for delta time measurement
	auto timePoint = std::chrono::steady_clock::now();
	
	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Get delta time
		float dt;
		{
			const auto newTimePoint = std::chrono::steady_clock::now();
			dt = std::chrono::duration<float>(newTimePoint - timePoint).count();
			timePoint = newTimePoint;
		}

		//Handle Input
		sf::Vector2f dir = { 0.0f, 0.0f };
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			dir.y -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			dir.y += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			dir.x -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			dir.x += 1.0f;
		}
		
		player.setDirection(dir);
		player.update(dt);
		
		sf::Vector2f direction = { 0.0f, 0.0f };
		direction = (player.getPosition() - enemy->getPosition());


		enemy->setDirection(direction); //need different way to move towards character - position vector - get x,y?
		enemy->update(dt);
		

		// Clear screen
		window.clear();
		//Scenery - always draw before characters
		test->draw(window);
		// Draw the sprite
		player.draw(window);	
		enemy->draw(window);
		// Update the window
		window.display();
	}
	return EXIT_SUCCESS;
}