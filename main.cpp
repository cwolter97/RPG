#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "Player.h"
#include "Room.h"

using namespace std;

string selectName();
string selectClass();
Player createNewPlayer();
Player loadPlayerFromSave();
void commandHelp();

enum STATS {NAME, CLASS, MAXHEALTH, HEALTH, MAXMANA, MANA, LEVEL};

//overloads the tolower() function to return strings in all lowercase / created compact because not important to game
string tolower(string c){for(int i=0;i<c.length();i++){c[i]=tolower(c[i]);}return c;}

int main()
{
    string pCommand;
    Player* pPlayer = 0; //pointers used for current player and room
    Room* pCurrentRoom = 0;
    Player player;
    //character creation
    cout << "Super Awesome Coolio Fun RPG Game Thingy!\n\n";

    //create player, then create pointer to player (useful for later with multiple players)

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

    //pointer to current room so main game loop doesn't have to test for several rooms
    Room room1("Room 1");
    pCurrentRoom = &room1;

    //main game loop
    do{
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
        if(pCommand=="move"){
            //pCurrentRoom->ShowExits();
            //take input N S E W
            //find &nextRoom;
            //pCurrentRoom = &nextRoom ?
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