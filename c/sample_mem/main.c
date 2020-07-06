#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int num;
    char* str;
} strct;

// 何度も出てくる値なので、こんな感じでわかりやすい名前をつけて定義しておきます
#define STR_LENGTH 5

int main()
{
    strct* entity;
    printf("entity = %p\n", entity);

    // 構造体のメモリを確保して、その先頭アドレスを渡す
    entity = (strct*)malloc(sizeof(strct));
    printf("entity = %p\n", entity);

    // 数値を入れてみる
    entity->num = 0;

    // 数値は、構造体の先頭なので、entity変数が持っているアドレスと同じアドレス値が出る
    printf("entity = %p\n", &(entity->num));

    // charの5文字分のメモリを確保
    entity->str = (char*)malloc(sizeof(char) * STR_LENGTH);

    // ここでallocateしたメモリ全部に、nullを書き込む
    memset(entity->str, 0x00, STR_LENGTH);

    // allocateしたサイズ−1分だけを、書き込む
    memcpy(entity->str, "Hello World", STR_LENGTH - 1);

    // 書き込んだ分だけが出力される
    printf("entity->str = %s(%p)\n", entity->str, entity->str);

    // いらなくなったら開放する
    free((void*)entity->str);
    entity->str = 0x00;

    free((void*)entity);
    entity = 0x00;

    return 0;
}