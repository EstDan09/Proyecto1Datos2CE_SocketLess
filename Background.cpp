//
// Created by esteban on 4/5/23.
//

#include "Background.h"

Background::Background(raylib::Texture* texture, raylib::Rectangle inClip, raylib::Rectangle outClip, float speed)
: Entity(texture, inClip, outClip), speed(speed) {}

void Background:: Update(){
    outClip.x += GetFrameTime() * speed;
    if(outClip.x >= outClip.height) outClip.y = 0;
}

void Background::DrawSegment() {
    outClip.y = 0;
    texture->Draw(inClip, outClip);
    outClip.y += outClip.height;
    texture->Draw(inClip, outClip);
}

void Background::Draw() {
    DrawSegment();
    outClip.x -= outClip.width;
    DrawSegment();
    outClip.x += outClip.width;

}