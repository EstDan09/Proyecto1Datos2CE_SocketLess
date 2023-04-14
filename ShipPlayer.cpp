//
// Created by dadu on 02/04/23.
//

#include "ShipPlayer.h"

ShipPlayer::ShipPlayer(int sVida){
    ShipPlayer::vida = sVida;
    //ShipPlayer::vida = 100;

}
ShipPlayer::~ShipPlayer() {}

int ShipPlayer::getVida() const {
    return vida;
}

void ShipPlayer::setVida(int cVida) {
    ShipPlayer::vida = cVida;
}

const std::string &ShipPlayer::getSelecPower() const {
    return selecPower;
}

void ShipPlayer::setSelecPower(const std::string nSelecPower) {
    ShipPlayer::selecPower = nSelecPower;
}

bool ShipPlayer::isAlive(){
    if(vida<=0){
        return false;
    }
    return true;
}

void ShipPlayer::setAlive(bool cAlive) {
    ShipPlayer::alive = cAlive;
}




