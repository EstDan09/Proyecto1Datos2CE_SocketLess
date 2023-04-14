//
// Created by esteban on 4/5/23.
//

#ifndef PROYECTO1DATOS2CE_CLIENTE_BACKGROUND_H
#define PROYECTO1DATOS2CE_CLIENTE_BACKGROUND_H

#include "Entity.h"

class Background : public Entity{
public:
    Background(raylib::Texture* texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed);
    void Update();
    void DrawSegment();
    void Draw();
private:
    float speed;
};


#endif //PROYECTO1DATOS2CE_CLIENTE_BACKGROUND_H
