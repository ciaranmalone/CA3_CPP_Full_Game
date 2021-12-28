//
// Created by crayon on 19/12/2021.
//

#ifndef CA2_PHYSICSCOMPONENT_H
#include <iostream>
#include "Component.h"


class PhysicsComponent: public Component{

public:
    PhysicsComponent(){};
    PhysicsComponent(float gravity);

    void SetGravity(float gravity);

    float GetGravity() {
     return m_gravity;
    }

protected:
    float m_gravity;
};


#endif //CA2_PHYSICSCOMPONENT_H
