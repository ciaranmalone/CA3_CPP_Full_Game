//
//  TextureManager.hpp
//  SimplisticComponentECS
//
//  Created by Denis Flynn on 10/11/2021.
//  Copyright © 2021 Denis Flynn. All rights reserved.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

#include <iostream>
#include <map>
#include "Scenes/Game.h"

class TextureManager
{
private:
    static int m_currentId; ///current Key value
    ///A map of each texture along with its ID
    ///e.g. {filename,  (ID,  pointer to texture)  }
    static std::map<std::string, std::pair<int, std::unique_ptr<sf::Texture>>> m_textures;

    TextureManager(){}
public:

    static int AddTexture(std::string filePath);


    static void RemoveTexture(int textureID);

    // Gets a texture from the texture manager from an ID.
    static sf::Texture& GetTexture(int textureID);


};


#endif /* TextureManager_hpp */
