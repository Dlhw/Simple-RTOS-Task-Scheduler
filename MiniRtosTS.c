/*
A real-time operating system (RTOS) is a special kind of Operating system
designed to handle tasks that need to be completed quickly and on time. 
Unlike general-purpose operating systems, which are good at multitasking 
and user interaction, RTOS focuses on doing things in real time.
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_TASKS 3

/// @brief Initialise Tasks -------------------------------------------

typedef struct {
    int taskNo;  
    int state; // 0: Stopped, 1: Running, 2: Done
    int priority;
    void (*someFunc)(void);
    int completion;
    int tracker;
}Task;

Task tasks[MAX_TASKS];

Task createTask(void(*task)(),int taskNo, int priority, int completion, int tracker){
    Task temp;
    temp.taskNo = taskNo;
    temp.someFunc = task;
    temp.priority = priority;
    temp.state = 0;
    temp.completion = completion;
    temp.tracker = tracker;
    return temp;
}

int currentTask = 0;

void task1(){
    if (++tasks[currentTask].tracker == tasks[currentTask].completion){
        tasks[currentTask].state = 2;
    }
}

void task2(){
    if (++tasks[currentTask].tracker == tasks[currentTask].completion){
        tasks[currentTask].state = 2;
    }
}

void task3(){
    if (++tasks[currentTask].tracker == tasks[currentTask].completion){
        
        tasks[currentTask].state = 2;
    }
}

void initialise_tasks(){
    tasks[0] = createTask(task1,1,1,3,0);
    tasks[1] = createTask(task2,2,3,2,0);
    tasks[2] = createTask(task3,3,2,1,0);
}
/// @brief-------------------------------------------------------------

/// @brief Scheduling -------------------------------------------------


void executeTask(){
    tasks[currentTask].someFunc();
    if (tasks[currentTask].state != 2){
        tasks[currentTask].state = 1;
    }
    printf("Task %d running.\n",tasks[currentTask].taskNo);
}

void stopTask(){
    if (tasks[currentTask].state != 2){
        tasks[currentTask].state = 0;
    }
    printf("Task %d stopped.\n",tasks[currentTask].taskNo);
}

void status(){
    for (int i = 0; i < MAX_TASKS; i++){
        printf("State of Task %d: %d\n", tasks[i].taskNo, tasks[i].state);
    }
}

int compare(const void *a, const void *b){
    return ((Task *)a)->priority - ((Task *)b)->priority;
}

void reset(){
    for (int i=0; i<MAX_TASKS; i++){
        tasks[i].state=0;
        tasks[i].tracker=0;
    }
    currentTask = 0;
}
void round_robin(){
    int incomplete = 1;
    int count = 0;
    while (incomplete){
        if (tasks[currentTask].state!=2){
            executeTask();
            status();
            sleep(2); // time given for each execute
            stopTask();
        }
        else if (++count != MAX_TASKS){ // current task completed
            printf("\nTask %d Completed\n\n", tasks[currentTask].taskNo);
            status();
        }
        else{ // all task completed
            incomplete = 0;
            printf("All tasks completed\n");
            reset();
            break;
        }
        currentTask = (currentTask + 1) % MAX_TASKS;
        printf("\nSwitched to Task %d\n\n", tasks[currentTask].taskNo);
    }
}

void priority_based(){
    int incomplete = 1;
    int count = 0;
    qsort(tasks,sizeof(tasks)/sizeof(Task),sizeof(Task),compare);
    while (incomplete){
        if (tasks[currentTask].state!=2){
            executeTask();
            status();
            sleep(2); // time given for each execute
        }
        else if (count++ != MAX_TASKS){ // current task completed
            stopTask();
            printf("\nTask %d Completed\n\n", tasks[currentTask].taskNo);
            status();
            currentTask = (currentTask + 1) % MAX_TASKS;
            printf("\nSwitched to Task %d\n\n", tasks[currentTask].taskNo);
        }
        else{ // all task completed
            incomplete = 0;
            printf("All tasks completed\n");
            reset();
            break;
        }
        
    }
}

/// @brief -----------------------------------------------------------

int main(){

    initialise_tasks();
    
    int approach;

    while(1){
        printf("Please select scheduling algorithm:\n"
            "1: Round-Robin\n"
            "2: Priority-Based\n"
            "3: Exit\n");
 
        scanf("%d",&approach);

        switch (approach) {
            case 1:
                round_robin();
                break;
            case 2:
                priority_based();
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid Selection.\n");
        }
    }
    return 0;
}