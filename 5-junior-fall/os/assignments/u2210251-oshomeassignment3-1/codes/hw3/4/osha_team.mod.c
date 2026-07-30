#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
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
__used __section("__versions") = {
	{ 0x2b4dfa79, "module_layout" },
	{ 0xae2ae519, "param_ops_int" },
	{ 0x38ccd1b1, "param_ops_charp" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0x25327573, "kernel_read" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x4176d998, "filp_close" },
	{ 0x47283f92, "kernel_write" },
	{ 0x37a0cba, "kfree" },
	{ 0xd6729abe, "filp_open" },
	{ 0x656e4a6e, "snprintf" },
	{ 0xa3859b3a, "kmem_cache_alloc_trace" },
	{ 0xbb49aaf1, "kmalloc_caches" },
	{ 0x92997ed8, "_printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "81733F710F4124180CBE1C3");
