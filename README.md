# Mini Linux

A minimal Linux running system consisting only of the kernel and a small init program.

> For systems not using `apt` change `run.sh` to use existing package manager
> For *x86_64* system only



To just compile kernel and RAM disk;
```
./compile.sh
```

This will:
- Install needed packages, if not installed
- Clone Linux kernel repository
- Build Linux kernel
- Build Init program
- Create [CPIO](https://linux.die.net/man/1/cpio) archive of the file system containing `init`



To run in QEMU:
```sh
./run.sh
```

This will:
- Run `compile.sh`
- Run `QEMU` in _curses_ mode using built kernel and init.



To create bootable ISO:
```sh
./create-iso.sh
```

This will:
- Run `compile.sh`
- Create a bootable ISO in `builds/bigsby-linux.iso`.



## Exemple output
```
 ___ _         _
| _ |_)__ _ __| |__ _  _
| _ \ / _` (_-< '_ \ || |
|___/_\__, /__/_.__/\_, |
      |___/         |__/

Welcome to Bigsby Linux

Bigsby Linux v0.0.2

Available commads:
    info            display system information
    ls              list filesystem content
    clear           clear screen
    help            print this help
    quit            exit system
>
```

```
> info
Uptime:         189     seconds
Total RAM:      36581376        bytes
Free RAM:       20336640        bytes
Proc count:     41
```

```
> ls
d .
d ..
- init
d root
d dev
```
