#ifndef _GRAPH_H_
#define _GRAPH_H_

//Must add -fpermissive to build options -> compiler setings -> other settings
#include <vector>
#include <stack>
#include <string.h>

using namespace std;

template<typename T>
class GraphVertex{
    public:
        GraphVertex(T node) : m_node(node) {}
        T GetNode(){ return m_node; }
    private:
        T m_node;
};

template<typename T>
class Graph{
    public:
        Graph(int numVerts) : m_maxVerts(numVerts), m_adjMatrix(NULL){
            m_vertices.reserve(m_maxVerts);
            m_adjMatrix = new char*[m_maxVerts];

            for(int i = 0; i < m_maxVerts; i++){
                m_adjMatrix[i] = new char[m_maxVerts];
                memset(m_adjMatrix[i], 0, m_maxVerts);
            }
        }

        ~Graph(){
            if(m_adjMatrix != NULL){
                for(int i = 0; i < m_maxVerts; i++){

                    if(m_adjMatrix[i] != NULL){
                        delete[] m_adjMatrix[i];
                        m_adjMatrix[i] = NULL;
                    }
                }

                delete[] m_adjMatrix;
                m_adjMatrix = NULL;
            }
        }

        bool push(T node){
            if((int)m_vertices.size() >= m_maxVerts){
                return false;
            }

            m_vertices.push_back(GraphVertex<T>(node));
            return true;
        }

        void attachEdge(int index1, int index2){
            m_adjMatrix[index1][index2] = 1;
            m_adjMatrix[index2][index1] = 1;
        }

        bool isAttached(int index1, int index2){
            return (m_adjMatrix[index1][index2] == 1);
        }

    private:
        vector<GraphVertex<T> > m_vertices;
        int m_maxVerts;

        char **m_adjMatrix;
};
#endif // _GRAPH_H_
