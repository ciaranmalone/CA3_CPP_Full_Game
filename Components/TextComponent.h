//
// Created by crayon on 01/01/2022.
//

#ifndef CA2_TEXTCOMPONENT_H
#define CA2_TEXTCOMPONENT_H

#include <SFML/Graphics.hpp>
#include "Component.h"

class TextComponent: public Component{
public:
    void SetComponent(std::string m_textString, sf::Vector2<float> pos = {10,10}, sf::Color color = sf::Color::White, int textSize = 22);


protected:
    sf::Text m_text;
    sf::Color m_color;
    int m_textSize;
    std::string m_textString;

};


#endif //CA2_TEXTCOMPONENT_H
