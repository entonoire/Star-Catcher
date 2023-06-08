#ifndef PLAYER_H
#define PLAYER_H

class Player 
{
private:
    int pos[2];
    int oldPos[2];
    int score;

public:
    Player(int posX, int posY);

    int getScore();
    void increaseScore();

    void setPosition(int posX, int posY);
    void setOldPosition(int posX, int posY);
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    int* getPosition();
    int getX();
    int getY();
    int* getOldPosition();
    int getOldX();
    int getOldY();

};

#endif