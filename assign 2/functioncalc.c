#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int main(void) {
    int a, b;

    printf("Enter first number: ");
    scanf("%d", &a);

    printf("Enter second number: ");
    scanf("%d", &b);

    printf("The sum of the two numbers is: %d\n", add(a, b));
    printf("The difference of the two numbers is: %d\n", subtract(a, b));

}
