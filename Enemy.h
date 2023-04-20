//
// Created by esteban on 4/6/23.
//

#ifndef PROYECTO1DATOS2CE_CLIENTE_ENEMY_H
#define PROYECTO1DATOS2CE_CLIENTE_ENEMY_H

#include "Entity.h"
#include "Bullet.h"

class Enemy : public Entity{
public:
    Enemy(raylib::Texture* texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed,
            raylib::Texture* textureForBullet, bool stop, int move);
    ~Enemy();
    void Update();
    void Draw();
    raylib::Rectangle getOutclip();
    raylib::Rectangle getOutclipB();
    void setOutClip(raylib::Rectangle outClipNew);
    void setOutClipB(raylib::Rectangle outClipNew);
    int getMove();

private:
    float speed;
    Bullet* bullet;
    float shootingTime;
    bool stop;
    raylib::Rectangle outClipB;
    int move;

};


#endif //PROYECTO1DATOS2CE_CLIENTE_ENEMY_H
