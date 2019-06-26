CC := g++ -std=c++11
CFLAGS = -Wall -O2 -std=c++11
INCLUDE := -I ./include

HXBASE = $(shell cd ../..; pwd)
HXSRC = $(HXBASE)/src
HXLIB = $(HXBASE)/lib
#LDFLAGS := -L /usr/lib64/mysql
#LDLIBS := -l mysqlclient
TARGET := libdbpool.so
OBJS := DBConnect.o DBConnPool.o
SRCS := DBConnect.cpp DBConnPool.cpp

all: $(TARGET) 

$(TARGET):$(OBJS)
	$(CC) -shared -o $(TARGET) $(OBJS)
	cp $(TARGET) $(HXLIB)

%.o : %.cpp
	$(CC) -fpic -c $< $(CXXFLAGS) $(INCLUDE)

clean: 
	rm -f $(TARGET) $(OBJS)
	rm -f $(HXLIB)/$(TARGET)
