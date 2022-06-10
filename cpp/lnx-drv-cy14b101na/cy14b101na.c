// SPDX-License-Identifier: GPL-2.0-only
/*
 * CY14B101NA driver for Linux.
 *
 * Copyright (C) 2019 Joe Turner <joe@agavemountain.com>
 *
 * The Cypress CY14B101LA/CY14B101NA is a fast static RAM(SRAM), with a
 * nonvolatile element in each memory cell.
 *
 * The data are supplied as a (seekable) character device, /dev/nvsram. The
 * size of this file is dependent on the controller.
 */
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/ioctl.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Joe Turner");
MODULE_DESCRIPTION("CY14B101LA/CY14B101NA SRAM/NVRAM driver");
MODULE_SUPPORTED_DEVICE("nvsram");

#define DEVICE_NAME "nvsram"

/**
 * 1-Mbit (128 K × 8/64 K × 16) nvSRAM
 */
#define NVSRAM_SIZE (0x20000)
#define NVSRAM_BASE_ADDR 0x30000000
#define NVSRAM_VERSION "0.1"

static ssize_t nvram_size = NVSRAM_SIZE;

/**
 * virtual pointer to io memory
 */
void __iomem *io_nvsram = NULL;
void *nvram_cache = NULL;

static loff_t nvsram_llseek(struct file *file, loff_t offset, int origin)
{
	loff_t newpos;

	switch (origin) {
	case 0: /* SEEK_SET */
		newpos = offset;
		break;

	case 1: /* SEEK_CUR */
		newpos = file->f_pos + offset;
		break;

	case 2: /* SEEK_END */
		newpos = NVSRAM_SIZE + offset;
		break;

	default: /* can't happen */
		return -EINVAL;
	}
	if (newpos < 0)
		return -EINVAL;
	file->f_pos = newpos;
	return newpos;
}

/**
 *  @brief This function is called whenever device is being read from user space i.e. data is
 *  being sent from the device to the user.
 *
 *  User issues a read of the device.  We have to make sure we handle
 *  unaligned access via mapped io memory, etc.
 *
 *  We want to be able to hex dump, copy, etc., the sram/nvram data for backing up or
 *  overwritting sram/nvram.
 *
 * </code>
 * $ cat /dev/nvsram > nvsram.backup
 * $ cp /dev/nvsram nvsram.backup
 * $ hexdump -C /dev/nvsram
 * </endcode>
 *
 * or even clone nvsram from one device to another vi network:
 *
 * </code>
 * $ scp /dev/nvsram <user>@<remote ip>:/dev/nvsram
 * </endcode>
 *
 *  @param file     A pointer to a file object (defined in linux/fs.h)
 *  @param buf      The pointer to the user-space buffer to which this function writes the data
 *  @param count    The length of the user's buffer
 *  @param ppos   The offset if required
 *
 *  @returns
 *  This function returns the number of bytes read (copied from the io memory region),
 *  or a negative integer (error code).
 */
static ssize_t nvsram_read(struct file *file, char __user *buf, size_t count,
			   loff_t *ppos)
{
	unsigned long ret;

	memcpy_fromio(nvram_cache, io_nvsram, count);

	ret = copy_to_user(buf, nvram_cache, count);
	return ret;
}

static ssize_t nvsram_write(struct file *file, const char __user *buf,
			    size_t count, loff_t *ppos)
{
	unsigned long ret;
	ret = copy_from_user(nvram_cache, buf, count);
	memcpy_toio(io_nvsram, nvram_cache, count);
	return ret;
}

static long nvsram_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	if (!io_nvsram) {
		return -ENODEV;
	}

	switch (cmd) {
	default:
		return -ENOTTY;
	}

	return -ENOTTY;
}

static int nvsram_open(struct inode *inode, struct file *file)
{
	if (!io_nvsram) {
		return -ENODEV;
	}
	return 0;
}

static int nvsram_release(struct inode *inode, struct file *file)
{
	return 0;
}

#ifndef CONFIG_PROC_FS
static int nvsram_add_proc_fs(void)
{
	return 0;
}

static void nvsram_remove_proc_fs(void)
{
	return;
}

#else

static void nvsram_remove_proc_fs(void)
{
	remove_proc_entry("driver/nvsram", NULL);
}

static int nvsram_proc_read(struct seq_file *seq, void *offset)
{
	seq_printf(seq, "physical address: 0x%X\n", NVSRAM_BASE_ADDR);

	if (!io_nvsram) {
		seq_printf(seq, "size            : %d\n", (int)0);
	} else {
		seq_printf(seq, "size            : %d\n", (int)nvram_size);
	}

	return 0;
}

static int nvsram_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, nvsram_proc_read, NULL);
}

static const struct file_operations nvram_proc_fops = {
	.owner = THIS_MODULE,
	.open = nvsram_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int nvram_add_proc_fs(void)
{
	if (!proc_create("driver/nvsram", 0, NULL, &nvram_proc_fops))
		return -ENOMEM;
	return 0;
}

#endif /* CONFIG_PROC_FS */

static const struct file_operations nvsram_fops = {
	.owner = THIS_MODULE,
	.llseek = nvsram_llseek,
	.read = nvsram_read,
	.write = nvsram_write,
	.unlocked_ioctl = nvsram_ioctl,
	.open = nvsram_open,
	.release = nvsram_release,
};

static struct miscdevice nvsram_dev = {.minor = MISC_DYNAMIC_MINOR,
				       .name = "nvsram",
				       .fops = &nvsram_fops };

static int __init init_nvsram(void)
{
	int err = -ENOMEM;
	int ret;

	ret = misc_register(&nvsram_dev);
	if (ret) {
		printk(KERN_ERR "nvsram: can't misc_register.\n");
		goto fail;
	}

	ret = nvram_add_proc_fs();
	if (ret) {
		printk(KERN_ERR "nvsram: can't create /proc/driver/nvram\n");
		goto outmisc;
	}

	if (request_mem_region(NVSRAM_BASE_ADDR, NVSRAM_SIZE, DEVICE_NAME)) {
		printk("nvsram: memory already in use\n");
		return -EBUSY;
	}

    /*
    * remap memory area at NVSRAM_BASE_ADDR,
    * size NVSRAM_SIZE, so that we can access it.
    */
	io_nvsram = ioremap(NVSRAM_BASE_ADDR, NVSRAM_SIZE);

	pr_info("Hybrid Non-volatile memory driver CY14B101NA v" NVSRAM_VERSION
		"\n");

	nvram_cache = kmalloc(NVSRAM_SIZE, GFP_KERNEL);

	if (io_nvsram) {
		printk(KERN_INFO "nvsram base address (0x%X) successfully "
				 "mapped to %p.\n",
		       NVSRAM_BASE_ADDR, io_nvsram);
	} else {
        /**
         * Failed to map memory; this is probably x86/64.
         */
		pr_err("nvsram base address (0x%X) could not be mapped.\n",
		       NVSRAM_BASE_ADDR);
	}

	return 0; // success.

outmisc:
	misc_deregister(&nvsram_dev);

fail:
	return err;
}

static __exit void cleanup_nvsram_module(void)
{
	nvsram_remove_proc_fs();
	misc_deregister(&nvsram_dev);
	if (io_nvsram) {
		iounmap(io_nvsram);
		release_mem_region(NVSRAM_BASE_ADDR, NVSRAM_SIZE);
	}
	kfree(nvram_cache);
	printk(KERN_INFO "nvsram unloaded.\n");
}

module_init(init_nvsram);
module_exit(cleanup_nvsram_module);
