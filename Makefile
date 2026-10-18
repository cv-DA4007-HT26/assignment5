CXX = g++
CXXFLAGS = -Wall -std=c++17 -O2

CLEAN = rm -rf

OBJECTFILES = build/slm.o build/text_generator.o build/gram_builder.o

TARGET = build/slm

all: $(TARGET)

build:
	mkdir -p build

build/%.o : src/%.cpp | build
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(TARGET): $(OBJECTFILES)
	$(CXX) -o $@ $^

clean:
	$(CLEAN) build
