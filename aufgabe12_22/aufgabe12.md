## LRU (Least Recently Used):
    - Evicts the page that has not been used for the longest time.
    - Uses historical information to make decisions.
    - Tends to retain pages that have been accessed recently.

## LFU (Least Frequently Used):
    - Evicts the page that has been accessed the least number of times.
    - Considers the frequency of page accesses.
    - Aims to retain pages that have been accessed frequently.

## OPT (Optimal):
    - Theoretical policy that makes eviction decisions based on future accesses.
    - Assumes perfect knowledge of future access patterns.
    - Used as a benchmark to compare the performance of other policies.

## UNOPT (Unoptimized):
    - Generic term used to refer to policies like FIFO or Random that lack sophistication.
    - Prone to evicting important pages that might be accessed soon.

## RAND (Random):
    - Evicts a randomly chosen page.
    - Simple and lacks consideration for past or future access patterns.

## CLOCK:
    - Variant of the clock algorithm, which uses a circular list of pages.
    - Scans pages randomly and considers the reference bit (use bit) to approximate LRU.
    - Offers a compromise between accuracy and computational overhead.



## 1.Generate random addresses with the following arguments: -s 0 -n 10, -s 1 -n 10, and -s 2 -n 10. Change the policy from FIFO, to LRU, to OPT. Compute whether each access in said address   traces are hits or misses
    python2 paging-policy.py -s 0 -n 10 -p FIFO => 1 / 10
    python2 paging-policy.py -s 1 -n 10 -p FIFO => 2 / 10
    python2 paging-policy.py -s 2 -n 10 -p FIFO => 4 / 10

    python2 paging-policy.py -s 0 -n 10 -p LRU => 2 / 10
    python2 paging-policy.py -s 1 -n 10 -p LRU => 2 / 10
    python2 paging-policy.py -s 2 -n 10 -p LRU => 4 / 10

    python2 paging-policy.py -s 0 -n 10 -p OPT => 4 / 10
    python2 paging-policy.py -s 1 -n 10 -p OPT => 3 / 10
    python2 paging-policy.py -s 2 -n 10 -p OPT => 4 / 10

## 2. For a cache of size 5, generate worst-case address reference streams for each of the following policies: FIFO, LRU, and MRU worst-case reference streams cause the most misses possible. For the worst case reference streams, how much bigger of a cache is needed to improve performance dramatically and approach OPT?
    FIFO => python2 paging-policy.py -s 0 -n 10 -C 5 -p FIFO -a 1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5 -c
    LRU => python2 paging-policy.py -s 0 -n 10 -C 5 -p LRU -a 1,2,3,4,5,6,1,2,3,4,5,6,1,2,3,4,5 -c
    RU => python2 paging-policy.py -s 0 -n 10 -C 5 -p MRU -a 1,2,3,4,5,6,5,6,5,6,5,6,5,6,5,6 -c

    In meinen beispielen reicht 1 bit

## 3.  Generate a random trace (use python or perl). How would you expect the different policies to perform on such a trace?
    Alle sollten ungefair gleich schlecht performen.

## 4. Now generate a trace with some locality. How can you generate such a trace? How does LRU perform on it? How much better than RAND is LRU? How does CLOCK do? How about CLOCK with different numbers of clock bits?
    python2 paging-policy.py -s 0 -n 10 -C 5 -p LRU -a 1,2,3,4,5,1,6,7,8,9,1,10,11,12,13,14,15,1 -c
    LRU => recht gut da öfftern genutzte adressen nicht direkt rausfliegen.
    RAND vs LRU => kommt sehr aus die größen an aber deutlich besser.
