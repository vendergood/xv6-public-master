# xv6 Thread


## What is implemeted

Implement 4 new system calls for supporting thread and getting thread ID.

### Support thread

- `thread_create()`

  - int thread_create(void *(*function)(void *), void *arg, void *stack)
  - Create a new thread at calling process
  - Return the thread ID(tid) of the new thread. If err, return -1
  - The new thread starts execution in invoking function.
  - Arg is passed as the argument of function.
  - Stack is the pointer to call stack of new thread.
  - All threads in a process have same pid & priority.
  - Initial thread in a process is a main thread which has tid ‘1’.
  - A process can have maximum 8 threads.

- `thread_exit()`

  - void thread_exit(void *retval)
  - Terminate the calling thread
  - Each thread save retval at thread_exit().
  - Thread state transfers to ZOMBIE.
  - Thread resources are retrieved at thread_join.
  - Exiting thread may wake up threads which have a same pid.
  


- `thread_join()`

  - thread_join(int tid, void **retval)
  - Join with terminated thread
  - If success, return 0. If there’s no thread with input tid, return -1
  - Wait thread specified with tid to terminate.
    - Caller may sleep until corresponding thread terminated.
    - If thread has already terminated, return immediately.
  - Copy the exit status of the target thread into the location pointed to by retval.
  - The call stack of the terminated thread should be freed by the calling thread.


  
### Getting thread ID

- `gettid()`

  - Returns caller’s thread ID.
  - In multi-thread process, all threads have the same PID.
  - Each thread has a unique TID within a process.
  
### Things to consider

- We assume that each thread always terminates by calling `thread_exit()`.

- If the main thread terminates or any thread calls `exit()`, whole process is terminated.
In this case, all threads should be terminated as well.
Also, address space should be freed and open files should be closed.

- When a thread calls `thread_exit()`, the thread remains in ZOMBIE state until another thread calls `thread_join()`.

- Any thread within a process can invoke `thread_join()` for another thread.

- All threads within a process should return the same process ID.
Thread IDs are guaranteed to be unique only within a process.


## Change log
### Changed files
- [proc.h](#proch)
- [proc.c](#procc)
- [defs.h](#defsh)
- [user.h](#userh)
- [usys.S](#usyss)
- [syscall.c](#syscallc)
- [sysproc.c](#sysprocc)
- [syscall.h](#syscallh)

### proc.h

Add `tid` variable in `proc` structure. It contains tid of that process.

Add `*retval` pointer in `proc` structure. It contains return value that will be used in `thread_join()`.


### proc.c

- `allocproc()`

Initialize tid to 1.

- `thread_create()`

  - Allocate thread

  Make `thread_create()` by referencing to `fork()`.

  Unlike `fork()` function, thread shares pgdir. (fork copies pgdir)

  Has same nice value and pid as current thread.

  - Moving arg to function
  
  The way that moving arg to function is using stack.

  pre-sp is pointing to stack+4096, and new sp is pointing to stack+4096-8

  stack      | sp
  ---------- | --------- |
  ...        | ← new sp(stack+4088) |
  arg        |　  |
  0xffffffff | ← pre-sp(stack+4096) |

  Set
  
  `esi`: function
  
  `eax`: 0 (initialize return value)
  
  `esp`: sp (top of stack)
  
  `ebp`: sp (for x86)

  Then, change state to `RUNNABLE`.


- `thread_exit()`

Make `thread_exit()` by referencing to `exit()`.

If tid is 1, make all threads that have same pid value to zombie, and save `retval` of main thread to `retval`.

If tid is not 1, make current thread to `ZOMBIE`, and save `retval` of current thread to `retval`


- `thread_join()`

Make `thread_join()` by referencing to `wait()`.

Return resource of `ZOMBIE` thread, change status to `UNUSED`, and return `retval` which gets from `exit()`.

If there is no thread corresponds to tid, return -1.

If there is a thread corresponeds to tid but it is running, make current process to sleep.


- `gettid()`

Return tid value of current process.

- `exit()`

Find the maximum value of tid.

If the maximum value is 1(only main thread exist), use `exit()` function

If the maximum value is not 1(there are threads), make all process that has same pid value exit.(make `ZOMBIE` state).


### defs.h

Add definition of new functions: `thread_create()` `thread_exit()` `thread_join()` `gettid()`

### user.h

Add system call for `thread_create()` `thread_exit()` `thread_join()` `gettid()`


### usys.S

Add system call for `thread_create()` `thread_exit()` `thread_join()` `gettid()`


### syscall.c

Add `thread_create()` `thread_exit()` `thread_join()` `gettid()`

### sysproc.c

Add interrupt function for `thread_create()` `thread_exit()` `thread_join()` `gettid()`


### syscall.h

Add system call number for `thread_create()` `thread_exit()` `thread_join()` `gettid()`
