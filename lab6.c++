#include <iostream>
#include <map>
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
        double data;

};
//hi 

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

        void InsertMid(NodeDC **head, NodeDC *prev, NodeDC **tail, int value){
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

        void uniqueValues(int arr[], int n) {
            set<int> seen;
            for (int i = 0; i < n; ++i) {
                if (seen.insert(arr[i]).second) {
                    InsertMid(&head, nullptr, &tail, arr[i]);
                }
            }
        }
        
        void countOccurrences(int arr[], int n){
            map<int, int> freq;
            for(int i = 0; i < n; i++){
                freq[arr[i]]++;
            }
            for(auto j = freq.begin(); j != freq.end(); ++j){
                InsertLast(j->second);
            }
        }

        void greaterThan(int arr[], int x){
            for(int i = 0; i < 6; i++){
                if(arr[i] > x){
                    InsertMiddle(arr[i]);
                }
            }
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

        NodeDC* getTail() {
            return tail;
        }
    
        void removeLast() {
            if (tail == nullptr) return;
    
            NodeDC* temp = tail;
            tail = tail->previous;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
            else {
                head = nullptr;
            }
            delete temp;
            n--;
        }

    private:
        NodeDC *head, *tail;
        int n;
};

typedef double MyType;
class MyStack{
    public:
        MyStack(){
            list = new MyClass();
            capacity = 0;
            size = 0;
        }

        MyStack(int capacity1){
            list = new MyClass();
            capacity = capacity1;
            size = 0;
        }

        ~MyStack(){
            delete list;
        }

        bool IsFull(){
            return (size == capacity);
        }

        bool IsEmpty(){
            return (size == 0);
        }

        MyType Pop(){
            if(!IsEmpty()){
                NodeDC* tail = list->getTail();
                MyType value = tail->data;
                list->removeLast();
                size--;
                return value;
            }
            throw out_of_range("Stack is empty");
        }

        MyType Top(){
            if (!IsEmpty()) {
                NodeDC* tail = list->getTail();
                return tail->data;
            }
            throw out_of_range("Stack is empty");
        }

        void Push(MyType x){
            if (size < capacity || capacity == 0) {
                list->InsertLast(static_cast<int>(x));
                size++;
            }
        }

        void Display(){
            list->Display();
        }

    private:
        MyClass* list;
        int capacity;
        int size;

};

int main(){
    MyClass* LD = new MyClass();
    MyClass* LD1 = new MyClass();
    MyClass* LD2 = new MyClass();
    MyClass* LD3 = new MyClass();

    //possibility 2 recursive function
    LD->InsertLast(10);
    LD->InsertLast(1);
    LD->InsertLast(6);
    LD->InsertLast(4);
    LD->Display();

    //problem 1
    int a[7] = {0,1,0,2,3,0,1};
    int n = sizeof(a) / sizeof(a[0]);
    LD1->uniqueValues(a, n);
    LD1->Display();

    //problem 2
    LD2->countOccurrences(a, n);
    LD2->Display();

    //problem 3
    int a2[6] = {4,8,1,3,9,6};
    int x = 5;
    LD3->greaterThan(a2, x);
    LD3->Display();

    //problem 4
    MyStack* s = new MyStack(5);
    s->Push(10);
    s->Push(20);
    s->Push(30);
    s->Push(40);
    s->Display();

    cout << "Top element: " << s->Top() << endl;
    cout << "Popped element: " << s->Pop() << endl;
    s->Display();

    return 0;
}