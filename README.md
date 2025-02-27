# Simple RTOS Task Scheduler

This repository contains a C implementation of a simple task scheduler designed to simulate real-time operating system (RTOS) scheduling algorithms. The scheduler supports two primary algorithms: Round-Robin and Priority-Based scheduling.

Features:

- Task Management: Define tasks with attributes such as task number, state (Stopped, Running, Done), priority, completion count, and a function pointer to the task's execution function.

- Scheduling Algorithms:

  - Round-Robin Scheduling: Assigns equal time slices to each task in a cyclic order, ensuring fair execution without priority considerations. 
  
  - Priority-Based Scheduling: Sorts tasks based on priority and executes them accordingly, allowing higher-priority tasks to run before lower-priority ones.
- Task Execution Simulation: Simulate task execution with a fixed time slice (2 seconds) for each task in the Round-Robin algorithm.

Usage:

1. Initialization: Define tasks using the createTask function, specifying the task's function, number, priority, completion count, and initial tracker value.

2. Scheduling:

    -  Round-Robin: Use the round_robin function to execute tasks in a cyclic manner.
    -  Priority-Based: Use the priority_based function to execute tasks based on their priority.
3. Status Monitoring: Use the status function to display the current state of all tasks.
