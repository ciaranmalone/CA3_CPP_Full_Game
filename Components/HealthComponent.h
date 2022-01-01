//
// Created by crayon on 01/01/2022.
//

#ifndef CA2_HEALTHCOMPONENT_H
#define CA2_HEALTHCOMPONENT_H


#include "Component.h"
#include "memory"

class HealthComponent: public Component {
public:
    HealthComponent() {};


    void SetHealth(float health);

    float getHealth();

    void decreaseHealth(float amount);

protected:
    float m_health;
};


#endif //CA2_HEALTHCOMPONENT_H
