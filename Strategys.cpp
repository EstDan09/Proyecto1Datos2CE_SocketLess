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
 * 0 = RATATATA
 * 1 = O Corona
 * 2 = La Curacao;
 * 3 = Amor Y Paz
 */
//shipPlayer->Ammunation.setDamage(strategys->activateP(0))
//shipPlayer->Ammunation.setDamage(strategys->deActivateP(0))
//shipPlayer->setVida(strategys->activateP(1))
//shipPlayer->setVida(strategys->deActivateP(1))
//shipPlayer->setVida(strategys->activateP(2))
//inGame->currentWve->setDamage(strategys->activateP(3))
//inGame->currentWve->setDamage(strategys->deActivateP(3))
Strategys::Strategys() {

    Strategys::loadedP[0] = new InformationNode(0,2);
    Strategys::loadedP[1] = new InformationNode(1,1000000000);
    //Strategys::damageincreased = 2;
    //Strategys::shield = 10000000;
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
    if(x==loadedP[0]->getType() || x==loadedP[1]->getType()){
        return inMemory(x, prevHealth, prevPlayerD, prevEnemyD, maxHealth);
    }
    else{
        return outOfMemory(x, prevHealth, prevPlayerD, prevEnemyD, maxHealth);
    }
}

int Strategys::deactivateP(char x) {
    switch (x) {
        case 0:
            return getAPrevPlayerD();
        case 1:
            return getAPrevHealth();
        case 3:
            return getAPrevEnemyD();
        default:
            return -1;
    }

}
int Strategys::inMemory(char x,int prevHealth, int prevPlayerD, int prevEnemyD, int maxHealth) {
    switch (x) {
        case 0:
            setAPrevPlayerD(prevPlayerD);
            if(loadedP[0]->getType()==0) {
                return prevPlayerD * loadedP[0]->getData();
            }
            else{
                return prevPlayerD * loadedP[1]->getData();
            }
        case 1:
            setAPrevHealth(prevHealth);
            if(loadedP[0]->getType()==1){
                return loadedP[0]->getData();
            }
            else{
                return loadedP[1]->getData();
            }
        case 2:
            if(loadedP[0]->getType()==2) {
                if (getHealing() + prevHealth >= maxHealth) {
                    return maxHealth;
                } else {
                    return getHealing() + loadedP[0]->getData();
                }
            }
            else{
                if (getHealing() + prevHealth >= maxHealth) {
                    return maxHealth;
                } else {
                    return getHealing() + loadedP[1]->getData();
                }
            }
        case 3:
            setAPrevEnemyD(prevEnemyD);
            if(loadedP[0]->getType()==3){
                return loadedP[0]->getData();
            }
            else{
                return loadedP[1]->getData();
            }
        default:
            return -1;
    }
}

int Strategys::outOfMemory(char x,int prevHealth, int prevPlayerD, int prevEnemyD, int maxHealth) {
    char output;
    if(x==0){
        setAPrevPlayerD(prevPlayerD);
        double data = reader(0);
        InformationNode* tmpNode = new InformationNode(0,data);
        loadedP[1]=loadedP[0];
        loadedP[0]=tmpNode;
        return getAPrevPlayerD() * loadedP[0]->getData();
    }
    else if(x==1){
        setAPrevHealth(prevHealth);
        int data = reader(1);
        InformationNode* tmpNode = new InformationNode(1,data);
        loadedP[1]=loadedP[0];
        loadedP[0]=tmpNode;
        return getAPrevPlayerD()*tmpNode->getData();
    }
    else if (x==2){
        int data = reader(2);
        InformationNode* tmpNode = new InformationNode(2,data);
        loadedP[1]=loadedP[0];
        loadedP[0]=tmpNode;
        if(getHealing()+getAPrevHealth()>=maxHealth) {
            return maxHealth;
        }
        else{
            return loadedP[0]->getData() + getAPrevHealth();
        }
    }
    else{
        setAPrevEnemyD(prevEnemyD);
        int data = reader(3);
        InformationNode* tmpNode = new InformationNode(3,data);
        loadedP[1]=loadedP[0];
        loadedP[0]=tmpNode;
        return loadedP[0]->getData();
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
        case 0:
            path = "RATATATA";
            break;
        case 1:
            path = "OCorona";
            break;
        case 2:
            path = "LaCuracao";
            break;
        case 3:
            path = "AmorYPaz";
            break;
        default:
            cout<<"caracter equivocado"<<endl;
    }
    ptree pt;
    string fullPath = "/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets" + path + ".xml";
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

bool Strategys::isLoaded(char x) {
    bool value = false;
    if(loadedP[0]->getType()==x){
        value = true;
        return value;
    }
    else if ( loadedP[1]->getType()==x){
        value = true;
        return value;
    }
    return value;
}

