CC := g++ -std=c++11
CXXFLAGS := -I ./include
LDFLAGS := -L /usr/lib64/mysql
LDLIBS := -l mysqlclient
TARGET := libdbpool.so
OBJS := DBConnect.o DBConnPool.o
SRCS := DBConnect.cpp DBConnPool.cpp

INCLUDE_PATH = ../include
LIB_PATH = ../lib

all: $(TARGET) subdir

$(TARGET):$(OBJS)
	$(CC) -shared -o $(TARGET) $(OBJS)
	rm -f $(OBJS)

$(OBJS): $(SRCS)
	$(CC) -fpic -c $^ $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

subdir:
	cp ./include/*.h $(INCLUDE_PATH)
	cp $(TARGET) $(LIB_PATH)

clean: 
	rm -f $(TARGET) $(OBJS)
