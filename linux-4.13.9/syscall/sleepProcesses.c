// sleepProcesses.c
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include "sleepProcesses.h"

asmlinkage long sys_listSleepingProcesses(char __user *buf, int size) {
    struct task_struct *task;
    unsigned char kbuf[1024]; // buffer temporário
    int total_len = 0;
    int ret;

    for_each_process(task) {
        if(task->state == TASK_INTERRUPTIBLE || task->state == TASK_UNINTERRUPTIBLE) {
            int len = snprintf(kbuf, sizeof(kbuf), "Process: %s PID: %d State: %ld\n",
                               task->comm, task_pid_nr(task), task->state);
            if(total_len + len > size)
                return -1; // buffer de usuário pequeno
            ret = copy_to_user(buf + total_len, kbuf, len);
            total_len += len - ret;
        }
    }

    return total_len;
}
