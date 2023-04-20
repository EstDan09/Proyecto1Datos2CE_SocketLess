//
// Created by dadu on 02/04/23.
//
#include <iostream>
#include "BulletD.h"
#include "Ammunation.h"
#ifndef PROYECTO1DATOS2CE_SERVER_SHIPPLAYER_H
#define PROYECTO1DATOS2CE_SERVER_SHIPPLAYER_H


class ShipPlayer {
public:
    ShipPlayer(int vida);

    ~ShipPlayer();

    int getVida() const;

    void setVida(int cVida);

    bool isAlive();

    void setAlive(bool cAlive);

    Ammunation* ammunation= new Ammunation();
private:
    int vida;
    bool alive;

};


#endif //PROYECTO1DATOS2CE_SERVER_SHIPPLAYER_H
