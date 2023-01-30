CXX = clang++
SDL_LIB = -lSDL2 -Wl
CXXFLAGS = -Wall -c -std=c++17
LDFLAGS = $(SDL_LIB)
EXE = SDL_Intro

all: $(EXE)

$(EXE): main.o

	$(CXX) $< $(LDFLAGS) -o $@

main.o: main.cpp

	$(CXX) $(CXXFLAGS) $< -o $@

clean:

	rm *.o && rm $(EXE)
