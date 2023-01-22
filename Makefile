GCC = gcc -fopenmp -Wall -Wextra
EXTRA_FILES = util.c

%: %.c
	$(GCC) $< $(EXTRA_FILES) -o $*.out

%-run:
	make $*
	./$*.out

clean:
	rm *.out
