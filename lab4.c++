#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

void selectionSort(int array[], int n){
    for(int i = 0; i < n - 1; i++){
        int min = i;
        for(int j = i + 1; j < n; j++){
            if(array[j] < array[min]){
                min = j;
            }
        }
        if(min != i){
            swap(array[i], array[min]);
        }
    }
}
void insertionSort(int array[], int n){
    for(int i = 1; i < n;i++){
        int key = array[i];
        int j = i - 1;
        while(j >= 0 && array[j] > key){
            array[j+1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

void bubbleSort(int array[], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(array[j] > array[j  + 1]){
                swap(array[j], array[j+1]);
            }
        }
    }
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
   
    runSort("Selection Sort", selectionSort, randomArray, size, "Random values");
    runSort("Selection Sort", selectionSort, sortedArray, size, "Sorted values");
    runSort("Selection Sort", selectionSort, ninetyPercentSortedArray, size, "90%sorted values");
    runSort("Selection Sort", selectionSort, halfSortedArray, size, "50% sortedvalues");
    runSort("Insertion Sort", insertionSort, randomArray, size, "Random values");
    runSort("Insertion Sort", insertionSort, sortedArray, size, "Sorted values");
    runSort("Insertion Sort", insertionSort, ninetyPercentSortedArray, size, "90%sorted values");
    runSort("Insertion Sort", insertionSort, halfSortedArray, size, "50% sortedvalues");
    runSort("Bubble Sort", bubbleSort, randomArray, size, "Random values");
    runSort("Bubble Sort", bubbleSort, sortedArray, size, "Sorted values");
    runSort("Bubble Sort", bubbleSort, ninetyPercentSortedArray, size, "90% sortedvalues");
    runSort("Bubble Sort", bubbleSort, halfSortedArray, size, "50% sorted values");

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