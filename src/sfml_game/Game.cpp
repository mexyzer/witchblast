/**  This file is part of sfmlGame.
  *
  *  FreeTumble is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  FreeTumble is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with FreeTumble.  If not, see <http://www.gnu.org/licenses/>.
  */

#include "Game.h"

#include "GameEntity.h"
#include "EntityManager.h"

#include <iostream>

Game::Game(int screenWidth, int screenHeight, std::string windowsTitle, bool fullScreen)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    if (fullScreen)
        app = new sf::RenderWindow(sf::VideoMode(this->screenWidth, this->screenHeight), windowsTitle, sf::Style::Fullscreen);
    else
        app = new sf::RenderWindow(sf::VideoMode(this->screenWidth, this->screenHeight), windowsTitle); // , sf::Style::Close);
    app->setFramerateLimit(60);
}

Game::~Game()
{
    printf("Deleting the game...\n");
    delete(app);
}

float Game::getAbsolutTime()
{
    static sf::Clock clock;
    //return clock.getElapsedTime();
    return clock.getElapsedTime().asSeconds();
}

void Game::startGame()
{
    lastTime = getAbsolutTime();

    // Start game loop
    while (app->isOpen())
    {



        // Process events
        sf::Event event;

        while (app->pollEvent(event))
        {

            // Close window : exit
            if (event.type == sf::Event::Closed)
                app->close();

        }

        onUpdate();
        onRender();

    }

    quitGame();
}

void Game::quitGame()
{
}

void Game::onRender()
{
    // clear the view
    app->clear(sf::Color(32, 32, 32));

    // render the game objects
    EntityManager::getEntityManager()->render(app);

    app->display();
}

void Game::onUpdate()
{
  float delta = getAbsolutTime() - lastTime;
  lastTime = getAbsolutTime();
  EntityManager::getEntityManager()->animate(delta);
  //if (delta > 0.02f) std::cout << delta << std::endl;
}

