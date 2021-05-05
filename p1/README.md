# xv6 System call


## What is implemeted

- Implement 3 new system calls

- The default nice value is 20. Lower nice values cause more favorable scheduling.
The range of valid nice value is 0~39.

### getnice

- The getnice function obtains the nice value of a process.

- Return the nice value of target process on success. Return -1 if there is no process corresponding to the pid.

  
### setnice

- The setnice function sets the nice value of a process.

- Return 0 on success. Return -1 if there is no process corresponding to the pid or the nice value is invalid.

### ps

- The ps function prints out process(s)’s information, which includes pid, nice, status, and name of each process.
If the pid is 0, print out all processes' information.
Otherwise, print out corresponding process’s information.
If there is no process corresponding to the pid, print out nothing.

- No return value.


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
- [getnice.c](#getnicec)
- [setnice.c](#setnicec)
- [ps.c](#psc)
- [Makefile](#makefile)

### proc.h

Add `nice` variable that contains priority of the process.


### proc.c

- `allocproc()`

`allocproc()` is function that related to allocating process.

Initialize nice value. Default value is 20.


- `getnice()`

Make system call `getnice()`

If there is a process that corresponds to the pid, return nice value of the process.

Else, return -1.

- `setnice()`

Make system call `setnice()`

If there is a process that corresponds to the pid and the nice value of that process is between 0 and 39, return 0.

Else, return -1.

- `ps()`

Make system call `ps()`

If pid is zero, print all the process.

If there is process that corresponds to the pid, print pid, nice, status, and name.

Else, do not print anything.



### defs.h

Add definition of new functions: `getnice()` `setnice()` `ps()`

### user.h

Add system call for `getnice()` `setnice()` `ps()`


### usys.S

Add system call for `getnice()` `setnice()` `ps()`


### syscall.c

Add `getnice()` `setnice()` `ps()`


### sysproc.c

Add interrupt function for `getnice()` `setnice()` `ps()`


### syscall.h

Add system call number for `getnice()` `setnice()` `ps()`

### getnice.c

Make `getnice.c` to execute system call `getnice()` function in qemu-nox.

If we call

```
$ getnice
```

in qemu-nox simulator, we can execute `getnice()` function.


### setnice.c

Make `getnice.c` to execute system call `setnice()` function in qemu-nox.

If we call

```
$ setnice <pid> <value>
```

in qemu-nox simulator, we can execute `setnice()` function.


### ps.c

Make `ps.c` to execute system call `ps()` function in qemu-nox.

If we call

```
$ ps <pid>
```

in qemu-nox simulator, we can execute `ps()` function.


### Makefile

To execute `getnice.c` `setnice.c` `ps.c`, we have to add

```
_getnice\
_setnice\
_ps\
```

in `UPROGS` of Makefile


