#include<iostream>
#include<chrono>
using namespace std;

void merge(int array[], int l, int m, int r){
    int i = l;
    int j = m+1;
    int k = l;
     
    int size = r;
    int temp[size];

    while(i <= m && j <= r){
        if(array[i] < array[j]){
            temp[k] = array[i];
            i++;
            k++;
        }
        else{
            temp[k] = array[j];
            j++;
            k++;
        }
    }
    while(i <= m){
        temp[k] = array[i];
        i++;
        k++;
    }
    while(j <= r){
        temp[k] = array[j];
        j++;
        k++;
    }
    for(int s = l; s <= r; s++){
        array[s] = temp[s];
    }
}

void mergeSort(int array[], int l, int r){
    
    if(l<r){
        int m = (l+r) /2;
        mergeSort(array, l, m);
        mergeSort(array, m+1, r);
        merge(array, l, m , r);
    }
}

int main(){

    int array1[4] = {2, 4, 0, 1};
    int array2[4] = {9, 3, 6, 5};

    merge()
    int size;
    cout << "Enter size";
    cin >> size;

    int myarray[size];
    cout << "Enter 4 numbers" << endl;
    for(int i = 0; i < size; i++){
        cin >> myarray[i];
    }

    for(int i = 0; i < size; i++){
        cout << myarray[i] << " ";
    }
    mergeSort(myarray, 0, (size-1));
    for(int i =0; i < size; i++){
        cout << myarray[i];
    }

    return 0;
}