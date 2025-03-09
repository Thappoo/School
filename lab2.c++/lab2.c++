#include <iostream>
#include <cmath>

using namespace std;


class Array3D{
    private:
        int ***array; //a lot of pointing
        int n, m, l; //dimensions

    public:

        // constructor
        Array3D(int n, int m, int l){
            this->n = n;
            this->m = m;
            this->l = l;

            array = new int**[n];
            for(int i = 0; i < n; i++){
                array[i] = new int*[m];
                for(int j = 0; j < m; j++){
                    array[i][j] = new int[l];
                }
                
            }

            for(int i = 0; i < n; i++){
                for(int j = 0; j <m; j++){
                    for(int k = 0; k < l;k++){
                        array[i][j][k] = 0;
                    }
                }
            }
        }

        ~Array3D(){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < m; j++){
                    delete[] array[i][j];
                }
                delete[] array[i];
            }
            delete[] array;
        }

        void setValue(int x, int y, int z, int value){
            if(x < n && y < m && z < l){
                array[x][y][z] = value;
            }else{
                cout << "Index out of bounds!" << endl;
            }
        }
        int getValue(int x, int y, int z){
            if (x < n && y < m && z < l) {
                return array[x][y][z];
            } else {
                cout << "Index out of bounds!" << endl;
                return -1; 
            }
        }
        void printArray() const {
        for (int i = 0; i < n; i++) {
            cout << "Layer " << i << ":\n";
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < l; k++) {
                    cout << array[i][j][k] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }

};


int iterative1(){
    int result = 0;
    for(int i = 0; i <= 100;i++){
        result += (2 * i + 9);
    }
    return result;
}

int iterative2(){
    int result = 0;
    for(int i = 1; i <= 100; i++){
        result += (5 * pow(i,3) + pow(i,2));
    }
    return result;
}

int iterative3(){
    int result = 0;
    for(int i = 0; i <= 500; i++){
        result += pow((5 * i), -1/2);
    }
    return result;
}

int recursive1(int n){
    if( n == 0){
        return 9;
    }
    else{
        return (2 * n + 9) + recursive1(n - 1);
    }
}

int recursive2(int n){
    if(n == 1){
        return 6;
    }
    else{
        return (5 * pow(n,3) + pow(n, 2)) + recursive2(n -1);
    }
}

int recursive3(int n){
    if(n == 0){
        return 1;
    }
    else{
        return pow((5 * n), -1/2) + recursive3(n-1);
    }
}

void Fib(int x, int* result){
    if(x == 0){
        *result = 0;
    }
    else if( x == 1){
        *result = 1;
    }
    else{
        int a =0;
        int b = 1;
        int f = 0;
        for(int i = 2; i <= x; i++){
            f = b + a;
            a = b;
            b = f;
        }
        *result = f;
    }
    
}

//Hanoi
void solve(int n, string start, string auxiliary, string end){
    if(n ==1){
        cout << start << " -> " << end << endl;
    }else{
        solve(n-1, start, end, auxiliary);
        cout << start << " -> " << end << endl;
        solve(n-1, auxiliary, start, end);
    }
}


int main(){

    //Part 0
    cout << "Part 0\n";
    Array3D myarr(2,3,4);

    myarr.setValue(1,2,3,42);
    myarr.printArray();

    //Part 1
    cout << endl;
    cout << "Part 1\n";
    cout << "f1 answer using iterative: " << iterative1() << endl;
    cout << "f2 answer using iterative: " << iterative2() << endl;
    cout << "f3 answer using iterative: " << iterative3() << endl;
    cout << "f1 answer using recursive: " << recursive1(100) << endl;
    cout << "f2 answer using revirsive: " << recursive2(100) << endl;
    cout << "f3 answer using recursive: " << recursive3(500) << endl;


    //Part 2
    cout << endl;
    cout << "Part 2\n";
    cout << "Big O and Big Omega of f1 is O(n^3) because the function"
            <<" will not grow faster than n^3 when n is large\n";
    cout << "The same thing applies for f2. Using the highest exponent" 
            << " as the upper we can tell that the function will cross n^3 when n is large.\n";

    //Part 3
    cout << endl;
    cout << "Part 3\n";
    int x = 8;
    int result;
    Fib(x, &result);
    cout <<"Fibonacci of " << x << " is "<< result << endl;

    //Part 4
    cout << endl;
    cout << "Part 4\n";
    int disks = 3;
    solve(disks, "0", "1", "2");

    return 0;
}