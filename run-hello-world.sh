#! /bin/sh

echo "Installing necessary packages"
sudo apt install gcc make bison build-essential flex git libelf-dev libssl-dev ncurses-dev qemu qemu-system-x86

if [ ! -d "builds" ]; then
    mkdir builds
    mkdir builds/linux
    mkdir builds/hello
    mkdir builds/fs
fi

echo "\n\n"
echo "Checking Linux Kernel"

if [ ! -d "linux" ]; then
    echo "Cloning Linux Kernel Repo"
    git clone https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git
fi

echo "Building Linux Kernel"

cd linux
make x86_64_defconfig
make -j $(nproc)
cd ..
cp linux/arch/x86/boot/bzImage builds/linux/


echo "\n\n"
echo "Build Init"

cd hello
make 
cd ..

cd builds/hello/
find . | cpio -o -H newc | gzip > ../fs/hello.cpio.gz
cd ../../

qemu-system-x86_64 -curses -no-reboot -kernel builds/linux/bzImage -initrd builds/fs/hello.cpio.gz -append "panic=1 quiet"
