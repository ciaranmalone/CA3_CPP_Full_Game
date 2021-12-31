//
// Created by crayon on 02/12/2021.
//

#include "Game.h"
#include "../Components/SpriteComponent.h"
#include "../TextureManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/InputComponent.h"
#include "../Components/PhysicsComponent.h"
#include "../Json/json.hpp"
#include "../Components/AIMovementComponent.h"
#include "../Components/CollisionComponent.h"
#include <fstream>

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

float enemyTimeSpawner = 1000.0f;

std::vector<Object> Enemies;
Object player;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 640;

int numberOfEnemies = 5;

using nlohmann::json;

namespace data {
    struct GameData {
        int screenWidth;
        int ScreenHeight;
        float playerSpeed;
        float maxSpeed;
        int numOfEnemies;
    };

    void to_json(json& j, const GameData& g) {
        j = json{ {"screenWidth", g.screenWidth},
                  {"ScreenHeight", g.ScreenHeight},
                  {"playerSpeed", g.playerSpeed},
                  {"maxSpeed", g.maxSpeed},
                {"numberOfEnemies", g.numOfEnemies}};
        }

    void from_json(const json& j, GameData& g) {
        j.at("screenWidth").get_to(g.screenWidth);
        j.at("ScreenHeight").get_to(g.ScreenHeight);
        j.at("playerSpeed").get_to(g.playerSpeed);
        j.at("maxSpeed").get_to(g.maxSpeed);
        j.at("numberOfEnemies").get_to(g.numOfEnemies);
    }
}

Game::Game(std::string jsonLocation):mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GAME!")
{
    std::ifstream file (jsonLocation);
    json j;
    file >> j;
    std::cout << j << std::endl;
    auto gameData = j.get<data::GameData>();
    SCREEN_WIDTH = gameData.screenWidth;
    SCREEN_HEIGHT =gameData.ScreenHeight;
    numberOfEnemies = gameData.numOfEnemies;

    mWindow.setSize({static_cast<unsigned int>(SCREEN_WIDTH),static_cast<unsigned int>(SCREEN_HEIGHT)});
    InitPlayer();

}

void Game::InitPlayer() {
    extern Object player;
    auto tempTextureID = TextureManager::AddTexture("Assets/spr_skeleton_idle_down.png");
    player.AttachComponent<SpriteComponent>();
    player.AttachComponent<InputComponent>();
    player.GetComponent<SpriteComponent>()->setTexture(TextureManager::GetTexture(tempTextureID));
    player.GetComponent<SpriteComponent>()->setPosition(sf::Vector2f (SCREEN_WIDTH/2,SCREEN_HEIGHT/2));
    player.AttachComponent<TransformComponent>(sf::Vector2f (100, 100));
    player.GetComponent<TransformComponent>()->setPosition({40, 50});
    player.AttachComponent<CollisionComponent>();
    player.GetComponent<SpriteComponent>()->isPlayer = true;
    AddObjects(&player);
};

Object Game::InitEnemy() {
    Object Enemy;
    auto tempTextureID = TextureManager::AddTexture("Assets/spr_skeleton_idle_down.png");
    Enemy.AttachComponent<SpriteComponent>();
    Enemy.GetComponent<SpriteComponent>()->setTexture(TextureManager::GetTexture(tempTextureID));
    Enemy.GetComponent<SpriteComponent>()->setPosition(sf::Vector2f (rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT));
    Enemy.AttachComponent<TransformComponent>(sf::Vector2f (100, 100));
    Enemy.GetComponent<TransformComponent>()->setPosition({40, 50});
    Enemy.GetComponent<TransformComponent>()->setThrust(5);
    Enemy.GetComponent<TransformComponent>()->setMovingForward(true);
    return Enemy;
}

void Game::Run() {

    auto tempTextureID = TextureManager::AddTexture("Assets/spr_skeleton_idle_down.png");

    Object enemies [numberOfEnemies];
    for (int i = 0; i < numberOfEnemies; ++i) {
        enemies[i] = Game::InitEnemy();
        AddObjects(&enemies[i]);
    }

    Object boss;
    boss.AttachComponent<SpriteComponent>();
    boss.AttachComponent<TransformComponent>(sf::Vector2f (100, 100));
    boss.GetComponent<SpriteComponent>()->setTexture(TextureManager::GetTexture(tempTextureID));
    boss.GetComponent<SpriteComponent>()->setPosition(sf::Vector2f (rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT));

    AddObjects(&boss);

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

//    if(enemyTimeSpawner >= 0) {
//
//    } else {
//        enemyTimeSpawner += 1;
//    }
}

void Game::update(sf::Time deltaTime)
{
    for (auto &object: m_gameObjects) {
        auto sprite = object->GetComponent<SpriteComponent>();
        auto transform = object->GetComponent<TransformComponent>();
        auto physics = object->GetComponent<PhysicsComponent>();
        auto AIMovement = object->GetComponent<AIMovementComponent>();

        if(physics != nullptr)
            transform->updatePositionY(physics->GetGravity());

        if(sprite != nullptr && transform != nullptr) {

            sprite->setRotation(transform->getRotation());
            sprite->updateMovement(transform->getThrust());

            if (!transform->getMovingForward()){
                transform->decreaseSpeed(.2f);
            }
            transform->setPosition(sprite->getSprite().getPosition());
        }

        if (transform != nullptr) {
            sprite->setPosition(transform->getPosition());
        }

        if(sprite->getSprite().getPosition().x < 0)
            sprite->setPosition({static_cast<float>(SCREEN_WIDTH),sprite->getSprite().getPosition().y});

        else if(sprite->getSprite().getPosition().x > SCREEN_WIDTH)
            sprite->setPosition({0,sprite->getSprite().getPosition().y});

        if(sprite->getSprite().getPosition().y < 0)
            sprite->setPosition({sprite->getSprite().getPosition().x,static_cast<float>(SCREEN_HEIGHT)});

        else if(sprite->getSprite().getPosition().y > SCREEN_HEIGHT)
            sprite->setPosition({sprite->getSprite().getPosition().x,0});

        if (AIMovement != nullptr) {
            sprite->updateMovement(transform->getThrust());
        }
    }
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(player.GetComponent<SpriteComponent>()->getSprite());

    for (auto &object: m_gameObjects) {
        mWindow.draw(object->GetComponent<SpriteComponent>()->getSprite());
    }
    mWindow.display();
}

void Game::handlePlayerInput()
{
    auto physics = player.GetComponent<PhysicsComponent>();
    auto playerTransform = player.GetComponent<TransformComponent>();
    auto playerInput = player.GetComponent<InputComponent>();
    auto playerColl = player.GetComponent<CollisionComponent>();
    playerTransform->setMovingForward(false);

    if(playerInput->IsKeyPressed(InputComponent::KEY::KEY_LEFT))
        playerTransform->updateRotation(-5);

    else if(playerInput->IsKeyPressed(InputComponent::KEY::KEY_RIGHT))
        playerTransform->updateRotation(5);

    if(playerInput->IsKeyPressed(InputComponent::KEY::KEY_UP)){
        playerTransform->setMovingForward(true);
        playerTransform->increaseSpeed(.2f);
    }

    // Coll detection
    std::shared_ptr<SpriteComponent> playerSprite = player.GetComponent<SpriteComponent>();
    for (auto &object: m_gameObjects) {
        auto sprite = object->GetComponent<SpriteComponent>();

        if (sprite != nullptr) {
            playerColl->checkCollision(playerSprite, sprite);
        }
    }
}

void Game::LoadData() {

}
