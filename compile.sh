# Create a directory which will be our ISO root.
mkdir -p iso_root

# Copy the relevant files over.
mkdir -p iso_root/boot
cp -v bin/piss iso_root/boot/ -r
mkdir -p iso_root/boot/limine
cp -v limine.conf limine/limine-bios.sys limine/limine-bios-cd.bin \
      limine/limine-uefi-cd.bin iso_root/boot/limine/

# Create the EFI boot tree and copy Limine's EFI executables over.
mkdir -p iso_root/EFI/BOOT
cp -v limine/BOOTX64.EFI iso_root/EFI/BOOT/
cp -v limine/BOOTIA32.EFI iso_root/EFI/BOOT/

# Create the bootable ISO.
xorriso -as mkisofs -R -r -J -b boot/limine/limine-bios-cd.bin \
        -no-emul-boot -boot-load-size 4 -boot-info-table -hfsplus \
        -apm-block-size 2048 --efi-boot boot/limine/limine-uefi-cd.bin \
        -efi-boot-part --efi-boot-image --protective-msdos-label \
        iso_root -o image.iso

# Install Limine stage 1 and 2 for legacy BIOS boot.
./limine/limine bios-install image.iso

# Create an empty zeroed-out 64MiB image file.
dd if=/dev/zero bs=1M count=0 seek=64 of=image.hdd

# Create a partition table.
PATH=$PATH:/usr/sbin:/sbin sgdisk image.hdd -n 1:2048 -t 1:ef00 -m 1

# Download the latest Limine binary release for the 9.x branch.
git clone https://github.com/limine-bootloader/limine.git --branch=v9.x-binary --depth=1

# Build "limine" utility.
make -C limine

# Install the Limine BIOS stages onto the image.
./limine/limine bios-install image.hdd

# Format the image as fat32.
mformat -i image.hdd@@1M

# Make relevant subdirectories.
mmd -i image.hdd@@1M ::/EFI ::/EFI/BOOT ::/boot ::/boot/limine

# Copy over the relevant files.
mcopy -i image.hdd@@1M bin/piss ::/boot
mcopy -i image.hdd@@1M limine.conf limine/limine-bios.sys ::/boot/limine
mcopy -i image.hdd@@1M limine/BOOTX64.EFI ::/EFI/BOOT
mcopy -i image.hdd@@1M limine/BOOTIA32.EFI ::/EFI/BOOT