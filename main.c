#include <stdio.h>
#include <unistd.h>



int hookTargetFunction() {
    printf("Calling original function!\n");
    return 5;
}

int main() {
    printf("The number is: %d\n", hookTargetFunction());

    //int a =4;
    //scanf("%d", a);

    return 0;
}



