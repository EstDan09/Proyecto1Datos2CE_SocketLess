//
// Created by dadu on 02/04/23.
//

#include "Waves.h"
#include <iostream>
using namespace std;
Waves::Waves(){
    Waves::head= nullptr;
    size = 0;
}
Waves::~Waves(){}
ShipEnemy *Waves::getHead() const{
    return head;
}

void Waves::setHead(ShipEnemy *nHead) {
    head = nHead;
}
int Waves::getGenDamage() {
    return genDamage;
}

void Waves::setGenDamage(int genDamage) {
    Waves::genDamage = genDamage;
}


void Waves::insertShips(int numShips) {
    ShipEnemy* tempShip = new ShipEnemy();
    tempShip->setCode(0);
    setHead(tempShip);
    size ++;
    for(int i = 1; i<numShips;i++ ){
        ShipEnemy* tempShip = new ShipEnemy();
        tempShip->setCode(i);
        tempShip->setNextEnemy(head);
        setHead(tempShip);
        size ++;
    }
}
bool Waves::colShip(int sCode, int damage){
    ShipEnemy* tmp = head;
    while(tmp!= nullptr){
        if(tmp->getCode()==sCode){
            tmp->setVida(tmp->getVida()-damage);
            if(tmp->getVida()<=0){
                tmp->setAlive(false);
            }
            return tmp->isAlive();
        }
        else{
            tmp = tmp->getNextEnemy();
        }
    }
}



