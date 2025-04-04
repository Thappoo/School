#include <iostream>
#include <algorithm>

using namespace std;

//orignal fib
int fib(int x, int &step){
    if(x == 0){
        step++;
        return 0;
    }
    else if(x == 1){
        step++;
        return 1;
    }
    else{
        step++;
        return fib(x-1, step) + fib(x - 2, step);
    }
}

int fib2(int x, int* t, int &step){
    if(x == 0){
        t[x] = 0;
        step++;
        return 0;
    }
    else if(x == 1){
        t[x] = 1;
        step++;
        return 1;
    }
    else{
        int a,b;
        a = (t[x-1]!=-1) ? t[x-1] : fib2(x-1,t,step);
        b = (t[x-2]!=-1) ? t[x-2] : fib2(x-2,t,step);
        t[x] = a + b;
        step++;
        return t[x];    
    }
}

int main(){
    int step, n = 12;
    for(int v = 0; v < n; v++){
        step = 0;
        cout << "F1:" << v << ":"
            << fib(v, step);
        cout << " with " << step << " steps "<< endl;
        
        int* table = new int[n];
        for(int i = 0; i < n; i++){
            table[i] = -1;
        }
        step = 0;
        cout << "F2:" << v << ":" 
            << fib2(v, table, step);
        cout << " with " << step << " step " << endl;

        delete[] table;
    }

    return 0;
}