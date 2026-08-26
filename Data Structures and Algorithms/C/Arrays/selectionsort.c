#include <stdio.h>

int main(void){
    /*
    Selection sort arrays an array from the lowest to the higest value
    find the smallest element and swaps it with the first element
    finds the second smallest element and swaps it with the second element
    continues until the array is sorted

    Go through the array to find the lowest value
    Move the lowest value to the front of the unsorted part of the array 
    Go through the array again as man times as there are values in the array 

    Same time complexity as bubble sort but performs fewer swaps
    O(n^2)
    */

    int array[] = {100, 35, 2, 87, 12, 99, 56, 23, 78, 45};
    int n = sizeof(array) / sizeof(array[0]);
    printf("size of array = %d\n", n);

    //This could be improved by only checking the unsorted part of the array 
    //or by swapping the elements in place instead of using a temp value

    // for (int i = 0; i < n; i++){
    //     int minIndex = i;
            //iterator needs to be set to the next value, compare the iterator to the size of the array, increment the iterator
    //     for (int j = i + 1; j < n; j++){ 
    //         if (array[j] < array[minIndex]){
    //             minIndex = j;
    //         }
    //     }
    //     int temp = array[i];
    //     array[i] = array[minIndex];
    //     array[minIndex] = temp;
    //     printf("run %d swapped %d and %d\n", i, array[i], array[minIndex]);
        
    // }

    // for (int p = 0; p < 10; p++){
    //         printf("%d ", array[p]);
    //     }

    //Imporved selection sort
    for (int i = 0; i < n - 1; i++){
        int minIndex = i;
        for (int j = i + 1; j < n; j++){
            if(array[j] < array[minIndex]){
                minIndex = j;
            }
        }
        //swap elements in place
        if (minIndex != i) {
            array[i] ^= array[minIndex];
            array[minIndex] ^= array[i];
            array[i] ^= array[minIndex];
        }
        printf("run %d swapped %d and %d\n", i, array[i], array[minIndex]);
    }

    for (int p = 0; p < 10; p++){
        printf("%d ", array[p]);
    }

    return 0;
}