## 1. Let’s examine a simple program, “loop.s”. First, just read and understand it. Then, run it with these arguments (./x86.py -t 1 -p loop.s -i 100 -R dx) This specifies a single thread, an interrupt every 100 instructions, and tracing of register %dx. What will %dx be during the run? Use the -c flag to check your answers; the answers, on the left, show the value of the register (or memory value) after the instruction on the right has run
    python2 ./x86.py -t 1 -p loop.s -i 100 -R dx -a dx=100
    -Es lauft nur einmal aber wenn man dx=100 macht lauft es öffters 


## 2. Same code, different flags: (./x86.py -p loop.s -t 2 -i 100 -a dx=3,dx=3 -R dx) This specifies two threads, and initializes each %dx to 3. What values will %dx see? Run with -c to check. Does the presence of multiple threads affect your calculations? Is there a race in this code?
    python2 ./x86.py -p loop.s -t 2 -i 100 -a dx=3,dx=3 -R dx
    kein fehler oder ähnliches aber beide Threads zählen unabhängik runter (gewollt?)

## 3. Run this: ./x86.py -p loop.s -t 2 -i 3 -r -R dx -a dx=3,dx=3 This makes the interrupt interval small/random; use different seeds (-s) to see different interleavings. Does the interrupt frequency change anything?
    python2 ./x86.py -p loop.s -t 2 -i 3 -r -R dx -a dx=3,dx=3
    Ne halt ganz viele Interups


## 4. Now, a different program, looping-race-nolock.s, which accesses a shared variable located at address 2000; we’ll call this variable value. Run it with a single thread to confirm your understanding: ./x86.py -p looping-race-nolock.s -t 1 -M 2000 What is value (i.e., at memory address 2000) throughout the run? Use -c to check.
    python2 ./x86.py -p looping-race-nolock.s -t 1 -M 2000
    ok.

## 5. Run with multiple iterations/threads: ./x86.py -p looping-race-nolock.s -t 2 -a bx=3 -M 2000 Why does each thread loop three times? What is final value of value?
    weil jeder wert mit dx = 3 startet. Endet bei 6 

## 6. Run with random interrupt intervals: ./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 0 with different seeds (-s 1, -s 2, etc.) Can you tell by looking at the thread interleaving what the final value of value will be? Does the timing of the interrupt matter? Where can it safely occur? Where not? In other words, where is the critical section exactly?
    Da wir bei -s 0 und -s 2 den wert wieder speichern bevor wir ihn im anderen Thread laden ist das ergebnis dort 2
    Da wir bei -s 1 den wert bei Thread 1 laden bevor Thread 2 den wert Geändert und wieder draufgeschrieben hat bleibt dieser bei 1

## 7. Now examine fixed interrupt intervals: ./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 1 What will the final value of the shared variable value be? What about when you change -i 2, -i 3, etc.? For which interrupt intervals does the program give the “correct” answer?
    python2 ./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 1 -c
    Gleich wie bei -s 1 (Aufgabe 6) Wird hier vor dem laden gespeichert.
    Das gilt für -i 1 und -i 2 allerdings wird bei -i 3 passt es da es genau ausreicht um den veränderten wert wieder zu speichern

## 8. Run the same for more loops (e.g., set -a bx=100). What interrupt intervals (-i) lead to a correct outcome? Which intervals are surprising?
    python2 ./x86.py -p looping-race-nolock.s -a bx=100 -t 2 -M 2000 -i 3 -c
    => Alle vielfachen von 3 ergeben das richtige ergebnis

## 9. One last program: wait-for-me.s. Run: ./x86.py -p wait-for-me.s -a ax=1,ax=0 -R ax -M 2000 This sets the %ax register to 1 for thread 0, and 0 for thread 1, and watches %ax and memory location 2000. How should the code behave? How is the value at location 2000 being used by the threads? What will its final value be?
    python2 ./x86.py -p wait-for-me.s -a ax=1,ax=0 -R ax -M 2000
    finale wert ist 1??

## 10. Now switch the inputs: ./x86.py -p wait-for-me.s -a ax=0,ax=1 -R ax -M 2000 How do the threads behave? What is thread 0 doing? How would changing the interrupt interval (e.g., -i 1000, or perhaps to use random intervals) change the trace outcome? Is the program efficiently using the CPU?
    Thread 0 lauft solange bis Thread 1 2000 auf 1 setzt.
    python2 ./x86.py -p wait-for-me.s -a ax=0,ax=1 -R ax -M 2000 -c