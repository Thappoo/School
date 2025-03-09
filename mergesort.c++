#include <iostream>
#include <vector>

using namespace std;

void merge(int array[], int l, int m, int r){
    int i = l;
    int j = m + 1;
    int k = l;

    int size = r;
    int temp[size];

    while(i <= m && j <= r){
        if(array[i] <= array[j]){
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
    while(i<=m){
        temp[k] = array[i];
        i++;
        k++;
    }
    while(j<=r){
        temp[k] = array[j];
        j++;
        k++;
    }
    for(int s = l; s <= r; s++){
        array[s] = temp[s];
    }
}

void mergeSort(int array[], int l, int r){
    if(l < r){
        int m = (l + r) /2;
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
        merge(array, l, m, r);
    }
    
}

int main(){
    int size;
    cout << "Enter Array Size: ";
    cin >> size;
    
    cout << "Enter " << size << " elements in the array: " << endl;
    int  myarr[size];
    for(int i = 0; i < size; i++){
        cin >> myarr[i];
    }
    cout << "Before Merge Sort: " << endl;
    for(int i = 0; i < size; i++){
        cout << myarr[i] <<" ";
    }

    mergeSort(myarr, 0, (size-1));
    cout<< endl << "After Merge Sort: " << endl;
    for(int i = 0; i < size; i++){
        cout<< myarr[i] << " ";
    }

    return 0;
}