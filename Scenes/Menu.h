//
// Created by crayon on 28/12/2021.
//

#ifndef CA2_MENU_H
#define CA2_MENU_H


#include <SFML/Graphics.hpp>
#include "../Object.h"

class Menu {

public:
    Menu();
    ~Menu() {
        m_gameObjects.clear();
    };

    void Run();

    void AddObjects(Object* obj)
    {
        m_gameObjects.push_back(obj);
    }

private:
    std::vector<Object * > m_gameObjects;//vector of pointers to objects/entities

    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInput(sf::Vector2<int> key, bool isPressed);

    sf::RenderWindow mWindow;
    static const sf::Time TimePerFrame;

    void InitButton(std::string name, Object * button, int xPos, int yPos, std::string texture);
};


#endif //CA2_MENU_H
