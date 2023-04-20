//
// Created by esteban on 4/5/23.
//

#include "Player.h"
#include "iostream"
#include <boost/asio.hpp>

using namespace std;



Player::Player(raylib::Texture *texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed,
               raylib::Texture* textureForBullets, float delay)
: Entity(texture, inClip, outClip), speed(speed), shootingTime(0), shootingDelay(delay), alive(true), enemy1(nullptr),
    enemy2(nullptr), enemy3(nullptr), enemy4(nullptr), enemy5(nullptr), enemy6(nullptr), enemy7(nullptr), enemy8(nullptr),
    inGame(nullptr), shipPlayer(nullptr), ammunation(nullptr), bulletsLeft(300), bulletsCLeft(0), lives(15){
    maxBullets = 10;
    bullets = new Bullet[10]{
        Bullet(textureForBullets, raylib::Rectangle(64,56, 8,8),
               raylib::Rectangle(100,GetScreenHeight()/2, 32,32), 300.0f, 0),
        Bullet(textureForBullets, raylib::Rectangle(64,56, 8,8),
            raylib::Rectangle(100,GetScreenHeight()/2, 32,32), 300.0f, 0),
        Bullet(textureForBullets, raylib::Rectangle(64,56, 8,8),
            raylib::Rectangle(100,GetScreenHeight()/2, 32,32), 300.0f, 0),
        Bullet(textureForBullets, raylib::Rectangle(64,56, 8,8),
            raylib::Rectangle(100,GetScreenHeight()/2, 32,32), 300.0f, 0),
        Bullet(textureForBullets, raylib::Rectangle(64,56, 8,8),
               raylib::Rectangle(100,GetScreenHeight()/2, 32,32), 300.0f, 0),
        Bullet(textureForBullets, raylib::Rectangle(64,56, 8,8),
               raylib::Rectangle(100,GetScreenHeight()/2, 32,32), 300.0f, 0),
        Bullet(textureForBullets, raylib::Rectangle(64,56, 8,8),
               raylib::Rectangle(100,GetScreenHeight()/2, 32,32), 300.0f, 0),
        Bullet(textureForBullets, raylib::Rectangle(64,56, 8,8),
               raylib::Rectangle(100,GetScreenHeight()/2, 32,32), 300.0f, 0),
        Bullet(textureForBullets, raylib::Rectangle(64,56, 8,8),
               raylib::Rectangle(100,GetScreenHeight()/2, 32,32), 300.0f, 0),
        Bullet(textureForBullets, raylib::Rectangle(64,56, 8,8),
               raylib::Rectangle(100,GetScreenHeight()/2, 32,32), 300.0f, 0)
    };
    outClipB1 = bullets[0].getOutClip();
    outClipB2 = bullets[1].getOutClip();
    outClipB3 = bullets[2].getOutClip();
    outClipB4 = bullets[3].getOutClip();
    outClipB5 = bullets[4].getOutClip();
    outClipB6 = bullets[5].getOutClip();
    outClipB7 = bullets[6].getOutClip();
    outClipB8 = bullets[7].getOutClip();
    outClipB9 = bullets[8].getOutClip();
    outClipB10 = bullets[9].getOutClip();



}

Player::~Player(){
    delete[] bullets;
}

void Player::Event() {

//    boost::asio::streambuf buffer;
//    boost::asio::read_until(port, buffer, '\n');
//    string message;
//    istream input_stream(&buffer);
//    getline(input_stream, message);
//    if(message.find("U") != string::npos){
//        inClip.y = 0;
//        outClip.y -= GetFrameTime() * speed;
//        if(outClip.y < 0) outClip.y = 0;
//    }
//    if(message.find("D") != string::npos){
//        inClip.y = 16;
//        outClip.y += GetFrameTime() * speed;
//        if(outClip.y > GetScreenHeight() - outClip.height) outClip.y = GetScreenHeight() - outClip.height;
//    }
//
//    if (message.find("0") != string::npos){
//        setDelay(9.0);
//    }
//
//    if (message.find("1") != string::npos){
//        setDelay(8.0);
//    }
//
//    if (message.find("2") != string::npos){
//        setDelay(7.0);
//    }
//
//    if (message.find("3") != string::npos){
//        setDelay(6.0);
//    }
//
//    if (message.find("4") != string::npos){
//        setDelay(5.0);
//    }
//
//    if (message.find("5") != string::npos){
//        setDelay(4.0);
//    }
//
//    if (message.find("6") != string::npos){
//        setDelay(3.0);
//    }
//
//    if (message.find("7") != string::npos){
//        setDelay(2.0);
//    }
//
//    if (message.find("8") != string::npos){
//        setDelay(1.5);
//    }
//
//    if (message.find("9") != string::npos){
//        setDelay(1.0);
//    }




    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        inClip.y = 0;
        outClip.x += GetFrameTime() * speed;
        if(outClip.y < 0) outClip.y = 0;
    }
    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        inClip.y = 0;
        outClip.y -= GetFrameTime() * speed;
        if(outClip.y < 0) outClip.y = 0;
    }
    else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
        inClip.y = 16;
        outClip.y += GetFrameTime() * speed;
        if(outClip.y > GetScreenHeight() - outClip.height) outClip.y = GetScreenHeight() - outClip.height;

    }
    else{
        inClip.y= 8;
    }

    if(shootingTime <= 0){
        for (int i = 0; i < maxBullets; i++){
            if(bullets[i].IsHit()){
                bullets[i].Reset(outClip);
                outClipB1 = bullets[0].getOutClip();
                outClipB2 = bullets[1].getOutClip();
                outClipB3 = bullets[2].getOutClip();
                outClipB4 = bullets[3].getOutClip();
                shootingTime = shootingDelay;

                break;
            }
        }
    }
    else{
        shootingTime -= GetFrameTime();
    }
}

void Player::Update() {
    for (int i = 0; i < maxBullets; i++){
        if(!bullets[i].IsHit()){
            bullets[i].Update();
            outClipB1 = bullets[0].getOutClip();
            outClipB2 = bullets[1].getOutClip();
            outClipB3 = bullets[2].getOutClip();
            outClipB4 = bullets[3].getOutClip();
            outClipB5 = bullets[4].getOutClip();
            outClipB6 = bullets[5].getOutClip();
            outClipB7 = bullets[6].getOutClip();
            outClipB8 = bullets[7].getOutClip();
            outClipB9 = bullets[8].getOutClip();
            outClipB10 = bullets[9].getOutClip();

        }
    }
}

void Player::Draw() {
    for (int i = 0; i < maxBullets; i++){
        if(!bullets[i].IsHit()){
            bullets[i].Draw();
        }
    }
    texture->Draw(inClip, outClip);
}

raylib::Rectangle Player::getOutClip() {
    return outClip;
}

void Player::setOutClip(raylib::Rectangle outClipNew) {
     outClip = outClipNew;
}

void Player::setOutClipB1(raylib::Rectangle outClipNew) {
    bullets[0].setOutClip(outClipNew);
}

void Player::setOutClipB2(raylib::Rectangle outClipNew) {
    bullets[1].setOutClip(outClipNew);
}

void Player::setOutClipB3(raylib::Rectangle outClipNew) {
    bullets[2].setOutClip(outClipNew);
}

void Player::setOutClipB4(raylib::Rectangle outClipNew) {
    bullets[3].setOutClip(outClipNew);
}

void Player::setOutClipB5(raylib::Rectangle outClipNew) {
    bullets[4].setOutClip(outClipNew);
}

void Player::setOutClipB6(raylib::Rectangle outClipNew) {
    bullets[5].setOutClip(outClipNew);
}

void Player::setOutClipB7(raylib::Rectangle outClipNew) {
    bullets[6].setOutClip(outClipNew);
}

void Player::setOutClipB8(raylib::Rectangle outClipNew) {
    bullets[7].setOutClip(outClipNew);
}

void Player::setOutClipB9(raylib::Rectangle outClipNew) {
    bullets[8].setOutClip(outClipNew);
}

void Player::setOutClipB10(raylib::Rectangle outClipNew) {
    bullets[9].setOutClip(outClipNew);
}

raylib::Rectangle Player::getOutClipB1() {
    return outClipB1;
}

raylib::Rectangle Player::getOutClipB2() {
    return outClipB2;
}

raylib::Rectangle Player::getOutClipB3() {
    return outClipB3;
}

raylib::Rectangle Player::getOutClipB4() {
    return outClipB4;
}

raylib::Rectangle Player::getOutClipB5() {
    return outClipB5;
}

raylib::Rectangle Player::getOutClipB6() {
    return outClipB6;
}

raylib::Rectangle Player::getOutClipB7() {
    return outClipB7;
}

raylib::Rectangle Player::getOutClipB8() {
    return outClipB8;
}

raylib::Rectangle Player::getOutClipB9() {
    return outClipB9;
}

raylib::Rectangle Player::getOutClipB10() {
    return outClipB10;
}




void Player::setDelay(float x) {
    cout << "change to " << x << endl;

    shootingDelay = x;
}

//void Player::ricoMauro() {
//    port.set_option(boost::asio::serial_port_base::baud_rate(9600));
//}

void Player::setEnemy1(Enemy* x) {
    enemy1 = x;
}

void Player::setEnemy2(Enemy* x) {
    enemy2 = x;
}

void Player::setEnemy3(Enemy* x) {
    enemy3 = x;
}

void Player::setEnemy4(Enemy* x) {
    enemy4 = x;
}

void Player::setEnemy5(Enemy* x) {
    enemy5 = x;
}

void Player::setEnemy6(Enemy* x) {
    enemy6 = x;
}

void Player::setEnemy7(Enemy* x) {
    enemy7 = x;
}

void Player::setEnemy8(Enemy* x) {
    enemy8 = x;
}

void Player::setInGame(InGame* x) {
    inGame = x;
}

void Player::setShipPlayer(ShipPlayer* x) {
    shipPlayer = x;
}

void Player::setAmmunation(Ammunation *x) {
    ammunation = x;
}

void Player::setLives(int x) {
    lives = x;
}

int Player::getLives() {
    return lives;
}

void Player::setBulletsLeft(int x) {
    bulletsLeft = x;
}

int Player::getBulletsLeft() {
    return bulletsLeft;
}

void Player::setBulletsCLeft(int x) {
    bulletsCLeft = x;
}

int Player::getBulletsCLeft() {
    return bulletsCLeft;
}


