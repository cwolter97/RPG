#include "Player.h"
#include <string>
#include <vector>
#include <algorithm> //for std::remove()
#include <fstream>

using std::string;
using std::vector;

//overload the == operator to be able to test if item == item
bool operator==(const Item& itemX,const Item& itemY){
    return (itemX.m_Name == itemY.m_Name);
}
//overload the == operator to test if string name == object.m_Name
bool operator==(const string itemNameX,const Item& ItemY){
    return (itemNameX == ItemY.m_Name);
}

Player::Player(const string& name, const string& pClass, int maxhealth, int health, int strength, int level){
    m_Name = name;
    m_Class = pClass;
    //Level 1 Starter Stats
    m_MaxHealth = maxhealth;
    m_Health = health;
    m_Strength = strength;
    m_Level = level;
}

string Player::GetName(){ return m_Name; }

string Player::GetClass(){ return m_Class; }

int Player::GetMaxHealth(){ return m_MaxHealth; }
void Player::SetMaxHealth(int add){ m_MaxHealth += add; }
int Player::GetHealth(){ return m_Health; }
void Player::SetHealth(int add){ m_Health =+ add; }

int Player::GetStrength(){ return m_Strength; }
void Player::SetStrength(int add){ m_Strength += add; }

int Player::GetLevel(){ return m_Level; }
void Player::SetLevel(int add){ m_Level += add; }

int Player::GetExperience(){ return m_Experience; }
void Player::AddExperience(int add){ m_Experience += add; }

bool Player::DropItemFromInv(string ItemName){
    //Looks for ItemName in the vector
    std::vector<Item>::iterator iter = std::find(m_Inventory.begin(), m_Inventory.end(), ItemName);
    //If it didn't find it, say so and leave
    if(iter==m_Inventory.end()){
        std::cout << "\nObject does not exist!";
        return false;
    }
    //if it found, erase it and return true
    m_Inventory.erase(iter);
    return true;
}

void Player::AddItemToInv(Item ItemName){
    m_Inventory.push_back(ItemName);
}

void Player::DisplayInventory(){
    std::cout << "\nYour inventory contains: ";
    std::string itemname = "";

    if(m_Inventory.size() == 0){
        std::cout << "Your inventory is empty!";
        return;
    }

    for(std::vector<Item>::iterator iter = m_Inventory.begin(); iter != m_Inventory.end(); iter++){
        std::cout << iter->GetName() << " ";
    }
}

void Player::Save(){
    std::ofstream saveFile("player.dat");
    if(saveFile.is_open()){
        saveFile << "name=" << m_Name << std::endl;
        saveFile << "class=" << m_Class << std::endl;
        saveFile << "maxhealth=" << m_MaxHealth << std::endl;
        saveFile << "health=" << m_Health << std::endl;
        saveFile << "strength=" << m_Strength << std::endl;
        saveFile << "level=" << m_Level << std::endl;
        saveFile << "end" << std::endl;
        std::cout << "\nFile successfully saved!!\n";
    }else{
        std::cout << "ERROR: File could not be saved :(";
    }
}

void Player::ShowStats(){
    std::cout << "\nClass = " << m_Class << std::endl;
    std::cout << "Max Health = " << m_MaxHealth << std::endl;
    std::cout << "Health = " << m_Health << std::endl;
    std::cout << "Strength = " << m_Strength << std::endl;
    std::cout << "Level = " << m_Level << std::endl;
}
