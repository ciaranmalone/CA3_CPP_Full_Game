cmake_minimum_required(VERSION 3.21)
project(CA2)

set(CMAKE_CXX_STANDARD 14)

add_executable(CA2 main.cpp Game.cpp Game.h Object.h Components/Component.cpp Components/Component.h Components/SpriteComponent.cpp Components/SpriteComponent.h Components/TransformComponent.cpp Components/TransformComponent.h TextureManager.cpp TextureManager.h Components/InputComponent.cpp Components/InputComponent.h Components/PhysicsComponent.cpp Components/PhysicsComponent.h)
find_package(SFML 2.5
        COMPONENTS
        system window graphics network audio REQUIRED)

include(FetchContent)

target_link_libraries(CA2 PRIVATE
        sfml-system sfml-window sfml-graphics sfml-network sfml-audio)