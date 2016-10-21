CXX = g++

CXXFLAGS = -std=c++11

LINKFLAGS = -lcurl

TARGET  = X
SOURCES = User.cpp FileManager.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: CXXFLAGS += -O3
all: $(TARGET)

debug: CXXFLAGS += -g3
debug: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LINKFLAGS) -o $@

%.o: %.cpp
	$(CXX) -Wall $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(TARGET) *.o

.PHONY:	all debug clean
