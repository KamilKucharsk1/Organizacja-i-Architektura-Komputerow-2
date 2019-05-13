#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <stdint.h>
#include <string.h>


/*
 * 1st line : 0x3b8e5894855 - our foo() in machine language
 * 2nd line : 0xb8e5894855c35d00
 *
 * commands are launched from the end to the start
 *
 * 1st line explanation:
 *
 * 03 b8 - mov $0x3, %eax
 * e5 89 48 - mov %rsp, %rbp
 * 55 - push rbp
 *
 * 2nd line explanation:
 * 00
 * 5d - pop %rbp
 * c3 - retq - function return
 *
 * (...)
 *
 * based on the godbolt.org
 *
 *
 */

int x = 5; // Global variable

// ORiginal function
int foo() {
    return 3;
}

// NEw function
int foo2(){
    return 123;
}

int main() {

    // Calling method before change
    printf("Value is: %d\n" ,foo());

    // Pointers to method starts (getting addresses)
    int64_t *origFunc = (int64_t*)&foo;
    int64_t *newFunc = (int64_t*)&foo2;

    int addressToCheck = 8; // How many address should print?

    printf("Foo2 data: p: %p | *p: %p\n", newFunc, *newFunc);

    printf("+++++ Before changes ++++++\n");
    for(int i=0;i<addressToCheck+1;i++){
        printf("p: %p | *p: %p\n", origFunc+i, *(origFunc+i));
    }
    printf("++++++\n");

    // Offset for inserting new instruction
    int32_t offset = (int64_t)newFunc - ((int64_t)origFunc + 5 * sizeof(char));

    uintptr_t start = (uintptr_t)origFunc;  // get starting address of the original function
    uintptr_t end = start + 1;              // get end of the original function address

    size_t pageSize = sysconf(_SC_PAGESIZE); // Get size of the page in the current system
    uintptr_t pageStart = start & -pageSize; // Calculate where the page starts

    // Assign privilages for the memory to add instruction
    mprotect((void *)pageStart, end - pageStart, PROT_READ | PROT_WRITE | PROT_EXEC);

    // Prepare jump instruction(0xe9) at the start of the original function
    // JMP to offset << shift by 8 bits
    int64_t instruction = 0xe9 | offset << 8;

    *origFunc = instruction; // Add instruction to the original function address

    printf("+++++ After changes ++++++\n");
    for(int i=0;i<addressToCheck+1;i++){
        printf("p: %p | *p: %p\n", origFunc+i, *(origFunc+i));
    }
    printf("++++++\n");
    
    printf("Replaced\n");

    // Calling method after change
    printf("Value is: %d\n" ,foo());

    // ++++ GLOBAL VARIABLE CHANGE +++++

    printf("\nGlobal variable tests\n");

    int z = 999; // new value to set for global variable

    // uintptr_t startX = (uintptr_t) &x; // Assign the address of the x 

    printf("Value of x: %d\n", x); // Display value of x before change

    // Insert data from z address into the address of x
    memcpy((void *)&x, &z, sizeof(z));

    printf("Value of x: %d\n", x); // Display new changed value

}