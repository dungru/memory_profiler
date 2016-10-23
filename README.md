Memory Profiler
===== 

# How to Run a Example

1. Choose the following one malloc lib  
- **make tm=ltalloc** 
-  **make tm=scalloc**
-  **make tm=glibc**
2. **./main_test**

# Note 
## How to add your malloc
- Put your malloc code under **src** folder.
- Following the LTALLOC as tempalate to modify the **Makefile** 

## How to add your test pattern
- Put your testing code under **src** folder.
- Modify the makefile: add file path after ```$(MEMORY_PROFILER_PATCH_PATH)/src/main_test.c```

## Run simulation faster
- If you have enough memory, you can modify **#define NUM_OF_CELL** number in ```ringbuffer.h``` for more lager memory space.  

## Scalloc User
- Execute **scalloc_config.sh**before build the code.
- **make tm=scalloc**
- In Ubuntu, cannot allocate memory in static TLS block is known issue.

## PROPRIETARY_LOGGING
- When you need the extra memory profile information or custom information, you need change the **PROPRIETARY_LOGGING** to **1** in ```ringbuffer.h.```  
- Modify the ```malloc_count.cpp``` to add your logging method in the macro ```PROPRIETARY_LOGGING```
## Logging system Introduction
- We logging the message by a **reader thread**.
- Before execute the **main()**, the pre config environment is in ```static __attribute__((constructor)) void init(void)```
- Before finish the main_thread, It will run the ```static __attribute__((destructor)) void finish(void)```
- About the ```malloc_count.cpp``` is porting from [malloc_count](https://panthema.net/2013/malloc_count/).
You can reference this site for more detail.
- Now the profiler only support the SPSC.
