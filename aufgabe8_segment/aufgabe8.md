    Seg 0 => base + addresse
    Seg 1 => pysikal_größe + (adresse - segment_size)

## 1. 
### => python2 segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0
    ARG seed 0
    ARG address space size 128
    ARG phys mem size 512

    Segment register information:

    Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
    Segment 0 limit                  : 20

    Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
    Segment 1 limit                  : 20

    Virtual Address Trace
    VA  0: 0x0000006c (decimal:  108) --> VALID in SEG1: 0x000001ec (decimal:  492)    => gültig weil: 108 > 64(128/2) => seg 1 => 108 >= 108(128 -20)
    VA  1: 0x00000061 (decimal:   97) --> SEGMENTATION VIOLATION (SEG1)
    VA  2: 0x00000035 (decimal:   53) --> SEGMENTATION VIOLATION (SEG0)
    VA  3: 0x00000021 (decimal:   33) --> SEGMENTATION VIOLATION (SEG0)
    VA  4: 0x00000041 (decimal:   65) --> SEGMENTATION VIOLATION (SEG1)

    0x0000006c (decimal:  108) --> VALID in SEG1: 0x000001ec (decimal:  492) ADRESSE: 512 + (108 - 128) = 492
   
### => python2 segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1
    ARG seed 1
    ARG address space size 128
    ARG phys mem size 512

    Segment register information:

    Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
    Segment 0 limit                  : 20

    Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
    Segment 1 limit                  : 20

    Virtual Address Trace
    VA  0: 0x00000011 (decimal:   17) --> VALID in SEG0: 0x00000011 (decimal:   17)     => gültig weil: 16 <= 64 => seg0 => 17 < 20
    VA  1: 0x0000006c (decimal:  108) --> VALID in SEG1: 0x000001ec (decimal:  492)     => gültig weil: 108 > 64(128/2) => seg 1 => 108 >= 108(128 -20)
    VA  2: 0x00000061 (decimal:   97) --> SEGMENTATION VIOLATION (SEG1)
    VA  3: 0x00000020 (decimal:   32) --> SEGMENTATION VIOLATION (SEG0)
    VA  4: 0x0000003f (decimal:   63) --> SEGMENTATION VIOLATION (SEG0)

### => python2 segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2
    ARG seed 2
    ARG address space size 128
    ARG phys mem size 512

    Segment register information:

    Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
    Segment 0 limit                  : 20

    Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
    Segment 1 limit                  : 20

    Virtual Address Trace
    VA  0: 0x0000007a (decimal:  122) --> VALID in SEG1: 0x000001fa (decimal:  506)
    VA  1: 0x00000079 (decimal:  121) --> VALID in SEG1: 0x000001f9 (decimal:  505)
    VA  2: 0x00000007 (decimal:    7) --> VALID in SEG0: 0x00000007 (decimal:    7)
    VA  3: 0x0000000a (decimal:   10) --> VALID in SEG0: 0x0000000a (decimal:   10)
    VA  4: 0x0000006a (decimal:  106) --> SEGMENTATION VIOLATION (SEG1)


## 2. Now, let’s see if we understand this tiny address space we’ve constructed (using the parameters from the question above). What is the highest legal virtual address in segment 0? What about the lowest legal virtual address in segment 1? What are the lowest and highest illegal addresses in this entire address space? Finally, how would you run segmentation.py with the -A flag to test if you are right?

    What is the highest legal virtual address in segment 0? => (Segment 0 limit) - 1 => beispiel: python2 segmentation.py -s 1 -A 290 -c

    What about the lowest legal virtual address in segment 1? => address space - (Segment 1 limit) 

    What are the lowest and highest illegal addresses in this entire address space? (phys mem größe) und max kommt auf die anzahl an bits an

## 3. Let’s say we have a tiny 16-byte address space in a 128-byte physical memory. What base and bounds would you set up so as to get the simulator to generate the following translation results for the specified address stream: valid, valid, violation, ..., violation, valid, valid? Assume the following parameters: segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
    --b0 0
    --l0 2
    --b1 16
    --l1 2
    python2 ./segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 0 --l0 2 --b1 16 --l1 2 -c


## 4. Assume we want to generate a problem where roughly 90% of the randomly-generated virtual addresses are valid (not segmentation violations). How should you configure the simulator to do so? Which parameters are important to getting this outcome?
    Du musst schauen das 90% abgedeckt sind


## 5. Can you run the simulator such that no virtual addresses are valid? How?
    -l 0