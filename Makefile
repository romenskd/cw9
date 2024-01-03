CC = gcc 
my_program: main.o mat_io.o gauss.o backsubst.o
	$(CC) -o my_program main.o mat_io.o gauss.o backsubst.o $(LDFLAGS)

main.o: main.c mat_io.h gauss.h backsubst.h
	$(CC) -c $(CFLAGS) main.c

mat_io.o: mat_io.c mat_io.h
	$(CC) -c $(CFLAGS) mat_io.c

gauss.o: gauss.c gauss.h
	$(CC) -c $(CFLAGS) gauss.c

backsubst.o: backsubst.c backsubst.h
	$(CC) -c $(CFLAGS) backsubst.c

clean:
	rm -f my_program *.o