#include <stdio.h>


int function() {
    static int b = 0;
    int a = 1;

    b++;
    a++;
    printf("[func] a = %d\n", a);
    printf("[func] b = %d\n", b);
}

int main() {
    static int b = 1;
    function();
    function();
    function();
    printf("[main] b = %d\n", b);
}