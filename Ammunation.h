//
// Created by dadu on 02/04/23.
//

#ifndef PROYECTO1DATOS2CE_SERVER_AMMUNATION_H
#define PROYECTO1DATOS2CE_SERVER_AMMUNATION_H

#include "BulletD.h"
#include "BulletCollector.h"
class Ammunation {
public:
    Ammunation();

    ~Ammunation();

    BulletCollector* bulletCollector =new BulletCollector();

    BulletD *getHead() const;

    void setHead(BulletD *nHead);

    int getQuantity();

    void setQuantity(int nQuantity);

    void insertBullets(int num);

    void noImpact();

    void impact();

    int getDamage();

    void setDamage(int damage);



private:
    int quantity;
    BulletD* head;
    int damage;
    bool noAmmunation;
};




#endif //PROYECTO1DATOS2CE_SERVER_AMMUNATION_H
