## 1. We’ll start by redoing the measurements within this chapter. Use the call gettimeofday() to measure time within your program. How accurate is this timer? What is the smallest interval it can measure? Gain confidence in its workings, as we will need it in all subsequent questions. You can also look into other timers, such as the cycle counter available on x86 via the rdtsc instruction.
    - measurements_timeOfDay.c => 
    Es ist recht genau 120 microsecunden zu viel.

## 2. Now, build a simple concurrent counter and measure how long it takes to increment the counter many times as the number of threads increases. How many CPUs are available on the system you are using? Does this number impact your measurements at all?
    - gesamt: 10000000 hat mit 1 threads: 181_887 microsecunden gebraucht
    - gesamt: 10000000 hat mit 2 threads: 618_693 microsecunden gebraucht
    - gesamt: 10000000 hat mit 4 threads: 677_940 microsecunden gebraucht 
    - gesamt: 10000000 hat mit 8 threads: 1_061_344 microsecunden gebraucht
    - gesamt: 10000000 hat mit 100 threads: 1_026_330 microsecunden gebraucht
    Durch die mehr Threads ist Das system öfter mit thread wechseln beschäftigt

## 3. Next, build a version of the approximate counter. Once again, measure its performance as the number of threads varies, as well as the threshold. Do the numbers match what you see in the chapter?
    - gesamt: 4000000 | threshold 1 | 4 threads | 511107 microsecunden
    - gesamt: 4000000 | threshold 2 | 4 threads | 390143 microsecunden
    - gesamt: 4000000 | threshold 4 | 4 threads | 317614 microsecunden
    - gesamt: 4000000 | threshold 8 | 4 threads | 277068 microsecunden
    - gesamt: 4000000 | threshold 16 | 4 threads | 266018 microsecunden
    - gesamt: 4000000 | threshold 32 | 4 threads | 235535 microsecunden
    Ja es wird weniger aber nicht so extrem wie im Buch