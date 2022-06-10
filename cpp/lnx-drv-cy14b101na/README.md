# lnx-drv-cy14b101na
Simple memory mapped device driver example for the Cypress CY14B101LA/CY14B101NA
SRAM/NVRAM chip, for an ARM system.

The Cypress CY14B101LA/CY14B101NA is a fast static RAM(SRAM), with a
nonvolatile element in each memory cell.  In simple terms,
on power down, the contents of SRAM are automatically saved
to NVRAM and are persisted.

Note: Caption Obvious says, "even though this driver is written to be cross-platform,
obviously it won't work if you don't have the device, which is mapped into
the memory space."  However, you can use this an an example of how to accomplish
simular goals with your device driver.

## Building & Module Insertion

```
$ make
$ sudo insmod cy14b101na
```

## Design

This driver implements the following device: /dev/nvsram.  This device maps in
the device memory into kernel space, a memory area that is both global and persistent.
Global means that if the device is opened multiple times, the data contained within
the device is shared by all the file descriptors that opened it. Persistent means
that if the device is closed and reopened, data isn't lost.

This device can be:

- accessed and tested using conventional commands such as cp, cat, and shell I/O redirection; and
- memmapped into the user's process space;

Furthermore, the device driver:

- will politely request memory io regions, so it shows up in /proc/iomem;
- will use MINOR_DYNAMIC to automatically allocate a minor number, so fooling with devnodes; and
- will export a proc filesystem entry.

## /proc

If you have CONFIG_PROC_FS enabled, this driver will create a proc entry
that will display the physical address and size of memory mapped into
the kernel.  If you are not running on ARM, and the ioremap fails, size
will be 0:

```
$ cat /proc/driver/nvsram
physical address: 0x30000000
size            : 0
```