## Chapter 4

> 4.8: Provide two programming examples in which multithreading does not provide better performance than a
> single-threaded solution.

Ans:

1. A program that performs a lot of I/O operations, such as disk read/write or network operations. In this case, the
   program is likely to be I/O-bound, and multithreading does not help because the threads will spend most of their
   time waiting for I/O operations to complete.
2. A program that is CPU-bound and does not have any parallelize-able tasks. In this case, the program is likely to
   be
   CPU-bound, and multithreading does not help because the threads will compete for CPU resources and may even slow
   down the program due to the overhead of context switching.

> 4.10: Which of the following components of program state are shared across threads in a multithreaded process?
>
> - (a) Register values
> - (b) Heap memory
> - (c) Global variables
> - (d) Stack memory

Ans: (b) Heap memory, (c) Global variables

> 4.16: A system with two dual-core processors has four processors available for scheduling
>
> - A CPU-intensive application is running on this system
> - All input is performed at program start-up, when a single file must be opened
> - Similarly, all output is performed just before the program terminates, when the program results must be written to
>   > a single file
> - Between start-up and termination, the program is entirely CPU-bound
> - Your task is to improve the performance of this application by multithreading it
> - The application runs on a system that uses the one-to-one threading model (each user thread maps to a kernel
> - thread) How many threads will you create to perform the input and output? Explain.

Ans: One thread only as discussed in 4.8, tasks involving I/O operations are not CPU-bound and thus do not benefit
from multithreading.

- How many threads will you create for the CPU-intensive portion of the application? Explain.

Ans: Assume that the CPU-intensive portion of the application can be **equally** parallelized. Four threads should be
created to take advantage of the dual-core processors.

## Chapter 5

> 5.14: Most scheduling algorithms maintain a run queue, which lists processes eligible to run on a processor. On
> multicore systems, there are two general options:
> (1) each processing core has its own run queue, or
> (2) a single run queue is shared by all processing cores.
> What are the advantages and disadvantages of each of these approaches?

Ans:

1. Utilizing a unique queue for each core offers faster performance because it eliminates the need for
   locking/unlockingto prevent multiple cores from selecting the same thread. However, this approach may suffer from
   potential overhead due to load balancing.
2. On the other hand, using a shared queue naturally avoids imbalance issues, as processors can simply take another task
   from the queue whenever they are free. However, this method does require locking/unlocking to protect processors from
   performing redundant work.

> 5.18: The following processes are being scheduled using a preemptive, priority-based, round-robin scheduling
> algorithm.
>
> - Each process is assigned a numerical priority, with a higher number indicating a higher relative priority.
> - For processes with the same priority, a round-robin scheduler will be used with a time quantum of 10 units.
> - If a process is preempted by a higher-priority process, the preempted process is placed at the end of the
>   > queue.
>   > ![image.png](assets/5.18.png)
>   > (a) Show the scheduling order of the processes using a Gantt chart.
>   > (b) What is the turnaround time for each process?
>   > (c) What is the waiting time for each process?

Ans: (Grids marked with 'X' means that the CPU is currenting processing the thread during the time
interval [`t`, `t+5`]. while 'A' means that the process has arrived the waiting queue)


| Starting time | 0  | 5 | 10 | 15 | 20 | 25 | 30 | 35 | 40 | 45 | 50 | 55 | 60 | 65 | 70 | 75 | 80 | 85 | 90 | 95 |
| ------------- | -- | - | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- |
| P1            | AX | X | X  |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| P2            | A  |   |    | X  |    |    |    |    |    |    |    |    |    |    |    |    | X  | X  | X  |    |
| P3            |    |   |    |    | AX | X  |    |    | X  |    |    |    |    |    | X  |    |    |    |    |    |
| P4            |    |   |    |    |    | A  | X  | X  |    |    | X  |    |    |    |    | X  |    |    |    |    |
| P5            |    |   |    |    |    |    |    |    |    | AX |    |    |    |    |    |    |    |    |    |    |
| P6            |    |   |    |    |    |    |    |    |    |    |    | AX | X  | X  |    |    |    |    |    |    |


| Starting time | 0-5 | 5-10 | 10-15 | 15-20 | 20-25 | 25-30 | 30-35 | 35-40 | 40-45 | 45-50 | 50-55 | 55-60 | 60-65 | 65-70 | 70-75 | 75-80 | 80-85 | 85-90 | 90-95 | 95-100 |
| ------------- | --- | ---- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- | ------ |
| Process       | P1  | P1   | P1    | P2    | P3    | 3P    | P4    | P4    | P3    | P5    | P4    | P6    | P6    | P6    | P3    | P4    | P2    | P2    | P2    |        |


|         | Waiting time                       | Turnaround time |
| ------- | ---------------------------------- | --------------- |
| P1      | (0 - 0)= 0                         | 0 + 15 = 15     |
| P2      | (15 - 0)+(80 - 20)= 75             | 75 + 20 = 95    |
| P3      | (20 - 20)+(40 - 30)+(70 - 45)= 35 | 35 + 20 = 55    |
| P4      | (30 - 25)+(50 - 40)+(75 - 55)= 35  | 35 + 20 = 55    |
| P5      | (45 - 45)= 0                       | 0 + 5 = 5       |
| P6      | (55 - 55)= 0                       | 0 + 15 = 15     |
| Average | 135 / 6 = 22.5                     | 230 / 6 = 38.66 |

> 5.22: Consider a system running ten I/O-bound tasks and one CPU-bound task.
>
> - Assume that the I/O-bound tasks issue an I/O operation once for every millisecond of CPU computing and that each I/O
>   > operation takes 10 milliseconds to complete.
> - Also assume that the context-switching overhead is 0.1 millisecond and that all processes are long-running tasks.
> - Describe the CPU utilization for a round-robin scheduler when:
> - (a) The time quantum is 1 millisecond
> - (b) The time quantum is 10 millisecond

Ans:

1. (a) The time quantum is 1 millisecond
   The CPU utilization will be low because the time quantum is too short for the CPU-bound task to complete its
   computation. The CPU-bound task will be preempted frequently((1 * 10)+ 1 +(9 * 2)= 29 context switches are needed for
   each cycle), and the context-switching overhead will be high.
   => Time to finish a cycle = (1 + 0.1)* 10 + (1 + 0.1)* 17 + (1 + 0.1)* 2 = 31.9milliseconds
   => CPU utilization = 29 / 31.9 = 90.90%
2. (b) The time quantum is 10 millisecond
   The CPU utilization will be high because the time quantum is long enough for the CPU-bound task to complete its
   computation. The CPU-bound task will be preempted less frequently, and the context-switching overhead will be lower.
   => Time to finish a cycle = (1+0.1) * 10 + 10 = 21 milliseconds
   => CPU utilization = 20/21 = 95.24%

> 5.25: Explain the differences in how much the following scheduling algorithms discriminate in favor of short
> processes:
>
> - (a) FCFS
> - (b) RR
> - (c) Multilevel feedback queues

Ans:

1. FCFS: Potential long time when there's a long job heading it, which results in a long wait time and turnaround time.
2. RR: The turnaround time of the job is at most `Quantant * (n-1) + burstTime`time unit if its burst time is smaller
   than the quantum.
3. MFQ: Similar to RR, The short jobs would have a smaller waiting time than FCFS as they could finish in the early
   queues.

## Chapter 6

> 6.7: The pseudocode of Figure 6.15 illustrates the basic push() and pop() operations of an array-based stack. Assuming
> that this algorithm could be used in a concurrent environment, answer the following questions:
>
> - (a) What data have a race condition?
> - (b) How could the race condition be fixed?
>   > ![image.png](assets/6.7.png)
>   >

Ans:

1. The race condition occurs on both `stack` and `top` as the value read from `top` might be the last state rather than
   the value another thread/process trying to write. The following figure is the example in the textbook but the
   concepts are similar.
   ![image.png](assets/raceConditionFromTextbook.png)
2. Lock the critical section of the code, i.e. the `push()` and `pop()` functions, to prevent multiple threads from
   accessing the shared data simultaneously.

> 6.15: Explain why implementing synchronization primitives by disabling interrupts is not appropriate in a single-
> processor system if the synchronization primitives are to be used in user-level programs.

Ans: The processor could be interrupted by the hardware timer, I/O devices, etc. Disabling interrupts would prevent the
processor from responding to these events, which could lead to the processor is occupied by the process and eventually
result in system instability and poor performance.

> 6.18: The implementation of mutex locks provided in Section 6.5 suffers from busy waiting.
>
> - Describe what changes would be necessary so that a process waiting to acquire a mutex lock would be blocked and
>   > placed into a waiting queue until the lock became available.
>
>> ![image.png](assets/6.18.png)
>>

Ans:
Maintain a thread-shared queue consist of the identifiers of threads awaiting to enter the critical block. When a thread
tries to acquire the lock but fails, it should be placed in the queue and the processor can then switch to another task
or thread. Once the lock is released, the thread at the front(or whatever the algorithm applied) of the queue can
acquire the lock and enter the critical block.
