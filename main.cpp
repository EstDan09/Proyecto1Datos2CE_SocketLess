#include <iostream>
#include "Background.h"
#include "Player.h"
#include "InGame.h"
#include "Bullet.h"
#include "ShipPlayer.h"
#include "Enemy.h"
#include "/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/raylib-cpp-4.5.0/include/raylib-cpp.hpp"
#include "raymath.h"
#include "Strategys.h"
#include <boost/asio.hpp>
#include <unistd.h>
#include <string.h>
#include "wait.h"
#include "time.h"

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
string estadoPoder = "Waiting...";


//Pantallas que voy a usar
//------------------------------
typedef enum GameScreen {MENU = 0, F1, F6, F11} GameScreen;
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

    Image ratataButtonImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/ratata.png");
    ImageResize(&ratataButtonImage, 75, 75);
    Texture2D ratataButton = LoadTextureFromImage(ratataButtonImage);

    Image shieldButtonImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/shield.png");
    ImageResize(&shieldButtonImage, 75, 75);
    Texture2D shieldButton = LoadTextureFromImage(shieldButtonImage);

    Image amorButtonImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/amorYpaz.png");
    ImageResize(&amorButtonImage, 75, 75);
    Texture2D amorButton = LoadTextureFromImage(amorButtonImage);

    Image curaButtonImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/curacao.png");
    ImageResize(&curaButtonImage, 75, 75);
    Texture2D curaButton = LoadTextureFromImage(curaButtonImage);


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
    raylib::Texture backgroundImageF10 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/bgF10.png");
    raylib::Texture backgroundImageF11 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF11.png");
    //------------------------------

    //Objetos DATA

    auto* inGame = new InGame();
    inGame->changeDifficulty(1);
    auto* shipPlayer = new ShipPlayer(100);
    shipPlayer->ammunation->insertBullets(500);
    shipPlayer->ammunation->setDamage(1000);

    auto* strategiesMachine = new Strategys();
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
    auto* backgroundF6 = new Background(&backgroundImageF6,raylib::Rectangle(200,100,1300, 1000),
                                        raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);

    auto* backgroundF11 = new Background(&backgroundImageF11,raylib::Rectangle(200,100,1300, 1000),
                                        raylib::Rectangle(0,0,screenWidth, screenHeight),0.0f);

    //------------------------------
    player->setEnemy1(enemy1);
    player->setEnemy2(enemy1);
    player->setEnemy3(enemy1);
    player->setEnemy4(enemy1);
    player->setEnemy5(enemy1);
    player->setEnemy6(enemy6);
    player->setEnemy7(enemy7);
    player->setEnemy8(enemy8);
    player->setInGame(inGame);
    player->setShipPlayer(shipPlayer);
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

    float frameHeightRatata = (float)ratataButton.height/NUM_FRAMES; //390
    Rectangle sourceRecRatata = {0,0, (float)ratataButton.width, frameHeightRatata};
    Rectangle ratataButtonBounds = { 30, 75,
                                        (float)ratataButton.width, frameHeightRatata};

    float frameHeightShield = (float)shieldButton.height/NUM_FRAMES; //390
    Rectangle sourceRecShield = {0,0, (float)shieldButton.width, frameHeightShield};
    Rectangle shieldButtonBounds = { 30, 175,
                                     (float)shieldButton.width, frameHeightShield};

    float frameHeightAmor = (float)amorButton.height/NUM_FRAMES; //390
    Rectangle sourceRecAmor = {0,0, (float)amorButton.width, frameHeightAmor};
    Rectangle amorButtonBounds = { 30, 700,
                                     (float)amorButton.width, frameHeightAmor};

    float frameHeightCura = (float)curaButton.height/NUM_FRAMES; //390
    Rectangle sourceRecCura= {0,0, (float)curaButton.width, frameHeightCura};
    Rectangle curaButtonBounds = { 30, 800,
                                   (float)curaButton.width, frameHeightCura};

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
    bool ratataAction = false;
    bool shieldAction = false;
    bool curacaoAction = false;
    bool amorYpazAction = false;
    int framesCounter = 0;
    int pepe = 0;

    SetTargetFPS(60);

    Vector2 mousePoint = {0.0f, 0.0f};

    SetTargetFPS(60);

//    player->ricoMauro();

    //Main loop del juego y cliente
    //------------------------------
    while(!WindowShouldClose()) {

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
                    lives = 15;
                    inGame->changeDifficulty(1);
                    player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                    enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-300, 200, 64,64));
                    enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 300, 64,64));
                    enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 400, 64,64));
                    enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 500, 64,64));
                    enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    ratataAction = false;
                    obj = 0;
                    wave = 4;
                    shipPlayer->ammunation->insertBullets(500);

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
                    player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                    enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
                    enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 300, 64,64));
                    enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 400, 64,64));
                    enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 500, 64,64));
                    enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    obj = 0;
                    wave = 4;
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
                    player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                    enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
                    enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 300, 64,64));
                    enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 400, 64,64));
                    enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 500, 64,64));
                    enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    obj = 0;
                    wave = 4;
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
                mousePoint = GetMousePosition();
                cout << shipPlayer->ammunation->getDamage() << endl;
                ratataAction = false;
                shieldAction = false;
                curacaoAction = false;
                amorYpazAction = false;



                //shipPlayer->ammunation->setDamage(strategiesMachine->deactivateP(0)); quita ratata
                //curacao
                //shipPlayer->setVida(strategiesMachine->activateP(1,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100))
                //shield
                //shipPlayer->setVida(strategiesMachine->activateP(2,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100))
                //shipPlayer->setVida(strategiesMachine->deactivateP(1))
                //amorYpaz
                //inGame->getCurrentWave()->setGenDamage(activateP(3,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100))
                //inGame->getCurrentWave()->setGenDamage(deactivateP(3))


                if (CheckCollisionPointRec(mousePoint, ratataButtonBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        ratataAction = true;
                    }
                }
                if (ratataAction) {
                    shipPlayer->setVida(strategiesMachine->deactivateP(1));

                    inGame->getCurrentWave()->setGenDamage(strategiesMachine->deactivateP(3));

                    if (strategiesMachine->isLoaded(0)){
                        estadoPoder = "ratata";
                        shipPlayer->ammunation->setDamage(strategiesMachine->activateP(0,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));
                    }
                    else{
                        sleep(5);
                        estadoPoder = "ratata";
                        shipPlayer->ammunation->setDamage(strategiesMachine->activateP(0,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));
                    }
                }

                if (CheckCollisionPointRec(mousePoint, shieldButtonBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        shieldAction = true;
                    }
                }
                if (shieldAction) {

                    shipPlayer->ammunation->setDamage(strategiesMachine->deactivateP(0));

                    inGame->getCurrentWave()->setGenDamage(strategiesMachine->deactivateP(3));

                    if (strategiesMachine->isLoaded(1)){
                        estadoPoder = "O Corona";
                        shipPlayer->setVida(strategiesMachine->activateP(1,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));
                    }
                    else{
                        sleep(5);
                        estadoPoder = "O Corona";
                        shipPlayer->setVida(strategiesMachine->activateP(1,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));

                    }
                }

                if (CheckCollisionPointRec(mousePoint, curaButtonBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        curacaoAction = true;
                    }
                }
                if (curacaoAction) {

                    shipPlayer->ammunation->setDamage(strategiesMachine->deactivateP(0));

                    inGame->getCurrentWave()->setGenDamage(strategiesMachine->deactivateP(3));

                    shipPlayer->setVida(strategiesMachine->deactivateP(1));

                    if (strategiesMachine->isLoaded(2)){
                        estadoPoder = "Curacao";
                        shipPlayer->setVida(strategiesMachine->activateP(2,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));
                    }
                    else{
                        sleep(5);
                        estadoPoder = "Curacao";
                        shipPlayer->setVida(strategiesMachine->activateP(2,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));

                    }
                }

                if (CheckCollisionPointRec(mousePoint, amorButtonBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        amorYpazAction = true;
                        pepe = 0;
                    }
                }
                if (amorYpazAction) {

                        shipPlayer->ammunation->setDamage(strategiesMachine->deactivateP(0));

                        shipPlayer->setVida(strategiesMachine->deactivateP(1));

                    if (strategiesMachine->isLoaded(3)) {
                        estadoPoder = "Amor Y Paz";
                        inGame->getCurrentWave()->setGenDamage(strategiesMachine->activateP(3, shipPlayer->getVida(),
                                                                                            shipPlayer->ammunation->getDamage(),
                                                                                            inGame->getCurrentWave()->getGenDamage(),
                                                                                            100));
                    } else {
                        sleep(5);
                        estadoPoder = "Amor Y Paz";
                        inGame->getCurrentWave()->setGenDamage(
                                    strategiesMachine->activateP(3, shipPlayer->getVida(),
                                                                 shipPlayer->ammunation->getDamage(),
                                                                 inGame->getCurrentWave()->getGenDamage(), 100));

                    }

                }




                bulletsLeft = shipPlayer->ammunation->getQuantity();
                if (lives <= 0){
                    currentScreen = MENU;
                    inGame = new InGame();
                    shipPlayer = new ShipPlayer(100);
                }

                if (bulletsLeft == 0 and bulletsCLeft == 0){
                    player->setDelay(999.9f);
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

                }

//                if (wave == 4) {
//                    char soundAction = '4';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if (wave == 3) {
//                    char soundAction = '3';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if (wave == 2) {
//                    char soundAction = '2';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if (wave == 1) {
//                    char soundAction = '1';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if (wave == 0) {
//                    char soundAction = '0';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }



                //Colisiones

                    //Enemigo sale bacano
//                if(enemy1->getOutclip().y < 1100 &&   (enemy1->getOutclip().x < -10 and enemy1->getOutclip().x > -15)){
//                    char soundAction = 'S';
//                    inGame->getCurrentWave()->colShip(0, 500000);
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if(enemy2->getOutclip().y < 1100 &&   (enemy2->getOutclip().x < -10 and enemy2->getOutclip().x > -15)){
//                    inGame->getCurrentWave()->colShip(1, 500000);
//                    char soundAction = 'S';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if(enemy3->getOutclip().y < 1100 &&   (enemy3->getOutclip().x < -10 and enemy3->getOutclip().x > -15)){
//                    inGame->getCurrentWave()->colShip(2, 500000);
//                    char soundAction = 'S';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if(enemy4->getOutclip().y < 1100 &&   (enemy4->getOutclip().x < -10 and enemy4->getOutclip().x > -15)){
//                    inGame->getCurrentWave()->colShip(3, 500000);
//                    char soundAction = 'S';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }







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

                if (player->getOutClipB5().x > 1470 && player->getOutClipB5().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB6().x > 1470 && player->getOutClipB6().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB7().x > 1470 && player->getOutClipB7().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB8().x > 1470 && player->getOutClipB8().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB9().x > 1470 && player->getOutClipB9().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB10().x > 1470 && player->getOutClipB10().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));
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

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();

                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            cout << " me lo mato" << endl;
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                        else{
                            cout << " aguanta el guineo" << endl;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy2->getOutclip())){

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage()) << endl;

                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            cout << "is it here" << endl;
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                            cout << "sour grapes" << endl;

                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB5(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB5(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB5(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB5(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB6(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB6(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB6(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB6(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB7(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB7(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB7(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB7(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB8(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB8(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB8(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB8(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB9(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB9(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB9(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB9(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB10(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB10(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB10(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB10(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

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

                if (inGame->checkNextW()){
                    wave --;
                    obj = 0;
                    //currentScreen = F2;
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

                if (wave < 0) {
                    currentScreen = F6;
                    wave = 4;
                }
            }
            break;

            case F6:{
                player->Event();
                player->Update();
                enemy1->Update();
                enemy2->Update();
                enemy3->Update();
                enemy4->Update();
                enemy5->Update();
                enemy6->Update();
                player->getOutClipB1();
                ratataAction = false;
                shieldAction = false;
                curacaoAction = false;
                amorYpazAction = false;

                cout << inGame->checkNextW() << endl;

                if (CheckCollisionPointRec(mousePoint, ratataButtonBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        ratataAction = true;
                    }
                }
                if (ratataAction) {
                    shipPlayer->setVida(strategiesMachine->deactivateP(1));

                    inGame->getCurrentWave()->setGenDamage(strategiesMachine->deactivateP(3));

                    if (strategiesMachine->isLoaded(0)){
                        estadoPoder = "ratata";
                        shipPlayer->ammunation->setDamage(strategiesMachine->activateP(0,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));
                    }
                    else{
                        sleep(5);
                        estadoPoder = "ratata";
                        shipPlayer->ammunation->setDamage(strategiesMachine->activateP(0,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));
                    }
                }

                if (CheckCollisionPointRec(mousePoint, shieldButtonBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        shieldAction = true;
                    }
                }
                if (shieldAction) {

                    shipPlayer->ammunation->setDamage(strategiesMachine->deactivateP(0));

                    inGame->getCurrentWave()->setGenDamage(strategiesMachine->deactivateP(3));

                    if (strategiesMachine->isLoaded(1)){
                        estadoPoder = "O Corona";
                        shipPlayer->setVida(strategiesMachine->activateP(1,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));
                    }
                    else{
                        sleep(5);
                        estadoPoder = "O Corona";
                        shipPlayer->setVida(strategiesMachine->activateP(1,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));

                    }
                }

                if (CheckCollisionPointRec(mousePoint, curaButtonBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        curacaoAction = true;
                    }
                }
                if (curacaoAction) {

                    shipPlayer->ammunation->setDamage(strategiesMachine->deactivateP(0));

                    inGame->getCurrentWave()->setGenDamage(strategiesMachine->deactivateP(3));

                    shipPlayer->setVida(strategiesMachine->deactivateP(1));

                    if (strategiesMachine->isLoaded(2)){
                        estadoPoder = "Curacao";
                        shipPlayer->setVida(strategiesMachine->activateP(2,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));
                    }
                    else{
                        sleep(5);
                        estadoPoder = "Curacao";
                        shipPlayer->setVida(strategiesMachine->activateP(2,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));

                    }
                }

                if (CheckCollisionPointRec(mousePoint, amorButtonBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        amorYpazAction = true;
                        pepe = 0;
                    }
                }
                if (amorYpazAction) {

                    shipPlayer->ammunation->setDamage(strategiesMachine->deactivateP(0));

                    shipPlayer->setVida(strategiesMachine->deactivateP(1));

                    if (strategiesMachine->isLoaded(3)) {
                        estadoPoder = "Amor Y Paz";
                        inGame->getCurrentWave()->setGenDamage(strategiesMachine->activateP(3, shipPlayer->getVida(),
                                                                                            shipPlayer->ammunation->getDamage(),
                                                                                            inGame->getCurrentWave()->getGenDamage(),
                                                                                            100));
                    } else {
                        sleep(5);
                        estadoPoder = "Amor Y Paz";
                        inGame->getCurrentWave()->setGenDamage(
                                strategiesMachine->activateP(3, shipPlayer->getVida(),
                                                             shipPlayer->ammunation->getDamage(),
                                                             inGame->getCurrentWave()->getGenDamage(), 100));

                    }

                }

                bulletsLeft = shipPlayer->ammunation->getQuantity();
                if (lives <= 0){
                    currentScreen = MENU;
                    inGame = new InGame();
                    shipPlayer = new ShipPlayer(100);
                }

                if (bulletsLeft == 0 and bulletsCLeft == 0){
                    player->setDelay(999.9f);
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

                }


//                if (wave == 4) {
//                    char soundAction = '4';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if (wave == 3) {
//                    char soundAction = '3';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if (wave == 2) {
//                    char soundAction = '2';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if (wave == 1) {
//                    char soundAction = '1';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if (wave == 0) {
//                    char soundAction = '0';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                //Colisiones
//
//                //Enemigo sale bacano
//                if(enemy1->getOutclip().y < 1100 &&   (enemy1->getOutclip().x < -10 and enemy1->getOutclip().x > -15)){
//                    char soundAction = 'S';
//                    inGame->getCurrentWave()->colShip(0, 500000);
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if(enemy2->getOutclip().y < 1100 &&   (enemy2->getOutclip().x < -10 and enemy2->getOutclip().x > -15)){
//                    inGame->getCurrentWave()->colShip(1, 500000);
//                    char soundAction = 'S';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if(enemy3->getOutclip().y < 1100 &&   (enemy3->getOutclip().x < -10 and enemy3->getOutclip().x > -15)){
//                    inGame->getCurrentWave()->colShip(2, 500000);
//                    char soundAction = 'S';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if(enemy4->getOutclip().y < 1100 &&   (enemy4->getOutclip().x < -10 and enemy4->getOutclip().x > -15)){
//                    inGame->getCurrentWave()->colShip(3, 500000);
//                    char soundAction = 'S';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if(enemy5->getOutclip().y < 1100 &&   (enemy5->getOutclip().x < -10 and enemy5->getOutclip().x > -15)){
//                    inGame->getCurrentWave()->colShip(4, 500000);
//                    char soundAction = 'S';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if(enemy6->getOutclip().y < 1100 &&   (enemy6->getOutclip().x < -10 and enemy6->getOutclip().x > -15)){
//                    inGame->getCurrentWave()->colShip(5, 500000);
//                    char soundAction = 'S';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }


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

                if (player->getOutClipB5().x > 1470 && player->getOutClipB5().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB6().x > 1470 && player->getOutClipB6().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB7().x > 1470 && player->getOutClipB7().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB8().x > 1470 && player->getOutClipB8().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB9().x > 1470 && player->getOutClipB9().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB10().x > 1470 && player->getOutClipB10().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));
                }

                //Colision entre naves
                if (CheckCollisionRecs(player->getOutClip(), enemy1->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy2->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy3->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy4->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy5->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy6->getOutclip())){

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

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();

                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            cout << " me lo mato" << endl;
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                        else{
                            cout << " aguanta el guineo" << endl;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy2->getOutclip())){

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage()) << endl;

                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB2(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB3(), enemy1->getOutclip())){
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            cout << "is it here" << endl;
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                            cout << "sour grapes" << endl;

                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB4(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB5(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB5(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB5(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB5(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB5(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB5(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB6(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB6(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB6(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB6(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB6(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB6(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB7(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB7(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB7(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB7(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB7(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB7(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB8(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB8(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB8(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB8(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB8(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB8(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB9(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB9(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB9(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB9(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB9(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB9(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB10(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB10(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB10(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB10(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB10(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB10(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

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

                if (CheckCollisionRecs(player->getOutClip(), enemy5->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy5->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        sleep(1/2);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy5->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        sleep(1/2);
                    }
                }

                if (CheckCollisionRecs(player->getOutClip(), enemy6->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy6->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        sleep(1/2);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy6->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        sleep(1/2);
                    }
                }

                //Ver si paso de oleada
                if (inGame->checkNextW()){
                    wave--;
                    obj = 0;
                    player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                    enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
                    enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 300, 64,64));
                    enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 400, 64,64));
                    enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 500, 64,64));
                    enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy5->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 650, 64,64));
                    enemy5->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy6->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 900, 64,64));
                    enemy6->setOutClipB(raylib::Rectangle(-5, 500, 64,64));

                }

                if (wave > 0) {
                    currentScreen = F11;
                    wave = 4;
                }
            }
            break;

            case F11:{
                player->Event();
                player->Update();
                enemy1->Update();
                enemy2->Update();
                enemy3->Update();
                enemy4->Update();
                enemy5->Update();
                enemy6->Update();
                enemy7->Update();
                enemy8->Update();
                ratataAction = false;
                shieldAction = false;
                curacaoAction = false;
                amorYpazAction = false;

                player->getOutClipB1();

                cout << inGame->checkNextW() << endl;

                if (CheckCollisionPointRec(mousePoint, ratataButtonBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        ratataAction = true;
                    }
                }
                if (ratataAction) {
                    shipPlayer->setVida(strategiesMachine->deactivateP(1));

                    inGame->getCurrentWave()->setGenDamage(strategiesMachine->deactivateP(3));

                    if (strategiesMachine->isLoaded(0)){
                        estadoPoder = "ratata";
                        shipPlayer->ammunation->setDamage(strategiesMachine->activateP(0,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));
                    }
                    else{
                        sleep(5);
                        estadoPoder = "ratata";
                        shipPlayer->ammunation->setDamage(strategiesMachine->activateP(0,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));
                    }
                }

                if (CheckCollisionPointRec(mousePoint, shieldButtonBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        shieldAction = true;
                    }
                }
                if (shieldAction) {

                    shipPlayer->ammunation->setDamage(strategiesMachine->deactivateP(0));

                    inGame->getCurrentWave()->setGenDamage(strategiesMachine->deactivateP(3));

                    if (strategiesMachine->isLoaded(1)){
                        estadoPoder = "O Corona";
                        shipPlayer->setVida(strategiesMachine->activateP(1,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));
                    }
                    else{
                        sleep(5);
                        estadoPoder = "O Corona";
                        shipPlayer->setVida(strategiesMachine->activateP(1,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));

                    }
                }

                if (CheckCollisionPointRec(mousePoint, curaButtonBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        curacaoAction = true;
                    }
                }
                if (curacaoAction) {

                    shipPlayer->ammunation->setDamage(strategiesMachine->deactivateP(0));

                    inGame->getCurrentWave()->setGenDamage(strategiesMachine->deactivateP(3));

                    shipPlayer->setVida(strategiesMachine->deactivateP(1));

                    if (strategiesMachine->isLoaded(2)){
                        estadoPoder = "Curacao";
                        shipPlayer->setVida(strategiesMachine->activateP(2,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));
                    }
                    else{
                        sleep(5);
                        estadoPoder = "Curacao";
                        shipPlayer->setVida(strategiesMachine->activateP(2,shipPlayer->getVida(),shipPlayer->ammunation->getDamage(),inGame->getCurrentWave()->getGenDamage(),100));

                    }
                }

                if (CheckCollisionPointRec(mousePoint, amorButtonBounds)) {
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        amorYpazAction = true;
                        pepe = 0;
                    }
                }
                if (amorYpazAction) {

                    shipPlayer->ammunation->setDamage(strategiesMachine->deactivateP(0));

                    shipPlayer->setVida(strategiesMachine->deactivateP(1));

                    if (strategiesMachine->isLoaded(3)) {
                        estadoPoder = "Amor Y Paz";
                        inGame->getCurrentWave()->setGenDamage(strategiesMachine->activateP(3, shipPlayer->getVida(),
                                                                                            shipPlayer->ammunation->getDamage(),
                                                                                            inGame->getCurrentWave()->getGenDamage(),
                                                                                            100));
                    } else {
                        sleep(5);
                        estadoPoder = "Amor Y Paz";
                        inGame->getCurrentWave()->setGenDamage(
                                strategiesMachine->activateP(3, shipPlayer->getVida(),
                                                             shipPlayer->ammunation->getDamage(),
                                                             inGame->getCurrentWave()->getGenDamage(), 100));

                    }

                }


                bulletsLeft = shipPlayer->ammunation->getQuantity();
                if (lives <= 0){
                    currentScreen = MENU;
                    inGame = new InGame();
                    shipPlayer = new ShipPlayer(100);
                }

                if (bulletsLeft == 0 and bulletsCLeft == 0){
                    player->setDelay(999.9f);
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

                }
//                if (wave == 4) {
//                    char soundAction = '4';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if (wave == 3) {
//                    char soundAction = '3';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if (wave == 2) {
//                    char soundAction = '2';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if (wave == 1) {
//                    char soundAction = '1';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if (wave == 0) {
//                    char soundAction = '0';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                //Colisiones
//
//                //Enemigo sale bacano
//                if(enemy1->getOutclip().y < 1100 &&   (enemy1->getOutclip().x < -10 and enemy1->getOutclip().x > -15)){
//                    char soundAction = 'S';
//                    inGame->getCurrentWave()->colShip(0, 500000);
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if(enemy2->getOutclip().y < 1100 &&   (enemy2->getOutclip().x < -10 and enemy2->getOutclip().x > -15)){
//                    inGame->getCurrentWave()->colShip(1, 500000);
//                    char soundAction = 'S';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if(enemy3->getOutclip().y < 1100 &&   (enemy3->getOutclip().x < -10 and enemy3->getOutclip().x > -15)){
//                    inGame->getCurrentWave()->colShip(2, 500000);
//                    char soundAction = 'S';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if(enemy4->getOutclip().y < 1100 &&   (enemy4->getOutclip().x < -10 and enemy4->getOutclip().x > -15)){
//                    inGame->getCurrentWave()->colShip(3, 500000);
//                    char soundAction = 'S';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if(enemy5->getOutclip().y < 1100 &&   (enemy5->getOutclip().x < -10 and enemy5->getOutclip().x > -15)){
//                    inGame->getCurrentWave()->colShip(4, 500000);
//                    char soundAction = 'S';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if(enemy6->getOutclip().y < 1100 &&   (enemy6->getOutclip().x < -10 and enemy6->getOutclip().x > -15)){
//                    inGame->getCurrentWave()->colShip(5, 500000);
//                    char soundAction = 'S';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if(enemy7->getOutclip().y < 1100 &&   (enemy7->getOutclip().x < -10 and enemy7->getOutclip().x > -15)){
//                    inGame->getCurrentWave()->colShip(6, 500000);
//                    char soundAction = 'S';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }
//
//                if(enemy8->getOutclip().y < 1100 &&   (enemy8->getOutclip().x < -10 and enemy8->getOutclip().x > -15)){
//                    inGame->getCurrentWave()->colShip(7, 500000);
//                    char soundAction = 'S';
//                    boost::asio::write(player->port, boost::asio::buffer(&soundAction, 1));
//                }



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

                if (player->getOutClipB5().x > 1470 && player->getOutClipB5().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB6().x > 1470 && player->getOutClipB6().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB7().x > 1470 && player->getOutClipB7().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB8().x > 1470 && player->getOutClipB8().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB9().x > 1470 && player->getOutClipB9().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB10().x > 1470 && player->getOutClipB10().y < 1000){
                    if (bulletsLeft != 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->noImpact();
                        bulletsCLeft += 1;
                    }
                    else{
                        bulletsCLeft -= 1;
                    }

                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));
                }

                //Colision entre naves
                if (CheckCollisionRecs(player->getOutClip(), enemy1->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy2->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy3->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy4->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy5->getOutclip())
                    || CheckCollisionRecs(player->getOutClip(), enemy6->getOutclip())){

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

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();

                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            cout << " me lo mato" << endl;
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                        else{
                            cout << " aguanta el guineo" << endl;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy2->getOutclip())){

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        cout << inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage()) << endl;

                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy7->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy8->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB2(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy7->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy8->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB3(), enemy1->getOutclip())){
                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            cout << "is it here" << endl;
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                            cout << "sour grapes" << endl;

                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy7->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy8->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB4(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
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
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy7->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy8->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB5(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB5(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB5(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB5(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB5(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB5(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB5(), enemy7->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB5(), enemy8->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB6(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB6(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB6(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB6(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB5(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB6(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB6(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB6(), enemy7->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB6(), enemy8->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB6(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB7(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB7(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB7(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB7(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB7(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB7(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB7(), enemy7->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB7(), enemy8->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB7(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB8(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB8(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB8(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB8(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB8(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB8(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB8(), enemy7->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB8(), enemy8->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB8(raylib::Rectangle(0,1100, 32,32));

                }



                if (CheckCollisionRecs(player->getOutClipB9(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB9(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB9(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB9(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB9(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB9(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB9(), enemy7->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB9(), enemy8->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB9(raylib::Rectangle(0,1100, 32,32));

                }


                if (CheckCollisionRecs(player->getOutClipB10(), enemy1->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB10(), enemy2->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB10(), enemy3->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        cout << "tercero" << endl;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClipB10(), enemy4->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB10(), enemy5->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(4, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy5->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB10(), enemy6->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(5, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB10(), enemy7->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB10(), enemy8->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB10(raylib::Rectangle(0,1100, 32,32));

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

                if (CheckCollisionRecs(player->getOutClip(), enemy5->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy5->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        sleep(1/2);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy5->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        sleep(1/2);
                    }
                }

                if (CheckCollisionRecs(player->getOutClip(), enemy6->getOutclipB())){

                    shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
                    if (shipPlayer->getVida() > 0){
                        cout << "aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy6->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        cout << shipPlayer->getVida() << endl;
                        sleep(1/2);
                    }
                    else{
                        cout << "No aguanto" << endl;
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        enemy6->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                        lives --;
                        shipPlayer->setVida(50);
                        sleep(1/2);
                    }
                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy7->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(6, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy7->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy8->getOutclip())){

                    if (bulletsLeft > 0){
                        bulletsLeft -= 1;
                        shipPlayer->ammunation->impact();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    if (bulletsLeft == 0 and bulletsCLeft != 0){
                        bulletsCLeft -=1;
                        shipPlayer->ammunation->bulletCollector->deleteF();
                        if (!inGame->getCurrentWave()->colShip(7, shipPlayer->ammunation->bulletCollector->getDamage())){
                            enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));
                            obj ++;
                        }
                    }
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                }

                //Ver si paso de oleada
                if (inGame->checkNextW()){
                    wave--;
                    obj = 0;
                    player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                    enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
                    enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 300, 64,64));
                    enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 400, 64,64));
                    enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 500, 64,64));
                    enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy5->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 650, 64,64));
                    enemy5->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
                    enemy6->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 900, 64,64));
                    enemy6->setOutClipB(raylib::Rectangle(-5, 500, 64,64));

                }

                if(wave < 0){
                    currentScreen = MENU;
                    wave = 4;
                }
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
                DrawTextureRec(ratataButton, sourceRecRatata, (Vector2){ratataButtonBounds.x, ratataButtonBounds.y}, WHITE);
                DrawTextureRec(shieldButton, sourceRecShield, (Vector2){shieldButtonBounds.x, shieldButtonBounds.y}, WHITE);
                DrawTextureRec(amorButton, sourceRecAmor, (Vector2){amorButtonBounds.x, amorButtonBounds.y}, WHITE);
                DrawTextureRec(curaButton, sourceRecCura, (Vector2){curaButtonBounds.x, curaButtonBounds.y}, WHITE);

                string firstTextB = "Bullets: ";
                string secondtextB = to_string(bulletsLeft);
                string bulletCounter = firstTextB + secondtextB;
                DrawText(bulletCounter.c_str(), 0,0,30, GREEN);

                string firstTextBC = "Bullets in the Kollector: ";
                string secondtextBC = to_string(bulletsCLeft);
                string bulletCCounter = firstTextBC + secondtextBC;
                DrawText(bulletCCounter.c_str(), 220,0,30, GREEN);

                string firstTextLives = "Lives: ";
                string secondtextLives = to_string(lives);
                string livesCounter = firstTextLives + secondtextLives;
                DrawText(livesCounter.c_str(), 640,0,30, GREEN);

                string firstTextWaves = "Wave: ";
                string secondTextWaves = to_string(wave);
                string waveCounter = firstTextWaves + secondTextWaves;
                DrawText(waveCounter.c_str(), 800,0,30, GREEN);

                string firstTextPower = "Power: ";
                string secondTextPower = estadoPoder;
                string powerState = firstTextPower + secondTextPower;
                DrawText(powerState.c_str(), 975,0,30, GREEN);




            }
            break;

            case F6: {
                backgroundF6->Update();
                backgroundF6->Draw();
                player->Draw();
                enemy1->Draw();
                enemy2->Draw();
                enemy3->Draw();
                enemy4->Draw();
                enemy5->Draw();
                enemy6->Draw();
                DrawTextureRec(ratataButton, sourceRecRatata, (Vector2){ratataButtonBounds.x, ratataButtonBounds.y}, WHITE);
                DrawTextureRec(shieldButton, sourceRecShield, (Vector2){shieldButtonBounds.x, shieldButtonBounds.y}, WHITE);
                DrawTextureRec(amorButton, sourceRecAmor, (Vector2){amorButtonBounds.x, amorButtonBounds.y}, WHITE);
                DrawTextureRec(curaButton, sourceRecCura, (Vector2){curaButtonBounds.x, curaButtonBounds.y}, WHITE);

                string firstTextB = "Bullets: ";
                string secondtextB = to_string(bulletsLeft);
                string bulletCounter = firstTextB + secondtextB;
                DrawText(bulletCounter.c_str(), 0,0,30, GREEN);

                string firstTextBC = "Bullet in the Kollector: ";
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

            case F11: {
                backgroundF11->Update();
                backgroundF11->Draw();
                player->Draw();
                enemy1->Draw();
                enemy2->Draw();
                enemy3->Draw();
                enemy4->Draw();
                enemy5->Draw();
                enemy6->Draw();
                enemy7->Draw();
                enemy8->Draw();
                DrawTextureRec(ratataButton, sourceRecRatata, (Vector2){ratataButtonBounds.x, ratataButtonBounds.y}, WHITE);
                DrawTextureRec(shieldButton, sourceRecShield, (Vector2){shieldButtonBounds.x, shieldButtonBounds.y}, WHITE);
                DrawTextureRec(amorButton, sourceRecAmor, (Vector2){amorButtonBounds.x, amorButtonBounds.y}, WHITE);
                DrawTextureRec(curaButton, sourceRecCura, (Vector2){curaButtonBounds.x, curaButtonBounds.y}, WHITE);

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


