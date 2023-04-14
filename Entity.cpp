//
// Created by esteban on 4/5/23.
//

#include "Entity.h"

Entity::Entity(raylib::Texture *texture, raylib::Rectangle inClip, raylib::Rectangle outClip) {
    this->texture = texture;
    this->inClip = inClip;
    this->outClip = outClip;
}

void Entity::Event() {
    //nothing
}

void Entity::Update() {
    //nothing
}


void Entity::Draw() {
    texture->Draw(inClip, outClip);
}



