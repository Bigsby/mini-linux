#! /bin/sh

./compile.sh

qemu-system-x86_64 -curses -no-reboot -m 64M -kernel builds/linux/bzImage -initrd builds/fs/init.cpio.gz -append "panic=20 quiet"
