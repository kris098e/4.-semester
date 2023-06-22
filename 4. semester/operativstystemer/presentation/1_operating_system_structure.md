**Services provided**
Draw the structure illustrated in book
- Interface to operating system
- Systemcalls with their types
    - Process control
    - File management
    - Device management
    - Information Maintnance
    - Communication
    - Protection   
**Services**
- File management
- Accounting
- File systems
- programming language support
- Program loading and execution
- Communication
- Background services
- I/O operations
- Resource allocation
**Hardware**
**why applications are operating-system specific**
- Different system calls
    - Different APIs
- File format (ELF, ABI)
- Different CPU instructions
**How to run on multiple systems**
- Interpreters
- Virtual machines
- Standard language or using same API
**Design**
- Policy and Mechanisms
**Operating system structure**
- Monolithic
- Layered approach (easy to test)
- Microkernels (easy to extend, userspace)
- Hybrid systems
**Boot**
- BIOS, UEFI (bootloaders)
**debugging**
- Memory dump
- Counter: `/proc`
- Tracing: Systemcalls
