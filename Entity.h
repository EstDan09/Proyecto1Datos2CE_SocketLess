//
// Created by esteban on 4/5/23.
//

#ifndef PROYECTO1DATOS2CE_CLIENTE_ENTITY_H
#define PROYECTO1DATOS2CE_CLIENTE_ENTITY_H

#include "/home/dadu/Documents/GitHub/Proyecto1Datos2CE_SocketLess/assets/raylib-cpp-4.5.0/include/raylib-cpp.hpp"
#include "assets/raylib-cpp-4.5.0/include/Texture.hpp"


class Entity {
public:
    Entity(raylib::Texture* texture, raylib::Rectangle inClip, raylib::Rectangle outClip);
    virtual void Event();
    virtual void Update();
    virtual void Draw();

protected:
    raylib::Texture* texture;
    raylib::Rectangle inClip;
    raylib::Rectangle outClip;
};


#endif //PROYECTO1DATOS2CE_CLIENTE_ENTITY_H
