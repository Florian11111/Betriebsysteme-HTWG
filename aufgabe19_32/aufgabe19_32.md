cd betriebsystem/homework/aufgabe19_32/

## 1. First let’s make sure you understand how the programs generally work, and some of the key options. Study the code in vector-deadlock.c, as well as in main-common.c and related files. Now, run ./vector-deadlock -n 2 -l 1 -v, which instantiates two threads (-n 2), each of which does one vector add (-l 1), and does so in verbose mode (-v). Make sure you understand the output. How does the output change from run to run?
    ./vector-deadlock -n 2 -l 1 -v
    Der Output bleibt großteils gleich aber ich habe es einmal geschaft das die reihnefolge andersrum ist.

## 2. Now add the -d flag, and change the number of loops (-l) from 1 to higher numbers. What happens? Does the code (always) deadlock?
    ./vector-deadlock -n 2 -l 1 -v -d
    - Es werden bei bei einem der 2 thread die reihenfolge gewechselt.
    - Nein der Code macht nicht immer ein Deadlook
    - Es kann sein das sich die 2 Thread gegenseitg jeweils eins der locks klauen und es so zum stillstand kommt

## 3. How does changing the number of threads (-n) change the outcome of the program? Are there any values of -n that ensure no deadlock occurs?
    Mehr threads erhöhen die change auf ein deadlock da es mehr durchlaufe sind.
    Auch bei gleicher duchlauf zahl:
        ./vector-deadlock -n 2 -l 5000 -v -d    (10000 adds)
        ./vector-deadlock -n 10 -l 1000 -v -d   (10000 adds)
    gibt es mehr deadlocks mit mehr threads.
    Theorie: durch mehr threads gibt es öfters context wechsel während eines locks.

    bei 2 threads ist ein Lock bei 15000 relativ sicher (nicht 100% aber sehr warscheinlich)
    ./vector-deadlock -n 2 -l 15000 -v -d 

## 4. Now examine the code in vector-global-order.c. First, make sure you understand what the code is trying to do; do you understand why the code avoids deadlock? Also, why is there a special case in this vector add() routine when the source and destination vectors are the same?
    - die locks werden nach adressen geordnet so das sich 2 threads nicht die adressen klauen können.
    - der special case der abfrägt ob es sich um die gleichen Vectoren handelt ist dafür da dass, sich das gleiche Lock nicht 2 mal gelockt wird da dies zu problemen führt (testProgramm/doubleLock.c)

## 5. Now run the code with the following flags: -t -n 2 -l 100000 -d. How long does the code take to complete? How does the total time change when you increase the number of loops, or the number of threads?
    ./vector-global-order -t -n 2 -l 100000     => Time: 0.04 seconds   (ohne -d)
    ./vector-global-order -t -n 2 -l 100000 -d  => Time: 0.03 seconds   (mit -d)
    => Warum???

    -l Zeit wächst Liniar mit erhöhung
        ./vector-global-order -t -n 8 -l 10000 -d   =>  Time: 0.04 seconds
        ./vector-global-order -t -n 8 -l 100000 -d  =>  Time: 0.44 seconds
        ./vector-global-order -t -n 8 -l 1000000 -d =>  Time: 4.44 seconds

    -n erhöht sich die zeit exponetial
        ./vector-global-order -t -n 2 -l 1000000 -d => Time: 0.24 seconds
        ./vector-global-order -t -n 4 -l 1000000 -d => Time: 1.53 seconds
        ./vector-global-order -t -n 8 -l 1000000 -d => Time: 4.62 seconds


## 6. What happens if you turn on the parallelism flag (-p)? How much would you expect performance to change when each thread is working on adding different vectors (which is what -p enables) versus working on the same ones?
    Deutlich bessere zeit da jeder thread eigene werte hat und somit nicht auf locks warten muss
        ./vector-global-order -t -n 60 -l 100000 -p     =>   Time: 0.16 seconds
        ./vector-global-order -t -n 60 -l 100000        =>   Time: 3.19 seconds


## 7. Now let’s study vector-try-wait.c. First make sure you understand the code. Is the first call to pthread mutex trylock() really needed? Now run the code. How fast does it run compared to the global order approach? How does the number of retries, as counted by the code, change as the number of threads increases?
    Man kann es auch ohne das erste trylock Implementieren (aufgabe19_32/vector-try-wait2.c) ist aber nicht so schnell
        ./vector-try-wait -t -n 4 -l 1000000 -d -p      => Time: 0.22 seconds
        ./vector-try-wait2 -t -n 4 -l 1000000 -d -p     => Time: 0.73 seconds

    Die Zeit ist nicht so gut wie bei vector-global-order.c
    -t -n 2 -l 1000000 -d
        ./vector-global-order => Time: 0.25 seconds
        ./vector-try-wait     => Time: 1.09 seconds
    -t -n 4 -l 1000000 -d
        ./vector-global-order => Time: 1.53 seconds
        ./vector-try-wait     => Time: 5.44 seconds

    mit -p macht es aber kaum einen unterschied
    -t -n 2 -l 1000000 -d -p
        ./vector-global-order   => Time: 0.12 seconds
        ./vector-try-wait       => Time: 0.12 seconds
    -t -n 4 -l 1000000 -d -p    
        ./vector-global-order   => Time: 0.23 seconds
        ./vector-try-wait       => Time: 0.23 seconds

## 8. Now let’s look at vector-avoid-hold-and-wait.c. What is the main problem with this approach? How does its performance compare to the other versions, when running both with -p and without it?
    Der problem ist das es ein globales lock gibt. dies ist nicht schlimm wenn alle threads sich 2 vectoren teilen (ohne -o). Wenn
    aber jeder thread seine eigenen Vectoren hat bremmst das lock die geschwindichkeit sehr.

    Ohne -p 
        -t -n 2 -l 1000000 -d
            ./vector-global-order           => Time: 0.24 seconds
            ./vector-avoid-hold-and-wait    => Time: 0.53 seconds

        -t -n 4 -l 1000000 -d
            ./vector-global-order           => Time: 1.53 seconds
            ./vector-avoid-hold-and-wait    => Time: 2.34 seconds
        
        -t -n 8 -l 1000000 -d
            ./vector-global-order           => Time: 4.62 seconds
            ./vector-avoid-hold-and-wait    => Time: 4.60 seconds
            
    mit -p 
        -t -n 2 -l 1000000 -d -p        
            ./vector-global-order           => Time: 0.13 seconds
            ./vector-avoid-hold-and-wait    => Time: 0.28 seconds

        -t -n 4 -l 1000000 -d -p 
            ./vector-global-order           => Time: 0.23 seconds
            ./vector-avoid-hold-and-wait    => Time: 0.76 seconds
        
        -t -n 8 -l 1000000 -d -p
            ./vector-global-order           => Time: 0.38 seconds
            ./vector-avoid-hold-and-wait    => Time: 2.06 seconds


## 9. Finally, let’s look at vector-nolock.c. This version doesn’t use locks at all; does it provide the exact same semantics as the other versions? Why or why not?
    Das ergebnis sollte gleich sein. => also kein deadlock

## 10. Now compare its performance to the other versions, both when threads are working on the same two vectors (no -p) and when each thread is working on separate vectors (-p). How does this no-lock version perform?
    Ohne -p 
        -t -n 2 -l 1000000 -d
            ./vector-global-order           => Time: 0.24 seconds
            ./vector-nolock                 => Time: 2.03 seconds

        -t -n 4 -l 1000000 -d
            ./vector-global-order           => Time: 1.53 seconds
            ./vector-nolock                 => Time: 5.48 seconds

        -t -n 8 -l 1000000 -d
            ./vector-global-order           => Time: 4.62 seconds
            ./vector-nolock                 => Time: 9.42 seconds
    
    mit -p 
        -t -n 2 -l 1000000 -d -p        
            ./vector-global-order           => Time: 0.13 seconds
            ./vector-nolock                 => Time: 0.48 seconds

        -t -n 4 -l 1000000 -d -p 
            ./vector-global-order           => Time: 0.23 seconds
            ./vector-nolock                 => Time: 0.72 seconds

        -t -n 8 -l 1000000 -d -p
            ./vector-global-order           => Time: 0.38 seconds
            ./vector-nolock                 => Time: 1.41 seconds

    Performenc ist nicht gut :(