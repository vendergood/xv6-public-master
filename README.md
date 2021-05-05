# xv6-public

## what is xv6

xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
Version 6 (v6).  xv6 loosely follows the structure and style of v6,
but is implemented for a modern x86-based multiprocessor using ANSI C.

ACKNOWLEDGMENTS

xv6 is inspired by John Lions's Commentary on UNIX 6th Edition (Peer
to Peer Communications; ISBN: 1-57398-013-7; 1st edition (June 14,
2000)). See also https://pdos.csail.mit.edu/6.828/, which
provides pointers to on-line resources for v6.

xv6 borrows code from the following sources:
    JOS (asm.h, elf.h, mmu.h, bootasm.S, ide.c, console.c, and others)
    Plan 9 (entryother.S, mp.h, mp.c, lapic.c)
    FreeBSD (ioapic.c)
    NetBSD (console.c)

The following people have made contributions: Russ Cox (context switching,
locking), Cliff Frey (MP), Xiao Yu (MP), Nickolai Zeldovich, and Austin
Clements.

We are also grateful for the bug reports and patches contributed by Silas
Boyd-Wickizer, Anton Burtsev, Cody Cutler, Mike CAT, Tej Chajed, eyalz800,
Nelson Elhage, Saar Ettinger, Alice Ferrazzi, Nathaniel Filardo, Peter
Froehlich, Yakir Goaron,Shivam Handa, Bryan Henry, Jim Huang, Alexander
Kapshuk, Anders Kaseorg, kehao95, Wolfgang Keller, Eddie Kohler, Austin
Liew, Imbar Marinescu, Yandong Mao, Matan Shabtay, Hitoshi Mitake, Carmi
Merimovich, Mark Morrissey, mtasm, Joel Nider, Greg Price, Ayan Shafqat,
Eldar Sehayek, Yongming Shen, Cam Tenny, tyfkda, Rafael Ubal, Warren
Toomey, Stephen Tu, Pablo Ventura, Xi Wang, Keiichi Watanabe, Nicolas
Wolovick, wxdao, Grant Wu, Jindong Zhang, Icenowy Zheng, and Zou Chang Wei.

The code in the files that constitute xv6 is
Copyright 2006-2018 Frans Kaashoek, Robert Morris, and Russ Cox.

ERROR REPORTS

Please send errors and suggestions to Frans Kaashoek and Robert Morris
(kaashoek,rtm@mit.edu). The main purpose of xv6 is as a teaching
operating system for MIT's 6.828, so we are more interested in
simplifications and clarifications than new features.

BUILDING AND RUNNING XV6

To build xv6 on an x86 ELF machine (like Linux or FreeBSD), run
"make". On non-x86 or non-ELF machines (like OS X, even on x86), you
will need to install a cross-compiler gcc suite capable of producing
x86 ELF binaries (see https://pdos.csail.mit.edu/6.828/).
Then run "make TOOLPREFIX=i386-jos-elf-". Now install the QEMU PC
simulator and run "make qemu".


## Project

### [p0: xv6 install and boot](https://github.com/contestpark/xv6-public/tree/master/p0)

- How to install and boot xv6

- Print any message in init (There is no format)

### [p1: xv6 system call](https://github.com/contestpark/xv6-public/tree/master/p1)

Make some system call related to nice value.

- `setnice()`: function for set nice value

- `getnice()`: function for get nice value

- `ps()`: function for print pid, nice, status, and name

### [p2: xv6 thread](https://github.com/contestpark/xv6-public/tree/master/p2)

Make some system call related to thread.

- `thread_create()`: function for making thread

- `thread_exit()`: function for exiting thread

- `thread_join()`: function for join thread

- `gettid()`: function for return tid(thread ID) value

### [p3: xv6 synchronization](https://github.com/contestpark/xv6-public/tree/master/p3)

Make some system call related to mutex and condition variable.

- `mutex_init()`: funtion for initng mutex

- `mutex_lock()`: function for lock mutex

- `mutex_unlock()`: function for unlock mutex

- `cond_init()`: funtion for initing condition variable

- `cond_wait()`: function for waiting condition variable

- `cond_signal()`: function for signal condition variable

### [p4: xv6 priority scheduler](https://github.com/contestpark/xv6-public/tree/master/p4)

- Change round-robin scheduler to priority-based scheduler

### [p5: xv6 page fault handler](https://github.com/contestpark/xv6-public/tree/master/p5)

- Implement page fault handler

- Increase number of stacks to 4

### [p6: xv6 copy on write (COW)](https://github.com/contestpark/xv6-public/tree/master/p6)

- Make a system call `numfree()` that returns number of free page frames in physical memory

- Implement copy on write
