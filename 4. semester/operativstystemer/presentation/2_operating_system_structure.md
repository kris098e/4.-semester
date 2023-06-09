# Overall structure of operating systems
## Services provided
Draw the structure illustrated in book
- Interface to operating system
- Systemcalls
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

# why applications are operating-system specific
- Different system calls
    - Different APIs
- File format (ELF, ABI)
- Different CPU instructions
## How to run on multiple systems
- Interpreters
- Virtual machines
- Standard language or using same API

# Design
- Policy and Mechanisms (Implementation)

# Operating system structure
- Monolithic
- Layered approach
- Microkernels
- Hybrid systems

# Boot
- BIOS, UEFI

# Operating System Debugging
- Memory dump
- Counter: `/proc`
- Tracing: Systemcalls
