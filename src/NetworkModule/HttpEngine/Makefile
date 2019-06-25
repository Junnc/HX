CC=g++
CFLAGS=-std=c++11 -O2
INCLUDE = -I ../../
LIBS=-lhpsocket -ljsoncpp -lpthread -llog4cxx
CPPS=./HttpServerEngine.cpp \
     ./HttpServer.cpp \
     ../HttpHandle/HttpHandle.cpp \
     ../HttpHandle/EchoHandle/echoHandle.cpp \
     test.cxx

TARGET=httpserv

all:
	$(CC) $(CPPS) $(LIBS) $(CFLAGS) $(INCLUDE) -o $(TARGET) -g
	
clean:
	rm $(TARGET) -f
