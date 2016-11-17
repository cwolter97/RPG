#ifndef PLAYER_H
#define PLAYER_H
#include "Item.h"
#include <vector>
//a 'p' prefix to a variable name means "player"

class Player{
    public:
        Player(const string& name="Player", const string& pClass="Bard", int maxHealth = 10, int health = 10, int maxmana = 5, int mana = 5, int level = 1);
        string GetName();
        string GetClass();

        int GetMaxHealth();
        void SetMaxHealth(int add = 0);
        int GetHealth();
        void SetHealth(int add = 0);

        int GetMaxMana();
        void SetMaxMana(int add = 0);
        int GetMana();
        void SetMana(int add = 0);

        int GetLevel();
        void SetLevel(int add = 0);

        //returns true if DropItemFromInv was successful
        bool DropItemFromInv(string ItemName);
        void AddItemToInv(Item ItemName);
        void DisplayInventory();

        void Save();
        void ShowStats();

    private:
        string m_Name;
        string m_Class;

        int m_MaxHealth;
        int m_Health;

        int m_MaxMana;
        int m_Mana;

        int m_Level;

        std::vector<Item> m_Inventory;
};

#endif // PLAYER_H
