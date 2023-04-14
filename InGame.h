//
// Created by dadu on 08/04/23.
//

#ifndef PROYECTO1DATOS2CE_SERVER_INGAME_H
#define PROYECTO1DATOS2CE_SERVER_INGAME_H
#include "Waves.h"

class InGame {
public:
    InGame();

    ~InGame();

    Waves* waves[15];

    void changeDifficulty(char x);

    Waves *getCurrentWave();

    void setCurrentWave(Waves *currentWave);

    bool checkNextW();

    int countCurrent;
private:

    Waves* currentWave;
};


#endif //PROYECTO1DATOS2CE_SERVER_INGAME_H
