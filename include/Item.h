#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>

using std::string;

class Item{
    //give overload in player.cpp the ability to read m_Name
    friend bool operator==(const Item& itemX,const Item& itemY);
    friend bool operator==(const string itemNameX,const Item& ItemY);
    public:
        Item(string name=" ");
        string GetName();

    private:
        string m_Name;
};

#endif // ITEM_H
