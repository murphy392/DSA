#include <stdio.h>

//Function declerations go here. 
    //Are these the declerations I want? I think I need to change the signature
int partition (int array[], int low, int high);
void sort(int array[], int low, int high);

int main(void){
    /*
        Faster sorting algorithm that utilizes recursion 
        Works the same by taking the last element of an array and using it as a pivot element ( or any element as the pivot element)
        Does the same operatuion with recursion on the sub-arrays to the left and right side of the pivot element until sorted

        How it works:
        1. Choose a value in the array to be the pivot element.
        2. Order the rest of the array so that lower values than the pivot element are on the left, and higher values are on the right.
        3. Swap the pivot element with the first element of the higher values so that the 
            pivot element lands in between the lower and higher values.
        4. Do the same operations (recursively) for the sub-arrays on the left and right side of the pivot element.

        Time Complexity: 
        worst case scenario = O(n^2) | this is ONLY if the array is already sorted
        average case scenario = O(n log of n)
    */

    int array[] = {100, 35, 2, 87, 12, 99, 56, 23, 78, 45};
    // int array[] = {100, 35, 2, 87, 12, 99, 56, 23, 78, 45, 1000, 393, 1093, 1849, 23, 192819, 193, 1827, 19, 10934, 2840};
    int n = sizeof(array) / sizeof(array[0]);

    printf("Original Array: ");
    for (int p = 0; p < n; p++){
        printf("%d ", array[p]);
    }
    printf("\n\n"); // add three new lines

    // start the sorting by passing in your array, low value = 0, high value is length - 1
    sort(array, 0, n - 1);
    printf("Sorted Array: ");
    for (int i = 0; i < n; i++){
        printf("%d ", array[i]);
    }

    return 0;
}

void sort(int array[], int low, int high){
    if (low < high){
        // find the pivot by partitioning the array
        int pivot = partition(array, low, high);
        //how many times would I need to call this for a larger array? 
        //20 value array only called twice. 
        sort(array, low, pivot -1);
        sort(array, pivot + 1, high);
    }
}

int partition (int array[], int low, int high) {
    //set pivot to the high value of the array. array[high] = array[length - 1]
    int pivot = array[high];
    int i = low - 1;
    //j = -1, while j < 9 ( length - 1); increment j by 1
    for (int j = low; j < high; j++){
        if (array[j] <= pivot){
            i++;
            //set temp to the value at array[i] | First iteration is array[0]
            int temp = array[i];
            //set array[i] to the value of array[j] | first iteration array[0] = array[0] ( just happened to be the same )
            array[i] = array[j];
            //set array[j] to the temp value 
            array[j] = temp;
        }
    }

    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;

    return i + 1; 
}
