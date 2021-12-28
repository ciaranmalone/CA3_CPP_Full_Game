//
// Created by crayon on 02/12/2021.
//

#ifndef CA2_GAME_H
#define CA2_GAME_H

#include <SFML/Graphics.hpp>
#include "Object.h"
class Game {
public:
    Game();
    void Run();
    void AddObjects(Object* obj)
    {
        m_gameObjects.push_back(obj);
    }

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    std::vector<Object * > m_gameObjects;//vector of pointers to objects/entities

    sf::RenderWindow mWindow;

    static const sf::Time TimePerFrame;
};


#endif //CA2_GAME_H
