# Comp 362 Operating Systems
An introductory but very intense course on the principles of operating systems. We learned about operating system structures, processes, threads, CPU scheduling, process synchronization, deadlocks and race conditions, memory management, file system interface, input/output management, and mass storage organization.

### Lab 5
#### Task 1:

Exponential Averaging ( on Wikipedia it is called moving average)

Key Formula: T(next) =  (alpha * most_recent_value) + (pervious_average * (1 - alpha));

Depending on the alpha, this calculation can either make the pass more important or the present more important. Alpha is (only past -->) 0 <= alpha(.5 make past and present equally weighted)  <= 1 (<-- only recent)

Program take in Alpha first then a set of numbers to do T(next).
Use standard input, can also use piping


#### Task 2 - Scheduling Thread Test

Testing three types of threads

1. HIGH_PRIORITY → RR → SCHED_RR
2. MEDIUM_PRIORITY → FCFS → SCHED_FIFO
3. LOW_PRIORITY → Default (other) → SCHED_OTHER
 
Change: setSchedPolicy to one of the above

*note : FIFO = FCFS*

#### Task 3: CPU Scheduler
Concept: 
Image a simple CPU on a timeline

0 1 2 3 4 5 6 7 8 9
|--|--|--|--|-|-|----------|--|
0-1: 1 work unit

A burst time is the number of work units a process has to complete in order to be done.
CPU can only work on one process at a time

Imagine a Queue with list of process name and burst time.
Scheduling Algorithm searches at every time tick for the element to process.  
No movements in Queue

### Lab 6

#### Task 1, 2, and 3

Deadlock and the Dining Philosophers



