//
// Created by crayon on 31/12/2021.
//

#include "ButtonComponent.h"
#include <SFML/Graphics.hpp>

std::basic_string<char> ButtonComponent::checkButtonClick(std::shared_ptr<SpriteComponent> location, sf::Vector2i mousePos) {

    auto spritePos = location->getSprite().getPosition();
    auto spriteSize = location->getSprite().getTexture()->getSize();

    std::cout << spritePos.x << " "<< spritePos.y << " spritePos" << std::endl;
    std::cout << mousePos.x <<  " " << mousePos.y << " spriteSize" << std::endl;


    if (spritePos.x <= mousePos.x + spriteSize.x && spritePos.x >= mousePos.x - spriteSize.x
    && spritePos.y <= mousePos.y + spriteSize.y && spritePos.y >= mousePos.y - spriteSize.y)
    {
        std::cout << "Collision Detected" << std::endl;

        return m_buttonName;
    } else {
        return "";
    }
}

void ButtonComponent::setButtonName(std::string name) {
    m_buttonName = name;
}

std::string ButtonComponent::getButtonName() {
    return m_buttonName;
}
