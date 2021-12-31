//
// Created by crayon on 02/12/2021.
//

#ifndef CA2_GAME_H
#define CA2_GAME_H

#include <SFML/Graphics.hpp>
#include "../Object.h"
class Game {
public:
    Game();
    void LoadData();
    void Run();
    void AddObjects(Object* obj)
    {
        m_gameObjects.push_back(obj);
    }
    std::vector<Object * > m_gameObjects;//vector of pointers to objects/entities


private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInput();
    sf::RenderWindow mWindow;

    static const sf::Time TimePerFrame;

    void InitPlayer();
    Object InitEnemy();
    void InitEnemies(int num);


};


#endif //CA2_GAME_H
