#include <Node.h>
#include <string>

Node::Node(string obj) : m_object(obj), m_next(NULL), m_prev(NULL), m_child(NULL){
    //cout << "Node Created~~!" << endl;
    int depth = 0;

    for(int i = 0; i < m_object.length();i++){
        if(m_object[i] == '*'){
            depth++;
        }
    }

    m_object = m_object.substr(depth);
    m_depth = depth;
}

Node::~Node(){
    m_prev = NULL;
    if(m_child != NULL){
        delete m_child;
    }
    if(m_next != NULL){
        delete m_next;
    }
    m_child = NULL;
    m_next = NULL;
    cout << "Node deleted~~!" << endl;
}

void Node::AddChild(Node *node){
    //if no children, create one. Otherwise, add a sibling.
    if(m_child == NULL){
        m_child = node;
    }else{
        m_child->AddSibling(node);
    }
}

void Node::AddSibling(Node *node){
    Node *ptr = m_next;

    if(m_next == NULL){
        m_next = node;
        node->m_prev = this;
    }else{
        while(ptr->m_next != NULL){
            ptr = ptr->m_next;
        }

        ptr->m_next = node;
        node->m_prev = ptr;
    }
}

void Node::DisplayTree(){
    cout << m_object;

    if(m_next != NULL){
        cout << "  or  ";
        m_next->DisplayTree();
    }

    if(m_child != NULL){
        cout << endl;
        m_child->DisplayTree();
    }
}

Node* Node::ReturnNextSibling(){
    return m_next;
}

Node* Node::ReturnChild(){
    return m_child;
}

bool Node::HasChild(){
    return (m_child != NULL);
}

int Node::ShowSiblings(int x){
    x++;
    cout << x << ". " << this->ReturnString() << "\n";
    if(m_next != NULL){
        x = m_next->ShowSiblings(x);
    }
    return x;
}

string Node::ReturnString(){
    return m_object;
}

bool Node::Search(string value){
    if(m_object.find(value)){
        return true;
    }

    if(m_child != NULL){
        if(m_child->Search(value)){
            return true;
        }
    }

    if(m_next != NULL){
        if(m_next->Search(value)){
            return true;
        }
    }

    return false;
}
