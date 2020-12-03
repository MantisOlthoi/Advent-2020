CC := gcc

all: part1 part2 test1 test2

part1: part1.c
	$(CC) -o $@ $^

part2: part2.c
	$(CC) -o $@ $^

test1: part1
	./$<

test2: part2
	./$<

clean:
	rm -f part1 part2
