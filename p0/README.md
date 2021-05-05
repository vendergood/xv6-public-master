# xv6 Install and boot


## Intall and boot

### Download xv6

```
$ wget https://github.com/contestpark/xv6-public.git
```

### Install qemu emulator

```
$ sudo apt install qemu
```

### Run xv6

```
$ cd p0
$ make qemu-nox // or $ make qemu
```

### Terminate xv6

ctrl + ‘a’ + ‘x’ (keep press all keys)

Or

```
$ halt
```

## What is implemeted

- Print any message(optional) (There is no format)


## Change log
### Changed files
- [init.c](#initc)


### init.c

Add any message like

```
printf(1, "======= Hello World! =======\n");
```

right after

```
printf(1, "init: starting sh\n");
```


