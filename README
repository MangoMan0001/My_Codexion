*This project has been created as part of the 42 curriculum by ayhirose.*

# Codexion

## Description
This project simulates the "Dining Philosophers" problem to master concurrency and synchronization control in C.

**Common Goals**
- Understand programs, processes, threads, and registers.
- Implement necessary synchronization controls for concurrent processing.
- Optimize resource allocation using scheduling algorithms (FIFO / EDF).
- Implement a priority queue using a Min-Heap structure.

**Personal Goal**
- Implement polymorphism-like behavior in C, mimicking object-oriented programming patterns.

## Directory Structure
```text
.
├── Makefile                # Build configuration (all, clean, fclean, re, run, etc.)
├── README.md               # Project documentation
├── include/
│   └── codexion.h          # Header file (Struct definitions, Prototypes)
└── coders/                 # Source code directory
    ├── core/               # [Initialization & Main Control]
    │   ├── main.c          # Entry point
    │   ├── codexion.c      # Main flow control & cleanup
    │   ├── init.c          # Initialization of structs, mutexes, and threads
    │   └── validate.c      # Argument validation
    ├── scheduler/          # [Scheduling Logic]
    │   ├── scheduler.c     # Arbitration logic (FIFO / EDF)
    │   └── heap.c          # Priority Queue (Min-Heap) implementation
    ├── simulation/         # [Thread Routine & Simulation]
    │   ├── simulation.c    # Thread creation and joining
    │   ├── routine.c       # Coder's life cycle (Compile -> Debug -> Refactor)
    │   ├── compile.c       # Compilation logic (Mutex locking & deadlock prevention)
    │   └── subroutine.c    # Monitor thread (Burnout detection & termination)
    └── utils/              # [Utilities]
        ├── time.c          # Time management (gettimeofday wrapper)
        ├── clean.c         # Memory freeing & Mutex destruction
        └── utils.c         # Helper functions

### Instructions


1. **Compilation**
```bash
make
```

2. **Execuion**
```bash
./codexion [coders] [burnout] [compile] [debug] [refactor] [must_compile] [cooldown] [scheduler]
```
Arguments:

coders: Number of coders (and dongles).

time_to_burnout: Time in ms before a coder burns out if they havent started compiling.

time_to_compile: Duration of compilation in ms.

time_to_debug: Duration of debugging in ms.

time_to_refactor: Duration of refactoring in ms.

must_compile_count: Number of times each coder must compile to stop the simulation (0 for infinite).

dongle_cooldown: Cooldown time in ms after returning a dongle.

scheduler: Arbitration policy (fifo or edf).

Example:
```bash
./codexion 5 910 200 200 200 7 100 edf
```

## Additional sections

### Blocking cases handled
To ensure a robust simulation, the following concurrency issues have been addressed:

**Deadlock Prevention**
The system checks if the required USB dongles are available and assesses the coder's priority based on burnout status before attempting to acquire resources. If the conditions are not met, the coder waits without holding any resources. This breaks Coffman's "Hold and Wait" condition, effectively preventing deadlocks.

**Starvation Prevention**
The EDF (Earliest Deadline First) scheduler ensures that coders closest to burnout are prioritized for USB access. While FIFO is also implemented, the high processing speed of the simulation means starvation is rare even with simple queuing.

**Cooldown Handling**
Dongle availability is verified within the can_i_get_the_usb function, which strictly enforces the cooldown period before a dongle can be reacquired.

**Precise Burnout Detection**
An independent monitor thread checks the status of all coders every 1ms, ensuring that burnout is detected and reported within the required 10ms tolerance.

**Log Serialization**
The global_lock mutex controls all calls to printf, ensuring that log messages are serialized and do not interleave or scramble.

### Thread synchronization mechanisms
**Condition Variables vs. Sleep**
To manage waiting threads efficiently, Condition Variables (pthread_cond_t) are used instead of usleep. This allows threads to sleep while waiting for resources and be dynamically woken up precisely when needed, reducing unnecessary CPU usage.

**Mutex Management Strategy**
While each dongle has its own Mutex, the coder threads themselves decide whether they can acquire the dongles before attempting to lock them. This means threads rarely block on the dongle mutexes themselves, preventing chain-blocking.

**Centralized Data Management**
All shared information is defined in a rule structure. Access to this data is universally protected by a single global_lock. Managing all shared states with one central mutex simplifies data management and makes it significantly easier to prevent race conditions.

### Resources
AI Tools (Gemini)
- Design template creation.
- Error log analysis.
- Docstring generation.

References
- Literature on the Dining Philosophers problem (assignment understanding).
