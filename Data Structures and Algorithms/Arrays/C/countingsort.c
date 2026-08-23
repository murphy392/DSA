#include <stdio.h>

void countSort(int array[], int n);

/*
    Counting sorts count the number of times a value occurs
    Does not compare values like the previous sorting algorithms and ONLY works on non-negative values

    How it works:
    1. Create a new array for counting how many there are of the different values.
    2. Go through the array that needs to be sorted.
    3. For each value, count it by increasing the counting array at the corresponding index.
    4. After counting the values, go through the counting array to create the sorted array.
    5. For each count in the counting array, create the correct number of elements, with values that correspond to the counting array index.
    
    Implementation
    1. Have an array with valus to sort
    2. A 'countingSort' method that recieves an array of integers
    3. An array inside the method to keep count of the values
    4. A loop inside the method that counts and removes values, by incrementing 
        in the counting array
    5. A loop inside the method that recreates the array by using the counting array, 
        so that the elements appear in the right order

    Tip: Find the highest value in the sarray so that the counting array can be created with the correct size

    The speed of the counting sort algorithm depends on both the range of possible values and the number of values
    General time complexity is O(n+k)
    Best case scanario: k is very small compred to n O(n)
    worse case scenario: K is very big compared to n and can have O(n^2)
*/

int main(void) {
    int array[] = {100, 35, 2, 87, 12, 99, 56, 23, 78, 45};
    int n = sizeof(array) / sizeof(array[0]);

    countSort( array,  n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}

void countSort(int array[], int n){

    int maxVal = array[0];
    for(int i = 1; i < n; i++){
        if(array[i] > maxVal){
            maxVal = array[i];
        }
    }

    int count[maxVal + 1];
    for (int i = 0; i <= maxVal; i++){
        count[i] = 0;
    }

    for (int i = 0; i < n; i++){
        count[array[i]]++;
    }

    int index = 0;
    for (int i = 0; i <= maxVal; i++){
        while(count[i] > 0){
            array[index++] = i;
            count[i]--;
        }
    }


}