# all: 
# 	g++ src\main.cpp -Ilibrary\include -Llibrary\lib -w "-Wl,-subsystem,windows" -lmingw32 -lSDL2main -lSDL2 -o main
# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Ilibrary\include

# Linker flags
LDFLAGS = -Llibrary\lib -w 
LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# Target executable
TARGET = main

# Source files
SRCS = scr\main.cpp scr\init.cpp scr\input.cpp scr\stage.cpp scr\util.cpp scr\text.cpp scr\draw.cpp scr\sound.cpp scr\highscores.cpp scr\menu.cpp scr\title.cpp

# Object files
OBJS = $(SRCS) 

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LDLIBS)

# Rule to build object files
# %.exe: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -exe $@

# Rule to clean the build
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
