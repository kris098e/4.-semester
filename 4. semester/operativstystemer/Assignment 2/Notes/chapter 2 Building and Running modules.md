[[ch02_linux_modules.pdf]]

****
**LOOK AT THE BOTTOM OF THE CHAPTER FOR ALL THE USED HEADER FILES AND CODE EXPLANATION**
****

code for hello world kernel: [[ch02_linux_modules.pdf#page=2]]
* Module_init
* Module_exit
* MODULE_LICENSE has to be included, as this says it is free

 make: [[ch02_linux_modules.pdf#page=3]]

make kernel files: [[ch02_linux_modules.pdf#page=9]]

* Modules are loaded via commands and unloaded via commands. When loaded the `Module_init()` is invoked. When unloaded the `Module_exit()` is invoked, which has to do all the cleanup, such we dont have reboot the system to get rid of what the module has done altogether.
* Only source code from the kernel may be imported to kernel-modules, only special cases they should not be
* seg-faults may take down the entire system or the process, as there are no debugger such as in applications
* kernel can have several levels of security, where kernel has highest priority and can do what it want (privileged) and user-mode is of course then lower than this
* user-space and kernel-space may have different memory mappings, i.e what we did with `acess_ok()` was mapping userspace address to kernel-space
* Can access which process has called a specific systemcall by `<asm/current.h>` which yields a pointer to `struct task_struct`, defined by `<linux/sched.h>`.

* A specific process is called when loading the new module into the kernel, which will invoke the `Module_init()`.

* Have to build the module for the specific kernel version. When the kernel module is being maked i.e to the `$MODULENAME.o` , it is linked against `vermagic.o` if this fails, some versioning of the module is wrong for the kernel-version. Errors are printed to the `/var/log/messages` to see what went wrong. This can usually be solved by updating the `KERNELDIR`.
* in the `linux/module.h`-file versions for this linux is displayed and can be used, if imported in the module
* `Kernel-modules` are also platform dependant, i.e the module may only be compatible with a specific distro. But the license can changed such that we say that the distro is for the **mainline-linux**
* Module-stacking, other modules may use something from other modules. I.e they are dependent on eachother.
* using `modprobe` as commandline arugment instead of `ìnsmod` will also load all the modules that the module is dependant on
	* `modprobe` only looks in the _standard installed module directories_


# Preliminaries
* These header files must live inside each module source code:
	* `#include <linux/module.h>`
	* `#include <linux/init.h>`
* May also include
	* `moduleparam.h`
* `MODULE_LICENSE("gpl")` should be used
	* The specific licenses recognized by the kernel are “GPL” (for any version of the GNU
		General Public License), “GPL v2” (for GPL version two only), “GPL and additional
		rights,” “Dual BSD/GPL,” “Dual MPL/GPL,” and “Proprietary.”

Other descriptive definitions that can be contained within a module include
MODULE_AUTHOR (stating who wrote the module), MODULE_DESCRIPTION (a human-readable statement of what the module does), MODULE_VERSION (for a code revision number; see the comments in <linux/module.h> for the conventions to use in creating
version strings), MODULE_ALIAS (another name by which this module can be known),
and MODULE_DEVICE_TABLE (to tell user space about which devices the module supports). We’ll discuss MODULE_ALIAS in Chapter 11 and MODULE_DEVICE_TABLE in
Chapter 12.

# Init
see chapter **Initialization and shutdown**
* \_\_init 
* \_\_initdata
* \_\_module_init
	* mandatory to include
* \_\_exit
* module\_exit()

* If module depends on other modules that cannot be loaded, the code can be used. It uses `goto` statements for handling failues.  Unroll those that has been added. Return errors from the `errno.h` file.
```c
int __init my_init_function(void)
{
 int err;
 /* registration takes a pointer and a name */
 err = register_this(ptr1, "skull");
 if (err) goto fail_this;
 err = register_that(ptr2, "skull");
 if (err) goto fail_that;
 err = register_those(ptr3, "skull");
 if (err) goto fail_those;
 return 0; /* success */
 fail_those: unregister_that(ptr2, "skull");
 fail_that: unregister_this(ptr1, "skull");
 fail_this: return err; /* propagate the error */
 }
```
* CLeanup also has to **unregister** the modules loaded
```c
void __exit my_cleanup_function(void)
{
 unregister_those(ptr3, "skull");
 unregister_that(ptr2, "skull");
 unregister_this(ptr1, "skull");
 return;
}
```
* can have cleanup function specified here [[ch02_linux_modules.pdf#page=20]]
	* cannot have \_\_exit in the function for cleanup if its not for exiting
* The kernel may use the code immediately after the module has completed the first line of codes in the `init` function, therefore has to be concurrent. Be careful when failing, as the calls to the module may then be comprimised and the kernel will be in some unstable state


# Module parameters
can pass parameters. I.e `insmod hellop howmany=10 whom="Mom"`
```c
static char *whom = "world";
static int howmany = 1;
module_param(howmany, int, S_IRUGO);
module_param(whom, charp, S_IRUGO);
```
Many types can be used. See the page for this chapter

_The final module_param field is a permission value; you should use the definitions
found in <linux/stat.h>. This value controls who can access the representation of the
module parameter in sysfs. If perm is set to 0, there is no sysfs entry at all; otherwise,
it appears under /sys/module* with the given set of permissions. Use S_IRUGO for a
parameter that can be read by the world but cannot be changed; S_IRUGO|S_IWUSR
allows root to change the parameter. Note that if a parameter is changed by sysfs, the
value of that parameter as seen by your module changes, but your module is not
notified in any other way. You should probably not make module parameters writable, unless you are prepared to detect the change and react accordingly._