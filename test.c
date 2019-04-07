//
// Created by kam on 01.04.19.
//
#include <stdio.h>
#include <dlfcn.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint-gcc.h>

int hookReplacementFunction() {
    printf("Calling replacement function!\n");
    return 3;
}

__attribute__((constructor))
static void ctor(void) {

    void *mainProgramHandle = dlopen(NULL, RTLD_NOW);
int64_t *origFunc = dlsym(mainProgramHandle , "hookTargetFunction");
    int64_t *newFunc = (int64_t*)&hookReplacementFunction;
    int32_t offset = (int64_t)newFunc - ((int64_t)origFunc + 5 * sizeof(char));

    size_t pageSize = sysconf(_SC_PAGESIZE);
    uintptr_t start = (uintptr_t)origFunc;
    uintptr_t end = start + 1;
    uintptr_t pageStart = start & -pageSize;
    uintptr_t pagediff = end-pageStart;
    mprotect((void *)pageStart, pagediff, PROT_READ | PROT_WRITE | PROT_EXEC);

    printf("Page start %p \n",&pageStart);
    printf("start %p \n",&start);

    printf("end %p \n",&end);
    printf("diff %p \n",&pagediff);
    printf("offset %d \n",offset);


    int64_t instruction = 0xe9 | (offset << 8);
    printf("%d", instruction);
    *origFunc = instruction;

}
