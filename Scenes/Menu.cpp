//
// Created by crayon on 28/12/2021.
//

#include "Menu.h"
#include "Game.h"


const sf::Time Menu::TimePerFrame = sf::seconds(1.f/60.f);

Menu::Menu(): mWindow(sf::VideoMode(320, 320), "Main Menu!")
{

}

void Menu::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}


void Menu::processEvents()
{
    sf::Event event{};

    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
            default:
                break;
        }

    }
}

void Menu::update(sf::Time deltaTime)
{
    // TODO: Update your objects here
    // Example: mWindow.draw(mPlayer);
}


void Menu::render()
{
    mWindow.clear();
    mWindow.display();
}

void Menu::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
     if (key == sf::Keyboard::W)
     {
         Game game;
         game.Run();
         mWindow.close();
     }
}