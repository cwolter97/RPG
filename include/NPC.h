#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>
#include "Item.h"

class NPC
{
    public:
        NPC(const std::string name);
        void Talk();
        void DialogueTree();
        void LoadDialogue(std::string NPC_Name);
        std::string GetName();
        bool DropItemFromInv(string ItemName);
        void AddItemToInv(Item ItemName);
    private:
        std::string m_Name;
        std::vector<std::string> m_RawDialogue;
        std::vector<Item> m_Inventory;
};

#endif // NPC_H
