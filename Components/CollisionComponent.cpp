//
// Created by crayon on 30/12/2021.
//

#include "CollisionComponent.h"
#include <SFML/Graphics.hpp>
#include <cmath>

void CollisionComponent::checkCollision(std::shared_ptr<SpriteComponent> playerTransform, std::shared_ptr<SpriteComponent> otherTransform) {

    if(playerTransform == otherTransform) {
        return;
    }
    auto playerPos = playerTransform->getSprite().getPosition();
    auto otherPos = otherTransform->getSprite().getPosition();
    auto playerRadius = playerTransform->getSprite().getTexture()->getSize().x/2;
    auto otherRadius = otherTransform->getSprite().getTexture()->getSize().x/2;

    float dx = (playerPos.x + playerRadius) - (otherPos.x + otherRadius);
    float dy = (playerPos.y + playerRadius) - (otherPos.y + otherRadius);
    float distance = std::sqrt((dx*dx) + (dy*dy));

    if(distance <= (playerRadius + otherRadius)) {
        std::cout << "Collision Detected" << std::endl;
    }
}
