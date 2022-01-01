//
// Created by crayon on 01/01/2022.
//

#include "TextComponent.h"

void TextComponent::textSetup(std::string textString, sf::Vector2<float> pos, sf::Color color, int textSize) {
    m_color = color;
    m_textSize = textSize;
    m_textString = textString;
    m_pos = pos;
    m_font.loadFromFile("Assets/PAPYRUS.ttf");

    m_text.setFont(m_font);
    m_text.setCharacterSize(textSize);
    m_text.setString(m_textString);
    m_text.setFillColor(color);
    m_text.setPosition({pos.x - (m_text.getGlobalBounds().width/2), pos.y});
}

void TextComponent::SetText(std::string newText) {
    m_text.setString(newText);
}
