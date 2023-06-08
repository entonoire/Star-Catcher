#include "Player.h"

Player::Player(int posX, int posY) {
    pos[0] = posX;
    pos[1] = posY;
    oldPos[0] = posX;
    oldPos[1] = posY;
    score = 0;

}

int Player::getScore() { return score; }
void Player::increaseScore() { score += 1; }


void Player::setPosition(int posX, int posY) {
    pos[0] = posX;
    pos[1] = posY;

}

void Player::setOldPosition(int posX, int posY) {
    oldPos[0] = posX;
    oldPos[1] = posY;

}

void Player::moveRight() { pos[0] += 1; }
void Player::moveLeft() { pos[0] -= 1; }

void Player::moveUp() { pos[1] -= 1; }
void Player::moveDown() { pos[1] += 1; }


int* Player::getPosition() { return pos; }
int Player::getX() { return pos[0]; }
int Player::getY() { return pos[1]; }

int* Player::getOldPosition() { return oldPos; }
int Player::getOldX() { return oldPos[0]; }
int Player::getOldY() { return oldPos[1]; }
