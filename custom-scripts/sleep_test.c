#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdlib.h>

#define SYSCALL_SLEEP 386

int main() {
    char buf[4096]; // maior buffer para pegar todos os processos
    long ret;

    ret = syscall(SYSCALL_SLEEP, buf, sizeof(buf));
    if(ret > 0) {
        printf("%s\n", buf);
    } else {
        printf("Error: %ld\n", ret);
    }
    return 0;
}
