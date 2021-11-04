Philosophers - 42 project  

Debugging  

==7196== Syscall param write(buf) points to uninitialised byte(s)  
==7196==    at 0x4E4F371: write (write.c:27)  
==7196==    by 0x4E4E358: sem_open (sem_open.c:269)  

https://stackoverflow.com/questions/29870357/writing-struct-writebuf-points-to-uninitialised-bytes
