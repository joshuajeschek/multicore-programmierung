GCC          = gcc -fopenmp -Wall -Wextra
EXTRA_FILES  = util.c

NVCC         = /opt/cuda/bin/nvcc

LATEX        = lualatex -shell-escape
BIB          = bibtex

SHELL        = /bin/bash # fix for not running clean
TMPFILES     = *.{log,aux,toc,out,lof,lot,snm,nav,vrb,bak,bbl,blg,ent}

%: %.c
	$(GCC) $< $(EXTRA_FILES) -o $*.out
%: %.cu
	$(NVCC) $< $(EXTRA_FILES) -o $*.out

%-run:
	make $*
	./$*.out

%: %.tex
	$(LATEX) $<
	$(LATEX) $<

%: %.py
	python $<

clean:
	rm -f $(TMPFILES)
	rm -r _minted*
