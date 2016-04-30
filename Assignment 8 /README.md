#Assignment Description 

###IO, Asynchrony and Threads

1. First part of the assignment we had to use multiple ways to perform a disk read. The files aRead.c, sRead.c and tRead.c do the same thing but with different implementation. ARead.c does the read asynchronously. SRead does the read sequentially and tRead.c does the read with threads to hide asynchrony. 

2. The last part of this assignment was to implement the functions produce, consume, producer and consumer. Since producers and consumers can't add and take away items at the same time we have to ensure that they're probably synchronized. In this case, we used spinlocks to ensure mutual exlusion (pc_spinlock.c)