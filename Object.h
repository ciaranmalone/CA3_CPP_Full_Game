//
//  Object.hpp
//  SimplisticComponentECS
//
//  Created by Denis Flynn on 01/11/2021.
//  Copyright © 2021 Denis Flynn. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <memory>
#include <cstdarg> //added - for variadic args
#include "Components/Component.h"

class Object
{
    //do nothing for the moment, except, add and remove components.

public:

    /**
        Variable parameter version.
        Note we are using Variadic templates here, see e.g. https://eli.thegreenplace.net/2014/variadic-templates-in-c/
     */

    template <typename T, typename... Args>
    std::shared_ptr<T> AttachComponent(Args... args)
    {
        // Create the component.
        std::shared_ptr<T> newComponent = std::make_shared<T>();
        // Check that we don't already have a component of this type.
        for (std::shared_ptr<Component>& exisitingComponent : m_components)
        {
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
                // If we do replace it.
                exisitingComponent = newComponent;
                return newComponent;
            }

        }

        // The component is the first of its type so add it.
        m_components.push_back(newComponent);

        return newComponent;
    }

    /**
        Gets our component
     */
    template <typename T>
    std::shared_ptr<T> GetComponent()//returning effectively T*
    {
        // Check that we have a component of this type.
        for (std::shared_ptr<Component> exisitingComponent : m_components)
        {
            if (std::dynamic_pointer_cast<T>(exisitingComponent))
            {
                return std::dynamic_pointer_cast<T>(exisitingComponent);
            }
        }
        //std::cerr <<"did we just return a nullptr?\n";
        return nullptr;
    }

private:
    //A collection of all components the object has attached.
    std::vector<std::shared_ptr<Component>> m_components; //vector<Component*> m_component


};


#endif /* Object_hpp */
