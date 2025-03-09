#include <iostream>
#include <vector>

using namespace std;


int main(){

    
    int arr[4] = {2, 9, 4, 0};
    cout << "Enter a number" << endl;
    int number;
    cin >> number;
    for(int i = 0; i < number; i++){
        for(int j = 0; j < i; j++){
            cout << "*";
        }
        cout << endl;
    }

    return 0;
}