//
// Created by crayon on 01/01/2022.
//

#include "HealthComponent.h"

float HealthComponent::getHealth() {
    return m_health;
}

void HealthComponent::SetHealth(float health) {
    m_health = health;
}

void HealthComponent::decreaseHealth(float amount) {
    m_health -= amount;
}
