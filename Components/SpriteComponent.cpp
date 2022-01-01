//
// Created by crayon on 02/12/2021.
//

#include "SpriteComponent.h"
#include <iostream>
#include <cmath>

//void SpriteComponent::Draw(sf::RenderWindow &window, float timeDelta)
//{
//    window.draw(m_sprite);
//}

SpriteComponent::SpriteComponent(const sf::Texture &texture)//new v0.5
{
    m_sprite.setTexture(texture);
}

SpriteComponent::SpriteComponent(std::string filename)//new v0.5
{

    auto texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filename))
    {
        std::cout << "I couldn't load " << filename << std::endl;
        exit(-1);
    }
    m_sprite.setTexture(*texture);
}

void SpriteComponent::load_texture(std::string filename)//new v0.5
{

    auto texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(filename))
    {
        std::cout << "I couldn't load " << filename << std::endl;
        exit(-1);
    }
    m_sprite.setTexture(*texture);
}

void SpriteComponent::setTexture(const sf::Texture &texture) //note will only have reference to texture!
{
    m_sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
    m_sprite.setTexture(texture);
}

void SpriteComponent::setPosition(sf::Vector2f position) {
    m_sprite.setPosition(position);
}

void SpriteComponent::setRotation(float rotation) {
    m_sprite.setRotation(rotation);
}

void SpriteComponent::Draw(sf::RenderWindow window) {
    window.draw(m_sprite);
}

void SpriteComponent::updateMovement(float thrust){
    m_sprite.move(thrust * sin(m_sprite.getRotation()*3.14159265/180), thrust * -cos(m_sprite.getRotation()*3.14159265/180));
}

void SpriteComponent::setColor(sf::Color color) {
    m_sprite.setColor(color);
}
