# Philosophers - 42 project  

## Mandatory part - Getting started

## Bonus part - Semaphore vs Mutex

## Debugging

- [ ] If you run valgrind and get the following error, initialise your struct to 0 with memset (explanation here on [Stackoverflow](https://stackoverflow.com/questions/29870357/writing-struct-writebuf-points-to-uninitialised-bytes))

```
==7196== Syscall param write(buf) points to uninitialised byte(s)  
==7196==    at 0x4E4F371: write (write.c:27)  
==7196==    by 0x4E4E358: sem_open (sem_open.c:269)
```

- [ ] If you get an infinite loop somewhere before the end of your code, check the way you have locked and unlocked your mutex  

- [ ] If your code runs smoothly till the end (i.e. the death of a philosophers), but it gets stuck without exiting, it means there is a mutex still locked somewhere.  
Solution 1: try `pthread_detach` instead of `pthread_join`. `pthread_join` blocks if a thread has not terminated until it actually is; `pthread_detach` returns immediately without terminating the thread (you might have leaks though, because the thread is detached but keep running in the background (if you do a while loop after detaching the thread, you'll see it running in the shell, try it out!).  
Solution 2: another way to go about it and keep using `pthread_join` is to check that all mutex have been correctly unlocked


