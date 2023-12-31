### 1. First, write a simple program called null.c that creates a pointer to an integer, sets it to NULL, and then tries to dereference it. Compile this into an executable called null. What happens when you run this program?

- ./null  =>  Segmentation fault

### 2. Next, compile this program with symbol information included (with the -g flag). Doing so let’s put more information into the executable, enabling the debugger to access more useful information about variable names and the like. Run the program under the debugger by typing gdb null and then, once gdb is running, typing run. What does gdb show you?

- Program received signal SIGSEGV, Segmentation fault.
0x0000555555555161 in main () at null.c:5
5           printf("%d\n", *ptr);

### 3. Finally, use the valgrind tool on this program. We’ll use the memcheck tool that is a part of valgrind to analyze what happens. Run this by typing in the following: valgrind --leak-check=yes null. What happens when you run this? Can you interpret the output from the tool?

- valgrind ./null --leak-check=yes

### 4. Write a simple program that allocates memory using malloc() but forgets to free it before exiting. What happens when this program runs? Can you use gdb to find any problems with it? How about valgrind (again with the --leak-check=yes flag)?

- gdb noFree
- run

Starting program: /home/bsys/betriebsystem/homework/aufgabe6_vm_api/noFree 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
[Inferior 1 (process 9198) exited normally]

- valgrind ./noFree --leak-check=yes


### 5. Write a program that creates an array of integers called data of size 100 using malloc; then, set data[100] to zero. What happens when you run this program? What happens when you run this program using valgrind? Is the program correct?

- ./data => das programm wird normal ausgeführt
- valgrind ./data
- Es schreibt einfach ausßerhalb von dem bereicht was ihmn gehört

### 6. Create a program that allocates an array of integers (as above), frees them, and then tries to print the value of one of the elements of the array. Does the program run? What happens when you use valgrind on it?

- ./wertGeloescht => es kommen random werte raus

### 7. Now pass a funny value to free (e.g., a pointer in the middle of the array you allocated above). What happens? Do you need tools to find this type of problem?

- ./freeOhneGrund => free(): invalid pointer Aborted
- valgrind ./freeOhneGrund

### 8.  Try out some of the other interfaces to memory allocation. For example, create a simple vector-like data structure and related routines that use realloc() to manage the vector. Use an array to store the vectors elements; when a user adds an entry to the vector, use realloc() to allocate more space for it. How well does such a vector perform? How does it compare to a linked list? Use valgrind to help you find bugs.

~/betriebsystem/homework/aufgabe6_vm_api$ time ./vector 300000
insgesamt: 300000000 Intiger werte!
real    0m4,235s
user    0m3,744s
sys     0m0,492s

bsys@86127022ab6b:~/betriebsystem/homework/aufgabe6_vm_api$ time ./vector-Vergrleich 300000
insgesamt: 300000000 Intiger werte!
real    0m1,095s
user    0m1,094s
sys     0m0,001s

bsys@86127022ab6b:~/betriebsystem/homework/aufgabe6_vm_api$ time ./vector-Vergrleich 3000000
insgesamt: 3000000000 Intiger werte!
real    0m10,717s
user    0m10,708s
sys     0m0,010s

bsys@86127022ab6b:~/betriebsystem/homework/aufgabe6_vm_api$ time ./vector 3000000
Killed

real    0m36,772s
user    0m26,919s
sys     0m9,604s

bsys@86127022ab6b:~/betriebsystem/homework/aufgabe6_vm_api$ time ./vector 1000000

insgesamt: 1000000000 Intiger werte!
real    0m13,885s
user    0m11,831s
sys     0m2,053s
