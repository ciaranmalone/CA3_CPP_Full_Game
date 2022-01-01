//
//  TransformCmpt.cpp
//  SimplisticComponentECS
//
//  Created by Denis Flynn on 03/11/2021.
//  Copyright © 2021 Denis Flynn. All rights reserved.
//
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include "TransformComponent.h"

TransformComponent::TransformComponent() {
    //"safe" defaults
    m_position.x = 0;
    m_position.y = 0;
    //new v0.5
    m_speed = {0, 0};
}

TransformComponent::TransformComponent(int x, int y) {
    m_position.x = x;
    m_position.y = y;
    //new v0.5
    m_speed = {0, 0};
}

TransformComponent::TransformComponent(sf::Vector2f pos) {
    m_position = pos;
    //new v0.5
    m_speed = {0, 0};
}

void TransformComponent::setPosition(sf::Vector2f pos) {

    m_position = pos;
}

sf::Vector2f TransformComponent::getPosition() {
    return m_position;
}

float TransformComponent::getRotation(){
    return  m_rotation;
}

void TransformComponent::updatePosition() {
    m_position += m_speed;
}

void TransformComponent::updatePosition(sf::Vector2f speed) {
    m_speed = speed;
    m_position += m_speed;
}
void TransformComponent::updatePositionY(float y) {
    m_position.y += y;
}


void TransformComponent::updateRotation(float d) {
    m_rotation += d;
}

void TransformComponent::updatePositionX(float x) {
    m_position.x += x;
}

void TransformComponent::decreaseSpeed(float speed) {
    if (m_thrust > 0) {
        m_thrust -= speed;
    }
    else {
        m_thrust = 0;
    }
}

void TransformComponent::increaseSpeed(float speed) {
    if (m_thrust < max_thrust) {
        m_thrust += speed;
    }
    else {
        m_thrust = max_thrust;
    }
}

float TransformComponent::getThrust() {
    return m_thrust;
}

void TransformComponent::setThrust(float thrust) {
    m_thrust =  thrust;
}

void TransformComponent::setMovingForward(bool set) {
    movingForward = set;
}

bool TransformComponent::getMovingForward() {
    return movingForward;
}

void TransformComponent::setRotation(float d) {
    m_rotation = d;
}


