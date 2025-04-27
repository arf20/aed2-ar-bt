BTDIR := bt
BTTARGET := bt
ARDIR := ar
ARTARGET := ar

CXX_FLAGS := -g -O0 -Wall -pedantic
C_FLAGS := -g -O0 -Wall -pedantic

all: $(BTDIR)/$(BTTARGET) $(BTDIR)/$(BTTARGET)-c $(ARDIR)/$(ARTARGET)

$(BTDIR)/$(BTTARGET): $(BTDIR)/main.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $? $(LD_FLAGS)

$(BTDIR)/$(BTTARGET)-c: $(BTDIR)/main.c
	$(CC) $(C_FLAGS) -o $@ $? $(LD_FLAGS)

$(ARDIR)/$(ARTARGET): $(ARDIR)/main.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $? $(LD_FLAGS)

.PHONY: clean doc test test-c plot plot-c plot-tree

clean:
	rm $(BTDIR)/$(BTTARGET) $(BTDIR)/$(BTTARGET)-c $(ARDIR)/$(ARTARGET)

doc:
	iconv -f utf8 -t latin1 memoria.txt | enscript -l -M A4 -f Courier@11 -p - | ps2pdf - - > memoria.pdf

bt-test: $(BTDIR)/$(BTTARGET)
	./bt/bt < bt/test.stdin > bt/run.stdout
	cmp -s bt/test.stdout bt/run.stdout && echo "PASS" || echo "FAIL"

bt-test-c: $(BTDIR)/$(BTTARGET)-c
	./bt/bt-c < bt/test.stdin > bt/run.stdout
	cmp -s bt/test.stdout bt/run.stdout && echo "PASS" || echo "FAIL"

bt-plot-tree:
	echo "set term dumb size 80 25 ansirgb; set autoscale; set key opaque; set key left top; set xlabel 'n'; set ylabel 'time (s)'; set datafile separator \",\"; set logscale y; plot 'bt/iterations.csv' using 1:2 with points pt '+' title 'con poda criterio 1 y 2', 'bt/iterations.csv' using 1:3 with points pt '#' title 'con poda criterio 1', 'bt/iterations.csv' using 1:4 with points pt '*' title 'sin poda';" | gnuplot -p

bt-plot:
	echo "set term dumb size 80 25 ansirgb; set autoscale; set key opaque; set key left top; set xlabel 'n'; set ylabel 'time (s)'; set datafile separator \",\"; set logscale y; plot 'bt/time.csv' using 1:2 with points pt '+' title 'con poda criterio 1 y 2', 'bt/time.csv' using 1:3 with points pt '#' title 'con poda criterio 1', 'bt/time.csv' using 1:4 with points pt '*' title 'sin poda';" | gnuplot -p

bt-plot-c:
	echo "set term dumb size 80 25 ansirgb; set autoscale; set key opaque; set key left top; set xlabel 'n'; set ylabel 'time (s)'; set datafile separator \",\"; set logscale y; plot 'time-c.csv' using 1:2 with points pt '+' title 'con poda', 'bt/time-c.csv' using 1:3 with points pt '*' title 'sin poda';" | gnuplot -p

ar-plot-tree:
	echo "set term dumb size 80 25 ansirgb; set autoscale; set key opaque; set key left top; set xlabel 'casos'; set ylabel 'time (s)'; set datafile separator \",\"; plot [0:11000] [-1:50] 'ar/tiempos.csv' using 1:2 with linespoint pt '+' title 'n pequeña', 'ar/tiempos.csv' using 1:3 with linespoint pt '#' title 'n mediana', 'ar/tiempos.csv' using 1:4 with linespoint pt '*' title 'n grande';" | gnuplot -p



