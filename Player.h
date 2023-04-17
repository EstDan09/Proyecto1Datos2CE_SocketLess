//
// Created by esteban on 4/5/23.
//

#ifndef PROYECTO1DATOS2CE_CLIENTE_PLAYER_H
#define PROYECTO1DATOS2CE_CLIENTE_PLAYER_H


#include "Entity.h"
#include "Bullet.h"
#include "Enemy.h"
#include "InGame.h"

#include <boost/asio.hpp>




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
    raylib::Rectangle getOutClipB5();
    raylib::Rectangle getOutClipB6();
    raylib::Rectangle getOutClipB7();
    raylib::Rectangle getOutClipB8();
    raylib::Rectangle getOutClipB9();
    raylib::Rectangle getOutClipB10();

    void setOutClip(raylib::Rectangle outClipNew);
    void setOutClipB1(raylib::Rectangle outClipNew);
    void setOutClipB2(raylib::Rectangle outClipNew);
    void setOutClipB3(raylib::Rectangle outClipNew);
    void setOutClipB4(raylib::Rectangle outClipNew);
    void setOutClipB5(raylib::Rectangle outClipNew);
    void setOutClipB6(raylib::Rectangle outClipNew);
    void setOutClipB7(raylib::Rectangle outClipNew);
    void setOutClipB8(raylib::Rectangle outClipNew);
    void setOutClipB9(raylib::Rectangle outClipNew);
    void setOutClipB10(raylib::Rectangle outClipNew);

    void setEnemy1(Enemy x);
    void setEnemy2(Enemy x);
    void setEnemy3(Enemy x);
    void setEnemy4(Enemy x);
    void setEnemy5(Enemy x);
    void setEnemy6(Enemy x);
    void setEnemy7(Enemy x);
    void setEnemy8(Enemy x);

    void setDelay(float x);
    void ricoMauro();

    boost::asio::io_service io;
    boost::asio::serial_port  port = boost::asio::serial_port(io, "/dev/ttyACM0");

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
    raylib::Rectangle outClipB5;
    raylib::Rectangle outClipB6;
    raylib::Rectangle outClipB7;
    raylib::Rectangle outClipB8;
    raylib::Rectangle outClipB9;
    raylib::Rectangle outClipB10;

    Enemy enemy1;
    Enemy enemy2;
    Enemy enemy3;
    Enemy enemy4;
    Enemy enemy5;
    Enemy enemy6;
    Enemy enemy7;
    Enemy enemy8;








};



#endif //PROYECTO1DATOS2CE_CLIENTE_PLAYER_H
