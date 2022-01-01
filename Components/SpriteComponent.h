//
// Created by crayon on 02/12/2021.
//

#ifndef CA2_SPRITECOMPONENT_H
#define CA2_SPRITECOMPONENT_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <memory>
#include "Component.h"

class SpriteComponent : public Component {

public:
    ///this will be a non animated sprite
    SpriteComponent(){}
    SpriteComponent(const sf::Texture& texture);
    SpriteComponent(std::string filename );

    void load_texture(std::string filename );
    void Draw(sf::RenderWindow &window, float timeDelta);
    void setTexture(const sf::Texture& texture);
    void setPosition(sf::Vector2f position);
    void setRotation(float position);
    float getRotation() {
        return getSprite().getRotation();
    }
    void updateMovement(float thrust);

    sf::Sprite getSprite() {
        return m_sprite;
    }

    void setColor(sf::Color color);

    void Draw(sf::RenderWindow window);
    bool isPlayer = false;


protected:
    sf::Sprite m_sprite;
    float m_timeDelta;
};


#endif //CA2_SPRITECOMPONENT_H
