BUILDDIR = build
SOURCEDIR = src
INSTALLDIR = /usr/bin/

CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17 -I$(SOURCEDIR) -c -g
LDFLAGS = -L.

EXEC_FILE = csgolyrics
OBJ = main.o
OBJECTS = $(patsubst %, $(BUILDDIR)/%, $(OBJ))

all: $(EXEC_FILE)

run: $(EXEC_FILE)
	./$(EXEC_FILE)

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cpp
	mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(EXEC_FILE): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf $(BUILDDIR)
	rm -f $(EXEC_FILE)

remake: clean $(EXEC_FILE)

install: $(EXEC_FILE)
	cp $(EXEC_FILE) $(INSTALLDIR)

w64: CXX = x86_64-w64-mingw32-g++
w64: $(OBJECTS)
	mkdir -p $(BUILDDIR)
	x86_64-w64-mingw32-g++ -static -static-libgcc -static-libstdc++ -o $(EXEC_FILE).exe $^ $(LDFLAGS)
