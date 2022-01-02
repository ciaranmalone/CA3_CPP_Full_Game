//
// Created by crayon on 01/01/2022.
//

#ifndef CA2_SOUNDCOMPONENT_H
#define CA2_SOUNDCOMPONENT_H
#include "Component.h"
#include <memory>
#include <SFML/Audio.hpp>
#include <iostream>

class SoundComponent: public Component {

public:

    SoundComponent() {};

    void setBuffer(sf::SoundBuffer buffer) {
        sound.setBuffer(buffer);
    }

    void playSound(){
        std::cout << "Sound played" << std::endl;
        sound.play();
    }

protected:
    sf::Sound sound;
};


#endif //CA2_SOUNDCOMPONENT_H
