//
// Created by dadu on 02/04/23.
//

#include "BulletCollector.h"
#include <iostream>
using namespace std;
BulletCollector::BulletCollector()  {
    BulletCollector::cHeadPtr = nullptr;
    BulletCollector::quantity = 0;
}

int BulletCollector::getQuantity() const {
    return quantity;
}

void BulletCollector::setQuantity(int nQuantity) {
    BulletCollector::quantity = nQuantity;
}

void BulletCollector::insertF(BulletD* x){
    if (cHeadPtr == nullptr){
        cHeadPtr = x;
        cHeadPtr->setNextPtr(nullptr);
        quantity++;
    }
    else{
        x->setNextPtr(cHeadPtr); //aca
        cHeadPtr= x;
        quantity++;
    }
}
void BulletCollector::deleteF(){
    if ( cHeadPtr->getNextPtr() == nullptr){
        cHeadPtr = nullptr;
        quantity--;
    }
    else{
        BulletD* tmp = cHeadPtr;
        cHeadPtr = tmp->next;
        delete tmp;
        quantity--;
    }

}
bool BulletCollector::available() const{
    if (cHeadPtr == nullptr){
        return false;
    }
    else{
        return true;
    }
}
void BulletCollector::showCol() const{
    if(cHeadPtr != nullptr){
        for(BulletD* temp = cHeadPtr; temp != nullptr; temp=temp->next){
           cout << temp << endl;
        }
    }
    else{
        cout << "estoy empty :(" << endl;
    }
}

int BulletCollector::getDamage(){
    return damage;
}

void BulletCollector::setDamage(int damage) {
    BulletCollector::damage = damage;
}
