#include "Item.h"
#include <string>
using std::string;

Item::Item(string name):m_Name(name){}

string Item::GetName(){
    return m_Name;
}
