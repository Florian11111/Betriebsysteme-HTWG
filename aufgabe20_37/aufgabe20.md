## 1. Compute the seek, rotation, and transfer times for the following sets of requests: -a 0, -a 6, -a 30, -a 7,30,8, and finally -a 10,11,12,13.
    - python .\disk.py -a 0             => Seek:  0  Rotate:165  Transfer: 30  Total: 195
    - python .\disk.py -a 6             => Seek:  0  Rotate:345  Transfer: 30  Total: 375
    - python .\disk.py -a 30            => Seek:  80  Rotate:240  Transfer: 30  Total: 375
    - python .\disk.py -a 7,30,8        => Seek:  160  Rotate:545  Transfer: 90  Total: 795
    - python .\disk.py -a 10,11,12,13   => Seek:  40  Rotate:363  Transfer:120  Total: 585

## 2. Do the same requests above, but change the seek rate to different values: -S 2, -S 4, -S 8, -S 10, -S 40, -S 0.1. How do the times change?

    python .\disk.py -a 7,30,8 -S 1         => Total: 795
    python .\disk.py -a 7,30,8 -S 2         => Total: 795
        => ab -S 4 ist er so schnell das er die 8 nicht verpasst
    python .\disk.py -a 7,30,8 -S 4         => Total: 435   
    python .\disk.py -a 7,30,8 -S 8         => Total: 435 
    python .\disk.py -a 7,30,8 -S 10        => Total: 435 
        => mit einem geringen wert wie -S 0.1 verpasst er einige runden
    python .\disk.py -a 7,30,8 -S 0.1       => Total:2235

## 3. Do the same requests above, but change the rotation rate: -R 0.1, -R 0.5, -R 0.01. How do the times change?
    python .\disk.py -a 7,30,8 -R 0.1   => Total:4349 (Zehl fache von dem normalen)
    python .\disk.py -a 7,30,8 -R 0.5   => Total:1590  (Langsam aber nicht langsam genug um die 8 zu erwischen)
     python .\disk.py -a 7,30,8 -R 0.01 => Total:43500

## 4. FIFO is not always best, e.g., with the request stream -a 7,30,8, what order should the requests be processed in? Run the shortest seek-time first (SSTF) scheduler (-p SSTF) on this workload; how long should it take (seek, rotation, transfer) for each request to be served?
    - python .\disk.py -a 7,30,8 -p FIFO    => Seek:160  Rotate:545  Transfer: 90  Total: 795

    - python .\disk.py -a 7,30,8 -p SSTF    => Seek: 80  Rotate:205  Transfer: 90  Total: 375
        (Sehr gut hier weil die 8 direkt hinter der 7 und nur einmal zur mitte)
    
## 5. Now use the shortest access-time first (SATF) scheduler (-p SATF). Does it make any difference for -a 7,30,8 workload? Find a set of requests where SATF outperforms SSTF; more generally, when is SATF better than SSTF?
    - python .\disk.py -a 7,30,8 -p SSTF    => Seek: 80  Rotate:205  Transfer: 90  Total: 375
    - python .\disk.py -a 7,30,8 -p SATF    => Seek: 80  Rotate:205  Transfer: 90  Total: 375
        Performt gleich wie SSTF Hier

    - python .\disk.py -a 0,21 -p SSTF      => Seek: 40  Rotate:365  Transfer: 60  Total: 465
    - python .\disk.py -a 0,21 -p SATF      => Seek: 80  Rotate: 55  Transfer: 60  Total: 195

## 6. Here is a request stream to try: -a 10,11,12,13. What goes poorly whenm it runs? Try adding track skew to address this problem (-o skew). Given the default seek rate, what should the skew be to maximize performance? What about for different seek rates (e.g., -S 2, -S 4)? In general, could you write a formula to figure out the skew?

    - python .\disk.py -a 10,11,12,13       => Seek: 40  Rotate:425  Transfer:120  Total: 585
        verpasst 12 so das es eine extra runde gehen muss.

    - python .\disk.py -a 10,11,12,13 -o 2  => Seek: 40  Rotate:125  Transfer:120  Total: 285

    Normal würde -o 1 nicht ausreichen aber mit einer höheren seek rate schon.
    - python .\disk.py -a 10,11,12,13 -o 1          => Seek: 40  Rotate:455  Transfer:120  Total: 615
    - python .\disk.py -a 10,11,12,13 -o 1 -S 2     => Seek: 20  Rotate:115  Transfer:120  Total: 255
    - python .\disk.py -a 10,11,12,13 -o 1 -S 4     => Seek: 20  Rotate:115  Transfer:120  Total: 255

## 7. Specify a disk with different density per zone, e.g., -z 10,20,30, which specifies the angular difference between blocks on the outer, middle, and inner tracks. Run some random requests (e.g., -a -1 -A 5,-1,0, which,specifies that random requests should be used via the -a -1 flag and that five requests ranging from 0 to the max be generated), and compute the seek, rotation, and transfer times. Use different random seeds. What is the bandwidth (in sectors per unit time) on the outer, middle, and inner tracks?
    - python .\disk.py -a -1 -A 5,-1,0 -z 10,20,30
    Außen = 10 Grad
    Mitte = 20 Grad
    Innen = 10 Grad
    Varieren zwischen 500 und 1500 meistens 

## 8. A scheduling window determines how many requests the disk can examine at once. Generate random workloads (e.g., -A 1000,-1,0, with different seeds) and see how long the SATF scheduler takes when the scheduling window is changed from 1 up to the number of requests. How big of a window is needed to maximize performance? Hint: use the -c flag and don’t turn on graphics (-G) to run these quickly. When the scheduling window is set to 1, does it matter which policy you are using?
    - mit -w 1 spielt es keine rolle da sowieso einfach das nächste genommen wird. Um so höher um so besser die performence
        python .\disk.py -A 1000,-1,0 -p FIFO -w 1  => Total:220125
        python .\disk.py -A 1000,-1,0 -p SATF -w 1  => Total:220125

    - in diesem fall steigt die performence bis 14% der gesamt balance stark an danach flacht es ab. (in dem beispiel gibt es nicht so viele felder)
        python .\disk.py -A 1000,-1,0 -p SATF -w 1      => Total:220125
        python .\disk.py -A 1000,-1,0 -p SATF -w 2      => Total:149565
        python .\disk.py -A 1000,-1,0 -p SATF -w 4      => Total:100965
        python .\disk.py -A 1000,-1,0 -p SATF -w 8      => Total:69315
        python .\disk.py -A 1000,-1,0 -p SATF -w 130    => Total:36195
        python .\disk.py -A 1000,-1,0 -p SATF -w 140    => Total:35835


## 9. Create a series of requests to starve a particular request, assuming an SATF policy. Given that sequence, how does it perform if you use a bounded SATF (BSATF) scheduling approach? In this approach, you specify the scheduling window (e.g., -w 4); the scheduler only moves onto the next window of requests when all requests in the current window have been serviced. Does this solve starvation? How does it perform, as compared to SATF? In general, how should a disk make this trade-off between performance and starvation avoidance?
    - python .\disk.py -A 1000,-1,0 -p SATF -a 24,25,26,27,28,29,30,31,32,33,34,35,8,10,0,2,4,6,8,10,0,2,4,6,8,10,0,2,4,6,8,10,0,2,4,6,8,10,0,2,4,6,8,10,0,2,4,6,8,10,0,2,4,6
    - Mit -w4 kommt es nicht zu einem Starving da es zwar sortiert was am besten ist aber irgentwann zu allen kommt.
    - Eine Disk sollte eine gute mischung haben um eine gute performence und kein Starving zu haben

## 10. All the scheduling policies we have looked at thus far are greedy; they pick the next best option instead of looking for an optimal schedule. Can you find a set of requests in which greedy is not optimal?
    python .\disk.py -A 1000,-1,0 -p SATF -a 24,25,26,27,28,29,30,31,32,33,34,35,8,10,0,2,4,6,8,10,0,2,4,6,8,10,0,2,4,6,8,10,0,2,4,6,8,10,0,2,4,6,8,10,0,2,4,6,8,10,0,2,4,6
    