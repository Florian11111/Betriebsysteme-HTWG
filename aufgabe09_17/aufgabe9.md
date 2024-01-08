## 1. First run with the flags -n 10 -H 0 -p BEST -s 0 to generate a few random allocations and frees. Can you predict what alloc()/free() will return? Can you guess the state of the free list after each request? What do you notice about the free list over time?
    python2 malloc.py  -n 10 -H 0 -p BEST -s 0 -c 

## 2. How are the results different when using a WORST fit policy to search the free list (-p WORST)? What changes?
    Er nimmt sich immer den kleinesten teil wodurch es in mehr teile aufgeteilt wird

## 3. What about when using FIRST fit (-p FIRST)? What speeds up when you use first fit?
    Die suche nach der "richtigen" stelle wird schneller. 

## 4. For the above questions, how the list is kept ordered can affect the time it takes to find a free location for some of the policies. Use the different free list orderings (-l ADDRSORT, -l SIZESORT+, -l SIZESORT-) to see how the policies and the list orderings interact.
    SIZESORT- => ist schnell da es nicht lange nach einem platz suchen muss. Erzeugt aber viele segmente
    SIZESORT+ => langsamer erschafft aber weniger segmente
    ADDRSORT => eine mischung 

## 5. Coalescing of a free list can be quite important. Increase the number of random allocations (say to -n 1000). What happens to larger allocation requests over time? Run with and without coalescing (i.e., without and with the -C flag). What differences in outcome do you see? How big is the free list over time in each case? Does the ordering of the list matter in this case?
    python2 malloc.py -n 1000 -H 0 -p BEST -s 0 -c 
    python2 malloc.py -n 1000 -H 0 -p BEST -s 0 -C -c 
    => Durch Coalescing wirden die listen immer wieder zusammengefügt

## 6. What happens when you change the percent allocated fraction -P to higher than 50? What happens to allocations as it nears 100? What about as the percent nears 0?
    50% => liste wird immer wieder reserviert und wieder befreit (Gleichgewicht)
        python2 malloc.py  -n 100 -H 0 -p BEST -s 0 -C -p 50 -c
    90% => es ist nur noch sehr wenig platz frei weil kaum speicher frei wird.
        python2 malloc.py  -n 100 -H 0 -p BEST -s 0 -C -p 90 -c
    10% => speicher ist fast immer komplett frei
        python2 malloc.py  -n 100 -H 0 -p BEST -s 0 -C -p 10 -c

## 7. What kind of specific requests can you make to generate a highlyfragmented free space? Use the -A flag to create fragmented free lists, and see how different policies and options change the organization of the free list.
    python2 malloc.py -H 0 -p WORST -s 0 -A +1,+1,-1,+1,+1,-3,+1,+1,-5,+1,+1,-7,+1,+1,-9,+1,+1,-11,+1,+1,-13,+1,+1,-15,+1,+1,-17,+1,+1,-19,+1,+1,-21,+1,+1,-23,+1,+1,-25,+1,+1,-27,+1,+1,-29,+1,+1,-31,+1,+1,-33,+1,+1,-35,+1,+1,-37,+1,+1,-39,+1,+1,-41,+1,+1,-43,+1,+1,-45,+1,+1,-47,+1,+1,-49 -c

    worst fit und -C sind der Key