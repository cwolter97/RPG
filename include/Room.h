#ifndef ROOM_H
#define ROOM_H
#include "Item.h"
#include "NPC.h"
#include <vector>


class Room
{
    public:
        Room(const string& name = "Generic Room", int MapIndex = 0);
        void ShowPlayer_and_NPCs();
        void ShowCollectibles();
        //returns TRUE if RemoveCollectible was successful
        bool RemoveCollectible(string collectible);
        void AddCollectible(Item collectible);
        void TalkTo(string NPCName);
        void Look();
        int m_MapIndex;
    private:
        std::string m_Name;
        std::vector<Item> m_Collectibles;
        std::vector<NPC> m_NPCs;
};

#endif // ROOM_H
