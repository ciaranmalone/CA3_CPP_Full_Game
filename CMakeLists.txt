cmake_minimum_required(VERSION 3.21)
project(CA2)

set(CMAKE_CXX_STANDARD 14)

add_executable(CA2 main.cpp Scenes/Game.cpp Scenes/Game.h Object.h Components/Component.cpp Components/Component.h Components/SpriteComponent.cpp Components/SpriteComponent.h Components/TransformComponent.cpp Components/TransformComponent.h TextureManager.cpp TextureManager.h Components/InputComponent.cpp Components/InputComponent.h Components/PhysicsComponent.cpp Components/PhysicsComponent.h Scenes/Menu.cpp Scenes/Menu.h)
find_package(SFML 2.5
        COMPONENTS
        system window graphics network audio REQUIRED)

include(FetchContent)

FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
        GIT_TAG v3.10.4)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

target_link_libraries(CA2 PRIVATE
        sfml-system sfml-window sfml-graphics sfml-network sfml-audio
        nlohmann_json::nlohmann_json)