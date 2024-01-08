A = ""

for x in range(1, 1000, 2):
    A += "+1,+1,-" + str(x) + ","

print(f'python2 malloc.py -H 0 -p WORST -s 0 -A {A[:-1]} -c')

