    Adressspace: 15 
    xxx xxxx xxxx xxxx
          xxx xxxx
          offset

adresse: 611c

110 0001 0001 1100


Virtuell 12 bits (5 offset, 7 for the PFN).
PFN       off
xxxxxxx xxxxx

7f6c => 

binär adresse: 
111 1111 0110 1100
page direktery index: 111 11 (ersten fünf)
nachscheuen 108 und (111 11) => ff

1111 1111 erstes bit ist valid
111 1111 => adresse von wirklichen table
127 in zeile den 2. offset rechnen und diese adresse dann nehmen und erstes bit checken


## 0bad
    000 1011 1010 1101
    entry = 000 10
    108 + 2 => 1110 0000
    valid: 110 0000

## 6d60
    110 1101 0110 0000

    Entry: 110 11 = 1B = 27
    table: 01 011 = B = 11
    offset: 0 0000 = 0 = 0

    108 (27) = c2 => 1100 0010 valid
    100 0010 => 42
    42 (11) => 0001 0001 


    0001 00010 0000

## Anleitung Beipsiel 2592:
    -> adresse in binär ausrechnen und ersten 15 bits raussuchen
    01001 01100 10010
    -> in Entry, table und offset aufteilen
    Entry:  01001 = 9 = 9
    table:  01100 = C = 12
    offset: 10010 = 12 = 18

    -> Als erstes den table suchen.
    table = base (Entry) => 108(9) => 9e binär: 1001 1110
    -> das erste bit ist um zu checken ob es valid ist (wenn nein ungültige adresse) 
    table_number 1001 1110 => 001 1110 => 30
    -> dann suchen wir den genauen eintrag:
    page_phy = table_number (table) =>  30 (12) => bd => 1011 1101
    -> das erste bit ist valid bit: 
    page_phy = 1011 1101 => 011 1101 => 61
    -> jetzt suchen
    page_phy(offset) => 61(18) => 1b

## Anleitung Beipsiel 3e99:
    -> adresse in binär ausrechnen und ersten 15 bits raussuchen
    01111 10100 11001
    
    01111 => 15
    108(15) => d6 => 1101 0110 
    VALDID => 101 0110 => 86
    86 (20) => ca => 1100 1010
    VALID => 100 1010 => 74
    74(25) => 1e => 1e 
          

## ---
01111 01101 01000

=> 1101 0110 Valid
101 0110

86 (13)

7f => 0111 1111



## ---
17f5 => 00101 11111 10101
108(5) => D4 => Valid 1101 0100
101 0100 => 84
84(31) => ce => 1100 1110 VALID
100 1110 => 78
Adresse: 0100 1110 10101 => 9D5
78(21) => 1c 
