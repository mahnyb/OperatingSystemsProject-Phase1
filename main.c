/*Mahny Barazandehtar - 20210702004 - CSE 331 Project - Phase 1*/

#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <string.h>
#include <sys/types.h> // so we can use the nice and setuid 
#include <linux/getInfoSpring2024.h>

int main(){

    // allocate memory to struct pointer 
    struct structSpring2024 * task = (struct structSpring2024 *)malloc(sizeof(struct structSpring2024));

    nice(15); // setting the nice value 
    setuid(89); // setting the user ID
    task->flag = 2; // manually setting the flag value, as instructed

    int result = getInfoSpring2024(task);
    
    if (result == 0){
        printf("process Flag: %d\n", task->flag);
        printf("process ID: %d\n", task->pid);
        printf("process Parent ID: %d\n", task->pid_parent);
        printf("process Process Counter: %ld\n", task->process_counter);
        printf("process Nice value: %ld\n", task->nice);
        printf("process Nice of Parent value: %ld\n", task->nice_parent);
        printf("process User ID: %ld\n", task->uid);
        printf("process Weight: %d\n", task->weight);
    }
    else {
        if (task->flag < 0){
            printf("the flag is below zero\n");
        }
        else if (task->flag > 24){
            printf("the flag is above 24\n");
            printf("process weight: %d\n", task->weight);
        }
    }

    return 0;
}