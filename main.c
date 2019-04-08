#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/mman.h>

int* foo(){
    int* p = 5;
    return p;
}

void swap(int *p, int *p2){
    *p = *p2;
}

int* fooOther(){
    int *p = 88;
    return p;
}

int main() {
    int *t = 0;
    int *t2 = fooOther();
    int *a = 123;
    int *b = malloc(sizeof(int));

    //mprotect(a, sizeof(int), PROT_EXEC);
    //mprotect(t, sizeof(int), PROT_EXEC);

    bool exit = false;
    printf("Started!\n");
    while(true){
        if(exit) break;

        char c = getchar();

        switch (c){
            case '1':
                printf("DATA t:\n");
                printf("&Address: %p\n", &t);
                printf("Address: %p\n", t);
                printf("Value: %d\n", t);
                printf("&Value inne: %d\n", &t);
                break;
            case '2':
                printf("DATA t2:\n");
                printf("&Address: %p\n", &t2);
                printf("Address: %p\n", t2);
                printf("Value: %d\n", t2);
                printf("&Value inne: %d\n", &t2);
                break;
            case '3':
                t = foo();
                printf("t assigned..\n");
                break;
            case '4':
                //*a = *t;
                swap(&t, &t2);
                printf("Swapped..\n");
                break;
            case '5':
                t2 = 666;
                printf("t2 changed..\n");
                break;
            case '6':
                printf("DATA a:\n");
                printf("&Address: %p\n", &a);
                printf("Address: %p\n", a);
                printf("Value: %d\n", a);
                printf("&Value inne: %d\n", &a);
                break;
            case '7':
                printf("DATA b:\n");
                printf("&Address: %p\n", &b);
                printf("Address: %p\n", b);
                printf("Value: %d\n", b);
                printf("&Value inne: %d\n", &b);
                break;

            case 'e':
                printf("ending..\n");
                exit = true;
                break;
        }
    }
    printf("Exited.\n");
    return 0;
}