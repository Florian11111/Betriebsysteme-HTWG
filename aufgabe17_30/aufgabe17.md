## 1. Our first question focuses on main-two-cvs-while.c (the working solution). First, study the code. Do you think you have an understanding of what should happen when you run the program?
    Der Producer legt daten in den Buffer. Dann kann der Consumer diese nehmen

## 2. Run with one producer and one consumer, and have the producer produce a few values. Start with a buffer (size 1), and then increase it. How does the behavior of the code change with larger buffers? (or does it?) What would you predict num full to be with different buffer sizes (e.g., -m 10) and different numbers of produced items (e.g., -l 100), when you change the consumer sleep string from default (no sleep) to -C 0,0,0,0,0,0,1?
    Bei vergrößern von Buffer ändert sich das verhalten kaum

    Wenn man das sleep verhalten änder sammel sich mehrer items an

## 3. If possible, run the code on different systems (e.g., a Mac and Linux). Do you see different behavior across these systems?
    ungefair gleich aber habe es inerhalb docker getestet also auch mehr oder weniger Windows.

## 4. Let’s look at some timings. How long do you think the following execution, with one producer, three consumers, a single-entry shared buffer, and each consumer pausing at point c3 for a second, will take? `./main-two-cvs-while -p 1 -c 3 -m 1 -C 0,0,0,1,0,0,0:0,0,0,1,0,0,0:0,0,0,1,0,0,0 -l 10 -v -t`
    Lange da der erste Consumer das item rausnimmt und die anderen 2 dann immer noch nachschauen und nichts finden. Erst dann kommt der Producer

## 5. Now change the size of the shared buffer to 3 (-m 3). Will this make any difference in the total time?
    Ist von der zeit her recht gleich.

## 6. Now change the location of the sleep to c6 (this models a consumer taking something off the queue and then doing something with it), again using a single-entry buffer. 
    nur noch 5 sekunden

## 7. Finally, change the buffer size to 3 again (-m 3). What time do you predict now?
    hätte eine bischen bessere zeit predictet aber sind auch 5 sekunden

## 8. Now let’s look at main-one-cv-while.c. Can you configure a sleep string, assuming a single producer, one consumer, and a buffer of size 1, to cause a problem with this code?
    Nein.

## 9. Now change the number of consumers to two. Can you construct sleep strings for the producer and the consumers so as to cause a problem in the code?
    `./main-one-cv-while -m 1 -c 2 -p 1 -l 3 -v -C 0,0,0,1,0,0,0:0,0,0,0,0,0,0` bleibt stecken weil alle Threads schlafen gehen

## 10. Now examine main-two-cvs-if.c. Can you cause a problem to happen in this code? Again consider the case where there is only one consumer, and then the case where there is more than one.
    Bei einem Consumer gibt es keine probleme nur wenn es mehrere sind:
    ./main-two-cvs-if -m 1 -c 2 -p 1 -l 3 -v -C 0,0,0,1,0,0,0:0,0,0,0,0,0,0
    Hier wird sich ein lehrer buffer genommen.

## 11. Finally, examine main-two-cvs-while-extra-unlock.c. What problem arises when you release the lock before doing a put or a get?  Can you reliably cause such a problem to happen, given the sleep strings? What bad thing can happen?
    - Wenn man das lock zu früh aufmacht kann ein anderer thread den inhalt bearbeiten und es kommt zu einem fehler.
    - Man kann in dem code keine einfachen fehler auslösen Wenn man bei c4 anhält.
    - 2 producer schreiben gleichzeitig in daten oder ein Consumer list leere daten