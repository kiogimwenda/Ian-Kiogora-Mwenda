#include <stdio.h>

int main() {
    int nums[7] = {32, 35, 23, 53, 65, 72, 90};
    int size = sizeof(nums) / sizeof(nums[0]);
    int pos = 3; // position of the element to be deleted (0-indexed)
    int deleted_element;

    printf("Original array:\n");
    for(int i = 0; i < size; i++) {
        printf("%d ", nums[i]);
    }

    // Store the deleted element
    deleted_element = nums[pos];

    // Shift elements to the left
    for(int i = pos; i < size - 1; i++) {
        nums[i] = nums[i + 1];
    }
    size--; // Reduce the size of the array

    printf("\n\nArray after deleting the 4th element:\n");
    for(int i = 0; i < size; i++) {
        printf("%d ", nums[i]);
    }

    // Add the deleted element back to the end of the array
    nums[size] = deleted_element;
    size++; // Increase the size of the array

    printf("\n\nOriginal array after returning the deleted element:\n");
    for(int i = 0; i < size; i++) {
        printf("%d ", nums[i]);
    }

    return 0;
}
