#include <iostream>

using namespace std;


void f(int* a, int low, int high, int y){  //adding all 下 = O(n+2)
    int m = low - high;
    int s = 0; //O(1)  
    for(int i = 0; i < m; i++){ //O(n) 
        s += i;
        cout << s << endl; //O(1) 
        
    }
    int mid = low + high /2;
    if(low < high){
        f(a, low, mid, y*2);
        f(a, mid, high, y*2); 
        //having 2 of these calls gives us log2
        //callによってlog number changes

    }
}

//theroem 3

void f(int* a , int low, int high){
    int p =1; 
    int m = high - low +1;
    //f(m)
    for(int i = 0; i < m;i++){
        for(int j; j < m/2; j++){ //このforloop = O(n^2)
            p = i *j;
        }
    }
    if(low < high){
        f(a,low,high/2); //この = log_b^2 
        f(a,high/2,high); //log2
    }
}

int main(){



    return 0;
}