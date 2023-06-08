#ifndef ITEM_H
#define ITEM_H

class Item
{
private:
    static int pos[2];

public:
    Item(int posX, int posY);

    static void updateItem(int sizeX, int sizeY);
    int* getPosition();
    int getX();
    int getY();

};

#endif
