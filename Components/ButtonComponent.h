//
// Created by crayon on 31/12/2021.
//

#ifndef CA2_BUTTONCOMPONENT_H
#define CA2_BUTTONCOMPONENT_H


#include "Component.h"
#include "SpriteComponent.h"

class ButtonComponent: public Component {

public:
    std::basic_string<char> checkButtonClick(std::shared_ptr<SpriteComponent> location, sf::Vector2i vector2);

    std::string m_buttonName;

    void setButtonName(std::string name);

    std::string getButtonName();
};


#endif //CA2_BUTTONCOMPONENT_H
