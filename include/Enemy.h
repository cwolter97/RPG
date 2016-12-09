#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Item.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Enemy
{
    public:
        Enemy();
        ~Enemy();

    private:
        int m_health;
        int m_maxHealth;


};

#endif // _ENEMY_H_
