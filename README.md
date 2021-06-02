# Mini Linux

A minimal Linux running system consisting only of the kernel and a small init program.

To run:
```sh
./run.sh
```
> For systems not using `apt` change `run.sh` to use existing package manager

This will:
- Install needed packages, if not installed
- Clone Linux kernel repository
- Build Linux kernel
- Build Init program
- Create [CPIO](https://linux.die.net/man/1/cpio) archive of the file system containing `init`
- Run `QEMU` in _curses_ mode using built kernel and init.
