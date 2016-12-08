#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "Player.h"
#include "Room.h"
#include "Graphs.h"

using namespace std;

string selectName();
string selectClass();
Player createNewPlayer();
Player loadPlayerFromSave();
void commandHelp();

enum STATS {NAME, CLASS, MAXHEALTH, HEALTH, MAXMANA, MANA, LEVEL};
const int MAX_ROOMS = 5;

//overloads the tolower() function to return strings in all lowercase / created compact because not important to game
string tolower(string c){for(int i=0;i<c.length();i++){c[i]=tolower(c[i]);}return c;}

int main()
{
    string pCommand;
    Player* pPlayer = 0; //pointers used for current player and room
    Room* pCurrentRoom = 0;
    Room* pLastRoom = 0;
    Player player;
    //character creation
    cout << "Super Awesome Coolio Fun RPG Game Thingy!\n\n";

    //create player, then create pointer to player

    ifstream myfile("player.dat");
    if(myfile.is_open()){
        cout << "Loading player from save...!\n";
        myfile.close(); //these 3 lines are to test if the save file exists, then goes to the load function
        player = loadPlayerFromSave();
    }else{ //otherwise start out new
        cout << "Could not read from save, create new character.\n";
        player = createNewPlayer();
    }

    pPlayer = &player;

    cout << "\nGenerating your first room...\n";

    //create rooms
    Room room1("Room 1", 0);
    Room room2("Room 2", 1);
    Room room3("Room 3", 2);
    Room room4("Room 4", 3);
    Room room5("Room 5", 4);
    room3.m_isLocked = true;

    //create WorldMap and start connecting rooms
    Graph<Room> WorldMap(MAX_ROOMS);
    WorldMap.push(room1);
    WorldMap.push(room2);
    WorldMap.push(room3);
    WorldMap.push(room4);
    WorldMap.push(room5);
    WorldMap.attachEdge(0,1);
    WorldMap.attachEdge(0,4);
    WorldMap.attachEdge(1,4);
    WorldMap.attachEdge(1,2);
    WorldMap.attachEdge(2,3);

    //Start of game, start in room 1.
    pCurrentRoom = &room1;

    //main game loop
    do{
        cout << "You are in " << pCurrentRoom->m_Name;
        cout << "\nGive a command\n>>";
        getline(cin, pCommand);
        //make the input into all lowercase to match all command cases(HeLP == help)
        pCommand = tolower(pCommand);
        if(pCommand=="help"){commandHelp();} else //shows available commands
        if(pCommand=="look"){pCurrentRoom->Look();} else //shows everything in room
        if(pCommand=="inv"){pPlayer->DisplayInventory();} else //displays player inventory
        if(pCommand=="pickup"){ //shows room inventory, then prompts which item to pickup
            cout << "Which item will you pickup?";
            pCurrentRoom->ShowCollectibles();

            cout << "\n>>";
            getline(cin, pCommand);
            //if drop was successful, then add that object to player inventory
            if(pCurrentRoom->RemoveCollectible(pCommand))
                pPlayer->AddItemToInv(Item(pCommand));
        } else
        if(pCommand=="drop"){ //displays inventory then asks which item to drop
            cout << "Which item will you drop?";
            pPlayer->DisplayInventory();

            //Maybe add a break if m_Inventory is empty?

            cout << "\n>>";
            getline(cin, pCommand);
            //if drop was successful, then add that object to room inventory
            if(pPlayer->DropItemFromInv(pCommand))
                pCurrentRoom->AddCollectible(Item(pCommand));
        } else
        if(pCommand=="move")
        { //Show rooms that are connected via WorldMap

            //default to false, change to true if those rooms are connected @ L:113
            bool ValidMapIndex[MAX_ROOMS] = {};

            cout << "You can go to rooms:\n";
            for(int i = 0; i < MAX_ROOMS; i++){
                if(WorldMap.isAttached(pCurrentRoom->m_MapIndex, i)){
                    cout << i+1 << endl;
                    ValidMapIndex[i] = true;
                }
            }

            string GoToRoom = "";
            int RoomIndex = -1;
            bool valid = false;
            do{
                cout << "\nGo To Room: ";
                getline(cin, GoToRoom);

                //input validation
                if(GoToRoom.length() == 1){
                    try{
                        RoomIndex = (GoToRoom[0] - '0') - 1; //this line converts the string char to an int, and uses it. Subtract 1 to use with Array Index
                        if(ValidMapIndex[RoomIndex] && RoomIndex < MAX_ROOMS){
                            valid = true;
                        }
                        if(isalpha(GoToRoom[0])){ valid = false;}
                    }catch(int e){}
                }
                //if the conversion fails, retry the input
            }while(!valid);

            //Select and change room here
            pLastRoom = pCurrentRoom;
            pCurrentRoom = &(WorldMap.m_vertices[RoomIndex]);

            //test to see if room is locked, puts player in last room is true;
            if(pCurrentRoom->m_isLocked){
                cout << pCurrentRoom->m_Name << " is locked...\n";
                pCurrentRoom = pLastRoom;
            }
        }else
        if(pCommand=="stats"){
            pPlayer->ShowStats();
        }else
        if(pCommand=="save"){
            pPlayer->Save();
        }else
        if(pCommand=="talk"){
            cout << "Who do you want to talk to?";

            pCurrentRoom->ShowPlayer_and_NPCs();

            cout << "\n>>";
            getline(cin, pCommand);

            pCurrentRoom->TalkTo(pCommand);
        }
    }while(pCommand != "quit");

    cout << "Bye bye " << pPlayer->GetName() << " :)";
    return 0;
}

string selectName(){
    string pName;
    do{
        cout << "Enter your player name\n>>";
        getline(cin, pName);
    }while(pName == "");
    return pName;
}

string selectClass(){
    string pChar = " ";
    int x = -1;
    string y;
    do{
        cout << "Please select a class!\n";
        cout << "1. Bard\n";
        cout << "2. Mage\n";
        cout << "3. Gladiator\n";
        cout << "4. Sorcerer\n";
        cout << "5. Healer\n>>";

        getline(cin, y);

        //input validation
        if(y.length() == 1){
        try{
            x = y[0] - '0'; //this line converts the string char to an int, and uses it
        }catch(int e){}
        }
        //if the conversion fails, it uses the initialized value for x, -1.

        switch(x){
            case 1:
                pChar = "Bard";
                break;
            case 2:
                pChar = "Mage";
                break;
            case 3:
                pChar = "Gladiator";
                break;
            case 4:
                pChar = "Sorcerer";
                break;
            case 5:
                pChar = "Healer";
                break;
            default:
                cout << "ERROR: Invalid selection made. Please select 1 - 5\n";
        }
    }while(pChar == " ");

    return pChar;
}

Player createNewPlayer(){
    string pName = selectName();

    cout << "Welcome, " << pName << ".\n";

    string pClass = selectClass();

    cout << "Creating your new character...!";
    Player player(pName, pClass);
    return player;
}

Player loadPlayerFromSave(){
    ifstream myLoad("player.dat");
    string stats[7] = {""};
    int i = 0;
    string line;
    while(getline(myLoad, line)){
        stats[i] = line;
        i++;
    }
    myLoad.close();

    //Parse the data, get the data by themselves
    int pos;
    for(int i = 0; i < 7; i++){
        pos = (stats[i].find("=") + 1);
        stats[i] = stats[i].substr(pos);
    }

    int intStats[7] = {0};
    for(int i=2;i<7;i++){
        intStats[i] = atoi(stats[i].c_str()); //for some reason atoi(intStats[MAXHEALTH].c_str()) does not work in the Player Cons()call
                                              //so manually do an array here
    }

    //Create new player with loaded stats from file then return player
    //string name = stats[NAME];
    //string classs = stats[CLASS];
    Player player(stats[NAME],stats[CLASS],intStats[MAXHEALTH],intStats[HEALTH],intStats[MAXMANA],intStats[MANA],intStats[LEVEL]);
    return player;

}

void commandHelp(){
    cout << "\n-------AVAILABLE COMMANDS-------";
    cout << "\n-- help - inv --- look - quit --";
    cout << "\n--- pickup --- drop --- move ---";
    cout << "\n------save---stats---talk-------";
    cout << "\n--------------------------------";
}
