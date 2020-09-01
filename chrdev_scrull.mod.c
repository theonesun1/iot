#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x945ce7d8, "module_layout" },
	{ 0x7e41b4ff, "class_destroy" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x8a94638d, "cdev_del" },
	{ 0x327de545, "device_destroy" },
	{ 0xa3843e32, "device_create" },
	{ 0xa5e2d55a, "cdev_add" },
	{ 0x2c7249e3, "cdev_init" },
	{ 0x972cb2f3, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xf4fa543b, "arm_copy_to_user" },
	{ 0x5f754e5a, "memset" },
	{ 0x7c32d0f0, "printk" },
	{ 0x28cc25db, "arm_copy_from_user" },
	{ 0xefd6cf06, "__aeabi_unwind_cpp_pr0" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "630E7DA89DA13C81FE7E99F");
