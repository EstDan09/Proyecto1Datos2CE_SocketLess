//
// Created by dadu on 04/04/23.
//

#ifndef PROYECTO1DATOS2CE_SERVER_STRATEGYS_H
#define PROYECTO1DATOS2CE_SERVER_STRATEGYS_H
#include <iostream>
#include "Ammunation.h"
#include "InformationNode.h"

using namespace std;

class Strategys {
public:
    Strategys();
    ~Strategys();

    void selectingS(char x);

    int getShield() const;

    void setShield(int shield);

    int getHealing() const;

    void setHealing(int healing);

    int getDamageincreased() const;

    void setDamageincreased(int damageincreased);

    int getDamageEnemies() const;

    void setDamageEnemies(int damageEnemies);

    InformationNode* loadedP[2];

    int activateP(char x, int prevHealth, int prevPlayerD, int prevEnemyD, int maxHealth);

    int inMemory(char x,int prevHealth, int prevPlayerD, int prevEnemyD, int maxHealth);

    int outOfMemory(char x,int prevHealth, int prevPlayerD, int prevEnemyD, int maxHealth);

    int getAPrevHealth();

    void setAPrevHealth(int aPrevHealth);

    int getAPrevPlayerD() const;

    void setAPrevPlayerD(int aPrevPlayerD);

    int getAPrevEnemyD() const;

    void setAPrevEnemyD(int aPrevEnemyD);

    int reader(char x);

    string path;

    int deactivateP(char x);

    bool isLoaded(char x);

private:
    int shield;
    int healing;
    int damageincreased;
    int damageEnemies;
    int aPrevHealth;
    int aPrevPlayerD;
    int aPrevEnemyD;

};


#endif //PROYECTO1DATOS2CE_SERVER_STRATEGYS_H
