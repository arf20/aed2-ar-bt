TARGET := bt

CXX_FLAGS := -g -O0 -Wall -pedantic
C_FLAGS := -g -O0 -Wall -pedantic

all: $(TARGET) 

$(TARGET): main.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $? $(LD_FLAGS)

.PHONY: clean doc test

clean:
	rm $(TARGET) 

test: $(TARGET)
	./bt < test.stdin > run.stdout
	cmp -s test.stdout run.stdout && echo "PASS" || echo "FAIL"

doc:
	iconv -f utf8 -t latin1 memoria.txt | enscript -l -M A4 -f Courier@11 -p - | ps2pdf - - > memoria.pdf

