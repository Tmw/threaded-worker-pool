CC=clang
CFLAGS=-g -Wall -Wextra

DEPS := $(wildcard *.d)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

cmd: main.o jobqueue.o worker.o dequeue.o job.o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:clean
clean:
	rm *.o $(DEPS) cmd
