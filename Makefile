CC=clang
OBJS =find.o size.o swap.o remove.o between.o init_list.o empty_list.o main.o sort.o list.o
CFLAGS = -Wall -O2 -std=c99 -lm
TARGET=list
$(TARGET):	$(OBJS)
	$(CC)  $(CFLAGS) -o  $@ $(OBJS)
init_list.o:	init_list.c
	$(CC)  $(CFLAGS) -c   -o init_list.o init_list.c 

swap.o:	swap.c
	$(CC)  $(CFLAGS) -c   -o swap.o swap.c

find.o:	find.c
	$(CC)  $(CFLAGS) -c   -o find.o find.c

size.o:	size.c
	$(CC)  $(CFLAGS) -c   -o size.o size.c

remove.o: remove.c
	$(CC)  $(CFLAGS) -c   -o remove.o remove.c

between.o:	between.c
	$(CC)  $(CFLAGS) -c   -o between.o between.c

empty_list.o:	empty_list.c
	$(CC)  $(CFLAGS) -c   -o empty_list.o empty_list.c

list.o:	list.c
	$(CC)  $(CFLAGS) -c   -o list.o list.c

sort.o:	sort.c
	$(CC)  $(CFLAGS) -c   -o sort.o sort.c

main.o:	main.c
	$(CC) $(CFLAGS) -c   -o main.o main.c


clean:
	rm $(OBJS) $(TARGET)
