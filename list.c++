#include <iostream>
#include <set>

using namespace std;

class NodeDC{
    public:
        NodeDC():
            data(0), next(nullptr), previous(nullptr){}
        NodeDC(int d):
            data(d), next(nullptr), previous(nullptr){}
        NodeDC(int d, NodeDC* nxt, NodeDC* prv):
            data(d), next(nxt), previous(prv){}
        ~NodeDC(){}
        NodeDC *next;
        NodeDC *previous;
        int data;

};

class MyClass{
    public:
        MyClass(){
            head = nullptr;
            tail = nullptr;
            n = 0;
        }
        ~MyClass(){
            NodeDC *current = head;
            while(current){
                NodeDC *next = current->next;
                delete current;
                current = next;
            }
        }

        void InsertHead(int value){
            NodeDC *temp = new NodeDC(value, head, nullptr);
            if(head == nullptr){
                head = temp;
                tail = temp;
            }
        }

        void InsertMid(NodeDC **head, NodeDC *prev, NodeDC ** tail, int value){
            if((*head) == nullptr){
                NodeDC *temp = new NodeDC(value, nullptr, prev);
                *head = temp;
                *tail = temp;
            }else if((*head)->data > value){
                NodeDC *temp = new NodeDC(value);
                (*head)->previous = temp;
                temp->next = (*head);
                (*head) = temp;
                if(prev != nullptr){
                    temp->previous = prev;
                    prev->next = temp;
                }
            }
            else
                InsertMid(&(*head)->next, (*head), tail, value);
        }

        void InsertMiddle(int value){
            InsertMid(&head, nullptr, &tail, value);
            n++;
        }

        void InsertLast(int value){
            NodeDC *temp = new NodeDC(value);
            if(head == nullptr){
                head = temp;
                tail = temp;
            }else{
                tail->next = temp;
                temp->previous = tail;
                tail = temp;
            }
            n++;
        }

        
        void countUnique(int arr[], int size){
            set<int> seen;
            int count = 0;
            for(int i = 0; i < size; ++i){
                if(seen.find(arr[i]) == seen.end()){
                    seen.insert(arr[i]);
                    count++;
                }
            }
            cout << count;
        }

        void Display(){
            NodeDC *temp = new NodeDC;
            temp = head;
            while(temp != nullptr){
                cout << temp->data << "->";
                temp = temp->next;
            }
            cout << "NULL" << endl;
        }

    private:
        NodeDC *head, *tail;
        int n;
};


int main(){
    MyClass* LD1 = new MyClass();
    MyClass* LD2 = new MyClass();
    MyClass* LD3 = new MyClass();


    //problem 1
    int a[7] = {0,1,0,2,3,0,1};
    for(int i = 0; i < 7; i++){
        LD1->InsertLast(a[i]);
    }

    LD1->Display();
    

    //problem 2


    //problem 3
    int a2[6] = {4,8,1,3,9,6};
    int x = 5;
    for(int i = 0; i < 6; i++){
        if(a2[i] > x){
            LD3->InsertMiddle(a2[i]);
        }
    }
    LD3->Display();


    return 0;
}