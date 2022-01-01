//
// Created by crayon on 01/01/2022.
//

#include "TextComponent.h"

void TextComponent::SetComponent(std::string textString, sf::Vector2<float> pos, sf::Color color, int textSize) {
    m_color = color;
    m_textSize = textSize;
    m_textString = textString;

    m_text.setCharacterSize(m_textSize);
    m_text.setString(m_textString);
    m_text.setFillColor(m_color);
    m_text.setPosition(pos);
}
