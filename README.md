# Philosophers - 42 project  

## Mandatory part - Getting started  

Philosophers is a project about multi-threading programming, synchronisation and performance.  

### Multi-threading
A thread is a routine that keeps running in the background until terminated or interrupted.  
Threads share resources, and have access to resources once at a time.  
  
Real life example: with our mobile, we can both listen to music and receive notifications; the music player and the notification app both share the resource "sound": when we get a text, the music player will stop for a sec, the notification pop-up will ring and then free the resource "sound" again.

In philosophers, each person has a thread routine (eat-sleep-think), and forks are the shared resources.  
To avoid forks being used by more philosophers at once, we block the access with `mutex_lock()`, and we `mutex_unlock()` when we are done.
Once the routine is implemented with the right order of actions and mutexes at the right place, we need to think about synchronisation.  
You will check for death in a function parallel to the thread execution.

### Synchronisation
All threads and the check_death function need to run as parallel as possible, and thus start at the same time.

- [ ] use a flag `philo->start` to delay the execution until all threads are created
- [ ] delay odds philosophers, so that forks will be free for even philos to use, and then they can swap again.  Possible delayed time are `time2eat * 0.5` or `time2eat * 0.9 + 1`, respectively waiting until the first batch is halfway through their meal, or until they're 99% done with their meal  
- [ ] the function check_death needs to manage time like a swiss clock, checking as fast as possible if all philos are well and alive, so performances must be optimized.

### Performance

- [ ] Too many if/else in the thread routine will slow down your code -- better to let the check_death() function handle all the necessary checks in parallel
- [ ] Dividing is more time-consuming for a computer than multiplying, eg. `time2eat * 0.5` will take less time to calculate than `time2eat / 2`
- [ ] Use short variable names
- [ ] `printf` is quite slow as a function
- [ ] while loops such as `while (time < time2sleep) usleep(50);` will slow down the routine -- again, trust the check_death function to perform all necessary death checks (_nomen omen_)

## Bonus part - Semaphore vs Mutex  

| MUTEX         | SEMAPHORE       |
|--------------| ----------- |
| blocking mechanism | signaling mechanism |
| pthread_mutex_init() | sem_open() |
| pthread_mutex_lock() | sem_wait() |
| pthread_mutex_unlock() | sem_post() |
| pthread_mutex_destroy() | sem_unlink() sem_close() |

## Debugging

- [ ] If you run valgrind and get the following error, initialise your struct to 0 with memset (explanation here on [Stackoverflow](https://stackoverflow.com/questions/29870357/writing-struct-writebuf-points-to-uninitialised-bytes))

```
==7196== Syscall param write(buf) points to uninitialised byte(s)  
==7196==    at 0x4E4F371: write (write.c:27)  
==7196==    by 0x4E4E358: sem_open (sem_open.c:269)
```

- [ ] If you get an infinite loop somewhere before the end of your code, check the way you have locked and unlocked your mutex  

- [ ] If your code runs smoothly till the end (i.e. the death of a philosophers), but it gets stuck without exiting, it means there is a mutex still locked somewhere.  
Solution 1: try `pthread_detach` instead of `pthread_join`. `pthread_join` blocks until a thread terminates; `pthread_detach` returns immediately without terminating the thread (you might have leaks though, because the thread is detached but keeps running in the background -- if you do an infinite while loop after detaching the thread, you'll see it running in the shell, try it out!).  
Solution 2: another way to go about it and keep using `pthread_join` is to check that all mutex have been correctly unlocked


