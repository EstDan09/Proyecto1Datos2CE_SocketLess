//
// Created by dadu on 02/04/23.
//

#include "Ammunation.h"
#include <iostream>

using namespace std;
Ammunation::Ammunation() {
    Ammunation::quantity=0;
    Ammunation::damage= 22;
    Ammunation::bulletCollector->setDamage(Ammunation::getDamage()/2);
    Ammunation::head = nullptr;
    Ammunation::noAmmunation=false;
}

Ammunation::~Ammunation(){}

BulletD *Ammunation::getHead() const {
    return head;
}

void Ammunation::setHead(BulletD *nHead) {
    Ammunation::head = nHead;
}

int Ammunation::getQuantity() {
    return quantity;
}

void Ammunation::setQuantity(int nQuantity) {
    Ammunation::quantity = nQuantity;
}

void Ammunation::insertBullets(int num) {
    if (getQuantity() ==0 && num==1){
        Ammunation::setHead(new BulletD);
        quantity++;
    }
    else if (getQuantity()==0 && num!=1){
        Ammunation::setHead(new BulletD);
        quantity++;
        for(int i = 1; i<num;i++){
            BulletD* nBullet = new BulletD;
            nBullet->setNextPtr(head);
            head = nBullet;
            quantity++;
        }
    }
    else{
        for(int i = 0; i<num;i++){
            BulletD* nBullet = new BulletD;
            nBullet->setNextPtr(head);
            head = nBullet;
            quantity++;
        }
    }
}
void Ammunation::noImpact() {
    if ( head->getNextPtr() == nullptr){
        Ammunation::bulletCollector->insertF(head);
        head = nullptr;
        quantity--;
    }
    else{
        //BulletD* tmp = head;

        BulletD* tmp1 = head;
        head = tmp1->next;
        Ammunation::bulletCollector->insertF(tmp1);
        cout<< head << endl;
        quantity--;


    }
}
void Ammunation::impact(){
    if ( head->getNextPtr() == nullptr){
        head = nullptr;
        quantity--;
    }
    else{
        BulletD* tmp2 = head;
        head = tmp2->next;
        quantity--;
        delete tmp2;
    }
}

int Ammunation::countBullets() {
    int i =0;
    BulletD* tmp = head;
    while(tmp!= nullptr){
        i++;
        tmp=tmp->next;
    }
    return i;
}

int Ammunation::getDamage(){
    return damage;
}

void Ammunation::setDamage(int damage) {
    Ammunation::damage = damage;
}

bool Ammunation::isNoAmmunation() const {
    return noAmmunation;
}

void Ammunation::setNoAmmunation(bool noAmmunation) {
    Ammunation::noAmmunation = noAmmunation;
}
