#Assignment Description 

###Static Control Flow and the Stack

1. Part one of the assignment was to write if and loops in assembly. We were given A6-1.c and were asked to translate that into assembly (A6-1a.s)

2. The second part of the assignment was to translate Assembly into C. The given files were A6-3a.s and A6-3b.s and the translated files are A6-3a.c and A6-3b.c

3. Part 3 of the assignment was split into 2 parts. First take copy.c and change it into assembly. Since copy.c has a buffer-overflow bug we want to see how a hacker can use this to gain control of your computer. In stack_smash.s is the assembly code where we overwrite the return address of a function in the stack and then make it run whatever we want. In this case we changed all the register values to -1. 