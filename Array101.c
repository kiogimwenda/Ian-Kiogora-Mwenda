#include <stdio.h>

void printArray(int arr[], int len) {
    for(int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void bubbleSort(int arr[], int len) {
    for(int i = 0; i < len - 1; i++) {
        for(int j = 0; j < len - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arrayElements[7] = {32, 35, 23, 53, 65, 72, 90};
    int arraySize = sizeof(arrayElements) / sizeof(arrayElements[0]);
    int deletePosition = 3;
    int removedElement;

    printf("Original array:\n");
    bubbleSort(arrayElements, arraySize);
    printArray(arrayElements, arraySize);

    removedElement = arrayElements[deletePosition];

    for(int i = deletePosition; i < arraySize - 1; i++) {
        arrayElements[i] = arrayElements[i + 1];
    }
    arraySize--;

    printf("\n\nArray after deleting the 4th element:\n");
    bubbleSort(arrayElements, arraySize);
    printArray(arrayElements, arraySize);

    for(int i = arraySize; i > deletePosition; i--) {
        arrayElements[i] = arrayElements[i - 1];
    }
    arrayElements[deletePosition] = removedElement;
    arraySize++;

    printf("\n\nOriginal array after returning the deleted element:\n");
    bubbleSort(arrayElements, arraySize);
    printArray(arrayElements, arraySize);

    return 0;
}
