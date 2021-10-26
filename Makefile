parser: expr2.c main.c scan.c tree.c interp.c
	cc -o parser -g expr2.c main.c scan.c tree.c interp.c


clean:
	rm -f parser *.o

test: parser
	-(./parser input01; \
	 ./parser input02; \
	 ./parser input03; \
	 ./parser input04; \
	 ./parser input05)
