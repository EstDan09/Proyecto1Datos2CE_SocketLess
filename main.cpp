#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "raylib.h"
#define NUM_FRAMES 1 //recorte
#include "raymath.h"
using namespace std;

#include "Background.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

#include "/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/raylib-cpp-4.5.0/include/raylib-cpp.hpp"

int lives = 10;
int fase1Con = 0;
int bulletsLeft = 300;
int bulletsCLeft = 0;

//Pantallas que voy a usar
//------------------------------
typedef enum GameScreen {MENU = 0, F1, F2, F3} GameScreen;
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
    Image startButtonImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/start.png");
    ImageResize(&startButtonImage, 350, 200);
    Texture2D startButton = LoadTextureFromImage(startButtonImage);

    Image settingsButtonImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/settings.png");
    ImageResize(&settingsButtonImage, 100, 100);
    Texture2D settingsButton = LoadTextureFromImage(settingsButtonImage);

    Image shipImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/ships.png");
    raylib::Texture shipUsableImage = LoadTextureFromImage(shipImage);

    Image bulletImage = LoadImage("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/blasts.png");
    raylib::Texture bulletUsableImage = LoadTextureFromImage(bulletImage);

    raylib::Texture backgroundImageF1 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF1.png");

    raylib::Texture backgroundImageF2 = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgF2.png");

    raylib::Texture backgroundImageMenu = LoadTexture("/home/esteban/CLionProjects/Proyecto1Datos2CE_Cliente/assets/bgMenu.png");
    //------------------------------

    //Objetos
    //------------------------------
    auto* player = new Player (&shipUsableImage, raylib::Rectangle(40,8, 8,8),
                   raylib::Rectangle(100,GetScreenHeight()/2,64,64), 200.0f,
                   &bulletUsableImage, 1.0f);

    auto* enemy1 = new Enemy(&shipUsableImage, raylib::Rectangle(40,48,8,8),
                raylib::Rectangle(GetScreenWidth()-70, 200, 64,64), 200.0f,
                &bulletUsableImage, false);

    auto* enemy2 = new Enemy(&shipUsableImage, raylib::Rectangle(40,48,8,8),
                 raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64), 200.0f,
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
    //------------------------------


    //Parametros del boton Start
    //------------------------------
    float frameHeightStart = (float)startButton.height/NUM_FRAMES; //390
    Rectangle sourceRecStart = {0,0, (float)startButton.width, frameHeightStart};

    Rectangle startBottonBounds = { screenWidth/2.0f - startButton.width/2.0f, screenHeight/2.0f - startButton.height/NUM_FRAMES/2.0f,
                            (float)startButton.width, frameHeightStart};
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
    int startButtonState = 0;
    bool startButtonAction = false;
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
                startButtonAction = false;

                if (CheckCollisionPointRec(mousePoint, startBottonBounds)) {
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                        startButtonState = 2 ;
                    }
                    else {
                        startButtonState = 1;
                    }
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
                        startButtonAction = true;
                    }
                }
                else {
                    startButtonState = 1;
                }
                if (startButtonAction) {
                    //PlaySound(fxButton);
                    currentScreen = F1;
                    lives = 2;

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

                if (lives <= 0){
                    currentScreen = MENU;
                }

                //Colisiones
                if (player->getOutClipB1().x > 1470 && player->getOutClipB1().y < 1000){
                    bulletsLeft -= 1;
                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB2().x > 1470 && player->getOutClipB2().y < 1000){
                    bulletsLeft -= 1;
                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB3().x > 1470 && player->getOutClipB3().y < 1000){
                    bulletsLeft -= 1;
                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));
                }

                if (player->getOutClipB4().x > 1470 && player->getOutClipB4().y < 1000){
                    bulletsLeft -= 1;
                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));
                }

                if (CheckCollisionRecs(player->getOutClip(), enemy1->getOutclip())
                || CheckCollisionRecs(player->getOutClip(), enemy2->getOutclip())
                || CheckCollisionRecs(player->getOutClip(), enemy3->getOutclip())
                || CheckCollisionRecs(player->getOutClip(), enemy4->getOutclip())){


                    player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                    lives --;

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy1->getOutclip())){
                    bulletsLeft -= 1;

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                    enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));



//                            enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64));
//                            enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 700, 64,64));
//                            enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 790, 64,64));
//                            enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
//                            player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
//                            currentScreen = F2;
//                        }
//                    }

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy2->getOutclip())){

                    bulletsLeft -= 1;

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));

                    enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));
                }

                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy3->getOutclip())){
                    bulletsLeft -= 1;

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));


                    enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

                        string message = "E";
                        int sendRes = send(sock, message.c_str(), message.size() + 1, 0);

//                            enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64));
//                            enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 700, 64,64));
//                            enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 790, 64,64));
//                            enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
//                            player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
//                            currentScreen = F2;


                }

                if (CheckCollisionRecs(player->getOutClipB1(), enemy4->getOutclip())){
                    bulletsLeft -= 1;

                    player->setOutClipB1(raylib::Rectangle(0,1100, 32,32));




                    enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));


//                            enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64));
//                            enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 700, 64,64));
//                            enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 790, 64,64));
//                            enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
//                            player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
//                            currentScreen = F2;


                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy1->getOutclip())){
                    bulletsLeft -= 1;

                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                        enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

//                            enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64));
//                            enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 700, 64,64));
//                            enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 790, 64,64));
//                            enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
//                            player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
//                            currentScreen = F2;

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy2->getOutclip())){

                    bulletsLeft -= 1;

                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));

                    enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

//                            enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64));
//                            enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 700, 64,64));
//                            enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 790, 64,64));
//                            enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
//                            player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
//                            currentScreen = F2;


                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy3->getOutclip())){
                    bulletsLeft -= 1;

                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));


                    enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

//                            enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64));
//                            enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 700, 64,64));
//                            enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 790, 64,64));
//                            enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
//                            player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
//                            currentScreen = F2;

                }

                if (CheckCollisionRecs(player->getOutClipB2(), enemy4->getOutclip())){
                    bulletsLeft -= 1;

                    player->setOutClipB2(raylib::Rectangle(0,1100, 32,32));


                    enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));


//                            enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64));
//                            enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 700, 64,64));
//                            enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 790, 64,64));
//                            enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
//                            player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
//                            currentScreen = F2;
                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy1->getOutclip())){
                    bulletsLeft -= 1;

                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));


                        enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

//                            enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64));
//                            enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 700, 64,64));
//                            enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 790, 64,64));
//                            enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
//                            player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
//                            currentScreen = F2;


                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy2->getOutclip())){
                    bulletsLeft -= 1;

                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));

                        enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

//                            enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64));
//                            enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 700, 64,64));
//                            enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 790, 64,64));
//                            enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
//                            player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
//                            currentScreen = F2;

                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy3->getOutclip())){
                    bulletsLeft -= 1;

                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));

                    //if (recibido == "destruido"){
                        enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

                        //if (recibido == "nextF"){
//
//                            enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64));
//                            enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 700, 64,64));
//                            enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 790, 64,64));
//                            enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
//                            player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
//                            currentScreen = F2;
//                        }
//                    }

                }

                if (CheckCollisionRecs(player->getOutClipB3(), enemy4->getOutclip())){
                    bulletsLeft -= 1;

                    player->setOutClipB3(raylib::Rectangle(0,1100, 32,32));



//                    if (recibido == "destruido"){
                        enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

//                        if (recibido == "nextF"){
//
//                            enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64));
//                            enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 700, 64,64));
//                            enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 790, 64,64));
//                            enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
//                            player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
//                            currentScreen = F2;
//                        }
//                    }
                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy1->getOutclip())){
                    bulletsLeft -= 1;

                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

//                    if (recibido == "destruido"){
                        enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

//                        if (recibido == "nextF"){
//
//                            enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64));
//                            enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 700, 64,64));
//                            enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 790, 64,64));
//                            enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
//                            player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
//                            currentScreen = F2;
//                        }
//                    }

                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy2->getOutclip())){
                    bulletsLeft -= 1;

                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

//                    if (recibido == "destruido"){
                        enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

//                        if (recibido == "nextF"){
//
//                            enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64));
//                            enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 700, 64,64));
//                            enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 790, 64,64));
//                            enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
//                            player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
//                            currentScreen = F2;
//                        }
//                    }
                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy3->getOutclip())){
                    bulletsLeft -= 1;

                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

//                    if (recibido == "destruido"){
                        enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

//                        if (recibido == "nextF"){
//
//                            enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64));
//                            enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 700, 64,64));
//                            enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 790, 64,64));
//                            enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
//                            player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
//                            currentScreen = F2;
//                        }
//                    }

                }

                if (CheckCollisionRecs(player->getOutClipB4(), enemy4->getOutclip())){
                    bulletsLeft -= 1;

                    player->setOutClipB4(raylib::Rectangle(0,1100, 32,32));

//                    if (recibido == "destruido"){
                        enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));


//                        if (recibido == "nextF"){
//
//                            enemy1->setOutClip(raylib::Rectangle(GetScreenWidth()-70, GetScreenHeight()/2, 64,64));
//                            enemy2->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 700, 64,64));
//                            enemy3->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 790, 64,64));
//                            enemy4->setOutClip(raylib::Rectangle(GetScreenWidth()-70, 200, 64,64));
//                            player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
//                            currentScreen = F2;
//                        }
//                    }
                }

                if (CheckCollisionRecs(player->getOutClip(), enemy1->getOutclipB())
                    || CheckCollisionRecs(player->getOutClip(), enemy2->getOutclipB())
                    || CheckCollisionRecs(player->getOutClip(), enemy3->getOutclipB())
                    || CheckCollisionRecs(player->getOutClip(), enemy4->getOutclipB())){

//                    if (recibido == "false"){
                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                        lives --;
                        sleep(1);
//                    }
//                    else{
//                        player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
//                        sleep(1);
//                    }
                }

                string message = "W";
                int sendRes = send(sock, message.c_str(), message.size() + 1, 0);

                int bytesReceived = recv(sock, buf, 4096, 0);
                string recibido = string(buf, 0, bytesReceived);
                if (recibido == "false"){
                    player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                    lives --;
                    sleep(1);
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

            }
            break;
            default: break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch(currentScreen){
            case MENU:{
                backgroundMenu->Draw();
                DrawTextureRec(startButton, sourceRecStart, (Vector2){ startBottonBounds.x, startBottonBounds.y }, WHITE); // Draw button frame
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
            }
            break;

            case F2: {
                backgroundF2->Update();
                backgroundF2->Draw();
                player->Draw();
                //player->setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
                enemy1->Draw();
                //enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));
                enemy2->Draw();
                enemy3->Draw();
                enemy4->Draw();
            }
                break;
            default: break;
        }
        EndDrawing();

        //		Enter lines of text


        //		Send to server
        int sendRes = send(sock, userInput.c_str(), userInput.size() + 1, 0);
        if (sendRes == -1)
        {
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }

        //		Wait for response
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            cout << "There was an error getting response from server\r\n";
        }


        else
        {
            //		Display response
            cout << string(buf, 0, bytesReceived) << "\r\n";
        }
    };
    UnloadTexture(startButton);  // Unload button texture
    UnloadSound(fxButton);  // Unload sound

    CloseAudioDevice();     // Close audio device

    CloseWindow();
    close(sock);


}