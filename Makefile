Target = slm

all: $(Target)

%.o : %.cpp
	g++ -c -O2 $^

$(Target): slm.o text_generator.o gram_builder.o
	g++ -o $@ $^

clean:
	rm -f *.o slm
