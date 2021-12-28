//
// Created by crayon on 05/12/2021.
//

#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Mouse.hpp>
#include "InputComponent.h"

bool InputComponent::IsKeyPressed(InputComponent::KEY keycode) {
    switch (keycode) {
        case KEY::KEY_SHIFT:
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ||
                (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))) {
                std::cout << "shift pressed" << std::endl;
                return true;
            }
            break;
        case KEY::KEY_LEFT:
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ||
                (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -40)) {
                std::cout << "leftkey pressed" << std::endl;
                return true;
            }
            break;

        case KEY::KEY_RIGHT:
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ||
                (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 40)) {
                std::cout << "rightkey pressed" << std::endl;
                return true;
            }
            break;

        case KEY::KEY_UP:
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ||
                (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -40)) {
                return true;
            }
            break;

        case KEY::KEY_DOWN:
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) ||
                (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 40)) {
                return true;
            }
            break;

        case KEY::KEY_ATTACK:
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
                 sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) {
                return true;
            }
            break;

        case KEY::KEY_ESC:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                return true;
            }
    }

}
