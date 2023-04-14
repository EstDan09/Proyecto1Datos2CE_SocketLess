//
// Created by esteban on 3/29/23.
//

#include "BulletD.h"

BulletD::BulletD() {
    BulletD::recycled = false;
    BulletD::next = nullptr;
}
BulletD::~BulletD(){}

bool BulletD::getRecycled() const {
    return recycled;
}
BulletD* BulletD::getNextPtr() const {
    return next;
}
void BulletD::setRecycled(bool nCondition) {
    BulletD::recycled = nCondition;
}
void BulletD::setNextPtr(BulletD *next) {
    BulletD::next = next;
}
