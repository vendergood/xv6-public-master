# xv6 Copy on Write(COW)


## What is implemeted

- Add new system call `numfree()` which returns number of free page frames in physical memory

- When process forks,

  1. Create shared mapping to the same page frames in physical page
  
  2. Shared pages are read-only (not writable)

- When data is written to shared pages,

  1. Page fault is generated
  
  2. xv6 allocates new page frame in physical memory, and copy memory ofw original before write

- Reference counter for physical pages is needed

- Update page table after modifying page table


## Change log
### Changed files
- [vm.c](#vmc)
- [kalloc.c](#kallocc)
- [trap.c](#trapc)
- [defs.h](#defsh)
- [user.h](#userh)
- [usys.S](#usysS)
- [syscall.c](#syscallc)
- [sysproc.c](#sysprocc)
- [syscall.h](#syscallh)


### vm.c
Make `walkpgdir1` function to use `walkpgdir` function in `trap.c`

### kalloc.c

- `kmem`

Add `num_of_free_pages`(number of free pages), `reference_count[100000]`(condition for reference of each page. If 3 processes reference fourth page, reference_count[4]=3)


- `kinit`

Initialize `num_of_free_pages` `reference_count`


- `kfree`

v: virtual memory address, V2P(v): physical memory address
</br>
If physical memory address is referenced by more than 1 process, just decrease reference count.
</br>
If no process reference this physical memory address, free the memory and increase number of free pages.


- `kalloc`

This function is called when new page allocates. Make reference count 1, and decrease number of free pages.


- `numfree`

Function for returns number of free pages


- `increase_refcount`

Function for increses reference count


- `num_refcount`

Function for returns value of reference count


- `decrease_refcount`

Function for decreases reference count


### trap.c
Handling page fault(`T_PGFLT`). When process tries to write on read only page, page fault occurs.
</br>
If there is only one process that references this page, then change authority to writable.
</br>
If there are several processes that reference this page, then make new page and copy the contents, and decrease reference count.

### defs.h
Add definition of new funtions: `numfree` `increase_refcount` `num_refcount` `decrease_refcount`

### user.h
Add system call for `numfree`

### usys.S
Add system call for `numfree`

### syscall.c
Add `sys_numfree`

### sysproc.c
Add interrupt function for `numfree`

### syscall.h
Add system call number(23) for `numfree`
