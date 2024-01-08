
FLAGS = -Wall -pthread -g

all: main-race main-race-ohneGefahr main-race-lock main-deadlock main-deadlock-global main-signal main-signal-test main-signal-cv

clean:
	rm -f main-race main-race-ohneGefahr main-race-lock main-deadlock main-deadlock-global main-signal main-signal-test main-signal-cv

main-race: main-race.c common_threads.h
	gcc -o main-race main-race.c $(FLAGS)

main-race-lock: main-race-lock.c common_threads.h
	gcc -o main-race-lock main-race-lock.c $(FLAGS)

main-race-ohneGefahr: main-race-ohneGefahr.c common_threads.h
	gcc -o main-race-ohneGefahr main-race-ohneGefahr.c $(FLAGS)

main-deadlock: main-deadlock.c common_threads.h
	gcc -o main-deadlock main-deadlock.c $(FLAGS)

main-deadlock-global: main-deadlock-global.c common_threads.h
	gcc -o main-deadlock-global main-deadlock-global.c $(FLAGS)

main-signal-test: main-signal-test.c common_threads.h
	gcc -o main-signal-test main-signal-test.c $(FLAGS)

main-signal: main-signal.c common_threads.h
	gcc -o main-signal main-signal.c $(FLAGS)

main-signal-cv: main-signal-cv.c common_threads.h
	gcc -o main-signal-cv main-signal-cv.c $(FLAGS)

