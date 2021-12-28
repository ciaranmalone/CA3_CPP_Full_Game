//
// Created by crayon on 19/12/2021.
//

#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(float gravity) {
    std::cout << "Physics " << std::endl;
    m_gravity = gravity;
}

void PhysicsComponent::SetGravity(float gravity) {
    m_gravity = gravity;

}
