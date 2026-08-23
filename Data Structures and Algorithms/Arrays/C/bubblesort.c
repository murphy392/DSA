#include <stdio.h>

int main(void){
    /*
    bubble sort sorts an array fromthe lowest to the highest value
    highest value bubbles up to the end of the array 

    1. Go through the array and compare each element with the next element
    2. If the current element is greater than the next element, swap them
    3. Repeat until the array is sroted

    O(n^2) time complexity -> run time increases quadratically with the size of the input
    */

    int array[] = {100, 35, 2, 87, 12, 99, 56, 23, 78, 45};
    int n = sizeof(array) / sizeof(array[0]);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                printf("Run %d swapped %d and %d\n", i, array[j], array[j + 1]);
            }
        }
    }

    for (int i = 0; i < n; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}