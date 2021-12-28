//
//  TextureManager.cpp
//  SimplisticComponentECS
//
//  Created by Denis Flynn on 10/11/2021.
//  Copyright © 2021 Denis Flynn. All rights reserved.
//

#include "TextureManager.h"
int TextureManager::AddTexture(std::string filePath)
{
    auto it = m_textures.find(filePath);

    if (it != m_textures.end())
    {
        return it->second.first;
    }

    // At this point the texture doesn't exists, so we'll create and add it.
    m_currentId++;

    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
    if (!texture->loadFromFile(filePath))
    {
        return -1;
    }

    m_textures.insert(std::make_pair(filePath, std::make_pair(m_currentId, std::move(texture))));

    return m_currentId;
}

void TextureManager::RemoveTexture(int textureID)
{
    for (auto it = m_textures.begin(); it != m_textures.end(); ++it)
    {
        if (it->second.first == textureID)
        {
            m_textures.erase(it->first);
        }
    }
}


sf::Texture& TextureManager::GetTexture(int textureID)
{
    for (auto it = m_textures.begin(); it != m_textures.end(); ++it)
    {
        if (it->second.first == textureID)
        {
            return *it->second.second;
        }
    }
}

///Because the texturemanager class has static members, we must declare them outside of the class - a strange but necessary step
std::map<std::string, std::pair<int, std::unique_ptr<sf::Texture>>> TextureManager::m_textures;
int TextureManager::m_currentId = 0; //initial currentId is zero
