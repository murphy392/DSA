#include <stdio.h>

int main(void) {
    /*
    Insertion sort sorts an array by building up a sorted portion of the array
    starts with the first element as the sorted portion
    takes the next element and inserts it into the correct position in the sorted portion
    continues until the array is sorted

    1. Take the first value from the unsorted part of the array 
    2. Move the value into the correct place in the sorted part of the array 
    3. Go through the unsorted part of the array again as many times as there are values

    Take an array to be sorted
    use an outer loop that picks the value to be sorted. For an array with n values, the outer loop skips the first value and must run n-1 times
    an inner loop then goes through the sorted array, to find where to insert the value. if the value to be sorted is at index i, the sorted part of the array
        starts at index 0 and ends at index i -1

    O(n^2) time complexity
    */

    int array[] = {100, 35, 2, 87, 12, 99, 56, 23, 78, 45};
    int n = sizeof(array) / sizeof(array[0]);
    // printf("size of array = %d\n",n);

    for (int i = 1 ; i < n; i++){
        int value = array[i];
        int j = i - 1;
        // int compare = array[i+1];
        while (j >= 0 && array[j] > value){
            array[j+1] = array[j];
            j = j - 1;
        }
    array[j+1] = value;
    printf("run %d swapped %d and %d\n", i, array[i], value);
    }

    for (int p = 0; p < 10; p++){
        printf("%d ", array[p]);
    }

    // for (int i = 1; i < n; i++){
    //     int key = i;
    //     int current = array[i + 1]; //w3schools has this as array.pop[i]. how do I access this in C? 
    //     for (int j = i; j > 0; j++) {
    //         if (array[j] > current) {
    //             key = j;
    //         } else {
    //             array[j + 1 ] = current;
    //             break;
    //         }
    //         printf("After insertion sort: ");
    //         for (int k = 0; k < n; k++){
    //             printf("%d ", array[k]);
    //         }
    //         printf("\n");
    //     }
    // }

    return 0;
}