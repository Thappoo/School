#include <iostream>

using namespace std;

typedef int MyType;
class MyHashTable{
    public: 
        MyHashTable() : n(0), m(0), type(0){}

        MyHashTable(int n1, int m1, int type1){
            n = n1;
            m = m1;
            type = type1;
            ht = new MyType[n];
            htd = new bool[n];
            for(int i = 0; i < n; i++){
                ht[i] = -1;
                htd[i] = false;
            }
        }

        ~MyHashTable(){
            delete[] ht;
            delete[] htd;
        }

        void Delete(MyType x){
            pair<bool, int> r = SearchKey(x);
            if (r.second != -1){
                htd[r.second] = false;
            }
        }

        int HashFunction(MyType x) {
            return (int)x % m;
        }

        void Insert(MyType x){
            int key = HashFunction(x);
            if(htd[key]){
                int probe = key + 1;
                int step = 1;
                int k = 1;
                bool place = false;
                while((k < n) && (!place)){
                    if(!htd[probe]){
                        place = true;
                        ht[probe] = x;
                        htd[probe] = true;
                    }
                    else{
                        step++;
                        if(type == 0){
                            probe = key + step;
                        }
                        else{
                            probe = key + step*step;
                        }
                        probe = probe % m;
                    }
                    k++;
                }
            }else{
                ht[key] = x;
                htd[key] = true;
            }
        }

        bool Search(MyType x){
            int key = HashFunction(x);
            if(ht[key] == x){
                return true;
            }
            else{
                int probe = key + 1;
                int step = 1;
                int k = 1;
                while(k < n){
                    if((ht[probe] == x) && (htd[probe])){
                        return true;
                    }
                    else if(!htd[probe]){
                        return false;
                    }
                    else{
                        step++;
                        if(type == 0){
                            probe = key + step;
                        }
                        else{
                            probe = key + step*step;
                        }
                        probe = probe % m;
                    }
                    k++;
                }
                return false;
            }
        }

        pair<bool, int> SearchKey(MyType x){
            int key = HashFunction(x);
            if(ht[key] == x){
                return make_pair(true, key);
            }
            else{
                int probe = key + 1;
                int step = 1;
                int k = 1;
                while(k < n){
                    if((ht[probe] == x) && (htd[probe])){
                        return make_pair(true, probe);
                    }
                    else if(!htd[probe]){
                        return make_pair(false, -1);
                    }
                    else{
                        step++;
                        if(type == 0){
                            probe = key + step;
                        }
                        else{
                            probe = key + step*step;
                        }
                        probe = probe % m;
                    }
                    k++;
                }
                return make_pair(false, -1);
            }
        }

        void Display(){
            cout << "Hash Table of size " << n << endl;
            for(int i = 0; i < n; i++){
                cout << "Key: " << i << " with value: " << ht[i]
                    << "(" << htd[i] << ")" << endl;
            }
            cout << endl;
        }

    private:
        int n;
        int m;
        MyType* ht;
        bool* htd;
        int type;
};

int main(){
    MyHashTable* H = new MyHashTable(10, 10, 1);
    H->Insert(39);
    H->Insert(13);
    H->Insert(23);
    H->Insert(63);
    H->Insert(30);
    H->Insert(31);
    H->Insert(49);
    H->Delete(49);//
    H->Insert(59);
    H->Display();
    cout << "Search 39: " << H->Search(39) << endl;
    cout << "Search 49: " << H->Search(49) << endl;
    cout << "Search 59: " << H->Search(59) << endl;
    cout << "Search 23: " << H->Search(23) << endl;

    delete H;


    return 0;
}