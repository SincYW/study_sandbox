#include <stdio.h>

void callByValue(int value) {
    value++;
    return;
}

void callByReference(int* value) {
    (*value)++;
    return;
}

int main(void) {

    int value = 10;

    callByValue(value);
    printf("value : %d\n", value);

    callByReference(&value);
    printf("value : %d\n", value);

    return 0;
}
