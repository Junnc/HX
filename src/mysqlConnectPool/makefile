CC := g++ -std=c++11
CFLAGS = -Wall -O2 -std=c++11
INCLUDE := -I ./include
#LDFLAGS := -L /usr/lib64/mysql
#LDLIBS := -l mysqlclient
TARGET := libdbpool.so
OBJS := DBConnect.o DBConnPool.o
SRCS := DBConnect.cpp DBConnPool.cpp

all: $(TARGET) 

$(TARGET):$(OBJS)
	$(CC) -shared -o $(TARGET) $(OBJS)
	cp $(TARGET) ../../lib

$(OBJS): $(SRCS)
	$(CC) -fpic -c $^ $(CXXFLAGS) $(INCLUDE)

clean: 
	rm -f $(TARGET) $(OBJS)
	rm -f ../../lib/$(TARGET)
