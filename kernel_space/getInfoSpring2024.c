/*Mahny Barazandehtar - 20210702004 - CSE 331 Project - Phase 1*/

#include <linux/kernel.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/getInfoSpring2024.h>

asmlinkage int sys_getInfoSpring2024(struct structSpring2024 *data){
    
    struct structSpring2024 task; 

    // copy data to the kernel space
    if (copy_from_user(&task, data, sizeof(struct structSpring2024))) {
        return -EFAULT; // constant value for fault
    }
    
    if (task.flag >= 0 && task.flag <= 24) {

        // fill the struct with the information of the current process
        task.pid = current->pid;
        task.pid_parent = current->p_pptr->pid;
        task.process_counter = current->counter;
        task.nice = current->nice;
        task.nice_parent = current->p_pptr->nice;
        task.uid = current->uid;

        if (task.process_counter == 0 ){
            task.weight = 0;
        }
        else{
            task.weight = current->counter + 20 - current->nice;
        }

        if (copy_to_user(data, &task, sizeof(struct structSpring2024))) {
            return -EFAULT; 
        }
        
        return 0; // it was successful
        
    }

    // both are failed attempts
    else if(task.flag < 0){ 
        return -1;
    }
    else if(task.flag > 24){ // this one is going to return the weight
        
        if(task.process_counter == 0 ){

            task.weight = 0;
        }
        else{
            task.weight = current->counter + 20 - current->nice;
        }

        if (copy_to_user(data, &task, sizeof(struct structSpring2024))) {
            return -EFAULT; 
        }        

        return -1;                

    }
    
    return 0; // this is not accessible, but it is here just so the compiler doesn't panic
}
