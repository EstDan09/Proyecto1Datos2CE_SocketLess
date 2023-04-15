//
// Created by esteban on 4/6/23.
//

#include "Enemy.h"

Enemy::Enemy(raylib::Texture *texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed,
               raylib::Texture* textureForBullet, bool stop)
        : Entity(texture, inClip, outClip), speed(speed), shootingTime(0.0f), stop(stop){
    bullet = new Bullet(textureForBullet, raylib::Rectangle(56,40, 8,-8),
                   outClip, speed*(-4.0f), 0);
    shootingTime = 0;
    outClipB = bullet->getOutClip();
}

Enemy::~Enemy(){
    delete bullet;
}

void Enemy::Update() {

    if(shootingTime <= 0){

        if(bullet->IsHit()){
            bullet->Reset(outClip);
            outClipB = bullet->getOutClip();
            shootingTime = 5.0f; //cadencia
        }

    }
    else{
        shootingTime -= GetFrameTime();
    }


    if(!bullet->IsHit()){
        bullet->Update();
        outClipB = bullet->getOutClip();

    }
    if (!stop){
        outClip.x -= 1;
        if (outClip.x < 0){
            //stop
        }
    }



}

void Enemy::Draw() {

    if(!bullet->IsHit()){
        bullet->Draw();
    }
    texture->Draw(inClip, outClip);
}

raylib::Rectangle Enemy::getOutclip() {
    return outClip;
}

void Enemy::setOutClip(raylib::Rectangle outClipNew) {
    outClip = outClipNew;
}

raylib::Rectangle Enemy::getOutclipB() {
    return outClipB;
}

void Enemy::setOutClipB(raylib::Rectangle outClipNew) {
    bullet->setOutClip(outClipNew);
}