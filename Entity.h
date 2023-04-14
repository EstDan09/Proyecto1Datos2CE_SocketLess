//
// Created by esteban on 4/5/23.
//

#ifndef PROYECTO1DATOS2CE_CLIENTE_ENTITY_H
#define PROYECTO1DATOS2CE_CLIENTE_ENTITY_H

#include "/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/raylib-cpp-4.5.0/include/raylib-cpp.hpp"



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
