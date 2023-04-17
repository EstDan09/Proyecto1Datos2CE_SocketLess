//
// Created by dadu on 16/04/23.
//

#include "InformationNode.h"

InformationNode::InformationNode(char nType, int data) {
    InformationNode::type = nType;
    InformationNode::data = data;
}

InformationNode::~InformationNode() {}

char InformationNode::getType() const {
    return type;
}

void InformationNode::setType(char type) {
    InformationNode::type = type;
}

int InformationNode::getData() const {
    return data;
}

void InformationNode::setData(int data) {
    InformationNode::data = data;
}
