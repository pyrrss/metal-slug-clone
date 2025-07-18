# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Código fuente
SRC_FILES = $(shell find src -name '*.cpp')
TARGET = bin/exec

# Targets
all: $(TARGET)

$(TARGET): $(SRC_FILES)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC_FILES) $(LIBS)

clean:
	@rm -f $(TARGET)

.PHONY: all clean


