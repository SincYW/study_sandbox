#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num;
    char* str;
} strct;

int main()
{
    strct* entity;
    printf("entity = %p\n", entity);

    entity = (strct*)malloc(sizeof(strct));
    printf("entity = %p\n", entity);

    entity->num = 0;
    printf("entity = %p\n", &(entity->num));

    printf("entity->str = %s(%p)\n", entity->str, entity->str);

    entity->str = (char*)malloc(sizeof(char)*5);
    printf("entity->str[0] : %c(%p)\n", entity->str[0], &(entity->str[0]));
    printf("entity->str[1] : %c(%p)\n", entity->str[1], &(entity->str[1]));
    printf("entity->str[2] : %c(%p)\n", entity->str[2], &(entity->str[2]));
    printf("entity->str[3] : %c(%p)\n", entity->str[3], &(entity->str[3]));
    printf("entity->str[4] : %c(%p)\n", entity->str[4], &(entity->str[4]));

    sprintf(entity->str, "%s %s", "Hello", "World");
    printf("entity->str[0] : %c(%p)\n", entity->str[0], &(entity->str[0]));
    printf("entity->str[1] : %c(%p)\n", entity->str[1], &(entity->str[1]));
    printf("entity->str[2] : %c(%p)\n", entity->str[2], &(entity->str[2]));
    printf("entity->str[3] : %c(%p)\n", entity->str[3], &(entity->str[3]));
    printf("entity->str[4] : %c(%p)\n", entity->str[4], &(entity->str[4]));
    printf("entity->str[5] : %c(%p)\n", entity->str[5], &(entity->str[5]));

    printf("entity->str = %s(%p)\n", entity->str, entity->str);

    free((void*)entity->str);
    printf("entity->str[0] : %c(%p)\n", entity->str[0], &(entity->str[0]));
    printf("entity->str[1] : %c(%p)\n", entity->str[1], &(entity->str[1]));
    printf("entity->str[2] : %c(%p)\n", entity->str[2], &(entity->str[2]));
    printf("entity->str[3] : %c(%p)\n", entity->str[3], &(entity->str[3]));
    printf("entity->str[4] : %c(%p)\n", entity->str[4], &(entity->str[4]));

    free((void*)entity);
    printf("entity = %p\n", entity);

    return 0;
}