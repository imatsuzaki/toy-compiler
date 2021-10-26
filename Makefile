parser: expr.c main.c scan.c tree.c interp.c
	cc -o parser -g expr.c main.c scan.c tree.c interp.c


clean:
	rm -f parser *.o