## 1. Before doing any translations, let’s use the simulator to study how linear page tables change size given different parameters. Compute the size of linear page tables as different parameters change. Some suggested inputs are below; by using the -v flag, you can see how many page-table entries are filled. First, to understand how linear page table size changes as the address space grows, run with these flags:
    -P 1k -a 1m -p 512m -v -n 0
    -P 1k -a 2m -p 512m -v -n 0
    -P 1k -a 4m -p 512m -v -n 0
## Then, to understand how linear page table size changes as page size grows:
    -P 1k -a 1m -p 512m -v -n 0
    -P 2k -a 1m -p 512m -v -n 0
    -P 4k -a 1m -p 512m -v -n 0
## Before running any of these, try to think about the expected trends. How should page-table size change as the address space grows? As the page size grows? Why not use big pages in general?


## 2. Now let’s do some translations. Start with some small examples, and change the number of pages that are allocated to the address space with the -u flag. For example:

## 3. Which of these parameter combinations are unrealistic? Why?
    -P 8 -a 32 -p 1024 -v -s 1          => Ja sehr klein aber könnte sein
    -P 8k -a 32k -p 1m -v -s 2          => Ziehmlich grosse page aber ja...
    -P 1m -a 256m -p 512m -v -s 3       => Da lauft was großese...

## 4. Use the program to try out some other problems. Can you find the limits of where the program doesn’t work anymore? For example, what happens if the address-space size is bigger than physical memory?
    python2 paging-linear-translate.py -P 8 -a 3200 -p 1024 -v -s 1
        "Error: physical memory size must be GREATER than address space size (for this simulation)" => for this Simulation???
    python2 paging-linear-translate.py -P 32 -a 32 -p 1024 -v -s 1
        => Gibt halt nur eine Page
    python2 paging-linear-translate.py -P 33 -a 32 -p 1024 -v -s 1