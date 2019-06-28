CXX = g++
CFLAGS = -Wall -O2 -std=c++11
HXBASE = $(shell cd ../..; pwd)
HXSRC = $(HXBASE)/src
HXLIB = $(HXBASE)/lib

INCLUDE = -I ../common -I ../NetworkModule -I ../
SRCS = $(shell find ./ -name "*.cpp")
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

TARGET = libhxfuture.so

$(TARGET) : $(OBJS)
	$(CXX) -shared -o $(TARGET) $^ $(CFLAGS) $(INCLUDE)
	cp $(TARGET) $(HXLIB)

%.o : %.cpp
	$(CXX) -fPIC -c $< -o $@ $(CFLAGS) $(INCLUDE)

clean:
	@ echo $(HXSRC)
	rm $(TARGET) $(OBJS) -rf
	rm $(HXLIB)/$(TARGET)
