//
// Created by dadu on 04/04/23.
//
#include "Strategys.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>
using namespace std;
using boost::property_tree::ptree;
/*
 * 1 = RATATATA
 * 2 = O Corona
 * 3 = La Curacao;
 * 4 = Amor Y Paz
 */
Strategys::Strategys() {
    Strategys::loadedP[0] = 1;
    Strategys::loadedP[1] = 2;
    Strategys::unloadedP[0] = 3;
    Strategys::unloadedP[1] = 4;
    Strategys::damageincreased = 2;
    Strategys::shield = 10000000;
}
Strategys::~Strategys() {}

int Strategys::getShield() const {
    return shield;
}

void Strategys::setShield(int shield) {
    Strategys::shield = shield;
}

int Strategys::getHealing() const {
    return healing;
}

void Strategys::setHealing(int healing) {
    Strategys::healing = healing;
}

int Strategys::getDamageincreased() const {
    return damageincreased;
}

void Strategys::setDamageincreased(int damageincreased) {
    Strategys::damageincreased = damageincreased;
}

int Strategys::getDamageEnemies() const {
    return damageEnemies;
}

void Strategys::setDamageEnemies(int damageEnemies) {
    Strategys::damageEnemies = damageEnemies;
}
int Strategys::activateP(char x, int prevHealth, int prevPlayerD, int prevEnemyD,  int maxHealth) {
    if(x==loadedP[0] || x==loadedP[1]){
        return inMemory(x, prevHealth, prevPlayerD, prevEnemyD, maxHealth);
    }
    else{
        return outOfMemory(x, prevHealth, prevPlayerD, prevEnemyD, maxHealth);
    }
}

int Strategys::deactivateP(char x) {
    switch (x) {
        case 1:
            return getAPrevPlayerD();
        case 2:
            return getAPrevHealth();
        case 4:
            return getAPrevEnemyD();
        default:
            return -1;
    }

}
int Strategys::inMemory(char x,int prevHealth, int prevPlayerD, int prevEnemyD, int maxHealth) {
    switch (x) {
        case 1:
            setAPrevPlayerD(prevPlayerD);
            return prevPlayerD*getDamageincreased();
        case 2:
            setAPrevHealth(prevHealth);
            return getShield();
        case 3:
            if(getHealing()+prevHealth>=maxHealth) {
                return getHealing();
            }
            else{
                return getHealing() + prevHealth;
            }
        case 4:
            setAPrevEnemyD(prevEnemyD);
            return getDamageEnemies();
        default:
            return -1;
    }
}

int Strategys::outOfMemory(char x,int prevHealth, int prevPlayerD, int prevEnemyD, int maxHealth) {
    char output;
    if(x==unloadedP[0]){
        output = loadedP[1];
        unloadedP[0]=loadedP[1];
        loadedP[1]= loadedP[0];
        loadedP[0] = x;
    }
    else{
        output = loadedP[1];
        unloadedP[1]=loadedP[1];
        loadedP[1]= loadedP[0];
        loadedP[0] = x;
    }
    switch(output){
        case 1:

            setDamageincreased(0);
            break;
        case 2:

            setShield(0);
            break;
        case 3:
            setHealing(0);
            break;
        case 4:
            setDamageEnemies(0);
            break;
        default:
            return -1;
    }
    switch (x) {
        case 1:
            setAPrevPlayerD(prevPlayerD);
            setDamageincreased(reader(1));
            return getAPrevPlayerD()*getDamageincreased();
        case 2:
            setAPrevHealth(prevHealth);
            setShield(reader(2));
            return getShield();
        case 3:
            setHealing(reader(3));
            if(getHealing()+getAPrevHealth()>=maxHealth) {
                return getHealing();
            }
            else{
                return getHealing() + getAPrevHealth();
            }
        case 4:
            setAPrevEnemyD(prevEnemyD);
            setDamageEnemies(reader(4));
            return getDamageEnemies();
        default:
            return -1;
    }

}

int Strategys::getAPrevHealth() {
    return aPrevHealth;
}

void Strategys::setAPrevHealth(int prevHealth) {
    Strategys::aPrevHealth = prevHealth;
}

int Strategys::getAPrevPlayerD() const{
    return aPrevPlayerD;
}

void Strategys::setAPrevPlayerD(int prevPlayerD) {
    Strategys::aPrevPlayerD = prevPlayerD;
}

int Strategys::getAPrevEnemyD() const{
    return aPrevEnemyD;
}

void Strategys::setAPrevEnemyD(int prevEnemyD) {
    Strategys::aPrevEnemyD = prevEnemyD;
}

int Strategys::reader(char x){
    switch (x) {
        case 1:
            path = "RATATATA";
            break;
        case 2:
            path = "OCorona";
            break;
        case 3:
            path = "LaCuracao";
            break;
        case 4:
            path = "AmorYPaz";
            break;
        default:
            cout<<"caracter equivocado"<<endl;
    }
    ptree pt;
    string fullPath = "/home/dadu/Documents/GitHub/Proyecto1Datos2CE_Server/" + path + ".xml";
    read_xml(fullPath,pt);
    int value;
    BOOST_FOREACH( boost::property_tree::ptree::value_type const& node, pt.get_child( path + ".Powers" ) )
                {
                    boost::property_tree::ptree subtree = node.second;

                    BOOST_FOREACH( boost::property_tree::ptree::value_type const& v, subtree.get_child( "" ) )
                                {
                                    std::string label = v.first;

                                    if ( label != "<xmlattr>" )
                                    {
                                        value = stoi(subtree.get<std::string>( label ));
                                    }
                                }

                }
    return value;
}

