TARGET := bt

CXX_FLAGS := -g -O0 -Wall -pedantic
C_FLAGS := -g -O0 -Wall -pedantic

all: $(TARGET) $(TARGET)-c

$(TARGET): main.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $? $(LD_FLAGS)

$(TARGET)-c: main.c
	$(CC) $(C_FLAGS) -o $@ $? $(LD_FLAGS)

.PHONY: clean doc test test-c plot plot-c plot-tree

clean:
	rm $(TARGET) 

test: $(TARGET)
	./bt < test.stdin > run.stdout
	cmp -s test.stdout run.stdout && echo "PASS" || echo "FAIL"

test-c: $(TARGET)-c
	./bt-c < test.stdin > run.stdout
	cmp -s test.stdout run.stdout && echo "PASS" || echo "FAIL"

doc:
	iconv -f utf8 -t latin1 memoria.txt | enscript -l -M A4 -f Courier@11 -p - | ps2pdf - - > memoria.pdf

plot-tree:
	#echo "set term dumb size 80 25 ansirgb; set autoscale; set key opaque; set key left top; set xlabel 'n'; set ylabel 'time (s)'; set datafile separator \",\"; set logscale y; plot 'iterations.csv' using 1:2 with points pt '+' title 'con poda', 'iterations.csv' using 1:3 with points pt '*' title 'sin poda';" | gnuplot -p
	echo "set term dumb size 80 25 ansirgb; set autoscale; set key opaque; set key left top; set xlabel 'n'; set ylabel 'time (s)'; set datafile separator \",\"; set logscale y; plot 'iterations.csv' using 1:2 with points pt '+' title 'con poda criterio 1 y 2', 'iterations.csv' using 1:3 with points pt '#' title 'con poda criterio 1', 'iterations.csv' using 1:4 with points pt '*' title 'sin poda';" | gnuplot -p

plot:
	echo "set term dumb size 80 25 ansirgb; set autoscale; set key opaque; set key left top; set xlabel 'n'; set ylabel 'time (s)'; set datafile separator \",\"; set logscale y; plot 'time.csv' using 1:2 with points pt '+' title 'con poda criterio 1 y 2', 'time.csv' using 1:3 with points pt '#' title 'con poda criterio 1', 'time.csv' using 1:4 with points pt '*' title 'sin poda';" | gnuplot -p

plot-c:
	echo "set term dumb size 80 25 ansirgb; set autoscale; set key opaque; set key left top; set xlabel 'n'; set ylabel 'time (s)'; set datafile separator \",\"; set logscale y; plot 'time-c.csv' using 1:2 with points pt '+' title 'con poda', 'time.csv' using 1:3 with points pt '*' title 'sin poda';" | gnuplot -p



