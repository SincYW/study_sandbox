#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* boil_udon(){
    int second = 2;
    printf("うどんを茹でます\n");
    sleep(second);
    printf("うどんが茹で上がりました\n");
}

void* make_tuyu(){
    printf("ツユをつくります\n");
    printf("ツユができました\n");
}

int main()
{
    /*ptthread_t...スレッドを格納する型*/
    pthread_t thread1, thread2;
    /*第一引数:スレッド変数へのポインタ
    　第二引数:スレッドの属性へのポインタ*/
    pthread_create(&thread1, (void*)0, boil_udon, (void*)0);
    pthread_create(&thread2, (void*)0, make_tuyu, (void*)0);

    pthread_join(thread1, (void*)0);
    pthread_join(thread2, (void*)0);

    printf("盛り付けます\n");
    printf("うどんができました！\n");

    return 0;
}