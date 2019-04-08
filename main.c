#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

int foo() {
    printf("Calling original function!\n");
    return 1;
}

int foo2(){
    printf("Calling replaced function!\n");
    return 123;
}



int main() {
    printf("Value is: %d\n" ,foo());

    int64_t *origFunc = (int64_t*)&foo;
    int64_t *newFunc = (int64_t*)&foo2;

    int32_t offset = (int64_t)newFunc - ((int64_t)origFunc + 5 * sizeof(char));

    //Make the memory containing the original funcion writable
    //Code from http://stackoverflow.com/questions/20381812/mprotect-always-returns-invalid-arguments
    size_t pageSize = sysconf(_SC_PAGESIZE);
    uintptr_t start = (uintptr_t)origFunc;
    uintptr_t end = start + 1;
    uintptr_t pageStart = start & -pageSize;

    mprotect((void *)pageStart, end - pageStart, PROT_READ | PROT_WRITE | PROT_EXEC);

    //Insert the jump instruction at the beginning of the original function
    int64_t instruction = 0xe9 | offset << 8;
    *origFunc = instruction;

    printf("Replaced\n");
    printf("Value is: %d\n" ,foo());
}