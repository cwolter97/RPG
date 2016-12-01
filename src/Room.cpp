#include "Room.h"
#include <vector>
#include <algorithm>

Room::Room(const string& name, int MapIndex):m_Name(name),m_MapIndex(MapIndex)
{
    //just some default items to throw into the room
    m_Collectibles.push_back(Item("sword"));
    m_Collectibles.push_back(Item("shield"));
    NPC Bel("Bel Drock");
    m_NPCs.push_back(Bel);
    Bel.AddItemToInv(Item("Hocus Pocus by Focus"));
    Bel.AddItemToInv(Item("HUGESWORD"));
}

void Room::ShowCollectibles(){
    std::cout << "\nThis room contains: ";

    for(std::vector<Item>::iterator iter = m_Collectibles.begin(); iter != m_Collectibles.end(); iter++){
        std::cout << iter->GetName() << " ";
    }
}

bool Room::RemoveCollectible(string ItemName){
    //Look for ItemName in vector
    std::vector<Item>::iterator iter = std::find(m_Collectibles.begin(), m_Collectibles.end(), ItemName);
    //If it didn't find it, say so and leave
    if(iter==m_Collectibles.end()){
        std::cout << "\nObject does not exist!";
        return false;
    }
    //Erase item from vector if it was found
    m_Collectibles.erase(iter);
    return true;
}
void Room::AddCollectible(Item ItemName){
    m_Collectibles.push_back(ItemName);
}

void Room::ShowPlayer_and_NPCs(){
    std::cout << "\nPeople also in this room: ";

    for(std::vector<NPC>::iterator iter = m_NPCs.begin(); iter != m_NPCs.end(); iter++){
        std::cout << iter->GetName() << " ";
    }
}

void Room::TalkTo(string NPCName){
    bool talking = false;

    for(std::vector<NPC>::iterator iter = m_NPCs.begin(); iter != m_NPCs.end(); iter++){
        if(iter->GetName() == NPCName){
            iter->Talk();
            talking = true;
        }
    }

    if(!talking){
        std::cout << "\nCould not find NPC " << NPCName << "...";
    }
}

void Room::Look(){
    std::cout << "You look around and see...";
    ShowCollectibles();
    ShowPlayer_and_NPCs();
    //ShowExits();
}


