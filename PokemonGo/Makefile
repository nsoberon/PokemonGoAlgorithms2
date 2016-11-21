
CXXFLAGS = -g -Wall

SOURCES = tests.cpp Driver.cpp coordenada.cpp juego.cpp mapa.cpp ColaPrior.hpp DiccString.hpp
OBJS = $(SOURCES:.cpp=.o)

LIBS =

TARGET = tests

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

valgrind: all
valgrind --leak-check=full ./$(TARGET)
