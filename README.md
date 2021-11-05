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

- [ ] If your code runs smoothly till the end (i.e. the death of a philosophers), but it gets stuck without exiting, the problem lies in `pthread_join`. `pthread_join` blocks if a thread has not terminated until it actually is, and does not return; use `pthread_detach` instead, it returns immediately without terminating the thread though.


