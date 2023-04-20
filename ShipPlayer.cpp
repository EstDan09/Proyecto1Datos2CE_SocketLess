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

bool ShipPlayer::isAlive(){
    if(vida<=0){
        return false;
    }
    return true;
}

void ShipPlayer::setAlive(bool cAlive) {
    ShipPlayer::alive = cAlive;
}




