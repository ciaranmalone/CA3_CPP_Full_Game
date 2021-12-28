//
// Created by crayon on 05/12/2021.
//

#ifndef CA2_INPUTCOMPONENT_H


#include "Component.h"

class InputComponent: public Component{

public:

    enum class KEY
    {
        KEY_LEFT,
        KEY_RIGHT,
        KEY_UP,
        KEY_DOWN,
        KEY_ATTACK,
        KEY_ESC,
        KEY_SHIFT
    };

    bool IsKeyPressed(KEY keycode);

};


#endif //CA2_INPUTCOMPONENT_H
