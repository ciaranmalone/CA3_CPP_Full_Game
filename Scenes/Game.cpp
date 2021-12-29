//
// Created by crayon on 02/12/2021.
//

#include "Game.h"
#include "../Object.h"
#include "../Components/SpriteComponent.h"
#include "../TextureManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/InputComponent.h"
#include "../Components/PhysicsComponent.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Object player;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

Game::Game():mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GAME!")
{
    // Init objects
    system("dir");
    auto tempTextureID = TextureManager::AddTexture("Assets/spr_skeleton_idle_down.png");
    player.AttachComponent<SpriteComponent>();
    player.AttachComponent<InputComponent>();
    player.GetComponent<SpriteComponent>()->setTexture(TextureManager::GetTexture(tempTextureID));
    player.GetComponent<SpriteComponent>()->setPosition(sf::Vector2f (10,5));
    player.AttachComponent<TransformComponent>(sf::Vector2f (100, 100));
    player.GetComponent<TransformComponent>()->setPosition({40, 50});
//    player.AttachComponent<PhysicsComponent>();
//    player.GetComponent<PhysicsComponent>()->SetGravity(9.81);
    AddObjects(&player);

}

void Game::Run() {

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event{};

    while(mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
            default:
                break;
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    for (auto &object: m_gameObjects) {
        auto sprite = object->GetComponent<SpriteComponent>();
        auto transform = object->GetComponent<TransformComponent>();
        auto physics = object->GetComponent<PhysicsComponent>();

        if(physics != nullptr)
            transform->updatePositionY(physics->GetGravity());

        if(sprite != nullptr && transform != nullptr) {
            sprite->setRotation(transform->getRotation());

            if (transform->getThrust() > 0)
                sprite->updateMovement(transform->getThrust());
        }

        if(sprite->getSprite().getPosition().x < 0)
            sprite->setPosition({SCREEN_WIDTH,sprite->getSprite().getPosition().y});

        else if(sprite->getSprite().getPosition().x > SCREEN_WIDTH)
            sprite->setPosition({0,sprite->getSprite().getPosition().y});

        if(sprite->getSprite().getPosition().y < 0)
            sprite->setPosition({sprite->getSprite().getPosition().x,SCREEN_HEIGHT});

        else if(sprite->getSprite().getPosition().y > SCREEN_HEIGHT)
            sprite->setPosition({sprite->getSprite().getPosition().x,0});
    }
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(player.GetComponent<SpriteComponent>()->getSprite());
    mWindow.display();
}


void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    auto physics = player.GetComponent<PhysicsComponent>();
    auto playerTransform = player.GetComponent<TransformComponent>();
    auto playerInput = player.GetComponent<InputComponent>();

    if(playerInput->IsKeyPressed(InputComponent::KEY::KEY_LEFT))
        playerTransform->updateRotation(-5);
    else if(playerInput->IsKeyPressed(InputComponent::KEY::KEY_RIGHT))
        playerTransform->updateRotation(5);

    if(playerInput->IsKeyPressed(InputComponent::KEY::KEY_UP))
        playerTransform->increaseSpeed(.1f);
    else
        playerTransform->decreaseSpeed(.1f);
}