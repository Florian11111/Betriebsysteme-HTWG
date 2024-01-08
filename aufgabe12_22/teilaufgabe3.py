import random as rd

SEED = 1
ANZAHL_ADRESSEN = 100
MAX_ADRESSE = 200

addresen = [] 

if SEED != -1:
    rd.seed(SEED)
if len(addresen) == 0:
    addresen.extend([rd.randint(1, MAX_ADRESSE) for _ in range(ANZAHL_ADRESSEN)])

print(str(addresen).replace("[", "").replace("]", ""))