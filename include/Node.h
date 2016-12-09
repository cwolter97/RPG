#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node{
    public:
        Node(string obj);
        ~Node();

        void AddChild(Node *node);
        bool HasChild();
        void AddSibling(Node *node);
        void DisplayTree();
        string ReturnString();
        Node* ReturnChild();
        Node* ReturnNextSibling();
        int ShowSiblings(int x = 0);
        bool Search(string value);
        int m_depth;

    private:
        string m_object;
        Node *m_next, *m_prev, *m_child;
};

#endif //NODE_H
