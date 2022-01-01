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
#include "../Components/TagComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/TextComponent.h"
#include "../Components/SoundComponent.h"
#include <fstream>
#include <sstream>
#include <SFML/Audio.hpp>

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

float enemyTimeSpawner = 100.0f;
const int maxEnemies = 50;
int numOfEnemies=0;

sf::Color colors[] {sf::Color::Red, sf::Color::Green, sf::Color::Yellow, sf::Color::Blue, sf::Color::Cyan, sf::Color::Magenta, sf::Color::White};

sf::Time elapsed;
std::stringstream stream;

sf::SoundBuffer buffer;


Object enemies [maxEnemies];
Object player;
Object playerHealthText;
Object playerTimeText;

int playersHealth;

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 640;

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

    mWindow.setSize({static_cast<unsigned int>(SCREEN_WIDTH),static_cast<unsigned int>(SCREEN_HEIGHT)});
    InitPlayer();

    buffer.loadFromFile("Assets/bonk.wav");
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
    player.AttachComponent<TagComponent>();
    player.GetComponent<TagComponent>()->setTag("Player");
    player.AttachComponent<HealthComponent>();
    player.GetComponent<HealthComponent>()->SetHealth(100);
    playersHealth = player.GetComponent<HealthComponent>()->getHealth();

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
    Enemy.AttachComponent<TagComponent>();
    Enemy.GetComponent<TagComponent>()->setTag("Enemy");
    Enemy.AttachComponent<CollisionComponent>();
    Enemy.AttachComponent<SoundComponent>();
    Enemy.GetComponent<SoundComponent>()->setBuffer(buffer);

    return Enemy;
}

void Game::Run() {



    playerHealthText.AttachComponent<TextComponent>();
    playerHealthText.GetComponent<TextComponent>()->textSetup("Health: " + std::to_string(playersHealth), {80, 10},
                                                              sf::Color::White, 24);
    AddObjects(&playerHealthText);

    playerTimeText.AttachComponent<TextComponent>();
    playerTimeText.GetComponent<TextComponent>()->textSetup(
            "Time: " + std::to_string(roundf(elapsed.asSeconds() * 100) / 100),
            {100, static_cast<float>(SCREEN_HEIGHT - 50)}, sf::Color::Yellow, 24);

    AddObjects(&playerTimeText);

    auto tempTextureID = TextureManager::AddTexture("Assets/spr_skeleton_idle_down.png");

    Object boss;
    boss.AttachComponent<SpriteComponent>();
    boss.AttachComponent<TransformComponent>(sf::Vector2f (100, 100));
    boss.GetComponent<SpriteComponent>()->setTexture(TextureManager::GetTexture(tempTextureID));
    boss.GetComponent<SpriteComponent>()->setPosition(sf::Vector2f (rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT));

    AddObjects(&boss);

    sf::Clock clock;
    sf::Clock clockCountUp;

    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    sf::Time milli = sf::milliseconds(10);

    while(mWindow.isOpen())
    {
        elapsed = clockCountUp.getElapsedTime();
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

    if(enemyTimeSpawner <= 0) {
        enemyTimeSpawner = 100.0f;
//
        int sizeOfArr = sizeof(enemies)/sizeof(enemies[0]);
        if (numOfEnemies >= maxEnemies) {
            return;
        }

        enemies[numOfEnemies] = Game::InitEnemy();
        numOfEnemies += 1;
        AddObjects(&enemies[numOfEnemies]);

    } else {
        enemyTimeSpawner -= 1;
    }

    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << elapsed.asSeconds();
    std::string myString = ss.str();

    playerTimeText.GetComponent<TextComponent>()->SetText("Time: " + myString);
}

void Game::update(sf::Time deltaTime)
{
    for (auto &object: m_gameObjects) {
        auto sprite = object->GetComponent<SpriteComponent>();
        auto transform = object->GetComponent<TransformComponent>();
        auto physics = object->GetComponent<PhysicsComponent>();
        auto AIMovement = object->GetComponent<AIMovementComponent>();
        auto tag = object->GetComponent<TagComponent>();
        auto coll = object->GetComponent<CollisionComponent>();
        auto sound = object->GetComponent<SoundComponent>();

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

        if ( tag!= nullptr and coll != nullptr) {
            if(tag->getTag() == "Player") {
                coll->borderLoop(sprite, SCREEN_WIDTH, SCREEN_HEIGHT);
            } else if (tag->getTag() == "Enemy") {
                coll->borderBounce(sprite, SCREEN_WIDTH, SCREEN_HEIGHT, 40);
                if (transform->getRotation() != sprite->getRotation()) {
                    sprite->setColor(colors[rand() % 6]);

                    if (sound != nullptr) {
                        sound->playSound();
                    }
                }
                transform->setRotation(sprite->getRotation());
            }
        }

        if (AIMovement != nullptr) {
            sprite->updateMovement(transform->getThrust());
        }
    }

    if( playersHealth <= 0 ) {
        std::cout << " -=Death=-" << std::endl;
    }
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(player.GetComponent<SpriteComponent>()->getSprite());

    for (auto &object: m_gameObjects) {
        if (object->GetComponent<SpriteComponent>() != nullptr)
            mWindow.draw(object->GetComponent<SpriteComponent>()->getSprite());
        if (object->GetComponent<TextComponent>() != nullptr)
            mWindow.draw(object->GetComponent<TextComponent>()->getText());
    }
    mWindow.display();
}

void Game::handlePlayerInput()
{
    auto playerTransform = player.GetComponent<TransformComponent>();
    auto playerInput = player.GetComponent<InputComponent>();
    auto playerColl = player.GetComponent<CollisionComponent>();
    auto tag = player.GetComponent<TagComponent>();

    if(tag == nullptr or tag->getTag() != "Player") {
        return;
    }

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
            if (playerColl->checkCollision(playerSprite, sprite)) {

                player.GetComponent<HealthComponent>()->decreaseHealth(1);
                playersHealth = player.GetComponent<HealthComponent>()->getHealth();
                playerHealthText.GetComponent<TextComponent>()->SetText("Health: " + std::to_string(playersHealth));
            }
        }
    }
}