# Philosophers - 42 project  

## Mandatory part - Getting started  

Philosophers is a project about multi-threading programming, synchronisation and performance.  

### Multi-threading
A thread is a routine that keeps running in the background until terminated or interrupted.  
Threads share resources, and have access to resources once at a time.  
In real life for ex., when we use our mobile to listen to music, the music player will access the resource "sound", which is shared by other features such as, for ex., notifications, so "sound" is a shared resource and it must be accessed once at a time: when we get a text, the music player will stop for a sec, the notification pop-up will ring and then free the resource "sound" again.

In philosophers, each person has a thread routine (eat-sleep-think), and forks are the shared resources.  
To avoid forks being accessed by more philosophers at once, we block the access with `mutex_lock()`, and we `mutex_unlock()` when we are done.
Once the routine is implemented with the right order of actions and mutexes at the right place, we need to think about synchronisation.  
You will check for death in a function parallel to thread execution.

### Synchronisation
All threads and the check_death function need to run as parallel as possible, and thus start at the same time.

- [ ] use a flag simulation->start to delay the execution until all threads are created
- [ ] delay even or odds philosophers, so that some forks will be free for others to use, and then they can swap again. Possible delayed time time2eat * 0.5 or time2eat * 0.9 + 1, respectively waiting until the first batch is halfway through their meal, or until they're 99% done with their meal  
- [ ] the function check_death needs to manage time like a swiss clock, checking as fast as possible if all philos are well and alive, and this brings us to performances.

### Performance

- [ ] Too many if/else in your thread routine will slow down your code -- the check_death() function should make all the necessary checks in parallel without slowing down the thread execution
- [ ] Dividing is more time-consuming for a computer than multiplying, eg. `time2eat * 0.5` will take less time to calculate than `time2eat / 2`
- [ ] Long variables names take more time to execute (in philo you deal with milliseconds, every millisecond is precious)
- [ ] `printf` is quite slow as a function
- [ ] while loops such as `while (time < time2sleep) usleep(50);` will slow down your routine -- again, trust the check_death function to perform all necessary death checks (_nomen omen_)

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
Solution 1: try `pthread_detach` instead of `pthread_join`. `pthread_join` blocks until a thread terminates; `pthread_detach` returns immediately without terminating the thread (you might have leaks though, because the thread is detached but keeps running in the background -- if you do an infinite while loop after detaching the thread, you'll see it running in the shell, try it out!).  
Solution 2: another way to go about it and keep using `pthread_join` is to check that all mutex have been correctly unlocked


