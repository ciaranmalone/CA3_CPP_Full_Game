//
// Created by crayon on 30/12/2021.
//

#ifndef CA2_COLLISIONCOMPONENT_H
#define CA2_COLLISIONCOMPONENT_H
#include "Component.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

class CollisionComponent: public Component {

public:
    bool isPlayer = true;

    bool checkCollision(std::shared_ptr<SpriteComponent> playerTransform, std::shared_ptr<SpriteComponent> otherTransform);

    void borderLoop(std::shared_ptr<SpriteComponent> sprite, int screenWidth, int screenHeight);
    void borderBounce(std::shared_ptr<SpriteComponent> sprite, int screenWidth, int screenHeight, int angle);

};


#endif //CA2_COLLISIONCOMPONENT_H
