//
// Created by esteban on 4/6/23.
//
#include "Enemy.h"
#pragma once
#ifndef PROYECTO1DATOS2CE_CLIENTE_DECLARATIONS_H
#define PROYECTO1DATOS2CE_CLIENTE_DECLARATIONS_H

Image shipImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/ships.png");
raylib::Texture shipUsableImage = LoadTextureFromImage(shipImage);

Image bulletImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/blasts.png");
raylib::Texture bulletUsableImage = LoadTextureFromImage(bulletImage);

Enemy enemy1(&shipUsableImage, raylib::Rectangle(40,48,8,8),
             raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64), 200.0f,
             &bulletUsableImage);
#endif //PROYECTO1DATOS2CE_CLIENTE_DECLARATIONS_H
