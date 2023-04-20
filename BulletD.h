//
// Created by esteban on 3/29/23.
//

#ifndef PROYECTO1DATOS2CE_SERVER_BULLETD_H
#define PROYECTO1DATOS2CE_SERVER_BULLETD_H


class BulletD {
public:
    BulletD();
    ~BulletD();
    bool getRecycled() const;
    BulletD* getNextPtr() const;
    void setNextPtr(BulletD* next);
    void setRecycled(bool nCondition);
    BulletD* next;
private:
    bool recycled;
};


#endif //PROYECTO1DATOS2CE_SERVER_BULLETD_H
