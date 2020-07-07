#include <stdio.h>

void callByValue(int value) {
    printf("callByValue parameter address : %p\n", &value);
    value++;
    return;
}

void callByReference(int* value) {
    printf("callByReference parameter address : %p\n", value);
    (*value)++;
    return;
}

int main(void) {

    int value = 10;
    printf("original address: %p\n", &value);

    callByValue(value);
    printf("value : %d\n", value);

    callByReference(&value);
    printf("value : %d\n", value);

    return 0;
}
