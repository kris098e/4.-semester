[[ch02_linux_modules.pdf]]

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

# kommet til side 12
