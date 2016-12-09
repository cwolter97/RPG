#include "NPC.h"
#include "Node.h"
#include "Room.h"
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
string tolower(string& c){for(int i=0;i<c.length();i++){c[i]=tolower(c[i]);}return c;}

NPC::NPC(string name) : m_Name(name){}

string NPC::GetName(){
    return m_Name;
}

void NPC::LoadDialogue(string NPC_Name){
    ifstream diaFile("dialogue.txt");
    string line;
    bool found_npc_dialogue = false;
    string End_of_Dialogue = "newdialogue";

    m_RawDialogue.clear();

    if(diaFile.is_open()){
        while(getline(diaFile, line)){
            if((line == End_of_Dialogue) && found_npc_dialogue){
                return;
            }

            if(found_npc_dialogue){
                m_RawDialogue.push_back(line);
            }

            if(line == tolower(NPC_Name)){
                found_npc_dialogue = true;
            }
        }
    }else {cout<<"Couldn't open dialogue file...";}
}

void NPC::DialogueTree(){
    //std::vector<string>::iterator roottext = m_RawDialogue.begin();

    int arraysize = m_RawDialogue.size();

    Node *nodeArray[arraysize];


    int i = 0;
    for(std::vector<string>::iterator iter = m_RawDialogue.begin(); iter != m_RawDialogue.end(); iter++){
        nodeArray[i] = new Node(*iter);
        i++;
    }

    //starts at the children of the parent node
    for(int i = 1; i < arraysize; i++){
        int prev_node = i-1;
        int current_node = i;

        bool child_created = false;

        //loop to make sure every node is placed on the tree
        while(!child_created){
            int current_depth = nodeArray[current_node]->m_depth;
            int prev_depth = nodeArray[prev_node]->m_depth;

            if(current_depth > prev_depth){
                nodeArray[prev_node]->AddChild(nodeArray[current_node]);
                child_created = true;
            }else if(current_depth == prev_depth){
                nodeArray[prev_node]->AddSibling(nodeArray[current_node]);
                child_created = true;
            }else{
                prev_node--;
            }
        }
    }


    Node *current_node = nodeArray[0];

    bool ActionAvailable = false;

    do{
        //says NPC line
        cout << endl << current_node->ReturnString() << endl;
        if(!(current_node->HasChild())){
            ActionAvailable = true;
            continue;
        }
        //shows responses that can be given
        int actions = current_node->ReturnChild()->ShowSiblings();
        bool valid = false;

        string chatResponse;
        int response = -1;

        //input validation
        do{
            cout << "\nResponse: ";
            getline(cin, chatResponse);

            //input validation
            if(chatResponse.length() == 1){
            try{
                response = chatResponse[0] - '0'; //this line converts the string char to an int, and uses it
                if(response <= actions && response > 0){
                    valid = true;
                }
                if(isalpha(chatResponse[0])){ valid = false;}
            }catch(int e){}
            }
            //if the conversion fails, it uses the initialized value for x, -1.

        }while(!valid);

        //moves to responses
        current_node = current_node->ReturnChild();

        //selects user selected response
        for(int i = response - 1; i > 0; i--){
            current_node = current_node->ReturnNextSibling();
        }

        //Moves to next NPC chat/action
        current_node = current_node->ReturnChild();

        //tests to see if chat is done
        string teststring = current_node->ReturnString();
        if(teststring.find("ACTION") != string::npos){
            ActionAvailable = true;
        }

    }while(!ActionAvailable);

    string actionString = current_node->ReturnString();

    if(actionString.find("CLOSECHAT") != string::npos){
        return;
    }

}

void NPC::Talk(){
    this->LoadDialogue(m_Name);
    this->DialogueTree();
}

bool NPC::DropItemFromInv(string ItemName){
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

void NPC::AddItemToInv(Item ItemName){
    m_Inventory.push_back(ItemName);
}
