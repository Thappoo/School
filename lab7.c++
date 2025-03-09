#include <iostream>

using namespace std;


class MyHashTable{
    public:
        MyHashTable() : n(0), m(0), type(0){}

        MyHashTable(int n1, int m1, int type1){
            n = n1;
            m = m1;
            type = type1;
            ht = new MyType[n];
            
        }


    private:
        int HashFunction(MyType x);
        int n;
        int m;
        Mytype* ht;
        bool* htd;
        int type;



};


int main(){

    return 0;
}