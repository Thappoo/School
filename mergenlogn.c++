#include <iostream>

using namespace std;

void merge(int array1[], int size1, int array2[], int size2, int array3[]){

    int i = 0;
    int j = 0;
    int k = 0;
    int array3[9];

    while(i <= size1 && j <= size2){
        if(array1[i] <= array2[j]){
            array3[k] = array1[i];
            i++;
            k++;
        }else{
            array3[k] = array2[j];
            j++;
            k++;
        }
    }
    while(i <= size1){
        array3[k] = array1[i];
        i++;
        k++;
    }
    while(j <= size2){
        array3[k] = array2[j];
        j++;
        k++;
    }
    for(int i = 0; i < 0; i++){
        cout << array3[i];
    }
    
}

int main(){

    int arr1[4] = {4, 1, 9, 8};
    int arr2[5] = {2, 7, 5, 3, 6};

    int arr3[9];

    cout << "Array 1 and 2 before merge:"<< endl;
    for(int i = 0; i < 4; i++){
        cout << arr1[i] << " ";
    }
    for(int j = 0; j < 5; j++){
        cout << arr2[j] << " ";
    }
    cout << endl;

    merge(arr1, (4-1), arr2, (5-1), arr3);

    for(int i = 0; i < 9; i++){
        cout << arr3[i] << " ";
    }



    return 0;
}