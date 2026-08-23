#include <stdio.h>
#include <stdlib.h>

#define SIZE 10 //this is a constant

/*
    Radix sort algorithm sorts an array by the individual digits. 
    It starts with the lease significant digit (the right most)

    The base is the number of unique digits in a number system. 
    Radix sort uses the radix so that the decimal values are put into 10 different buckets
    corresponding to the digit that is in focusl then put back into the array before moving on to the next digit

    Works ONLY with non negative integers and is non comparative

    How it works:
    1. Start with the least significant digit (rightmost digit).
    2. Sort the values based on the digit in focus by first putting the values in the correct bucket based on the digit in focus, and then put them back into array in the correct order.
    3. Move to the next digit, and sort again, like in the step above, until there are no digits left.

    Radix Sorting must be done in a stable way.
    Stable sorting: Al algorithm that keeps the order of elements with the same value before and 
        after the sorting. 

    Implementation:
    1. Need an array with non negative integers that needs sorting
    2. A two dimensional array with index 0 to 9 to hold values with the current raix in focus
    3. A loop that takes values from the unsorted array and places them in the correct posistion
    4. A loop that puts values back into the initial array from the radix array
    5. An outer loop that rusn as many times as there are digits in the highest value
*/

int main(void) {
    int array[SIZE] = {100, 35, 2, 87, 12, 99, 56, 23, 78, 45};
    int n = sizeof(array) / sizeof(array[0]);
    
    printf("Original array: ");
    for (int i = 0; i < SIZE; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    printf("Sorted Array: ");
    for (int i = 0; i < SIZE; i++){
        printf("%d ", array[i]);
    }

    printf("\n");

    return 0;
}

void radix_sort(int array[], int size){
    int maxVal = array[0];
    for (int i = 0; i < size; i++){
        if (array[i] > maxVal){
            maxVal = array[i];
        }
    }

    int exp = 1; 
    int *radix_array[10];
    for (int i = 0; i < 11; i++){
        radix_array[i] = (int *)malloc(sizeof(int) *size); //first use of memory controls
    }

    int counts[10] = {0};

    while (maxVal / exp > 0){
        for (int i = 0; i < size; i++){
            int radix_index = (array[i] / exp) % 10;

            radix_array[radix_index][counts[radix_index]] = array[i];//learn and understand this one
            counts[radix_index]++;
        }

        int pos = 0;
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < counts[i]; j++){
                array[pos] = radix_array[i][j];
                pos++;
            }
            counts[i]=0;
        }
        exp *= 10;
    }

    for (int i = 0; i < 10; i++){
        free(radix_array[i]);
    }
}