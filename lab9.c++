#include <iostream>
#include <climits>

using namespace std;

enum class ColorNode{
    Visited, Unvisited, Finished
};

typedef double MyType;
class MyQueue{
    public:
        ~MyQueue(){
            delete [] q;
        }

        MyQueue(int capacity1){
            capacity = capacity1;
            front = size = 0;
            rear = 0;
            q = new MyType[capacity];
        }

        bool IsFull(){
            return (size == capacity);
        }

        bool IsEmpty(){
            return (size == 0);
        }

        void Enqueue(MyType x){
            if(!IsFull()){
                q[rear] = x;
                rear = (rear + 1) % capacity;
                size = size + 1;
            }else{
                cout << " Queue is full" << endl;
            }
        }

        MyType Dequeue(){
            if(IsEmpty()){
                return INT_MIN;
            }
            MyType item = q[front];
            front = (front + 1) % capacity;
            size = size - 1;
            return item;
        
        }

    private:
        int front, rear, size;
        int capacity;
        MyType* q;
};

class NodeGAL{
    public:
        NodeGAL():v(0), weight(0), next(nullptr){}
        NodeGAL(int v1, double weight1): v(v1), weight(weight1), next(nullptr){}
        ~NodeGAL(){}

        int v; //vertec index
        double weight; //weight of edge to reach v
        NodeGAL *next;
};

class MyAL{
    public:
        MyAL(){
            int n = 0;
            l = nullptr;
            current = nullptr;
            degree = nullptr;
        }

        MyAL(int n1){
            n = n1;
            l = new NodeGAL*[n];
            current = new NodeGAL*[n];
            degree = new int[n];
            for(int u = 0; u < n; u++){
                l[u]= nullptr;
                current[u] = nullptr;
                degree[u] = 0;
            }
        }

        ~MyAL(){
            for(int i = 0; i < n; i++){
                NodeGAL *current = l[i];
                while(current){
                    NodeGAL* next = current->next;
                    delete current;
                    current = next;
                }
            }
            delete[] l;
            delete[] current;
            delete[] degree;
        }

        int GetNumberVertices(){ return n;}
        int GetDegree(int u){return degree[u];}

        bool ExistEdge(int u, int v){
            if(u < n){
                NodeGAL* cursor = l[u];
                while(cursor != nullptr){
                    if(cursor ->v == v){
                        return true;
                    }else{
                        cursor = cursor->next;
                    }
                }
                return false;
            }else{
                return false;
            }
        }

        double GetEdgeWeight(int u, int v){
            if(u < n){
                NodeGAL* cursor = l[u];
                while(cursor != nullptr){
                    if(cursor->v == v){
                        return cursor->weight;
                    }else{
                        cursor = cursor->next;
                    }
                }
                return 0;
            }else{
                return 0;
            }
        }
        void SetDirectedEdge(int u, int v, double w){
            if(!ExistEdge(u,v)){
                NodeGAL* tmp = new NodeGAL(v,w);
                tmp->next = l[u];
                l[u] = tmp;
                degree[u]++;
            }
        }

        void SetDirectedEdge(int u, int v){
            SetDirectedEdge(u,v,1);
        }

        void SetUndirectedEdge(int u, int v, double w){
            SetDirectedEdge(u,v,w);
            SetDirectedEdge(v,u,w);
        }

        void SetUndirectedEdge(int u, int v){
            SetDirectedEdge(u,v,1);
            SetDirectedEdge(v,u,1);
        }
        void RemoveDirectedEdge(int u, int v){
            NodeGAL* cursor = l[u];
            if(cursor!=nullptr){
                if(cursor->v == v){
                    l[u] = cursor->next;
                    delete cursor;
                }else{
                    if(cursor->next != nullptr){
                        NodeGAL* prev = cursor;
                        cursor = cursor->next;
                        bool found = false;
                        while((cursor != nullptr) && (!found)){
                            if(cursor->v == v){
                                prev->next = cursor->next;
                                delete cursor;
                                found = true;
                            }else{
                                prev = cursor;
                                cursor = cursor->next;
                            }
                        }
                    }
                }
            }
            degree[u]--;
        }
        void RemoveUndirectedEdge(int u, int v){
            RemoveDirectedEdge(u,v);
            RemoveDirectedEdge(v,u);
        }

        bool HasSelfLoops(){
            int u = 0;
            while(u < n){
                if(GetEdgeWeight(u,u) != 0){
                    return true;
                }
                u++;
            }
            return false;
        }

        bool IsUndirected(){
            int v, u = 0;
            while(u < n){
                v = u;
                while(v < n){
                    if(GetEdgeWeight(u,v) != GetEdgeWeight(v,u)){
                        return false;
                    }
                    v++;
                }
                u++;
            }
            return !HasSelfLoops();
        }

        bool ExistAdjacent(int u){
            return current[u] != nullptr;
        }

        void SetCurrentVertex(int u){
            current[u] = l[u];
        }

        int GetNextAdjacent(int u){
            int v = current[u]->v;
            current[u] = current[u]->next;
            return v;
        }

        void BFS1(int s, MyAL* G, ColorNode* &color, int* &distance, int* &pi){
            int m = G->GetNumberVertices();
            if(!((s >= 0) && (s < n))){
                cout << "Bad source!" << endl;
            }else{
                MyQueue* Q = new MyQueue(n);
                color = new ColorNode[n];
                distance = new int[n];
                pi = new int[n];
                for(int u = 0; u < n;u++){
                    color[u] = ColorNode::Unvisited;
                    distance[u] = 0;
                    pi[u] = 0;
                }
                color[s] = ColorNode::Visited;
                distance[s] = 0;
                pi[s] = -1;
                Q->Enqueue(s);
                while(!Q->IsEmpty()){
                    int u = Q->Dequeue();
                    for(int v = 0; v < n;v++){
                        if(G->ExistEdge(u,v)){
                            if(color[v] == ColorNode::Unvisited){
                                color[v] = ColorNode::Visited;
                                distance[v] = distance[u] + 1;
                                pi[v] = u;
                                Q->Enqueue(v);
                            }
                        }
                    }
                    color[u] = ColorNode::Finished;
                }
                delete Q;
            }
        }

        void BFS(int s){
            cout << "BFS" << endl;
            ColorNode *color;
            int *distance, *pi;
            BFS1(s,this, color, distance, pi);
            for(int u = 0; u < n; u++){
                cout << "from " << s << " to " << u
                    << " Distance=" << distance[u]
                    << " Pi=" << pi[u] << endl;
            }
            delete[] color;
            delete[] distance;
            delete[] pi;
            
        }
        
        void Display(){
            for(int u = 0; u < n; u++){
                cout << u << ":";
                NodeGAL* cursor = l[u];
                while(cursor != nullptr){
                    cout << cursor->v << "(" << cursor->weight << ") ";
                    cursor = cursor->next;
                }
                cout << endl;
            }
        }


    private:
        int n; //number of vertices
        NodeGAL** l; //array of list
        NodeGAL** current; //iterators
        int* degree; //degree for each vertex
};

int main(){

    int n = 5;
    MyAL* G = new MyAL(n);

    G->SetUndirectedEdge(0,1);
    G->SetUndirectedEdge(1,2);
    G->SetUndirectedEdge(2,3);
    G->SetUndirectedEdge(3,0);
    G->SetUndirectedEdge(0,4);
    G->SetUndirectedEdge(1,4);
    G->Display();
    G->BFS(0);

    delete G;
    return 0;
}