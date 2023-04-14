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

    std::string getPatreon();

    void setPatreon(std::string nPatreon);

    std::string getColour();

    void setColour(std::string nColour);

    int getCode();

    void setCode(int code);


private:
    int vida;
    bool alive;
    std::string patreon;
    std::string colour;
    int code;

};


#endif //PROYECTO1DATOS2CE_SERVER_SHIPENEMY_H
