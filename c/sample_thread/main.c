#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* boil_udon(void* pu){
    int second = 2;
    printf("うどんを茹でます\n");
    sleep(second);
    printf("うどんが茹で上がりました\n");
}

void* make_tuyu(void* p){
    printf("ツユをつくります\n");
    printf("ツユができました\n");
}

int main()
{
    /ptthread_t...スレッドを格納する型/
    pthread_t thread1, thread2;
    /第一引数:スレッド変数へのポインタ
    　第二引数:スレッドの属性へのポインタ/
    pthread_create(&thread1, NULL, boil_udon, NULL);
    pthread_create(&thread2, NULL, make_tuyu, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("盛り付けます\n");
    printf("うどんができました！\n");

    return 0;
}