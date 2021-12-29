//
// Created by crayon on 02/12/2021.
//

#ifndef CA2_TRANSFORMCOMPONENT_H
#define CA2_TRANSFORMCOMPONENT_H

#include <SFML/System/Vector2.hpp>
#include "Component.h"

class TransformComponent: public Component{

public:
    TransformComponent();

    TransformComponent(int x, int y);

    TransformComponent(sf::Vector2f pos);

    void setPosition(sf::Vector2f pos);

    sf::Vector2f getPosition();
    float getRotation();
    float getThrust();

    void updatePosition();

    void updatePosition(sf::Vector2f speed);

    void updatePositionY(float y);
    void updatePositionX(float x);

    void updateRotation(float d);

    void increaseSpeed(float speed);
    void decreaseSpeed(float speed);

private:
    sf::Vector2f m_position;
    float m_rotation;
    //new v0.5
    sf::Vector2f m_speed;

    float m_thrust;
};

#endif //CA2_TRANSFORMCOMPONENT_H
