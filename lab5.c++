#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <random>

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


void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSort(int arr[], int size) {
    mergeSort(arr, 0, size - 1);
}


int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[++i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSort(int arr[], int size) {
    quickSort(arr, 0, size - 1);
}


void shuffleByPercent(int array[], int size, double percent) {
    int shuffleNumber = static_cast<int>(size * percent);
    random_device rd;
    mt19937 rng(rd());
    for (int i = 0; i < shuffleNumber; ++i) {
        uniform_int_distribution<int> dist(i, size - 1);
        int randomIndex = dist(rng);
        swap(array[i], array[randomIndex]);
    }
}
void display(const int array[], int size = 100) {
    for (int i = 0; i < size; ++i) {
        cout << array[i] << "\t";
        if ((i + 1) % 10 == 0) {
            cout << endl;
        }
    }
}
void runSort(const string& sortName, void (*sortFunc)(int[], int), int array[], int size, const string& caseName) {
    int* arrayCopy = new int[size];

    copy(array, array + size, arrayCopy);
    cout << sortName << " - " << caseName << ", size: " << size << endl;
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arrayCopy, size);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Time taken: " << elapsed.count() * 1000 << " milliseconds" << endl;
    display(arrayCopy);
    cout << endl;

    delete[] arrayCopy;
}

void setupAndRunAllCases(int size) {
    int* randomArray = new int[size]; 
    int* sortedArray = new int[size];
    int* ninetyPercentSortedArray = new int[size]; 
    int* halfSortedArray = new int[size]; 
    
    srand(time(0));
    for (int i = 0; i < size; ++i) {
        randomArray[i] = rand() % size;
        sortedArray[i] = i;
        ninetyPercentSortedArray[i] = i;
        halfSortedArray[i] = i;
    }
    shuffleByPercent(ninetyPercentSortedArray, size, 0.1); //shuffle case 3
    shuffleByPercent(halfSortedArray, size, 0.5); //shuffle case 4
   
    runSort("Merge Sort", mergeSort, randomArray, size, "Random values");
    runSort("Merge Sort", mergeSort, sortedArray, size, "Sorted values");
    runSort("Merge Sort", mergeSort, ninetyPercentSortedArray, size, "90%sorted values");
    runSort("Merge Sort", mergeSort, halfSortedArray, size, "50% sortedvalues");
    runSort("Quick Sort", quickSort, randomArray, size, "Random values");
    runSort("Quick Sort", quickSort, sortedArray, size, "Sorted values");
    runSort("Quick Sort", quickSort, ninetyPercentSortedArray, size, "90%sorted values");
    runSort("quick Sort", quickSort, halfSortedArray, size, "50% sortedvalues");
    
    delete[] randomArray;
    delete[] sortedArray;
    delete[] ninetyPercentSortedArray;
    delete[] halfSortedArray;
}

int main() {
    const int sizes[] = {100, 1000, 10000, 100000};

    for (int size : sizes) {
        setupAndRunAllCases(size);
    }
    return 0;
}