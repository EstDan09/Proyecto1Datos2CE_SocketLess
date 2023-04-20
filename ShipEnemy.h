//
// Created by dadu on 02/04/23.
//

#ifndef PROYECTO1DATOS2CE_SERVER_SHIPENEMY_H
#define PROYECTO1DATOS2CE_SERVER_SHIPENEMY_H
#include <iostream>
#include "Ammunation.h"


class ShipEnemy {
public:
    ShipEnemy();

    ~ShipEnemy();

    ShipEnemy* nextEnemy;

    ShipEnemy *getNextEnemy() const;

    void setNextEnemy(ShipEnemy *nextEnemy);

    int getVida();

    void setVida(int cVida);

    bool isAlive();

    void setAlive(bool cAlive);

    int getCode();

    void setCode(int code);


private:
    int vida;
    bool alive;
    int code;

};


#endif //PROYECTO1DATOS2CE_SERVER_SHIPENEMY_H
