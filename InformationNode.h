//
// Created by dadu on 16/04/23.
//

#ifndef PROYECTO1DATOS2CE_CLIENTE_INFORMATIONNODE_H
#define PROYECTO1DATOS2CE_CLIENTE_INFORMATIONNODE_H


class InformationNode {
public:
    InformationNode(char nType, int data);

    ~InformationNode();

    char getType() const;

    int getData() const;

    void setData(int data);

private:

    char type;

    int data;

};


#endif //PROYECTO1DATOS2CE_CLIENTE_INFORMATIONNODE_H
