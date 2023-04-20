//
// Created by dadu on 02/04/23.
//

#include "ShipEnemy.h"
ShipEnemy::ShipEnemy() {
    ShipEnemy::nextEnemy = nullptr;
    ShipEnemy::vida = 100;
    ShipEnemy::alive = true;
}
ShipEnemy::~ShipEnemy() {}

ShipEnemy *ShipEnemy::getNextEnemy() const {
    return nextEnemy;
}

void ShipEnemy::setNextEnemy(ShipEnemy *nextEnemy) {
    ShipEnemy::nextEnemy = nextEnemy;
}

int ShipEnemy::getVida() {
    return vida;
}

void ShipEnemy::setVida(int cVida) {
    ShipEnemy::vida = cVida;
}

bool ShipEnemy::isAlive(){
    return alive;
}

void ShipEnemy::setAlive(bool cAlive) {
    ShipEnemy::alive = cAlive;
}

int ShipEnemy::getCode() {
    return code;
}

void ShipEnemy::setCode(int code) {
    ShipEnemy::code = code;
}
