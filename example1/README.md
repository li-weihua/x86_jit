# simple jit example

## main workflow
1. generate machine code. (ommit here!)
2. use *mmap* malloc RWE memory.
3. copy machine code to the mapped memory.
4. cast mapped memory to appropriate function pointer, then run function.