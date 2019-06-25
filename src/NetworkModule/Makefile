CXX = g++
CFLAGS = -Wall -O2 -std=c++11
HXBASE = $(shell cd ../..; pwd)
HXSRC = $(HXBASE)/src
HXLIB = $(HXBASE)/lib

INCLUDE = -I $(HXSRC)
#CFLAGS = -Wall -O2 -g
#LIBS = -lhpsocket -lpthread -ljsoncpp -llog4cpp
SRCS = $(shell find ./ -name "*.cpp")
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

TARGET = libhxnet.so

$(TARGET) : $(OBJS)
	$(CXX) -shared -o $(TARGET) $^ $(CFLAGS) $(INCLUDE)
	cp $(TARGET) $(HXLIB)

%.o : %.cpp
	$(CXX) -fPIC -c $< -o $@ $(CFLAGS) $(INCLUDE)

clean:
	@ echo $(HXSRC)
	rm $(TARGET) $(OBJS) -rf
	rm $(HXLIB)/$(TARGET)
