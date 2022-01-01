//
// Created by crayon on 28/12/2021.
//

#include "Menu.h"
#include "Game.h"
#include "../TextureManager.h"
#include "../Components/SpriteComponent.h"
#include "../Components/ButtonComponent.h"
#include "../Components/TextComponent.h"
#include "../Components/TransformComponent.h"


const sf::Time Menu::TimePerFrame = sf::seconds(1.f/60.f);

Object ButtonOne;
Object ButtonTwo;
Object ButtonThree;
Object Title;
Object Description;

const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 320;

Menu::Menu(): mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Main Menu!")
{
    InitButton("buttonOne",&ButtonOne, (SCREEN_WIDTH/2) - 100, SCREEN_HEIGHT/2, "Assets/spr_skeleton_idle_down.png");
    InitButton("buttonTwo",&ButtonTwo, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, "Assets/spr_skeleton_idle_down.png");
    InitButton("buttonThree",&ButtonThree, (SCREEN_WIDTH/2) + 100, SCREEN_HEIGHT/2, "Assets/spr_skeleton_idle_down.png");

    Title.AttachComponent<TextComponent>();
    Title.GetComponent<TextComponent>()->textSetup("CA 3 GAME", {SCREEN_WIDTH / 2, 10}, sf::Color::White, 24);
    AddObjects(&Title);

    Description.AttachComponent<TextComponent>();
    Description.GetComponent<TextComponent>()->textSetup("Choose Difficulty", {SCREEN_WIDTH / 2, SCREEN_HEIGHT - 80},
                                                         sf::Color::Yellow, 20);
    AddObjects(&Description);
}

void Menu::InitButton(std::string name, Object * button, int xPos, int yPos, std::string textureLocation)
{
    auto tempTextureID = TextureManager::AddTexture(textureLocation);
    button->AttachComponent<SpriteComponent>();
    button->GetComponent<SpriteComponent>()->setTexture(TextureManager::GetTexture(tempTextureID));
    button->GetComponent<SpriteComponent>()->setPosition(sf::Vector2f (xPos,yPos));
    button->AttachComponent<ButtonComponent>();
    button->GetComponent<ButtonComponent>()->setButtonName(name);
    AddObjects(button);
}

void Menu::Run()
{

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
    }
}


void Menu::processEvents()
{
    sf::Event event{};

    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                mWindow.close();
                break;
            default:
                break;
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            handlePlayerInput(sf::Mouse::getPosition(), false);
        }
    }
}

void Menu::update(sf::Time deltaTime)
{

}

void Menu::render()
{
    mWindow.clear();
    for (auto &object: m_gameObjects) {
        if (object->GetComponent<SpriteComponent>() != nullptr)
            mWindow.draw(object->GetComponent<SpriteComponent>()->getSprite());
        if (object->GetComponent<TextComponent>() != nullptr)
            mWindow.draw(object->GetComponent<TextComponent>()->getText());
    }
    mWindow.display();
}

void Menu::handlePlayerInput(sf::Vector2<int> key, bool isPressed)
{
    for (auto &object: m_gameObjects) {
        std::shared_ptr<SpriteComponent> sprite = object->GetComponent<SpriteComponent>();
        auto button = object->GetComponent<ButtonComponent>();

        if(button->checkButtonClick(sprite, sf::Mouse::getPosition(mWindow)) == "buttonOne")  {
            RunGame("Assets/data.json");
        }

        else if(button->checkButtonClick(sprite, sf::Mouse::getPosition(mWindow)) == "buttonTwo") {
            RunGame("Assets/data.json");
        }

        else if(button->checkButtonClick(sprite, sf::Mouse::getPosition(mWindow)) == "buttonThree") {
            RunGame("Assets/data.json");
        } else {
            return;
        }
    }
}

void Menu::RunGame(std::string jsonName) {

    Game game(jsonName);
    game.Run();

    m_gameObjects.clear();
    mWindow.close();
    return;
}
