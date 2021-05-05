# xv6 Page fault handler


## What is implemeted

- Initial size of stack: Prepare 1 page initially. Can be grow up to 4 pages

- Growth of stack: tf->esp can move up to 32bytes. New page should be allocated to this process if current stack is full

- When stack pointer reaches guard page or a process accesses invalid address, kill that process

- Print out “Invalid access” when approaching abnormal address

- Print out “Allocate page” if page-fault handler is executed normally

address space |
--------- |
heap |
stack1(init) |
stack2 |
stack3 |
stack4 |
guard page |

## Change log
### Changed files
- [proc.h](#proch)
- [exec.c](#execc)
- [proc.c](#procc)
- [vm.c](#vmc)
- [trap.c](#trapc)


### proc.h

Make `stack_start` in `proc` structure to save starting point of virtual stack of that process.


### exec.c

When process starts, allocate guard page and stack as `PGSIZE`(=4096) and make guard page inaccessible.

Save starting point of stack to `sp` and `start_stack`

Save all size of stack and guard page size(in this case, it is same as starting point of stack) to `sz`


### proc.c

When process is forked, make child's `stack_start` value to parent's `stack_start` value.

Add `stack_start` value to `copyuvm`.


### vm.c

- Change definition of `copyuvm`

Change

```
copyuvm(pde_t *pgdir, uint sz)
```

to

```
copyuvm(pde_t *pgdir, uint sz, uint stack_start)
```

So we have to change defs.h ... that connected to `copyuvm` function.

- Modify the way that `copyuvm` mapping virtual memory to physical memory

`copyuvm` is function that connects virtual memory to physical memory.

In the past, there there was only one stack so we allocated stack and guard page consecutively.

Now the stack and guard pages are not contiguous, so we have to map them separately to physical memory.


### trap.c
Add page fault handler for 14 trap `T_PGFLT`

If the value in cr2 register overs heap or touches guard page, print "Invalid access" and terminate the procees.

Else, if return value of allocuvm is zero(error that mem overs `KERNBASE`..), print "Invalid access" and terminate the procees.

Else, allocate new page.
