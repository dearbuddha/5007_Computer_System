#include <stdio.h>
#include <stdlib.h>

int someFunction(int a, int b, int c, int rv) {
    rv = -b + (b * b - 4 * a * c) / (2 * a);
    return 0;
}
int main() {
    int first = 5;
    int second = 10;
    int third = 15;
    int fourth = 20;
    someFunction(first, second, third, fourth);
    printf("%d\n", fourth);
    return 0;
}