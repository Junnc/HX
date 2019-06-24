CXX = g++
CFLAGS = -Wall -O2 -std=c++11
#CFLAGS = -Wall -O2 -g
#LIBS = -lhpsocket -lpthread -ljsoncpp -llog4cpp
SRCS = $(wildcard *.cpp */*.cpp */*/*.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

TARGET = libhxnet.so

$(TARGET) : $(OBJS)
	$(CXX) -shared -o $(TARGET) $^ $(CFLAGS)

%.o : %.cpp
	$(CXX) -fPIC -c $< -o $@ $(CFLAGS)

clean:
	rm $(TARGET) $(OBJS) -rf
