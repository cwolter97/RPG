#ifndef PLAYER_H
#define PLAYER_H
#include "Item.h"
#include <vector>
//a 'p' prefix to a variable name means "player"

class Player{
    public:
        Player(const string& name="Player", const string& pClass="Bard", int maxHealth = 10, int health = 10, int strength = 5, int level = 1);
        string GetName();
        string GetClass();

        int GetMaxHealth();
        void SetMaxHealth(int add = 0);
        int GetHealth();
        void SetHealth(int add = 0);

        int GetStrength();
        void SetStrength(int add = 0);

        int GetLevel();
        void SetLevel(int add = 0);

        //returns true if DropItemFromInv was successful
        bool DropItemFromInv(string ItemName);
        void AddItemToInv(Item ItemName);
        void DisplayInventory();

        int GetExperience();
        void AddExperience(int add);

        void Save();
        void ShowStats();

    private:
        string m_Name;
        string m_Class;

        int m_MaxHealth;
        int m_Health;

        int m_Strength;

        int m_Level;
        int m_Experience;
        std::vector<Item> m_Inventory;
};

#endif // PLAYER_H
