//
// Created by esteban on 4/6/23.
//
#include <iostream>
#include "Background.h"
#include "Player.h"
#include "InGame.h"
#include "Bullet.h"
#include "ShipPlayer.h"
#include "Enemy.h"
#include "/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/raylib-cpp-4.5.0/include/raylib-cpp.hpp"
#include "raymath.h"
#include <boost/asio.hpp>
#include <unistd.h>
#include <string.h>
#include <string>
#include "raylib.h"
#define NUM_FRAMES 1 //recorte
using namespace std;
#pragma once
#ifndef PROYECTO1DATOS2CE_CLIENTE_DECLARATIONS_H
#define PROYECTO1DATOS2CE_CLIENTE_DECLARATIONS_H

int lives = 11;
int fase1Con = 0;
int bulletsLeft = 4;
int bulletsCLeft = 0;
int health = 100;
int obj = 0;
int wave = 1;

void logic1st();

//Pantallas que voy a usar
//------------------------------
typedef enum GameScreen {MENU = 0, F1, F2, F3, F4, F5, F6, F7, F8, F9,
    F10, F11, F12, F13, F14, F15} GameScreen;

//Variables para la ventana
//-----------------------------
const int screenWidth = 1500;
const int screenHeight = 1000;
//------------------------------


//Arrancamos la ventana
//------------------------------
raylib::Window window (screenWidth, screenHeight, "Lamento en el Tibet");
//------------------------------

GameScreen currentScreen = MENU;

//Audio
//------------------------------
InitAudioDevice();
Sound fxButton = LoadSound("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/one.wav");
//------------------------------

//Imagenes
//------------------------------

Image startButtonImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/normal.png");
ImageResize(&startButtonImage, 375, 225);
Texture2D startButton = LoadTextureFromImage(startButtonImage);

Image startEasyButtonImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/easy.png");
ImageResize(&startEasyButtonImage, 350, 200);
Texture2D startEasyButton = LoadTextureFromImage(startEasyButtonImage);

Image startHardButtonImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/hard.png");
ImageResize(&startHardButtonImage, 350, 200);
Texture2D startHardButton = LoadTextureFromImage(startHardButtonImage);


Image settingsButtonImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/settings.png");
ImageResize(&settingsButtonImage, 100, 100);
Texture2D settingsButton = LoadTextureFromImage(settingsButtonImage);

Image shipImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/ships.png");
raylib::Texture shipUsableImage = LoadTextureFromImage(shipImage);

Image bulletImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/blasts.png");
raylib::Texture bulletUsableImage = LoadTextureFromImage(bulletImage);

raylib::Texture backgroundImageMenu = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgMenu.png");
raylib::Texture backgroundImageF1 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF1.png");
raylib::Texture backgroundImageF2 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF2.png");
raylib::Texture backgroundImageF3 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF3.png");
raylib::Texture backgroundImageF4 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF4.png");
raylib::Texture backgroundImageF5 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF5.png");
raylib::Texture backgroundImageF6 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF6.png");
raylib::Texture backgroundImageF7 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF7.png");
raylib::Texture backgroundImageF8 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF8.png");
raylib::Texture backgroundImageF9 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF9.png");
raylib::Texture backgroundImageF10 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF10.png");
raylib::Texture backgroundImageF11 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF11.png");
raylib::Texture backgroundImageF12 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF12.png");
raylib::Texture backgroundImageF13 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF13.png");
raylib::Texture backgroundImageF14 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF14.png");
raylib::Texture backgroundImageF15 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF15.png");

//------------------------------

//Objetos DATA

auto* inGame = new InGame();
inGame->changeDifficulty(1);
auto* shipPlayer = new ShipPlayer(100);
shipPlayer->ammunation->insertBullets(500);
shipPlayer->ammunation->setDamage(101);
//------------------------------
auto* player = new Player (&shipUsableImage, raylib::Rectangle(40,8, 8,8),
                           raylib::Rectangle(100,GetScreenHeight()/2,64,64), 200.0f,

                           &bulletUsableImage, 3.0f);
auto* enemy1 = new Enemy(&shipUsableImage, raylib::Rectangle(40,48,8,8),
                         raylib::Rectangle(GetScreenWidth()-70, 200, 64,64), 200.0f,
                         &bulletUsableImage, false);
auto* enemy2 = new Enemy(&shipUsableImage, raylib::Rectangle(40,56,8,8),
                         raylib::Rectangle(GetScreenWidth()-70, (GetScreenHeight()/2) + 35, 64,64), 200.0f,
                         &bulletUsableImage, false);
auto* enemy3 = new Enemy(&shipUsableImage, raylib::Rectangle(40,64,8,8),
                         raylib::Rectangle(GetScreenWidth()-70, 700, 64,64), 200.0f,
                         &bulletUsableImage, false);
auto* enemy4 = new Enemy(&shipUsableImage, raylib::Rectangle(40,72,8,8),
                         raylib::Rectangle(GetScreenWidth()-70,900, 64,64), 200.0f,
                         &bulletUsableImage, false);
auto* enemy5 = new Enemy(&shipUsableImage, raylib::Rectangle(48,72,8,8),
                         raylib::Rectangle(GetScreenWidth()-70,550, 64,64), 200.0f,
                         &bulletUsableImage, false);
auto* enemy6 = new Enemy(&shipUsableImage, raylib::Rectangle(48,64,8,8),
                         raylib::Rectangle(GetScreenWidth()-70,700, 64,64), 200.0f,
                         &bulletUsableImage, false);
auto* enemy7 = new Enemy(&shipUsableImage, raylib::Rectangle(48,56,8,8),
                         raylib::Rectangle(GetScreenWidth()-70,800, 64,64), 200.0f,
                         &bulletUsableImage, false);
auto* enemy8 = new Enemy(&shipUsableImage, raylib::Rectangle(48,40,8,8),
                         raylib::Rectangle(GetScreenWidth()-70,900, 64,64), 200.0f,
                         &bulletUsableImage, false);

auto* backgroundMenu = new Background(&backgroundImageMenu,raylib::Rectangle(200,100,1300, 1000),
                                      raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
auto* backgroundF1 = new Background(&backgroundImageF1,raylib::Rectangle(200,100,1300, 1000),
                                    raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
auto* backgroundF2 = new Background(&backgroundImageF2,raylib::Rectangle(200,100,1300, 1000),
                                    raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
auto* backgroundF3 = new Background(&backgroundImageF3,raylib::Rectangle(200,100,1300, 1000),
                                    raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
auto* backgroundF4 = new Background(&backgroundImageF4,raylib::Rectangle(200,100,1300, 1000),
                                    raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
auto* backgroundF5 = new Background(&backgroundImageF5,raylib::Rectangle(200,100,1300, 1000),
                                    raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
auto* backgroundF6 = new Background(&backgroundImageF6,raylib::Rectangle(200,100,1300, 1000),
                                    raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
auto* backgroundF7 = new Background(&backgroundImageF7,raylib::Rectangle(200,100,1300, 1000),
                                    raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
auto* backgroundF8 = new Background(&backgroundImageF8,raylib::Rectangle(200,100,1300, 1000),
                                    raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
auto* backgroundF9 = new Background(&backgroundImageF9,raylib::Rectangle(200,100,1300, 1000),
                                    raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
auto* backgroundF10 = new Background(&backgroundImageF10,raylib::Rectangle(200,100,1300, 1000),
                                     raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
auto* backgroundF11 = new Background(&backgroundImageF11,raylib::Rectangle(200,100,1300, 1000),
                                     raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
auto* backgroundF12 = new Background(&backgroundImageF12,raylib::Rectangle(200,100,1300, 1000),
                                     raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
auto* backgroundF13 = new Background(&backgroundImageF13,raylib::Rectangle(200,100,1300, 1000),
                                     raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
auto* backgroundF14 = new Background(&backgroundImageF14,raylib::Rectangle(200,100,1300, 1000),
                                     raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
auto* backgroundF15 = new Background(&backgroundImageF15,raylib::Rectangle(200,100,1300, 1000),
                                     raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);


//------------------------------


//Parametros del boton Start
//------------------------------
float frameHeightStart = (float)startButton.height/NUM_FRAMES; //390
Rectangle sourceRecStart = {0,0, (float)startButton.width, frameHeightStart};
Rectangle startBottonBounds = { screenWidth/2.0f - startButton.width/2.0f, screenHeight/2.0f - startButton.height/NUM_FRAMES/2.0f,
                                (float)startButton.width, frameHeightStart};

float frameHeightStartEasy = (float)startEasyButton.height/NUM_FRAMES; //390
Rectangle sourceRecStartEasy = {0,0, (float)startEasyButton.width, frameHeightStartEasy};
Rectangle startEasyBottonBounds = { screenWidth/2.0f - startEasyButton.width/2.0f, (screenHeight/2.0f) - 310,
                                    (float)startEasyButton.width, frameHeightStartEasy};

float frameHeightStartHard = (float)startHardButton.height/NUM_FRAMES; //390
Rectangle sourceRecStartHard = {0,0, (float)startHardButton.width, frameHeightStartHard};
Rectangle startHardBottonBounds = { screenWidth/2.0f - startHardButton.width/2.0f, (screenHeight/2.0f) + 100,
                                    (float)startHardButton.width, frameHeightStartHard};

//------------------------------

//Parametros del boton Settings
//------------------------------
float frameHeightSettings = (float)settingsButton.height/NUM_FRAMES; //390
Rectangle sourceRecSettings = {0,0, (float)settingsButton.width, frameHeightSettings};

Rectangle settingButtonBounds = { screenWidth/10.0f - settingsButton.width/2.0f, screenHeight/8.0f - settingsButton.height/NUM_FRAMES/2.0f,
                                  (float)settingsButton.width, frameHeightSettings};
//------------------------------


//Variables que voy a usar
//------------------------------
bool startButtonAction = false;
bool startButtonActionEasy = false;
bool startButtonActionHard = false;
int framesCounter = 0;

SetTargetFPS(60);

Vector2 mousePoint = {0.0f, 0.0f};

SetTargetFPS(60);

player->ricoMauro();
             &bulletUsableImage);
#endif //PROYECTO1DATOS2CE_CLIENTE_DECLARATIONS_H
