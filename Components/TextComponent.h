//
// Created by crayon on 01/01/2022.
//

#ifndef CA2_TEXTCOMPONENT_H
#define CA2_TEXTCOMPONENT_H

#include <SFML/Graphics.hpp>
#include "Component.h"
#include <memory>

class TextComponent: public Component{

public:
    TextComponent(){};

    void textSetup(std::string textString, sf::Vector2<float> pos = {10, 10}, sf::Color color = sf::Color::White, int textSize = 22);

    void SetText(std::string newText);

    sf::Text getText() {
        return m_text;
    };


protected:
    sf::Font m_font;
    sf::Text m_text;
    sf::Color m_color;
    int m_textSize;
    sf::Vector2<float> m_pos;
    std::string m_textString;

};


#endif //CA2_TEXTCOMPONENT_H
