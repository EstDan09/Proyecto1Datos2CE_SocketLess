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

    boost::asio::streambuf buffer;
    boost::asio::read_until(port, buffer, '\n');
    string message;
    istream input_stream(&buffer);
    getline(input_stream, message);
    if(message.find("U") != string::npos){
        inClip.y = 0;
        outClip.y -= GetFrameTime() * speed;
        if(outClip.y < 0) outClip.y = 0;
    }
    if(message.find("D") != string::npos){
        inClip.y = 16;
        outClip.y += GetFrameTime() * speed;
        if(outClip.y > GetScreenHeight() - outClip.height) outClip.y = GetScreenHeight() - outClip.height;
    }

    if (message.find("0") != string::npos){
        setDelay(9.0);
    }

    if (message.find("1") != string::npos){
        setDelay(8.0);
    }

    if (message.find("2") != string::npos){
        setDelay(7.0);
    }

    if (message.find("3") != string::npos){
        setDelay(6.0);
    }

    if (message.find("4") != string::npos){
        setDelay(5.0);
    }

    if (message.find("5") != string::npos){
        setDelay(4.0);
    }

    if (message.find("6") != string::npos){
        setDelay(3.0);
    }

    if (message.find("7") != string::npos){
        setDelay(2.0);
    }

    if (message.find("8") != string::npos){
        setDelay(1.5);
    }

    if (message.find("9") != string::npos){
        setDelay(1.0);
    }




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

void Player::ricoMauro() {
    port.set_option(boost::asio::serial_port_base::baud_rate(9600));
}

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

void Player::logic1() {

    //Colisiones

    //Enemigo sale bacano
    if(enemy1->getOutclip().y < 1100 &&   (enemy1->getOutclip().x < -10 and enemy1->getOutclip().x > -15)){
        char soundAction = 'S';
        inGame->getCurrentWave()->colShip(0, 500000);
        boost::asio::write(port, boost::asio::buffer(&soundAction, 1));
    }

    if(enemy4->getOutclip().y < 1100 &&   (enemy4->getOutclip().x < -10 and enemy4->getOutclip().x > -15)){
        inGame->getCurrentWave()->colShip(3, 500000);
        char soundAction = 'S';
        boost::asio::write(port, boost::asio::buffer(&soundAction, 1));
    }



    //BulletsOutOfBounds
    if (getOutClipB1().x > 1470 && getOutClipB1().y < 1000){
        if (bulletsLeft != 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->noImpact();
            bulletsCLeft += 1;
        }
        else{
            bulletsCLeft -= 1;
        }

        setOutClipB1(raylib::Rectangle(0,1100, 32,32));
    }

    if (getOutClipB2().x > 1470 && getOutClipB2().y < 1000){
        if (bulletsLeft != 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->noImpact();
            bulletsCLeft += 1;
        }
        else{
            bulletsCLeft -= 1;
        }

        setOutClipB2(raylib::Rectangle(0,1100, 32,32));
    }

    if (getOutClipB3().x > 1470 && getOutClipB3().y < 1000){
        if (bulletsLeft != 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->noImpact();
            bulletsCLeft += 1;
        }
        else{
            bulletsCLeft -= 1;
        }

        setOutClipB3(raylib::Rectangle(0,1100, 32,32));
    }

    if (getOutClipB4().x > 1470 && getOutClipB4().y < 1000){
        if (bulletsLeft != 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->noImpact();
            bulletsCLeft += 1;
        }
        else{
            bulletsCLeft -= 1;
        }

        setOutClipB4(raylib::Rectangle(0,1100, 32,32));
    }

    if (getOutClipB5().x > 1470 && getOutClipB5().y < 1000){
        if (bulletsLeft != 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->noImpact();
            bulletsCLeft += 1;
        }
        else{
            bulletsCLeft -= 1;
        }

        setOutClipB5(raylib::Rectangle(0,1100, 32,32));
    }

    if (getOutClipB6().x > 1470 && getOutClipB6().y < 1000){
        if (bulletsLeft != 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->noImpact();
            bulletsCLeft += 1;
        }
        else{
            bulletsCLeft -= 1;
        }

        setOutClipB6(raylib::Rectangle(0,1100, 32,32));
    }

    if (getOutClipB7().x > 1470 && getOutClipB7().y < 1000){
        if (bulletsLeft != 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->noImpact();
            bulletsCLeft += 1;
        }
        else{
            bulletsCLeft -= 1;
        }

        setOutClipB7(raylib::Rectangle(0,1100, 32,32));
    }

    if (getOutClipB8().x > 1470 && getOutClipB8().y < 1000){
        if (bulletsLeft != 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->noImpact();
            bulletsCLeft += 1;
        }
        else{
            bulletsCLeft -= 1;
        }

        setOutClipB8(raylib::Rectangle(0,1100, 32,32));
    }

    if (getOutClipB9().x > 1470 && getOutClipB9().y < 1000){
        if (bulletsLeft != 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->noImpact();
            bulletsCLeft += 1;
        }
        else{
            bulletsCLeft -= 1;
        }

        setOutClipB9(raylib::Rectangle(0,1100, 32,32));
    }

    if (getOutClipB10().x > 1470 && getOutClipB10().y < 1000){
        if (bulletsLeft != 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->noImpact();
            bulletsCLeft += 1;
        }
        else{
            bulletsCLeft -= 1;
        }

        setOutClipB10(raylib::Rectangle(0,1100, 32,32));
    }

    //Colision entre naves
    if (CheckCollisionRecs(getOutClip(), enemy1->getOutclip())
        || CheckCollisionRecs(getOutClip(), enemy2->getOutclip())
        || CheckCollisionRecs(getOutClip(), enemy3->getOutclip())
        || CheckCollisionRecs(getOutClip(), enemy4->getOutclip())){

        shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
        if (shipPlayer->getVida() > 0){
            setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
            cout << shipPlayer->getVida() << endl;
        }
        else{
            setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
            lives --;
            shipPlayer->setVida(20);
        }
    }

    //Colision bala jugador - enemigo
    if (CheckCollisionRecs(getOutClipB1(), enemy1->getOutclip())){

        setOutClipB1(raylib::Rectangle(0,1100, 32,32));
        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();

            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                cout << " me lo mato" << endl;
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

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

            }
        }

    }

    if (CheckCollisionRecs(getOutClipB1(), enemy2->getOutclip())){

        setOutClipB1(raylib::Rectangle(0,1100, 32,32));
        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            cout << inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage()) << endl;

            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                cout << " me lo mato" << endl;
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

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

            }
        }
    }

    if (CheckCollisionRecs(getOutClipB1(), enemy3->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            cout << "tercero" << endl;
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));


            }
        }
        setOutClipB1(raylib::Rectangle(0,1100, 32,32));
    }

    if (CheckCollisionRecs(getOutClipB1(), enemy4->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB1(raylib::Rectangle(0,1100, 32,32));

    }


    if (CheckCollisionRecs(getOutClipB2(), enemy1->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB2(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB2(), enemy2->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB2(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB2(), enemy3->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            cout << "tercero" << endl;
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB2(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB2(), enemy4->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB2(raylib::Rectangle(0,1100, 32,32));
    }


    if (CheckCollisionRecs(getOutClipB3(), enemy1->getOutclip())){
        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB3(raylib::Rectangle(0,1100, 32,32));


    }

    if (CheckCollisionRecs(getOutClipB3(), enemy2->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB3(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB3(), enemy3->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            cout << "terceroBacam" << endl;
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                cout << "is it here" << endl;
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

                cout << "sour grapes" << endl;

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB3(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB3(), enemy4->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB3(raylib::Rectangle(0,1100, 32,32));
    }


    if (CheckCollisionRecs(getOutClipB4(), enemy1->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB4(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB4(), enemy2->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB4(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB4(), enemy3->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            cout << "tercero" << endl;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB4(raylib::Rectangle(0,1100, 32,32));
    }

    if (CheckCollisionRecs(getOutClipB4(), enemy4->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB4(raylib::Rectangle(0,1100, 32,32));

    }


    if (CheckCollisionRecs(getOutClipB5(), enemy1->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB5(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB5(), enemy2->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB5(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB5(), enemy3->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            cout << "tercero" << endl;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB5(raylib::Rectangle(0,1100, 32,32));
    }

    if (CheckCollisionRecs(getOutClipB5(), enemy4->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB5(raylib::Rectangle(0,1100, 32,32));

    }


    if (CheckCollisionRecs(getOutClipB6(), enemy1->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB6(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB6(), enemy2->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB6(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB6(), enemy3->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            cout << "tercero" << endl;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB6(raylib::Rectangle(0,1100, 32,32));
    }

    if (CheckCollisionRecs(getOutClipB6(), enemy4->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB5(raylib::Rectangle(0,1100, 32,32));

    }


    if (CheckCollisionRecs(getOutClipB7(), enemy1->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB7(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB7(), enemy2->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB7(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB7(), enemy3->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            cout << "tercero" << endl;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB7(raylib::Rectangle(0,1100, 32,32));
    }

    if (CheckCollisionRecs(getOutClipB7(), enemy4->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB7(raylib::Rectangle(0,1100, 32,32));

    }


    if (CheckCollisionRecs(getOutClipB8(), enemy1->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB8(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB8(), enemy2->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB8(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB8(), enemy3->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            cout << "tercero" << endl;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB8(raylib::Rectangle(0,1100, 32,32));
    }

    if (CheckCollisionRecs(getOutClipB8(), enemy4->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB8(raylib::Rectangle(0,1100, 32,32));

    }


    if (CheckCollisionRecs(getOutClipB9(), enemy1->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB9(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB9(), enemy2->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB9(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB9(), enemy3->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            cout << "tercero" << endl;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB9(raylib::Rectangle(0,1100, 32,32));
    }

    if (CheckCollisionRecs(getOutClipB9(), enemy4->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy6->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB9(raylib::Rectangle(0,1100, 32,32));

    }


    if (CheckCollisionRecs(getOutClipB10(), enemy1->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->getDamage())){
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(0, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy1->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB10(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB10(), enemy2->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(1, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy2->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB10(raylib::Rectangle(0,1100, 32,32));

    }

    if (CheckCollisionRecs(getOutClipB10(), enemy3->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            cout << "tercero" << endl;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(2, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy3->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB10(raylib::Rectangle(0,1100, 32,32));
    }

    if (CheckCollisionRecs(getOutClipB10(), enemy4->getOutclip())){

        if (bulletsLeft > 0){
            bulletsLeft -= 1;
            shipPlayer->ammunation->impact();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        if (bulletsLeft == 0 and bulletsCLeft != 0){
            bulletsCLeft -=1;
            shipPlayer->ammunation->bulletCollector->deleteF();
            if (!inGame->getCurrentWave()->colShip(3, shipPlayer->ammunation->bulletCollector->getDamage())){
                enemy4->setOutClip(raylib::Rectangle(5000,2000,64,64));

            }
        }
        setOutClipB10(raylib::Rectangle(0,1100, 32,32));

    }


    //Colision bala enmeiga-naveJugador
    if (CheckCollisionRecs(getOutClip(), enemy1->getOutclipB())){

        shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
        if (shipPlayer->getVida() > 0){
            cout << "aguanto" << endl;
            setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
            enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
            cout << shipPlayer->getVida() << endl;
            //sleep(1);
        }
        else{
            cout << "No aguanto" << endl;
            setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
            enemy1->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
            lives --;
            shipPlayer->setVida(50);
            //sleep(1);
        }
    }

    if (CheckCollisionRecs(getOutClip(), enemy2->getOutclipB())){

        shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
        if (shipPlayer->getVida() > 0){
            cout << "aguanto" << endl;
            setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
            enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
            cout << shipPlayer->getVida() << endl;
            sleep(1/2);
        }
        else{
            cout << "No aguanto" << endl;
            setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
            enemy2->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
            lives --;
            shipPlayer->setVida(50);
            sleep(1/2);
        }
    }

    if (CheckCollisionRecs(getOutClip(), enemy3->getOutclipB())){

        shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
        if (shipPlayer->getVida() > 0){
            cout << "aguanto" << endl;
            setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
            enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
            cout << shipPlayer->getVida() << endl;
            sleep(1/2);
        }
        else{
            cout << "No aguanto" << endl;
            setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
            enemy3->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
            lives --;
            shipPlayer->setVida(50);
            sleep(1/2);
        }
    }

    if (CheckCollisionRecs(getOutClip(), enemy4->getOutclipB())){

        shipPlayer->setVida((shipPlayer->getVida())-(inGame->getCurrentWave()->getGenDamage()));
        if (shipPlayer->getVida() > 0){
            cout << "aguanto" << endl;
            setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
            enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
            cout << shipPlayer->getVida() << endl;
            sleep(1/2);
        }
        else{
            cout << "No aguanto" << endl;
            setOutClip(raylib::Rectangle(100,GetScreenHeight()/2,64,64));
            enemy4->setOutClipB(raylib::Rectangle(-5, 500, 64,64));
            lives --;
            shipPlayer->setVida(50);
            sleep(1/2);
        }
    }

}
