//
// Created by crayon on 01/01/2022.
//

#include "TagComponent.h"

TagComponent::TagComponent(std::string tag) {
    m_tag = tag;
}

void TagComponent::setTag(std::string tag) {
    m_tag = tag;
}

std::string TagComponent::getTag() {
    return m_tag;
}
