# Philosophers - 42 project  

## Mandatory part - Getting started  

Philosophers is a project about multi-threading programming, synchronisation and performance.  

### Multi-threading
A thread is a routine running in background until terminated or interrupted.  
Threads share resources, and have access to resources once at a time.  
  
Real life example: mobiles can play music and receive notifications; the music player and the notification app both share the resource _sound_: when receiving a message, the music player stops for a sec, the notification rings and then frees the resource _sound_ again.

In philosophers, each person has a _thread routine_ (eat-sleep-think), and forks are the shared resources.  
To avoid forks being used by more philosophers at once, we block the access with `mutex_lock()`, and we `mutex_unlock()` when we are done.

 ```
 # HOW TO INIT MUTEXES

 pthread_mutex_t	*fork;
 
 p->fork = malloc(sizeof(pthread_mutex_t) * p->num); # p->num is the number of philosophers
 if (!p->fork)
  	return (error_msg("Error\nMutex fork: malloc failed\n", p, 0, 1));
 while (++i < p->num)
  	if (pthread_mutex_init(&p->fork[i], NULL) == -1)
	  	return (error_msg("Error\nMutex init failed\n", p, 0, 1));

# Each philospher starts with a fork assigned by default;
# they then need to grab a second fork from their neighbours
# lf: left fork; rf: right fork

while (++i < p->num)
{
   philo[i].lf = p->fork[i]; # fork assigned by default
   philo[i].rf = philo[(i + 1) % p->num].lf; # fork grabbed from the neighbour
}
 ```  

Once the routine is implemented with the right order of actions and mutexes, it needs to be synchronised.  
Check for death will be done in a function parallel to and synched with the threads execution.

### Synchronisation
All threads and the check_death function need to start at the same time to run as parallel as possible.

- [ ] use a flag `philo->start` to delay the execution until all threads are created
- [ ] delay odds philosophers, so that even philos can grab forks to eat, and then can swap again. ( A philosopher can eat only if they have two forks ) 

   ```
   if (p->id & 1)
      ft_usleep(p->par->t2e * 0.9 + 1);
      
   # Possible delayed times are `time2eat * 0.5` or `time2eat * 0.9 + 1`, 
   # respectively waiting until the first batch is halfway through their meal,
   # or until they're 99% done with their meal  
   ```  


- [ ] the function check_death needs to manage time like a swiss clock, checking as fast as possible if all philos are well and alive, so performances must be optimized.

### Performance

- [ ] Too many if/else in the thread routine will slow down your code  
-- better to let the check_death() function handle all the necessary checks in parallel
- [ ] Dividing is more time-consuming for a computer than multiplying  
eg. `time2eat * 0.5` will take less time to calculate than `time2eat / 2`
- [ ] Use short variable names
- [ ] `printf` is quite slow as a function
- [ ] while loops such as `while (time_now() - last_meal < time2sleep) usleep(50);` will slow down the routine  
-- again, trust the check_death function to perform all necessary death checks (_nomen omen_)

## Bonus part - Semaphore vs Mutex  

| MUTEX         | SEMAPHORE       |
|--------------| ----------- |
| blocking mechanism | signaling mechanism |
| pthread_mutex_init() | sem_open() |
| pthread_mutex_lock() | sem_wait() |
| pthread_mutex_unlock() | sem_post() |
| pthread_mutex_destroy() | sem_close() + sem_unlink() |  

Semaphores are created with sem_open(), specifiying the number of semaphores needed as last params.  
In the case of philo:  
`p->fork = sem_open("/fork", O_CREAT, 0660, p->num); // p->num is the number of forks` 

`sem_wait()` decreases the number of semaphores by one, while `sem_post()` increases it by one.  
When no semaphores are available, the function waits until one is unblocked.  

If you do not unlink your semaphore at the end of your program, you'll keep accumulating semaphores every time you run it.  
To check how many semaphores are available, you can use `sem_getvalue(sem_t *sem, int *sval);`  
```
int sval;
   
sem_getvalue(sem, &sval);
printf("sem val %d\n", sval);
      
# This will tell you how many semaphores are actively in use 
```  

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


