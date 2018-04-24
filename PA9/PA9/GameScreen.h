#pragma once
#include "Character.h"
#include "Zombie.h"
#include "Cursor.h"
#include "Background.h"
#include "Obstacle.h"
#include "BaseScreen.h"
#include "Cursor.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
class GameScreen
	: public BaseScreen
{
public:
	GameScreen()
		: BaseScreen("Game Screen")
	{
		m_Font.loadFromFile("OpenSans-Regular.ttf");
	}
	ScreenType run(sf::RenderWindow &window) {
		Cursor newCursor(window);
		Character player({ 100.0f, 100.0f });
		Character *zombieArray[25];

		for (int i = 0; i < 25; ++i)
		{
			zombieArray[i] = new Zombie();
		}


		Zombie *enemy = new Zombie();
		Background *test = new Background(0, 0, 800, 600, "overcast.jpg"); //Just a picture I had available

		//Timepoint for delta time measurement
		auto timePoint = std::chrono::steady_clock::now();

		while (window.isOpen()) {
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
			//direction = (player.getPosition() - enemy->getPosition());


			//enemy->setDirection(direction); //need different way to move towards character - position vector - get x,y?
			//enemy->update(dt);


			// Clear screen
			window.clear();
			//Scenery - always draw before characters
			test->draw(window);
			// Draw the sprite
			for (int i = 0; i < 25; ++i)
			{
				direction = (player.getPosition() - zombieArray[i]->getPosition());

				zombieArray[i]->setDirection(direction);
				zombieArray[i]->update(dt);
				zombieArray[i]->draw(window);
			}
			player.draw(window);
			//enemy->draw(window);
			// Update the window
			newCursor.setPosition(window);
			window.display();
		}

		return Title;
	}

private:
	sf::Font m_Font;

};