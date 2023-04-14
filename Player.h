//
// Created by esteban on 4/5/23.
//

#ifndef PROYECTO1DATOS2CE_CLIENTE_PLAYER_H
#define PROYECTO1DATOS2CE_CLIENTE_PLAYER_H


#include "Entity.h"
#include "Bullet.h"

class Player : public Entity{

public:
    Player(raylib::Texture* texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed,
           raylib::Texture* textureForBullets, float delay);
    ~Player();
    void Event();
    void Update();
    void Draw();
    raylib::Rectangle getOutClip();
    raylib::Rectangle getOutClipB1();
    raylib::Rectangle getOutClipB2();
    raylib::Rectangle getOutClipB3();
    raylib::Rectangle getOutClipB4();
    void setOutClip(raylib::Rectangle outClipNew);
    void setOutClipB1(raylib::Rectangle outClipNew);
    void setOutClipB2(raylib::Rectangle outClipNew);
    void setOutClipB3(raylib::Rectangle outClipNew);
    void setOutClipB4(raylib::Rectangle outClipNew);
    void setDelay(float x);

private:
    bool alive;
    float speed;
    Bullet* bullets;
    int maxBullets;
    float shootingTime;
    float shootingDelay;
    raylib::Rectangle outClipB1;
    raylib::Rectangle outClipB2;
    raylib::Rectangle outClipB3;
    raylib::Rectangle outClipB4;
};



#endif //PROYECTO1DATOS2CE_CLIENTE_PLAYER_H
