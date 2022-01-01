//
// Created by crayon on 30/12/2021.
//

#include "CollisionComponent.h"
#include <SFML/Graphics.hpp>
#include <cmath>

bool CollisionComponent::checkCollision(std::shared_ptr<SpriteComponent> playerTransform, std::shared_ptr<SpriteComponent> otherTransform) {

    if(playerTransform == otherTransform) {
        return false;
    }
    auto playerPos = playerTransform->getSprite().getPosition();
    auto otherPos = otherTransform->getSprite().getPosition();
    auto playerRadius = playerTransform->getSprite().getTexture()->getSize().x/2;
    auto otherRadius = otherTransform->getSprite().getTexture()->getSize().x/2;

    float dx = (playerPos.x + playerRadius) - (otherPos.x + otherRadius);
    float dy = (playerPos.y + playerRadius) - (otherPos.y + otherRadius);
    float distance = std::sqrt((dx*dx) + (dy*dy));

    if(distance <= (playerRadius + otherRadius)) {
        return true;
    }

    return false;
}

void CollisionComponent::borderLoop(std::shared_ptr<SpriteComponent> sprite, int screenWidth, int screenHeight) {

    if(sprite->getSprite().getPosition().x < 0)
        sprite->setPosition({static_cast<float>(screenWidth),sprite->getSprite().getPosition().y});

    else if(sprite->getSprite().getPosition().x > screenWidth)
        sprite->setPosition({0,sprite->getSprite().getPosition().y});

    if(sprite->getSprite().getPosition().y < 0)
        sprite->setPosition({sprite->getSprite().getPosition().x,static_cast<float>(screenHeight)});

    else if(sprite->getSprite().getPosition().y > screenHeight)
        sprite->setPosition({sprite->getSprite().getPosition().x,0});

}

void CollisionComponent::borderBounce(std::shared_ptr<SpriteComponent> sprite, int screenWidth, int screenHeight,
                                      int angle) {

    if(sprite->getSprite().getPosition().x < 0)
        sprite->setRotation(rand() % angle + 70); // 90 +- 20

    else if(sprite->getSprite().getPosition().x > screenWidth)
        sprite->setRotation(rand() % angle + 250); // 270 += 20

    if(sprite->getSprite().getPosition().y < 0)
        sprite->setRotation(rand() % angle + 160); // 180 -+ 20

    else if(sprite->getSprite().getPosition().y > screenHeight)
        sprite->setRotation(rand() % angle -20 ); // 0 -+ 20
}
