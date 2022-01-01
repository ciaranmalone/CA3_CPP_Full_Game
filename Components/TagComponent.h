//
// Created by crayon on 01/01/2022.
//

#ifndef CA2_TAGCOMPONENT_H
#define CA2_TAGCOMPONENT_H

#include <string>
#include "Component.h"
#include <memory>

class TagComponent: public Component{


public:

    TagComponent() {};

    TagComponent(std::string tag);;

    void setTag(std::string tag);

    std::string getTag();

    std::string m_tag;

};


#endif //CA2_TAGCOMPONENT_H
