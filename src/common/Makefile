CXX = g++
CFLAGS = -Wall -O2 -std=c++11
SRCS = $(shell find ./ -name "*.cpp")
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

TARGET = libhxcommon.so

$(TARGET) : $(OBJS)
	$(CXX) -shared -o $(TARGET) $^ $(CFLAGS) 
	cp $(TARGET) ../../lib

%.o : %.cpp
	$(CXX) -fPIC -c $< -o $@ $(CFLAGS) 

clean:
	rm $(TARGET) $(OBJS) -rf 
	rm ../../lib/$(TARGET) -rf 
