#include <iostream>
#include <algorithm>

using namespace std;

class Array{
    private:
        int* arr;
        int arrSize;
    
    public: 
        //constuructor
        Array(){
            arr = nullptr;
            arrSize = 0;
        }

        //constuctor by specifying
        Array(int array[], int size){
            arr = array;
            arrSize = size;
        }

        void insertFront(int array[], int arraySize, int newValue){
            //insert front
            for(int i = arraySize -1; i >= 0; i--){
                array[i+1] = array[i];
            }
            array[0] = newValue;
        }

        void insertBack(int array[], int arraySize){

        }
        
       
        
        ~Array(){
            delete[] arr;
        }



};
    


int main(){

    int arr[] = {2,6,3,9};
    int New = 1;
    Array array1(arr, 4);
    
    cout << "hello";

    return 0;
}