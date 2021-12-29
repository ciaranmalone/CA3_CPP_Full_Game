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
#include "../Json/json.hpp"
#include <fstream>

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Object player;

float SCREEN_WIDTH = 640;
float SCREEN_HEIGHT = 480;
using nlohmann::json;

namespace data {
    struct GameData {
        int screenWidth;
        int ScreenHeight;
        float playerSpeed;
        float maxSpeed;
    };

    void to_json(json& j, const GameData& g) {
        j = json{ {"screenWidth", g.screenWidth},
                  {"ScreenHeight", g.ScreenHeight},
                  {"playerSpeed", g.playerSpeed},
                  {"maxSpeed", g.maxSpeed}};
    }

    void from_json(const json& j, GameData& g) {
        j.at("screenWidth").get_to(g.screenWidth);
        j.at("ScreenHeight").get_to(g.ScreenHeight);
        j.at("playerSpeed").get_to(g.playerSpeed);
        j.at("maxSpeed").get_to(g.maxSpeed);
    }
}

Game::Game():mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GAME!")
{
    std::ifstream file ("data.json");
    json j;
    file >> j;
    std::cout << j << std::endl;
    auto gameData = j.get<data::GameData>();
    SCREEN_WIDTH = gameData.screenWidth;
    SCREEN_HEIGHT =gameData.ScreenHeight;
    mWindow.
    mWindow.setSize({40,40});
//    mWindow.setSize({static_cast<unsigned int>(SCREEN_WIDTH),static_cast<unsigned int>(SCREEN_HEIGHT)});
    // Init objects
    system("dir");
    auto tempTextureID = TextureManager::AddTexture("Assets/spr_skeleton_idle_down.png");
    player.AttachComponent<SpriteComponent>();
    player.AttachComponent<InputComponent>();
    player.GetComponent<SpriteComponent>()->setTexture(TextureManager::GetTexture(tempTextureID));
    player.GetComponent<SpriteComponent>()->setPosition(sf::Vector2f (10,5));
    player.AttachComponent<TransformComponent>(sf::Vector2f (100, 100));
    player.GetComponent<TransformComponent>()->setPosition({40, 50});

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
            handlePlayerInput();
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
            case sf::Event::Closed:
                mWindow.close();
                break;
            default:
                break;
        }
        break;
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

            transform->setPosition(sprite->getSprite().getPosition());
            sprite->setRotation(transform->getRotation());
            sprite->updateMovement(transform->getThrust());

            if (!transform->getMovingForward()){
                transform->decreaseSpeed(.2f);
            }
        }

        if(sprite->getSprite().getPosition().x < 0)
            sprite->setPosition({SCREEN_WIDTH,sprite->getSprite().getPosition().y});

        else if(sprite->getSprite().getPosition().x > SCREEN_WIDTH)
            sprite->setPosition({0,sprite->getSprite().getPosition().y});

        if(sprite->getSprite().getPosition().y < 0)
            sprite->setPosition({sprite->getSprite().getPosition().x,SCREEN_HEIGHT});

        else if(sprite->getSprite().getPosition().y > SCREEN_HEIGHT)
            sprite->setPosition({sprite->getSprite().getPosition().x,0});

//        if (transform != nullptr) {
//            sprite->setPosition(transform->getPosition());
//        }
    }
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(player.GetComponent<SpriteComponent>()->getSprite());
    mWindow.display();
}

void Game::handlePlayerInput()
{
    auto physics = player.GetComponent<PhysicsComponent>();
    auto playerTransform = player.GetComponent<TransformComponent>();
    auto playerInput = player.GetComponent<InputComponent>();

    playerTransform->setMovingForward(false);

    if(playerInput->IsKeyPressed(InputComponent::KEY::KEY_LEFT))
        playerTransform->updateRotation(-5);

    else if(playerInput->IsKeyPressed(InputComponent::KEY::KEY_RIGHT))
        playerTransform->updateRotation(5);

    if(playerInput->IsKeyPressed(InputComponent::KEY::KEY_UP)){
        playerTransform->setMovingForward(true);
        playerTransform->increaseSpeed(.2f);
    }
}