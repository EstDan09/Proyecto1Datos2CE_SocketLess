#include <iostream>
#include "Background.h"
#include "Player.h"
#include "InGame.h"
#include "Bullet.h"
#include "ShipPlayer.h"
#include "Enemy.h"
#include "/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/raylib-cpp-4.5.0/include/raylib-cpp.hpp"
#include "raymath.h"

#include <unistd.h>
#include <string.h>
#include <string>
#include "raylib.h"
#define NUM_FRAMES 1 //recorte
using namespace std;


int lives = 11;
int fase1Con = 0;
int bulletsLeft = 4;
int bulletsCLeft = 0;
int health = 100;
int obj = 0;
int wave = 1;

//Pantallas que voy a usar
//------------------------------
typedef enum GameScreen {MENU = 0, F1, F2, F3, F4, F5, F6, F7, F8, F9,
                         F10, F11, F12, F13, F14, F15} GameScreen;
//------------------------------



int main(int argc, const char * argv[])
{
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




    //------------------------------

    //Objetos DATA
    auto* inGame = new InGame();
    inGame->changeDifficulty(1);
    auto* shipPlayer = new ShipPlayer(100);
    shipPlayer->ammunation->insertBullets(50);
    shipPlayer->ammunation->setDamage(101);

    //------------------------------
    auto* player = new Player (&shipUsableImage, raylib::Rectangle(40,8, 8,8),
                            raylib::Rectangle(100,GetScreenHeight()/2,64,64), 200.0f,

                            &bulletUsableImage, 3.0f);
    auto* enemy1 = new Enemy(&shipUsableImage, raylib::Rectangle(40,48,8,8),
                            raylib::Rectangle(GetScreenWidth()-70, 200, 64,64), 200.0f,
                            &bulletUsableImage, false);
    auto* enemy2 = new Enemy(&shipUsableImage, raylib::Rectangle(40,48,8,8),
                            raylib::Rectangle(GetScreenWidth()-70, (GetScreenHeight()/2) + 35, 64,64), 200.0f,
                            &bulletUsableImage, false);
    auto* enemy3 = new Enemy(&shipUsableImage, raylib::Rectangle(40,48,8,8),
                            raylib::Rectangle(GetScreenWidth()-70, 700, 64,64), 200.0f,
                            &bulletUsableImage, false);
    auto* enemy4 = new Enemy(&shipUsableImage, raylib::Rectangle(40,48,8,8),
                            raylib::Rectangle(GetScreenWidth()-70,900, 64,64), 200.0f,
                            &bulletUsableImage, false);
    auto* enemy5 = new Enemy(&shipUsableImage, raylib::Rectangle(40,48,8,8),
                             raylib::Rectangle(GetScreenWidth()-70,550, 64,64), 200.0f,
                             &bulletUsableImage, false);
    auto* enemy6 = new Enemy(&shipUsableImage, raylib::Rectangle(40,48,8,8),
                             raylib::Rectangle(GetScreenWidth()-70,550, 64,64), 200.0f,
                             &bulletUsableImage, false);
    auto* enemy7 = new Enemy(&shipUsableImage, raylib::Rectangle(40,48,8,8),
                             raylib::Rectangle(GetScreenWidth()-70,550, 64,64), 200.0f,
                             &bulletUsableImage, false);
    auto* enemy8 = new Enemy(&shipUsableImage, raylib::Rectangle(40,48,8,8),
                             raylib::Rectangle(GetScreenWidth()-70,550, 64,64), 200.0f,
                             &bulletUsableImage, false);

    auto* backgroundMenu = new Background(&backgroundImageMenu,raylib::Rectangle(200,100,1300, 1000),
                              raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
    auto* backgroundF1 = new Background(&backgroundImageF1,raylib::Rectangle(200,100,1300, 1000),
                            raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
    auto* backgroundF2 = new Background(&backgroundImageF2,raylib::Rectangle(200,100,1300, 1000),
                                        raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);
    auto* backgroundF3 = new Background(&backgroundImageF3,raylib::Rectangle(200,100,1300, 1000),
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

    //Main loop del juego y cliente
    //------------------------------
    while(!WindowShouldClose()) {

        //Update
        //-------------
        switch(currentScreen){

            case MENU:{

                mousePoint = GetMousePosition();
                startButtonActionEasy = false;
                startButtonAction = false;
                startButtonActionHard = false;

                if (CheckCollisionPointRec(mousePoint, startEasyBottonBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        startButtonActionEasy = true;
                    }
                }
                if (startButtonActionEasy) {
                    //PlaySound(fxButton);
                    currentScreen = F1;
                    lives = 10;
                    inGame->changeDifficulty(1);
                }

                if (CheckCollisionPointRec(mousePoint, startBottonBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        startButtonAction = true;
                    }
                }
                if (startButtonAction) {
                    //PlaySound(fxButton);
                    currentScreen = F1;
                    lives = 5;
                    inGame->changeDifficulty(2);
                }

                if (CheckCollisionPointRec(mousePoint, startHardBottonBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        startButtonActionHard = true;
                    }
                }
                if (startButtonActionHard) {
                    //PlaySound(fxButton);
                    currentScreen = F1;
                    lives = 1;
                    inGame->changeDifficulty(3);
                }
            }
            break;

            case F1:{
                player->Event();
                player->Update();
                enemy1->Update();
                enemy2->Update();
                enemy3->Update();
                enemy4->Update();
                player->getOutClipB1();

                //inGame->getCurrentWave()->colShip(3, 1000);

                bulletsLeft = shipPlayer->ammunation->getQuantity();
                if (lives <= 0){
                    currentScreen = MENU;
                }

                if (bulletsLeft == 0 and bulletsCLeft == 0){
                    player->setDelay(999.9f);
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                //Colisiones

                    //BulletsOutOfBounds
                if (player->getOutClipB1().x > 1470 && player->getOutClipB1().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB2().x > 1470 && player->getOutClipB2().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB3().x > 1470 && player->getOutClipB3().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB4().x > 1470 && player->getOutClipB4().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));
                }

                    //Colision entre naves
                if (CheckCollisionRecs(player->getOutClip(), enemy1->getOutclip())
                || CheckCollisionRecs(player->getOutClip(), enemy2->getOutclip())
                || CheckCollisionRecs(player->getOutClip(), enemy3->getOutclip())
                || CheckCollisionRecs(player->getOutClip(), enemy4->getOutclip())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        cout << shipPlayer->getVida() << endl;
                    }
                    else{
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        lives --;
                        shipPlayer->setVida(20);
                    }
                }

                    //Colision bala jugador - enemigo
                if (CheckCollisionRecs(player->getOutClipB1(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;

                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;

                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy2->getOutclip())){

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage()) << endl;

                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            cout << " me lo mato" << endl;
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                        else{
                            cout << " aguanta el guineo" << endl;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << "tercero" << endl;
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;

                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB2(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << "tercero" << endl;
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                }


                if (CheckCollisionRecs(player->getOutClipB3(), enemy1->getOutclip())){
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));


                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy2->getOutclip())){
                    
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << "terceroBacam" << endl;
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            cout << "is it here" << endl;
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                            cout << "sour grapes" << endl;

                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                }


                if (CheckCollisionRecs(player->getOutClipB4(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                    //Colision bala enmeiga-naveJugador
                if (CheckCollisionRecs(player->getOutClip(), enemy1->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        //sleep(1);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        //sleep(1);
                    }
                }

                if (CheckCollisionRecs(player->getOutClip(), enemy2->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        sleep(1/2);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        sleep(1/2);
                    }
                }

                if (CheckCollisionRecs(player->getOutClip(), enemy3->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        sleep(1/2);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        sleep(1/2);
                    }
                }

                if (CheckCollisionRecs(player->getOutClip(), enemy4->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        sleep(1/2);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        sleep(1/2);
                    }
                }

                if (obj == 4){
                    wave ++;
                    obj = 0;
                    currentScreen = F2;
                    player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                    enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
                    enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 300, 64,64));
                    enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 400, 64,64));
                    enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 500, 64,64));
                    enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));

                }
            }
            break;

            case F2:{
                player->Event();
                player->Update();
                enemy1->Update();
                enemy2->Update();
                enemy3->Update();
                enemy4->Update();
                player->getOutClipB1();

                bulletsLeft = shipPlayer->ammunation->getQuantity();
                if (lives <= 0){
                    currentScreen = MENU;
                }

                if (bulletsLeft == 0 and bulletsCLeft == 0){
                    player->setDelay(999.9f);
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                //Colisiones

                //BulletsOutOfBounds
                if (player->getOutClipB1().x > 1470 && player->getOutClipB1().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB2().x > 1470 && player->getOutClipB2().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB3().x > 1470 && player->getOutClipB3().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB4().x > 1470 && player->getOutClipB4().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));
                }

                //Colision entre naves
                if (CheckCollisionRecs(player->getOutClip(), enemy1->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy2->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy3->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy4->getOutclip())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        cout << shipPlayer->getVida() << endl;
                    }
                    else{
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        lives --;
                        shipPlayer->setVida(20);
                    }
                }

                //Colision bala jugador - enemigo
                if (CheckCollisionRecs(player->getOutClipB1(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;

                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;

                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy2->getOutclip())){

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage()) << endl;

                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            cout << " me lo mato" << endl;
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                        else{
                            cout << " aguanta el guineo" << endl;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << "tercero" << endl;
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;

                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB2(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << "tercero" << endl;
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                }


                if (CheckCollisionRecs(player->getOutClipB3(), enemy1->getOutclip())){
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));


                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << "terceroBacam" << endl;
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            cout << "is it here" << endl;
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                            cout << "sour grapes" << endl;

                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                }


                if (CheckCollisionRecs(player->getOutClipB4(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                //Colision bala enmeiga-naveJugador
                if (CheckCollisionRecs(player->getOutClip(), enemy1->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        //sleep(1);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        //sleep(1);
                    }
                }

                if (CheckCollisionRecs(player->getOutClip(), enemy2->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        sleep(1/2);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        sleep(1/2);
                    }
                }

                if (CheckCollisionRecs(player->getOutClip(), enemy3->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        sleep(1/2);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        sleep(1/2);
                    }
                }

                if (CheckCollisionRecs(player->getOutClip(), enemy4->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        sleep(1/2);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        sleep(1/2);
                    }
                }

                if (obj == 4){

                    wave++;
                    obj = 0;
                    currentScreen = F3;
                    player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                    enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
                    enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 300, 64,64));
                    enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 400, 64,64));
                    enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 500, 64,64));
                    enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));

                }
            }
            break;

            case F3:{
                player->Event();
                player->Update();
                enemy1->Update();
                enemy2->Update();
                enemy3->Update();
                enemy4->Update();
                player->getOutClipB1();

                bulletsLeft = shipPlayer->ammunation->getQuantity();
                if (lives <= 0){
                    currentScreen = MENU;
                }

                if (bulletsLeft == 0 and bulletsCLeft == 0){
                    player->setDelay(999.9f);
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                //Colisiones

                //BulletsOutOfBounds
                if (player->getOutClipB1().x > 1470 && player->getOutClipB1().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB2().x > 1470 && player->getOutClipB2().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB3().x > 1470 && player->getOutClipB3().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB4().x > 1470 && player->getOutClipB4().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));
                }

                //Colision entre naves
                if (CheckCollisionRecs(player->getOutClip(), enemy1->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy2->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy3->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy4->getOutclip())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        cout << shipPlayer->getVida() << endl;
                    }
                    else{
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        lives --;
                        shipPlayer->setVida(20);
                    }
                }

                //Colision bala jugador - enemigo
                if (CheckCollisionRecs(player->getOutClipB1(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;

                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;

                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy2->getOutclip())){

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage()) << endl;

                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            cout << " me lo mato" << endl;
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                        else{
                            cout << " aguanta el guineo" << endl;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << "tercero" << endl;
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;

                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB2(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << "tercero" << endl;
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                }


                if (CheckCollisionRecs(player->getOutClipB3(), enemy1->getOutclip())){
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));


                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << "terceroBacam" << endl;
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            cout << "is it here" << endl;
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                            cout << "sour grapes" << endl;

                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                }


                if (CheckCollisionRecs(player->getOutClipB4(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                //Colision bala enmeiga-naveJugador
                if (CheckCollisionRecs(player->getOutClip(), enemy1->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        //sleep(1);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        //sleep(1);
                    }
                }

                if (CheckCollisionRecs(player->getOutClip(), enemy2->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        sleep(1/2);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        sleep(1/2);
                    }
                }

                if (CheckCollisionRecs(player->getOutClip(), enemy3->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        sleep(1/2);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        sleep(1/2);
                    }
                }

                if (CheckCollisionRecs(player->getOutClip(), enemy4->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        sleep(1/2);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        sleep(1/2);
                    }
                }

                if (obj == 4){

                    wave++;
                    obj = 0;
                    currentScreen = F4;
                    player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                    enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
                    enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 300, 64,64));
                    enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 400, 64,64));
                    enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 500, 64,64));
                    enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));

                }
            }
            break;

            case F4:{
                player->Event();
                player->Update();
                enemy1->Update();
                enemy2->Update();
                enemy3->Update();
                enemy4->Update();
                player->getOutClipB1();

                bulletsLeft = shipPlayer->ammunation->getQuantity();
                if (lives <= 0){
                    currentScreen = MENU;
                }

                if (bulletsLeft == 0 and bulletsCLeft == 0){
                    player->setDelay(999.9f);
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                //Colisiones

                //BulletsOutOfBounds
                if (player->getOutClipB1().x > 1470 && player->getOutClipB1().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB2().x > 1470 && player->getOutClipB2().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB3().x > 1470 && player->getOutClipB3().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB4().x > 1470 && player->getOutClipB4().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));
                }

                //Colision entre naves
                if (CheckCollisionRecs(player->getOutClip(), enemy1->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy2->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy3->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy4->getOutclip())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        cout << shipPlayer->getVida() << endl;
                    }
                    else{
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        lives --;
                        shipPlayer->setVida(20);
                    }
                }

                //Colision bala jugador - enemigo
                if (CheckCollisionRecs(player->getOutClipB1(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;

                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;

                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy2->getOutclip())){

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage()) << endl;

                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            cout << " me lo mato" << endl;
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                        else{
                            cout << " aguanta el guineo" << endl;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << "tercero" << endl;
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;

                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB2(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << "tercero" << endl;
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                }


                if (CheckCollisionRecs(player->getOutClipB3(), enemy1->getOutclip())){
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));


                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << "terceroBacam" << endl;
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            cout << "is it here" << endl;
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                            cout << "sour grapes" << endl;

                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                }


                if (CheckCollisionRecs(player->getOutClipB4(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                //Colision bala enmeiga-naveJugador
                if (CheckCollisionRecs(player->getOutClip(), enemy1->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        //sleep(1);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        //sleep(1);
                    }
                }

                if (CheckCollisionRecs(player->getOutClip(), enemy2->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        sleep(1/2);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        sleep(1/2);
                    }
                }

                if (CheckCollisionRecs(player->getOutClip(), enemy3->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        sleep(1/2);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        sleep(1/2);
                    }
                }

                if (CheckCollisionRecs(player->getOutClip(), enemy4->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        sleep(1/2);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        sleep(1/2);
                    }
                }

                if (obj == 4){
                    wave++;
                    obj = 0;
                    currentScreen = F5;
                    player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                    enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
                    enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 300, 64,64));
                    enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 400, 64,64));
                    enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 500, 64,64));
                    enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));

                }
            }
            break;

            case F5:{
                cout << "waiting for love2 " << endl;
            }
            break;

            case F6:{
                cout << "waiting for love2 " << endl;
            }
            break;

            case F7:{
                cout << "waiting for love2 " << endl;
            }
            break;

            case F8:{
                cout << "waiting for love2 " << endl;
            }
            break;

            case F9:{
                cout << "hoping for love" << endl;
            }
            break;

            case F10:{
                cout << "waiting for love2 " << endl;
            }
            break;

            case F11:{
                cout << "waiting for love2 " << endl;
            }
            break;

            case F12:{
                cout << "waiting for love2 " << endl;
            }
            break;

            case F13:{
                cout << "waiting for love2 " << endl;
            }
            break;

            case F14:{
                cout << "waiting for love2 " << endl;
            }
            break;

            case F15:{
                cout << "waiting for love2 " << endl;
            }
            break;
            default: break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch(currentScreen){
            case MENU:{
                backgroundMenu->Draw();
                DrawTextureRec(startEasyButton, sourceRecStartEasy,(Vector2){ startEasyBottonBounds.x, startEasyBottonBounds.y }, WHITE );
                DrawTextureRec(startButton, sourceRecStart, (Vector2){ startBottonBounds.x, startBottonBounds.y }, WHITE); // Draw button frame
                DrawTextureRec(startHardButton, sourceRecStartHard,(Vector2){ startHardBottonBounds.x, startHardBottonBounds.y }, WHITE );
                DrawTextureRec(settingsButton, sourceRecSettings, (Vector2){settingButtonBounds.x, settingButtonBounds.y}, WHITE);
            }
            break;

            case F1: {
                backgroundF1->Update();
                backgroundF1->Draw();
                player->Draw();
                enemy1->Draw();
                enemy2->Draw();
                enemy3->Draw();
                enemy4->Draw();

                string firstTextB = "Bullets: ";
                string secondtextB = to_string(bulletsLeft);
                string bulletCounter = firstTextB + secondtextB;
                DrawText(bulletCounter.c_str(), 0,0,30, GREEN);

                string firstTextBC = "Bulletin the Kollector: ";
                string secondtextBC = to_string(bulletsCLeft);
                string bulletCCounter = firstTextBC + secondtextBC;
                DrawText(bulletCCounter.c_str(), 300,0,30, GREEN);

                string firstTextLives = "Lives: ";
                string secondtextLives = to_string(lives);
                string livesCounter = firstTextLives + secondtextLives;
                DrawText(livesCounter.c_str(), 800,0,30, GREEN);

                string firstTextWaves = "Wave: ";
                string secondTextWaves = to_string(wave);
                string waveCounter = firstTextWaves + secondTextWaves;
                DrawText(waveCounter.c_str(), 1200,0,30, GREEN);


            }
            break;

            case F2: {
                backgroundF2->Update();
                backgroundF2->Draw();
                player->Draw();
                enemy1->Draw();
                enemy2->Draw();
                enemy3->Draw();
                enemy4->Draw();

                string firstTextB = "Bullets: ";
                string secondtextB = to_string(bulletsLeft);
                string bulletCounter = firstTextB + secondtextB;
                DrawText(bulletCounter.c_str(), 0,0,30, GREEN);

                string firstTextBC = "Bulletin the Kollector: ";
                string secondtextBC = to_string(bulletsCLeft);
                string bulletCCounter = firstTextBC + secondtextBC;
                DrawText(bulletCCounter.c_str(), 300,0,30, GREEN);

                string firstTextLives = "Lives: ";
                string secondtextLives = to_string(lives);
                string livesCounter = firstTextLives + secondtextLives;
                DrawText(livesCounter.c_str(), 800,0,30, GREEN);

                string firstTextWaves = "Wave: ";
                string secondTextWaves = to_string(wave);
                string waveCounter = firstTextWaves + secondTextWaves;
                DrawText(waveCounter.c_str(), 1200,0,30, GREEN);
            }
            break;

            case F3: {
                backgroundF3->Update();
                backgroundF3->Draw();
                player->Draw();
                enemy1->Draw();
                enemy2->Draw();
                enemy3->Draw();
                enemy4->Draw();

                string firstTextB = "Bullets: ";
                string secondtextB = to_string(bulletsLeft);
                string bulletCounter = firstTextB + secondtextB;
                DrawText(bulletCounter.c_str(), 0,0,30, GREEN);

                string firstTextBC = "Bulletin the Kollector: ";
                string secondtextBC = to_string(bulletsCLeft);
                string bulletCCounter = firstTextBC + secondtextBC;
                DrawText(bulletCCounter.c_str(), 300,0,30, GREEN);

                string firstTextLives = "Lives: ";
                string secondtextLives = to_string(lives);
                string livesCounter = firstTextLives + secondtextLives;
                DrawText(livesCounter.c_str(), 800,0,30, GREEN);

                string firstTextWaves = "Wave: ";
                string secondTextWaves = to_string(wave);
                string waveCounter = firstTextWaves + secondTextWaves;
                DrawText(waveCounter.c_str(), 1200,0,30, GREEN);
            }
            break;
            default: break;
        }
        EndDrawing();

    };
    UnloadTexture(startButton);  // Unload button texture
    UnloadSound(fxButton);  // Unload sound

    CloseAudioDevice();     // Close audio device

    CloseWindow();


}