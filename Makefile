CXX = g++
CXXFLAGS = -std=c++17 -O3 -Iinclude -Isrc

ISPC = ispc
ISPCFLAGS = --target=avx2-i32x8 --pic

SRC_DIR = src
INCLUDE_DIR = include

ISPC_SRC = $(SRC_DIR)/newton.ispc
ISPC_OBJ = $(SRC_DIR)/newton_ispc.o
ISPC_HDR = $(SRC_DIR)/newton_ispc.h

SRCS = main.cpp $(SRC_DIR)/renderer.cpp $(SRC_DIR)/image_writer.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = newton_fractal

all: $(TARGET)

$(TARGET): $(ISPC_OBJ) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(ISPC_OBJ): $(ISPC_SRC)
	$(ISPC) $(ISPCFLAGS) $< -o $@ -h $(ISPC_HDR)

%.o: %.cpp $(ISPC_HDR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS) $(ISPC_OBJ) $(ISPC_HDR)

.PHONY: all clean
