myprogram: prakt3_2.o myfunctions.o
	cc -o myprogram myfunctions.o prakt3_2.o
myfunctions.o: myfunctions.h myfunctions.c
	cc -c myfunctions.c
prakt3_2.o:  prakt3_2.c
	cc -c prakt3_2.c