CC=g++
CFLAGS=-std=c++11 -O2
LIBS=-lhpsocket -ljsoncpp -lpthread -llog4cxx
CPPS=./HttpServerEngine.cpp \
     ./HttpServer.cpp \
     ../HttpHandle/HttpHandle.cpp \
     ../HttpHandle/EchoHandle/echoHandle.cpp \
     test.cxx

TARGET=httpserv

all:
	$(CC) $(CPPS) $(LIBS) $(CFLAGS) -o $(TARGET) -g
	
clean:
	rm $(TARGET) -f
