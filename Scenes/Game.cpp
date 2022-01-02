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
#include <iostream>

using nlohmann::json;

namespace dataJson {
    struct GameData {
        int screenWidth;
        int ScreenHeight;
        float playerSpeed;
        float maxSpeed;
        int numOfEnemies;
        float bestTime;
        float enemySpeed;
        std::string enemySprite;
        std::string playerSprite;
        float spawnTime;
        int playerHealth;
    };

    void to_json(json& j, const GameData& g) {
        j = json{ {"screenWidth", g.screenWidth},
                  {"ScreenHeight", g.ScreenHeight},
                  {"playerSpeed", g.playerSpeed},
                  {"maxSpeed", g.maxSpeed},
                  {"numberOfEnemies", g.numOfEnemies},
                  {"bestTime", g.bestTime},
                  {"enemySpeed", g.enemySpeed},
                  {"enemySprite", g.enemySprite},
                  {"playerSprite", g.playerSprite},
                  {"spawnTime", g.spawnTime},
                  {"playerHealth",g.playerHealth}
        };
    }

    void from_json(const json& j, GameData& g) {
        j.at("screenWidth").get_to(g.screenWidth);
        j.at("ScreenHeight").get_to(g.ScreenHeight);
        j.at("playerSpeed").get_to(g.playerSpeed);
        j.at("maxSpeed").get_to(g.maxSpeed);
        j.at("numberOfEnemies").get_to(g.numOfEnemies);
        j.at("bestTime").get_to(g.bestTime);
        j.at("enemySpeed").get_to(g.enemySpeed);
        j.at("enemySprite").get_to(g.enemySprite);
        j.at("playerSprite").get_to(g.playerSprite);
        j.at("spawnTime").get_to(g.spawnTime);
        j.at("playerHealth").get_to(g.playerHealth);
    }
}

dataJson::GameData gameData;

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

float enemyTimeSpawner = 100.0f;
const int maxEnemies = 50;
int numOfEnemies=0;
bool gameOvered = false;

sf::Color colors[] {sf::Color::Red, sf::Color::Green, sf::Color::Yellow, sf::Color::Blue, sf::Color::Cyan, sf::Color::Magenta, sf::Color::White};

sf::Time elapsed;
std::stringstream stream;

sf::SoundBuffer buffer;

Object enemies [maxEnemies] ={};
Object player;
Object playerHealthText;
Object playerTimeText;
Object gameOverText;

int playersHealth;

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 640;

std::string JsonLocation;

Game::Game(std::string jsonLocation):mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GAME!")
{
    JsonLocation = jsonLocation;
    LoadData(jsonLocation);

    //Sound
    buffer.loadFromFile("Assets/bonk.wav");
    sf::SoundBuffer buffer2;
    if (!buffer2.loadFromFile("Assets/bonk.wav"))
        return;

    sf::Sound sound;
    sound.setBuffer(buffer2);
    sound.play();
}

void Game::LoadData(std::string jsonLocation) {
    //JSON
    std::ifstream file (jsonLocation);
    json j;
    file >> j;
    std::cout << j << std::endl;
    gameData = j.get<dataJson::GameData>();
    SCREEN_WIDTH = gameData.screenWidth;
    SCREEN_HEIGHT =gameData.ScreenHeight;
    enemyTimeSpawner = gameData.spawnTime;

    mWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GAME!");
    mWindow.setSize({static_cast<unsigned int>(SCREEN_WIDTH),static_cast<unsigned int>(SCREEN_HEIGHT)});
}

void Game::InitPlayer() {
    extern Object player;
    auto tempTextureID = TextureManager::AddTexture(gameData.playerSprite);
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
    player.GetComponent<HealthComponent>()->SetHealth(gameData.playerHealth);
    playersHealth = player.GetComponent<HealthComponent>()->getHealth();

    AddObjects(&player);
};

Object Game::InitEnemy() {
    Object Enemy;
    auto tempTextureID = TextureManager::AddTexture(gameData.enemySprite);
    Enemy.AttachComponent<SpriteComponent>();
    Enemy.GetComponent<SpriteComponent>()->setTexture(TextureManager::GetTexture(tempTextureID));
    Enemy.GetComponent<SpriteComponent>()->setPosition(sf::Vector2f (rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT));
    Enemy.AttachComponent<TransformComponent>(sf::Vector2f (100, 100));
    Enemy.GetComponent<TransformComponent>()->setPosition({40, 50});
    Enemy.GetComponent<TransformComponent>()->setThrust(gameData.enemySpeed);
    Enemy.GetComponent<TransformComponent>()->setMovingForward(true);
    Enemy.AttachComponent<TagComponent>();
    Enemy.GetComponent<TagComponent>()->setTag("Enemy");
    Enemy.AttachComponent<CollisionComponent>();
    Enemy.AttachComponent<SoundComponent>();
    Enemy.GetComponent<SoundComponent>()->setBuffer(buffer);
    Enemy.GetComponent<SoundComponent>()->playSound();
    return Enemy;
}

void Game::Run() {

    InitPlayer();

    playerHealthText.AttachComponent<TextComponent>();
    playerHealthText.GetComponent<TextComponent>()->textSetup("Health: " + std::to_string(playersHealth), {80, 10},
                                                              sf::Color::White, 24);
    AddObjects(&playerHealthText);

    playerTimeText.AttachComponent<TextComponent>();
    playerTimeText.GetComponent<TextComponent>()->textSetup(
            "Time: " + std::to_string(roundf(elapsed.asSeconds() * 100) / 100),
            {100, static_cast<float>(SCREEN_HEIGHT - 50)}, sf::Color::Yellow, 24);

    AddObjects(&playerTimeText);

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
        if (event.type == sf::Event::Closed)
            mWindow.close();
        break;
    }

    if(enemyTimeSpawner <= 0) {
        enemyTimeSpawner = gameData.spawnTime;
        if (numOfEnemies >= maxEnemies) {
            return;
        }

        enemies[numOfEnemies] = Game::InitEnemy();
        numOfEnemies += 1;
        AddObjects(&enemies[numOfEnemies]);

        int n = sizeof(enemies)/sizeof(enemies[0]);
    } else {
        enemyTimeSpawner -= 1;
    }

    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << elapsed.asSeconds();
    std::string myString = ss.str();
    if (!gameOver)
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

    if( playersHealth <= 0 && !gameOvered) {
        gameOvered = true;
        gameOver = true;

        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << elapsed.asSeconds();
        std::string myString = ss.str();

        gameOverText.AttachComponent<TextComponent>();
        gameOverText.GetComponent<TextComponent>()->textSetup(
                "Game Over\n Time: " + myString +"s", {static_cast<float>(SCREEN_WIDTH/2), static_cast<float>(SCREEN_HEIGHT/2)}, sf::Color::Yellow, 64);

        if(elapsed.asSeconds() > gameData.bestTime) {
            gameData.bestTime = elapsed.asSeconds();

            json j2 = gameData;
            std::ofstream outJson(JsonLocation);
            outJson << j2 << std::endl;
        }
        AddObjects(&gameOverText);
    }
}

void Game::render()
{
    mWindow.clear();
    //mWindow.draw(player.GetComponent<SpriteComponent>()->getSprite());

    for (auto &object: m_gameObjects) {
        if (object->GetComponent<SpriteComponent>() != nullptr and !gameOvered) {
            mWindow.draw(object->GetComponent<SpriteComponent>()->getSprite());
        } else if (object->GetComponent<SpriteComponent>() != nullptr and object != &player) {
            mWindow.draw(object->GetComponent<SpriteComponent>()->getSprite());
        }
        if (object->GetComponent<TextComponent>() != nullptr and !gameOvered) {
            mWindow.draw(object->GetComponent<TextComponent>()->getText());
        } else if (object->GetComponent<TextComponent>()){
            mWindow.draw(gameOverText.GetComponent<TextComponent>()->getText());
        }
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
        playerTransform->updateRotation(-gameData.maxSpeed);

    else if(playerInput->IsKeyPressed(InputComponent::KEY::KEY_RIGHT))
        playerTransform->updateRotation(gameData.maxSpeed);

    if(playerInput->IsKeyPressed(InputComponent::KEY::KEY_UP)){
        playerTransform->setMovingForward(true);
        playerTransform->increaseSpeed(gameData.playerSpeed);

    } else if(playerInput->IsKeyPressed(InputComponent::KEY::KEY_DOWN)) {
        playerTransform->setMovingForward(true);
        playerTransform->decreaseSpeed(gameData.playerSpeed);
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