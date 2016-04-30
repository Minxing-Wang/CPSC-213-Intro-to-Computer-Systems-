#Assignment Description 

###Synchronization (Mutex and Semaphores)

1. First part of the assignment we were asked to reimplement the producer and consumer problem from assignment 8 using mutexes instead of spinlocks. (pc_mutex_cond.c)

2. In part 2 of the assignment we were given the smokers problem where there is a dealer and he can only produce 2 out of the three items (paper, match or tobacco). There are 3 smokers and each of them has an unlimited supply of one of the items. Using mutexes and conditional variables we were asked to find a way to let all the smokers smoke without causing deadlock. (smoke.c)

3. In the last part of the assignment we were given the producer and consumer problem again but we were asked to implement it using semaphores instead of mutexes or spinlocking. 