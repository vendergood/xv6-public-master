# xv6 Priority Scheduler


## What is implemeted

- Implement priority-based scheduler on xv6

- The lower nice value, the higher priority. The highest priority process is selected for next running

    - Tiebreak: round-robin fashion
    
- Entering scheduler when

  1. Exiting process
  
  2. Sleeping process
  
  3. Yielding CPU
  
  4. Changing priority
  
- You also have to make 2 system calls

  - getnice
  
  - setnice

- When you call fork(), the child process has the ame priority as the parent process.

- You don’t need to make or consider thread.


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

Add `nice` variable to save nice value in `proc` structure.


### proc.c

- `scheduler`

Change round robin to priority scheduling.

Find process that has smallest nice value. If there are several process that has smallest nice value, then schedule again using round robin

- `fork`

Make nice value of child same as nice value of parent

- `getnice`

Make `getnice` function. Function for get nice value of this process

- `setnice`

Make `setnice` function. Function for set nice value of this process


### defs.h

Add definition of new functions: `getnice` `setnice`

### user.h

Add system call for `getnice` `setnice`


### usys.S

Add system call for `getnice` `setnice`


### syscall.c

Add `getnice` `setnice`


### sysproc.c

Add interrupt function for `getnice` `setnice`


### syscall.h

Add system call number for `getnice` `setnice`
