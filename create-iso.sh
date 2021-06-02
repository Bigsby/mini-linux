#! /bin/sh

./compile.sh

echo "Installing necessary packages"
sudo apt install grub-common xorriso grub-pc-bin

if [ ! -d "builds/iso" ]; then
    mkdir -p builds/iso/boot/grub
fi



echo "\n\nCreating GRUG config"

cat << EOF > builds/iso/boot/grub/grub.cfg

menuentry "Bigsby Linux" {
    linux /boot/bzImage quiet 
    initrd /boot/init.cpio.gz
}

menuentry "Bigsby Linux - Verbose" {
    linux /boot/bzImage initramfs_async=0  
    initrd /boot/init.cpio.gz
}
EOF


echo "\n\nCopying kernel and CPIO"
cp builds/linux/bzImage builds/fs/init.cpio.gz builds/iso/boot/

echo "\n\nCreating ISO"
grub-mkrescue -o builds/bigsby-linux.iso builds/iso

