Target = build/slm

all: $(Target)

build:
	mkdir -p build

build/%.o : src/%.cpp | build
	g++ -c -O2 $^ -o $@

$(Target): build/slm.o build/text_generator.o build/gram_builder.o
	g++ -o $@ $^

clean:
	rm -rf build
